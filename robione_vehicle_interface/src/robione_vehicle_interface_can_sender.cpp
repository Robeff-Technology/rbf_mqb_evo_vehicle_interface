#include "robione_vehicle_interface/robione_vehicle_interface_can_sender.hpp"

#include "robione_vehicle_interface/autoware_socketcan_bridge.hpp"
#include "robione_vehicle_interface/ultrasonic.h"

#include <robione_vehicle_interface_msgs/msg/ultrasonic_status.hpp>

#include <cmath>
#include <cstdlib>
namespace robione_vehicle_interface
{
RobioneVehicleInterfaceCanSender::RobioneVehicleInterfaceCanSender(
  const rclcpp::NodeOptions & options)
: Node{"robione_vehicle_interface_can_sender", options}, diag_updater_{this}
{
  // params
  base_frame_id_ = declare_parameter("base_frame_id", "base_link");
  steer_rate_ = declare_parameter("steering_angle_rate", 75.0);
  velocity_limit_ = declare_parameter("vehicle_velocity_limit", 10.0);
  msg_timeout_ = declare_parameter("autoware_msg_timeout_threshold", 1.0);
  serial_port_ = declare_parameter("serial_port", "/dev/ttyUSB0");
  baudrate_ = declare_parameter("baudrate", 9600);

  diag_updater_.setHardwareID("robione_vehicle_interface_can_sender");
  diag_updater_.add("CAN Status", this, &RobioneVehicleInterfaceCanSender::diagnostic_callback);

  try {
    serial_port_ptr_ = std::make_shared<SerialPort>(serial_port_.c_str());
    serial_port_ptr_->open();
    serial_port_ptr_->configure(baudrate_, 8, 'N', 1);
  } catch (const SerialPortException & e) {
    RCLCPP_ERROR(get_logger(), e.what());
    rclcpp::shutdown();
  }

  // Ultrasonic filter parameter (time constant tau in seconds)
  ultrasonic_last_emergency_change_time_ = rclcpp::Time(0);

  // Ultrasonic publisher
  ultrasonic_pub_ = create_publisher<robione_vehicle_interface_msgs::msg::UltrasonicStatus>(
    "/ultrasonic/status", rclcpp::QoS(10));

  // Set ultrasonic parser callback to publish the parsed distance
  ultrasonic_parser_.set_callback([this](uint16_t distance) {
    // Apply exponential moving average filter without changing publish rate.
    rclcpp::Time now = this->now();

    // Special case: sensor reports 0 -> means 'no obstacle'.
    // Publish immediately without filtering and reset emergency/filter state to avoid false
    // detections.
    if (distance == 0) {
      robione_vehicle_interface_msgs::msg::UltrasonicStatus msg_zero;
      msg_zero.stamp = now;
      msg_zero.distance = 0;
      msg_zero.is_emergency = false;
      msg_zero.ultrasonic_entry_emergency = false;
      // reset emergency/filter state
      ultrasonic_emergency_state_ = false;
      ultrasonic_emergency_counter_ = 0;
      ultrasonic_emergency_exit_counter_ = 0;
      ultrasonic_last_emergency_change_time_ = now;
      has_ultrasonic_filtered_ = false;
      msg_zero.ultrasonic_release_emergency_time = ultrasonic_last_emergency_change_time_;
      if (ultrasonic_pub_) {
        ultrasonic_pub_->publish(msg_zero);
      }
      return;
    }

    double dt = 0.1;  // default assumed period if first sample or time resolution fails
    if (has_ultrasonic_filtered_) {
      dt = (now - last_ultrasonic_time_).seconds();
      if (dt <= 0.0) dt = 0.1;
    }
    last_ultrasonic_time_ = now;

    double tau = ultrasonic_filter_time_constant_;
    double alpha = dt / (tau + dt);  // standard discrete-time EMA alpha

    double raw = static_cast<double>(distance);
    if (!has_ultrasonic_filtered_) {
      ultrasonic_filtered_distance_ = raw;
      has_ultrasonic_filtered_ = true;
    } else {
      ultrasonic_filtered_distance_ = alpha * raw + (1.0 - alpha) * ultrasonic_filtered_distance_;
    }

    // Emergency detection with hysteresis + debounce
    uint32_t filtered_mm = static_cast<uint32_t>(std::llround(ultrasonic_filtered_distance_));

    // If not currently in emergency, require consecutive low samples to enter
    if (!ultrasonic_emergency_state_) {
      if (filtered_mm < ultrasonic_emergency_enter_threshold_) {
        ultrasonic_emergency_counter_++;
      } else {
        ultrasonic_emergency_counter_ = 0;
      }
      if (ultrasonic_emergency_counter_ >= ultrasonic_emergency_count_required_) {
        ultrasonic_emergency_state_ = true;
        ultrasonic_last_emergency_change_time_ = now;
        ultrasonic_emergency_exit_counter_ = 0;
      }
    } else {
      // If emergency is active, enforce minimum hold time
      double held_ms = (now - ultrasonic_last_emergency_change_time_).seconds() * 1000.0;
      if (held_ms < static_cast<double>(ultrasonic_emergency_min_hold_ms_)) {
        // keep emergency true until min hold time passes
      } else {
        // require consecutive readings above exit threshold to clear
        if (filtered_mm > ultrasonic_emergency_exit_threshold_) {
          ultrasonic_emergency_exit_counter_++;
        } else {
          ultrasonic_emergency_exit_counter_ = 0;
        }
        if (ultrasonic_emergency_exit_counter_ >= ultrasonic_emergency_count_required_) {
          ultrasonic_emergency_state_ = false;
          ultrasonic_last_emergency_change_time_ = now;
          ultrasonic_emergency_counter_ = 0;
        }
      }
    }

    robione_vehicle_interface_msgs::msg::UltrasonicStatus msg;
    msg.stamp = now;
    msg.distance = filtered_mm;
    msg.is_emergency = ultrasonic_emergency_state_;
    // publish the last release time if available (zero time when none)
    msg.ultrasonic_release_emergency_time = ultrasonic_last_emergency_change_time_;
    if (ultrasonic_pub_) {
      ultrasonic_pub_->publish(msg);
    }
  });

  // publishers
  vehicle_motion_cmd_pub_ =
    create_publisher<robione_vehicle_interface_msgs::msg::VehicleMotionCommands>(
      "/robione_vehicle_interface/vehicle_motion_cmd", rclcpp::QoS(1));
  vehicle_cmd_pub_ = create_publisher<robione_vehicle_interface_msgs::msg::VehicleCommands>(
    "/robione_vehicle_interface/vehicle_cmd", rclcpp::QoS(1));

  // subscriptions
  control_cmd_sub_ = create_subscription<autoware_control_msgs::msg::Control>(
    "/control/command/control_cmd", rclcpp::QoS(1),
    std::bind(
      &RobioneVehicleInterfaceCanSender::control_cmd_callback, this, std::placeholders::_1));

  gear_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::GearCommand>(
    "/control/command/gear_cmd", rclcpp::QoS(1),
    std::bind(&RobioneVehicleInterfaceCanSender::gear_cmd_callback, this, std::placeholders::_1));

  turn_indicators_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::TurnIndicatorsCommand>(
    "/control/command/turn_indicators_cmd", rclcpp::QoS(1),
    std::bind(
      &RobioneVehicleInterfaceCanSender::turn_indicators_cmd_callback, this,
      std::placeholders::_1));

  hazard_lights_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::HazardLightsCommand>(
    "/control/command/hazard_lights_cmd", rclcpp::QoS(1),
    std::bind(
      &RobioneVehicleInterfaceCanSender::hazard_lights_cmd_callback, this, std::placeholders::_1));

  vehicle_emergency_cmd_sub_ =
    create_subscription<tier4_vehicle_msgs::msg::VehicleEmergencyStamped>(
      "/control/command/emergency_cmd", rclcpp::QoS(1),
      std::bind(
        &RobioneVehicleInterfaceCanSender::vehicle_emergency_cmd_callback, this,
        std::placeholders::_1));

  sub_route_state_ = this->create_subscription<autoware_adapi_v1_msgs::msg::RouteState>(
    "/api/ad_api_adapter/routing_state",
    rclcpp::QoS(rclcpp::KeepLast(1)).reliable().transient_local(),
    std::bind(
      &RobioneVehicleInterfaceCanSender::route_state_callback, this, std::placeholders::_1));

  tablet_feedback_sub_ = this->create_subscription<robeff_msgs::msg::TabletFeedback>(
    "/api/ad_api_adapter/tablet_feedback", rclcpp::QoS{1},
    std::bind(
      &RobioneVehicleInterfaceCanSender::tablet_feedback_callback, this, std::placeholders::_1));

  sick_zone_sub_ = this->create_subscription<robeff_msgs::msg::SickZone>(
    "/api/sick/zone", rclcpp::QoS(1).transient_local().reliable(),
    std::bind(&RobioneVehicleInterfaceCanSender::sick_zone_callback, this, std::placeholders::_1));

  // publishers
  can_frame_pub_ = create_publisher<can_msgs::msg::Frame>("to_can_bus", rclcpp::QoS(500));

  // timer
  const auto period_ns = rclcpp::Rate(100).period();
  data_publish_can_timer_ = create_timer(
    this, get_clock(), period_ns,
    std::bind(&RobioneVehicleInterfaceCanSender::data_publish_timer_callback, this));
}
void RobioneVehicleInterfaceCanSender::data_publish_timer_callback()
{
  rclcpp::Clock clock{RCL_ROS_TIME};
  bool is_all_received = true;  // Flag to track if all messages are received
  bool triggered_horn = false;

  can_frame_pub_->publish(AutowareSocketcanBridge::convert_vehicle_interface_life_signal());

  // Check if any of the subscribed messages are nullptr and log warnings
  if (control_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000, "control_cmd is not received");
    is_all_received = false;
  }

