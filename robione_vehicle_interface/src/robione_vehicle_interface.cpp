#include "robione_vehicle_interface/robione_vehicle_interface.hpp"
#include "robione_vehicle_interface/autoware_socketcan_bridge.hpp"

namespace robione_vehicle_interface
{
RobioneVehicleInterface::RobioneVehicleInterface(
  const rclcpp::NodeOptions & options)
: Node{"robione_vehicle_interface", options}, diag_updater_receiver_{this}, diag_updater_sender_{this}
{
  // params
  can_recv_timeout_threshold_ = declare_parameter("can_recv_timeout_threshold_", 2.0);
  data_publish_rate_ = declare_parameter("data_publish_rate", 100);
  base_frame_id_ = declare_parameter("base_frame_id", "base_link");
  steer_rate_ = declare_parameter("steering_angle_rate", 75.0);
  velocity_limit_ = declare_parameter("vehicle_velocity_limit", 10.0);
  msg_timeout_ = declare_parameter("autoware_msg_timeout_threshold", 1.0);

  //  subscriptions
  //    Rain mode
  rain_mode_sub_ = this->create_subscription<example_interfaces::msg::Bool>(
    "/robione_vehicle_interface/rain_mode", rclcpp::QoS{1},
    std::bind(
      &RobioneVehicleInterface::rain_mode_callback, this, std::placeholders::_1));
  //    receiver
  can_frame_sub_ = this->create_subscription<can_msgs::msg::Frame>(
    "/from_can_bus", 100,
    std::bind(
      &RobioneVehicleInterface::can_receive_callback, this, std::placeholders::_1));

  //    sender
  control_cmd_sub_ = create_subscription<autoware_control_msgs::msg::Control>(
    "/control/command/control_cmd", rclcpp::QoS(1),
    std::bind(
      &RobioneVehicleInterface::control_cmd_callback, this, std::placeholders::_1));


  gear_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::GearCommand>(
    "/control/command/gear_cmd", rclcpp::QoS(1),
    std::bind(&RobioneVehicleInterface::gear_cmd_callback, this, std::placeholders::_1));

  turn_indicators_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::TurnIndicatorsCommand>(
    "/control/command/turn_indicators_cmd", rclcpp::QoS(1),
    std::bind(
      &RobioneVehicleInterface::turn_indicators_cmd_callback, this,
      std::placeholders::_1));

  hazard_lights_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::HazardLightsCommand>(
    "/control/command/hazard_lights_cmd", rclcpp::QoS(1),
    std::bind(
      &RobioneVehicleInterface::hazard_lights_cmd_callback, this, std::placeholders::_1));

  vehicle_emergency_cmd_sub_ =
    create_subscription<tier4_vehicle_msgs::msg::VehicleEmergencyStamped>(
      "/control/command/emergency_cmd", rclcpp::QoS(1),
      std::bind(
        &RobioneVehicleInterface::vehicle_emergency_cmd_callback, this,
        std::placeholders::_1));

  sub_route_state_ = this->create_subscription<autoware_adapi_v1_msgs::msg::RouteState>(
    "/api/ad_api_adapter/routing_state",
    rclcpp::QoS(rclcpp::KeepLast(1)).reliable().transient_local(),
    std::bind(
      &RobioneVehicleInterface::route_state_callback, this, std::placeholders::_1));

  tablet_feedback_sub_ = this->create_subscription<robeff_msgs::msg::TabletFeedback>(
    "/api/ad_api_adapter/tablet_feedback", rclcpp::QoS{1},
    std::bind(
      &RobioneVehicleInterface::tablet_feedback_callback, this, std::placeholders::_1));

  sick_zone_sub_ = this->create_subscription<robeff_msgs::msg::SickZone>(
    "/api/sick/zone", rclcpp::QoS(1).transient_local().reliable(),
    std::bind(&RobioneVehicleInterface::sick_zone_callback, this, std::placeholders::_1));


  // publishers

  // There is no "robione_vehicle_interface" in neither diagnostics nor topic list
  //  receiver
  vehicle_info_pub_ = this->create_publisher<robione_vehicle_interface_msgs::msg::VehicleInfo>(
    "robione_vehicle_interface/vehicle_info", 10);
  vehicle_status_pub_ = this->create_publisher<robione_vehicle_interface_msgs::msg::VehicleStatus>(
    "robione_vehicle_interface/vehicle_status", 10);

  //  sender
  vehicle_motion_cmd_pub_ =
    create_publisher<robione_vehicle_interface_msgs::msg::VehicleMotionCommands>(
      "/robione_vehicle_interface/vehicle_motion_cmd", rclcpp::QoS(1));
  vehicle_cmd_pub_ = create_publisher<robione_vehicle_interface_msgs::msg::VehicleCommands>(
    "/robione_vehicle_interface/vehicle_cmd", rclcpp::QoS(1));
  can_frame_pub_ = create_publisher<can_msgs::msg::Frame>("to_can_bus", rclcpp::QoS(500));

  // autoware publishers
  control_mode_pub_ = create_publisher<autoware_vehicle_msgs::msg::ControlModeReport>(
    "/vehicle/status/control_mode", rclcpp::QoS{1});
  vehicle_twist_pub_ = create_publisher<autoware_vehicle_msgs::msg::VelocityReport>(
    "/vehicle/status/velocity_status", rclcpp::QoS{1});
  steering_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::SteeringReport>(
    "/vehicle/status/steering_status", rclcpp::QoS{1});
  gear_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::GearReport>(
    "/vehicle/status/gear_status", rclcpp::QoS{1});
  turn_indicators_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::TurnIndicatorsReport>(
    "/vehicle/status/turn_indicators_status", rclcpp::QoS{1});
  hazard_lights_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::HazardLightsReport>(
    "/vehicle/status/hazard_lights_status", rclcpp::QoS{1}); // DO WE NEED IT?
  steering_wheel_status_pub_ =
    create_publisher<tier4_vehicle_msgs::msg::SteeringWheelStatusStamped>(
      "/vehicle/status/steering_wheel_status", 1);

  // diagnostics
  // DIAGNOSTICS INCLUDE "robione_vehicle" ARE NOT VISIBLE ON DIAGNOSTICS TOPIC
  //  receiver
  diag_updater_receiver_.setHardwareID("robione_vehicle_interface_can_receiver");
  diag_updater_receiver_.add("CAN Status", this, &RobioneVehicleInterface::receiver_diagnostic_callback);

  //  sender
  diag_updater_sender_.setHardwareID("robione_vehicle_interface_can_sender");
  diag_updater_sender_.add("CAN Status", this, &RobioneVehicleInterface::sender_diagnostic_callback);

  // timer
  //  receiver
  const auto period_ns_receiver = rclcpp::Rate(data_publish_rate_).period();
  data_publish_timer_ = rclcpp::create_timer(
    this, get_clock(), period_ns_receiver,
    std::bind(&RobioneVehicleInterface::data_publish_timer_callback, this));

  //  sender
  const auto period_ns_sender = rclcpp::Rate(100).period();
  data_publish_can_timer_ = create_timer(
    this, get_clock(), period_ns_sender,
    std::bind(&RobioneVehicleInterface::data_publish_can_timer_callback, this));

}


// RECEIVER CALLBACKS
void RobioneVehicleInterface::data_publish_timer_callback(void)
{
  control_mode_pub_->publish(
    AutowareSocketcanBridge::convert_to_autoware_control_mode_report(vcu_rx_.VEHICLE_STATUS));

  vehicle_twist_pub_->publish(AutowareSocketcanBridge::convert_to_autoware_velocity_report(
    vcu_rx_.VEHICLE_INFO, base_frame_id_));

  steering_status_pub_->publish(
    AutowareSocketcanBridge::convert_to_autoware_steering_report(vcu_rx_.VEHICLE_INFO));

  gear_status_pub_->publish(
    AutowareSocketcanBridge::convert_to_autoware_gear_report(vcu_rx_.VEHICLE_STATUS));

  turn_indicators_status_pub_->publish(
    AutowareSocketcanBridge::convert_to_autoware_turn_indicators_report(vcu_rx_.VEHICLE_STATUS));

  hazard_lights_status_pub_->publish(
    AutowareSocketcanBridge::convert_to_autoware_hazard_light_report(vcu_rx_.VEHICLE_STATUS));
}

void RobioneVehicleInterface::can_receive_callback(can_msgs::msg::Frame::SharedPtr msg)
{
  if (vcu_Receive(
        &(RobioneVehicleInterface::vcu_rx_), msg->data.data(), msg->id, msg->dlc)) {
    switch (msg->id) {
      case VEHICLE_INFO_CANID:
        receive_time_vehicle_info_ = msg->header.stamp;
        publish_vehicle_info(vcu_rx_.VEHICLE_INFO);
        break;
      case VEHICLE_STATUS_CANID:
        receive_time_vehicle_status_ = msg->header.stamp;
        publish_vehicle_status(vcu_rx_.VEHICLE_STATUS);
        break;
      default:
        break;
    }
  }

  if (msg->id == 0xA0002DBU) {
    system("pkill -f /robione_vehicle_interface");
    rclcpp::shutdown();
  }
}

void RobioneVehicleInterface::publish_vehicle_info(const VEHICLE_INFO_t & vehicle_info)
{
  auto msg = robione_vehicle_interface_msgs::msg::VehicleInfo();
  msg.stamp = this->now();
  msg.vehicle_velocity = vehicle_info.vehicle_velocity_phys;
  msg.steering_wheel_angle = vehicle_info.steering_wheel_angle_phys;
  msg.steering_wheel_speed = vehicle_info.steering_wheel_speed_phys;
  msg.steering_wheel_torque = vehicle_info.steering_wheel_torque;
  msg.steering_tire_angle = vehicle_info.steering_tire_angle_phys;
  vehicle_info_pub_->publish(msg);
}

void RobioneVehicleInterface::publish_vehicle_status(
  const VEHICLE_STATUS_t & vehicle_status)
{
  auto msg = robione_vehicle_interface_msgs::msg::VehicleStatus();
  msg.stamp = this->now();

  msg.battery_voltage = vehicle_status.battery_voltage;
  msg.battery_soc = vehicle_status.battery_soc;
  msg.blinker = vehicle_status.blinker;
  msg.headlight = vehicle_status.headlight;
  msg.gear = vehicle_status.gear;
  msg.mode = vehicle_status.mode;
  msg.handbrake = vehicle_status.hand_brake;
  vehicle_status_pub_->publish(msg);
}

void RobioneVehicleInterface::receiver_diagnostic_callback(
  diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  double time_since_last_vehicle_info =
    this->now().seconds() - receive_time_vehicle_info_.seconds();
  double time_since_last_vehicle_status =
    this->now().seconds() - receive_time_vehicle_status_.seconds();

  if (time_since_last_vehicle_info > can_recv_timeout_threshold_) {
    stat.add("Vehicle Info", "TIMEOUT");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Vehicle Info timeout");
  } else {
    stat.add("Vehicle Info", "OK");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Vehicle Info OK");
  }

  if (time_since_last_vehicle_status > can_recv_timeout_threshold_) {
    stat.add("Vehicle Status", "TIMEOUT");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Vehicle Signal Status timeout");
  } else {
    stat.add("Vehicle Status", "OK");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Vehicle Signal Status OK");
  }
}


// SENDER CALLBACKS
void RobioneVehicleInterface::data_publish_can_timer_callback()
{
  rclcpp::Clock clock{RCL_ROS_TIME};
  bool is_all_received = true;  // Flag to track if all messages are received
  bool triggered_horn = false;

  can_frame_pub_->publish(AutowareSocketcanBridge::convert_vehicle_interface_life_signal()); // ASK WHAT IS IT 

  // Check if any of the subscribed messages are nullptr and log warningspublish
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
      is_restricted_area_detect, triggered_horn));

    // ROS2 Debug Messages
    vehicle_motion_cmd_pub_->publish(AutowareSocketcanBridge::convert_to_vehicle_motion_cmd());

    vehicle_cmd_pub_->publish(AutowareSocketcanBridge::convert_to_vehicle_cmd());
  }
}

