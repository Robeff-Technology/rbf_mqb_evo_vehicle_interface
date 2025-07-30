#include "robione_vehicle_interface/robione_vehicle_interface_can_sender.hpp"
#include "robione_vehicle_interface/autoware_socketcan_bridge.hpp"
#include <cstdlib>
namespace robione_vehicle_interface {
RobioneVehicleInterfaceCanSender::RobioneVehicleInterfaceCanSender(
    const rclcpp::NodeOptions &options)
    : Node{"robione_vehicle_interface_can_sender", options},
      diag_updater_{this} {
  // params
  base_frame_id_ = declare_parameter("base_frame_id", "base_link");
  steer_rate_ = declare_parameter("steering_angle_rate", 75.0);
  velocity_limit_ = declare_parameter("vehicle_velocity_limit", 10.0);
  msg_timeout_ = declare_parameter("autoware_msg_timeout_threshold", 1.0);

  diag_updater_.setHardwareID("robione_vehicle_interface_can_sender");
  diag_updater_.add("CAN Status", this,
                    &RobioneVehicleInterfaceCanSender::diagnostic_callback);

  // publishers
  vehicle_motion_cmd_pub_ = create_publisher<
      robione_vehicle_interface_msgs::msg::VehicleMotionCommands>(
      "/robione_vehicle_interface/vehicle_motion_cmd", rclcpp::QoS(1));
  vehicle_cmd_pub_ =
      create_publisher<robione_vehicle_interface_msgs::msg::VehicleCommands>(
          "/robione_vehicle_interface/vehicle_cmd", rclcpp::QoS(1));

  // subscriptions
  control_cmd_sub_ = create_subscription<autoware_control_msgs::msg::Control>(
      "/control/command/control_cmd", rclcpp::QoS(1),
      std::bind(&RobioneVehicleInterfaceCanSender::control_cmd_callback, this,
                std::placeholders::_1));
  gear_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::GearCommand>(
      "/control/command/gear_cmd", rclcpp::QoS(1),
      std::bind(&RobioneVehicleInterfaceCanSender::gear_cmd_callback, this,
                std::placeholders::_1));
  turn_indicators_cmd_sub_ =
      create_subscription<autoware_vehicle_msgs::msg::TurnIndicatorsCommand>(
          "/control/command/turn_indicators_cmd", rclcpp::QoS(1),
          std::bind(
              &RobioneVehicleInterfaceCanSender::turn_indicators_cmd_callback,
              this, std::placeholders::_1));
  hazard_lights_cmd_sub_ =
      create_subscription<autoware_vehicle_msgs::msg::HazardLightsCommand>(
          "/control/command/hazard_lights_cmd", rclcpp::QoS(1),
          std::bind(
              &RobioneVehicleInterfaceCanSender::hazard_lights_cmd_callback,
              this, std::placeholders::_1));
  engage_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::Engage>(
      "/autoware/engage", rclcpp::QoS(1),
      std::bind(&RobioneVehicleInterfaceCanSender::engage_cmd_callback, this,
                std::placeholders::_1));
  gate_mode_cmd_sub_ = create_subscription<tier4_control_msgs::msg::GateMode>(
      "/control/current_gate_mode", rclcpp::QoS(1),
      std::bind(&RobioneVehicleInterfaceCanSender::gate_mode_cmd_callback, this,
                std::placeholders::_1));
  vehicle_emergency_cmd_sub_ =
      create_subscription<tier4_vehicle_msgs::msg::VehicleEmergencyStamped>(
          "/control/command/emergency_cmd", rclcpp::QoS(1),
          std::bind(
              &RobioneVehicleInterfaceCanSender::vehicle_emergency_cmd_callback,
              this, std::placeholders::_1));
  sub_route_state_ =
      this->create_subscription<autoware_adapi_v1_msgs::msg::RouteState>(
          "/api/routing/state",
          rclcpp::QoS(rclcpp::KeepLast(1)).reliable().transient_local(),
          std::bind(&RobioneVehicleInterfaceCanSender::route_state_callback,
                    this, std::placeholders::_1));
  gui_to_drc_sub_ = this->create_subscription<robeff_msgs::msg::GuiToDrc>(
      "/interface/gui_to_drc", rclcpp::QoS{1},
      std::bind(&RobioneVehicleInterfaceCanSender::gui_to_drc_callback, this,
                std::placeholders::_1));

  sick_zone_sub_ = this->create_subscription<robeff_msgs::msg::SickZone>(
      "/interface/gui_to_drc", rclcpp::QoS(1).transient_local().reliable(),
      std::bind(&RobioneVehicleInterfaceCanSender::sick_zone_callback, this,
                std::placeholders::_1));

  // publishers
  can_frame_pub_ =
      create_publisher<can_msgs::msg::Frame>("to_can_bus", rclcpp::QoS(500));

  // timer
  const auto period_ns = rclcpp::Rate(100).period();
  data_publish_can_timer_ = create_timer(
      this, get_clock(), period_ns,
      std::bind(&RobioneVehicleInterfaceCanSender::data_publish_timer_callback,
                this));
}
void RobioneVehicleInterfaceCanSender::data_publish_timer_callback() {
  rclcpp::Clock clock{RCL_ROS_TIME};
  bool is_all_received = true; // Flag to track if all messages are received
  bool triggered_horn = false;

  can_frame_pub_->publish(
      AutowareSocketcanBridge::convert_vehicle_interface_life_signal());

  // Check if any of the subscribed messages are nullptr and log warnings
  if (control_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000,
                         "control_cmd is not received");
    is_all_received = false;
  }