  if (gear_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000, "gear_cmd is not received");
    is_all_received = false;
  }

  if (turn_indicators_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000, "turn_indicators_cmd is not received");
    is_all_received = false;
  }

  if (hazard_lights_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000, "hazard_lights_cmd is not received");
    is_all_received = false;
  }

  if (vehicle_emergency_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000, "vehicle_emergency_cmd is not received");
    is_all_received = false;
  }

  if (is_arrived_triggered && ((rclcpp::Clock().now() - arrived_timer_).seconds() < 10)) {
    triggered_horn = true;
  }

  // If all the required commands are received, publish the CAN messages
  if (is_all_received && !is_control_cmd_timeout_) {
    // Publish the CAN messages
    can_frame_pub_->publish(AutowareSocketcanBridge::convert_autoware_to_vehicle_motion_cmd(
      *control_cmd_, velocity_limit_, steer_rate_));

    can_frame_pub_->publish(AutowareSocketcanBridge::convert_autoware_vehicle_cmd(
      *gear_cmd_, *turn_indicators_cmd_, *hazard_lights_cmd_, *vehicle_emergency_cmd_,
      ultrasonic_emergency_state_, is_restricted_area_detect, triggered_horn));

    // ROS2 Debug Messages
    vehicle_motion_cmd_pub_->publish(AutowareSocketcanBridge::convert_to_vehicle_motion_cmd());

    vehicle_cmd_pub_->publish(AutowareSocketcanBridge::convert_to_vehicle_cmd());
  }

  // Read incoming serial bytes and feed to ultrasonic parser
  try {
    char buf[128];
    int n = serial_port_ptr_->read(buf, sizeof(buf));
    if (n > 0) {
      ultrasonic_parser_.process_bytes(reinterpret_cast<const uint8_t *>(buf), n);
    }
  } catch (const SerialPortException & e) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 2000, "Serial read error: %s", e.what());
  }
}