void RobioneVehicleInterface::control_cmd_callback(
  const autoware_control_msgs::msg::Control::SharedPtr msg)
{
  control_cmd_timeout_ = msg->stamp;
  control_cmd_ = msg;
}

void RobioneVehicleInterface::gear_cmd_callback(
  const autoware_vehicle_msgs::msg::GearCommand::SharedPtr msg)
{
  gear_cmd_ = msg;
}

void RobioneVehicleInterface::turn_indicators_cmd_callback(
  const autoware_vehicle_msgs::msg::TurnIndicatorsCommand::SharedPtr msg)
{
  turn_indicators_cmd_ = msg;
}

void RobioneVehicleInterface::hazard_lights_cmd_callback(
  const autoware_vehicle_msgs::msg::HazardLightsCommand::SharedPtr msg)
{
  hazard_lights_cmd_ = msg;
}

void RobioneVehicleInterface::vehicle_emergency_cmd_callback(
  const tier4_vehicle_msgs::msg::VehicleEmergencyStamped::SharedPtr msg)
{
  vehicle_emergency_cmd_ = msg;
}

void RobioneVehicleInterface::sender_diagnostic_callback(
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

void RobioneVehicleInterface::route_state_callback(
  const autoware_adapi_v1_msgs::msg::RouteState::ConstSharedPtr msg)
{
  route_state_ptr_ = msg;
  if (route_state_ptr_->state == autoware_adapi_v1_msgs::msg::RouteState::ARRIVED) {
    arrived_timer_ = rclcpp::Clock().now();
    is_arrived_triggered = true;
  }
}

void RobioneVehicleInterface::tablet_feedback_callback(
  const robeff_msgs::msg::TabletFeedback::ConstSharedPtr msg)
{
  if (
    msg->event_type == robeff_msgs::msg::TabletFeedback::ROUTE_COMPLETED ||
    msg->event_type == robeff_msgs::msg::TabletFeedback::ROUTE_REJECTED || msg->event_type == 6) {
    is_arrived_triggered = false;
  }
}

void RobioneVehicleInterface::sick_zone_callback(
  const robeff_msgs::msg::SickZone::ConstSharedPtr msg)
{
  if (msg->state == robeff_msgs::msg::SickZone::DEACTIVATE || rain_mode_) {
    is_restricted_area_detect = true;
  } else {
    is_restricted_area_detect = false;
  }
}

// Rain mode callback
// This callback handles the rain mode setting for the vehicle interface.
// If a valid message is received, it updates the rain_mode_ variable
// and logs the change. If the message is null, it logs a warning.
// Rain mode only changes if the incoming value is different from the current state.
// else, it logs that the rain mode was already set.
void RobioneVehicleInterface::rain_mode_callback(const example_interfaces::msg::Bool::SharedPtr msg)
{
  if (msg)
  {
    if (rain_mode_ != msg->data)
    {
      rain_mode_ = msg->data;
      RCLCPP_INFO(this->get_logger(), "Rain mode set to: %s", rain_mode_ ? "enabled" : "disabled");
    }
    else
    {
      RCLCPP_INFO(this->get_logger(), "Rain mode was already enabled.");
    }
  }
  else
  {
    RCLCPP_WARN(this->get_logger(), "Received null message for rain mode.");
  }
}


}  // namespace robione_vehicle_interface

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(robione_vehicle_interface::RobioneVehicleInterface)