  if (gear_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000, "gear_cmd is not received");
    is_all_received = false;
  }

  if (turn_indicators_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000,
                         "turn_indicators_cmd is not received");
    is_all_received = false;
  }

  if (hazard_lights_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000,
                         "hazard_lights_cmd is not received");
    is_all_received = false;
  }

  if (engage_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000,
                         "engage_cmd is not received");
    is_all_received = false;
  }

  if (gate_mode_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000,
                         "gate_mode_cmd is not received");
    is_all_received = false;
  }

  if (vehicle_emergency_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000,
                         "vehicle_emergency_cmd is not received");
    is_all_received = false;
  }

  if (is_arrived_triggered &&
      ((rclcpp::Clock().now() - arrived_timer_).seconds() < 10)) {
    triggered_horn = true;
  }

  // If all the required commands are received, publish the CAN messages
  if (is_all_received && !is_control_cmd_timeout_) {
    // Publish the CAN messages
    can_frame_pub_->publish(
        AutowareSocketcanBridge::convert_autoware_to_vehicle_motion_cmd(
            *control_cmd_, velocity_limit_, steer_rate_));

    can_frame_pub_->publish(
        AutowareSocketcanBridge::convert_autoware_vehicle_cmd(
            *gear_cmd_, *turn_indicators_cmd_, *hazard_lights_cmd_,
            *vehicle_emergency_cmd_, triggered_horn,
            is_restricted_area_detect));

    // ROS2 Debug Messages
    vehicle_motion_cmd_pub_->publish(
        AutowareSocketcanBridge::convert_to_vehicle_motion_cmd());

    vehicle_cmd_pub_->publish(
        AutowareSocketcanBridge::convert_to_vehicle_cmd());
  }
}

void RobioneVehicleInterfaceCanSender::control_cmd_callback(
    const autoware_control_msgs::msg::Control::SharedPtr msg) {
  control_cmd_timeout_ = msg->stamp;
  control_cmd_ = msg;
}

void RobioneVehicleInterfaceCanSender::gear_cmd_callback(
    const autoware_vehicle_msgs::msg::GearCommand::SharedPtr msg) {
  gear_cmd_ = msg;
}

void RobioneVehicleInterfaceCanSender::turn_indicators_cmd_callback(
    const autoware_vehicle_msgs::msg::TurnIndicatorsCommand::SharedPtr msg) {
  turn_indicators_cmd_ = msg;
}

void RobioneVehicleInterfaceCanSender::hazard_lights_cmd_callback(
    const autoware_vehicle_msgs::msg::HazardLightsCommand::SharedPtr msg) {
  hazard_lights_cmd_ = msg;
}

void RobioneVehicleInterfaceCanSender::engage_cmd_callback(
    const autoware_vehicle_msgs::msg::Engage::SharedPtr msg) {
  engage_cmd_ = msg;
}

void RobioneVehicleInterfaceCanSender::gate_mode_cmd_callback(
    const tier4_control_msgs::msg::GateMode::SharedPtr msg) {
  gate_mode_cmd_ = msg;
}

void RobioneVehicleInterfaceCanSender::vehicle_emergency_cmd_callback(
    const tier4_vehicle_msgs::msg::VehicleEmergencyStamped::SharedPtr msg) {
  vehicle_emergency_cmd_ = msg;
}

void RobioneVehicleInterfaceCanSender::diagnostic_callback(
    diagnostic_updater::DiagnosticStatusWrapper &stat) {
  double elapsed_time = this->now().seconds() - control_cmd_timeout_.seconds();
  if (control_cmd_ != nullptr) {
    if (elapsed_time > msg_timeout_) {
      stat.add("Control Command", "TIMEOUT");
      stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR,
                   "Control Command Timeout");
      is_control_cmd_timeout_ = true;
    }
  } else {
    stat.add("Control Command", "Not Received");
  }
}

void RobioneVehicleInterfaceCanSender::route_state_callback(
    const autoware_adapi_v1_msgs::msg::RouteState::ConstSharedPtr msg) {
  route_state_ptr_ = msg;
  if (route_state_ptr_->state ==
      autoware_adapi_v1_msgs::msg::RouteState::ARRIVED) {
    arrived_timer_ = rclcpp::Clock().now();
    is_arrived_triggered = true;
  } else {
    is_arrived_triggered = false;
  }
}

void RobioneVehicleInterfaceCanSender::gui_to_drc_callback(
    const robeff_msgs::msg::GuiToDrc::ConstSharedPtr msg) {
  if (msg->data_id == 7) {
    is_arrived_triggered = false;
  }
}

void RobioneVehicleInterfaceCanSender::sick_zone_callback(
    const robeff_msgs::msg::SickZone::ConstSharedPtr msg) {
      if(msg->state == robeff_msgs::msg::SickZone::DEACTIVATE) {
        is_restricted_area_detect = true;
      }
      else {
        is_restricted_area_detect = false;
      }
}

} // namespace robione_vehicle_interface

#include <rclcpp_components/register_node_macro.hpp>

RCLCPP_COMPONENTS_REGISTER_NODE(
    robione_vehicle_interface::RobioneVehicleInterfaceCanSender)