void RobioneVehicleInterfaceCanSender::control_cmd_callback(
  const autoware_control_msgs::msg::Control::SharedPtr msg)
{
  control_cmd_timeout_ = msg->stamp;
  control_cmd_ = msg;
}

void RobioneVehicleInterfaceCanSender::gear_cmd_callback(
  const autoware_vehicle_msgs::msg::GearCommand::SharedPtr msg)
{
  gear_cmd_ = msg;
}

void RobioneVehicleInterfaceCanSender::turn_indicators_cmd_callback(
  const autoware_vehicle_msgs::msg::TurnIndicatorsCommand::SharedPtr msg)
{
  turn_indicators_cmd_ = msg;
}

void RobioneVehicleInterfaceCanSender::hazard_lights_cmd_callback(
  const autoware_vehicle_msgs::msg::HazardLightsCommand::SharedPtr msg)
{
  hazard_lights_cmd_ = msg;
}

void RobioneVehicleInterfaceCanSender::vehicle_emergency_cmd_callback(
  const tier4_vehicle_msgs::msg::VehicleEmergencyStamped::SharedPtr msg)
{
  vehicle_emergency_cmd_ = msg;
}

void RobioneVehicleInterfaceCanSender::diagnostic_callback(
  diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  double elapsed_time = this->now().seconds() - control_cmd_timeout_.seconds();
  if (control_cmd_ != nullptr) {
    if (elapsed_time > msg_timeout_) {
      stat.add("Control Command", "TIMEOUT");
      stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Control Command Timeout");
      is_control_cmd_timeout_ = true;
    }
  } else {
    stat.add("Control Command", "Not Received");
  }
}

void RobioneVehicleInterfaceCanSender::route_state_callback(
  const autoware_adapi_v1_msgs::msg::RouteState::ConstSharedPtr msg)
{
  route_state_ptr_ = msg;
  if (route_state_ptr_->state == autoware_adapi_v1_msgs::msg::RouteState::ARRIVED) {
    arrived_timer_ = rclcpp::Clock().now();
    is_arrived_triggered = true;
  }
}

void RobioneVehicleInterfaceCanSender::tablet_feedback_callback(
  const robeff_msgs::msg::TabletFeedback::ConstSharedPtr msg)
{
  if (
    msg->event_type == robeff_msgs::msg::TabletFeedback::ROUTE_COMPLETED ||
    msg->event_type == robeff_msgs::msg::TabletFeedback::ROUTE_REJECTED || msg->event_type == 6) {
    is_arrived_triggered = false;
  }
}

void RobioneVehicleInterfaceCanSender::sick_zone_callback(
  const robeff_msgs::msg::SickZone::ConstSharedPtr msg)
{
  if (msg->state == robeff_msgs::msg::SickZone::DEACTIVATE) {
    is_restricted_area_detect = true;
  } else {
    is_restricted_area_detect = false;
  }
}

}  // namespace robione_vehicle_interface

#include <rclcpp_components/register_node_macro.hpp>

RCLCPP_COMPONENTS_REGISTER_NODE(robione_vehicle_interface::RobioneVehicleInterfaceCanSender)
