#include "leo_vehicle_interface/leo_vehicle_interface_can_sender.hpp"

#include "leo_vehicle_interface/autoware_socketcan_bridge.hpp"
namespace leo_vehicle_interface
{
LeoVehicleInterfaceCanSender::LeoVehicleInterfaceCanSender(const rclcpp::NodeOptions & options)
: Node{"leo_vehicle_interface_can_sender", options}, diag_updater_{this}
{
  // params
  base_frame_id_ = declare_parameter("base_frame_id", "base_link");
  steer_rate_ = declare_parameter("steering_angle_rate", 75.0);
  velocity_limit_ = declare_parameter("vehicle_velocity_limit", 10.0);

  diag_updater_.setHardwareID("leo_vehicle_interface_can_receiver");
  diag_updater_.add("CAN Status", this, &LeoVehicleInterfaceCanSender::diagnostic_callback);

  // publishers
  front_wheel_cmd_pub_ = create_publisher<leo_vehicle_interface_msgs::msg::FrontWheelCommand>(
    "/leo_vehicle_interface/front_wheel_cmd", rclcpp::QoS(1));
  longitudinal_cmd_pub_ = create_publisher<leo_vehicle_interface_msgs::msg::LongitudinalCommand>(
    "/leo_vehicle_interface/longitudinal_cmd", rclcpp::QoS(1));
  vehicle_cmd_pub_ = create_publisher<leo_vehicle_interface_msgs::msg::VehicleCommand>(
    "/leo_vehicle_interface/vehicle_cmd", rclcpp::QoS(1));

  // subscriptions
  control_cmd_sub_ = create_subscription<autoware_control_msgs::msg::Control>(
    "/control/command/control_cmd", rclcpp::QoS(1),
    std::bind(&LeoVehicleInterfaceCanSender::control_cmd_callback, this, std::placeholders::_1));
  gear_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::GearCommand>(
    "/control/command/gear_cmd", rclcpp::QoS(1),
    std::bind(&LeoVehicleInterfaceCanSender::gear_cmd_callback, this, std::placeholders::_1));
  turn_indicators_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::TurnIndicatorsCommand>(
    "/control/command/turn_indicators_cmd", rclcpp::QoS(1),
    std::bind(
      &LeoVehicleInterfaceCanSender::turn_indicators_cmd_callback, this, std::placeholders::_1));
  hazard_lights_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::HazardLightsCommand>(
    "/control/command/hazard_lights_cmd", rclcpp::QoS(1),
    std::bind(
      &LeoVehicleInterfaceCanSender::hazard_lights_cmd_callback, this, std::placeholders::_1));
  engage_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::Engage>(
    "/autoware/engage", rclcpp::QoS(1),
    std::bind(&LeoVehicleInterfaceCanSender::engage_cmd_callback, this, std::placeholders::_1));
  gate_mode_cmd_sub_ = create_subscription<tier4_control_msgs::msg::GateMode>(
    "/control/current_gate_mode", rclcpp::QoS(1),
    std::bind(&LeoVehicleInterfaceCanSender::gate_mode_cmd_callback, this, std::placeholders::_1));
 
  vehicle_emergency_cmd_sub_ =
    create_subscription<tier4_vehicle_msgs::msg::VehicleEmergencyStamped>(
      "/control/command/emergency_cmd", rclcpp::QoS(1),
      std::bind(
        &LeoVehicleInterfaceCanSender::vehicle_emergency_cmd_callback, this,
        std::placeholders::_1));

  // publishers
  can_frame_pub_ = create_publisher<can_msgs::msg::Frame>("to_can_bus", rclcpp::QoS(500));

  // timer
  const auto period_ns = rclcpp::Rate(100).period();
  data_publish_can_timer_ = create_timer(
    this, get_clock(), period_ns,
    std::bind(&LeoVehicleInterfaceCanSender::data_publish_timer_callback, this));
}
void LeoVehicleInterfaceCanSender::data_publish_timer_callback()
{
  bool is_autoware_running = false;
  rclcpp::Clock clock{RCL_ROS_TIME};
  bool is_all_received = true;  // Flag to track if all messages are received

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
  
  if (engage_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000, "engage_cmd is not received");
    is_all_received = false;
  }
  
  if (gate_mode_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000, "gate_mode_cmd is not received");
    is_all_received = false;
  }
  
  if (vehicle_emergency_cmd_ == nullptr) {
    RCLCPP_WARN_THROTTLE(get_logger(), clock, 1000, "vehicle_emergency_cmd is not received");
    is_all_received = false;
  }

  // If all the required commands are received, publish the CAN messages
  if (is_all_received) {
    can_frame_pub_->publish(
      AutowareSocketcanBridge::convert_autoware_to_front_wheel_cmd(*control_cmd_, steer_rate_));
    
    front_wheel_cmd_pub_->publish(AutowareSocketcanBridge::convert_to_front_wheel_cmd());
    
    can_frame_pub_->publish(
      AutowareSocketcanBridge::convert_autoware_to_longitudinal_cmd(*control_cmd_, velocity_limit_));
    
    longitudinal_cmd_pub_->publish(AutowareSocketcanBridge::convert_to_longitudinal_cmd());
    
    can_frame_pub_->publish(AutowareSocketcanBridge::convert_autoware_vehicle_cmd(
      *gear_cmd_, *turn_indicators_cmd_, *hazard_lights_cmd_, *vehicle_emergency_cmd_,
      *gate_mode_cmd_, *engage_cmd_));
    
    vehicle_cmd_pub_->publish(AutowareSocketcanBridge::convert_to_vehicle_cmd());
  }
}

void LeoVehicleInterfaceCanSender::control_cmd_callback(
  const autoware_control_msgs::msg::Control::SharedPtr msg)
{
  control_cmd_ = msg;
}

void LeoVehicleInterfaceCanSender::gear_cmd_callback(
  const autoware_vehicle_msgs::msg::GearCommand::SharedPtr msg)
{
  gear_cmd_ = msg;
}

void LeoVehicleInterfaceCanSender::turn_indicators_cmd_callback(
  const autoware_vehicle_msgs::msg::TurnIndicatorsCommand::SharedPtr msg)
{
  turn_indicators_cmd_ = msg;
}

void LeoVehicleInterfaceCanSender::hazard_lights_cmd_callback(
  const autoware_vehicle_msgs::msg::HazardLightsCommand::SharedPtr msg)
{
  hazard_lights_cmd_ = msg;
}

void LeoVehicleInterfaceCanSender::engage_cmd_callback(
  const autoware_vehicle_msgs::msg::Engage::SharedPtr msg)
{
  engage_cmd_ = msg;
}

void LeoVehicleInterfaceCanSender::gate_mode_cmd_callback(
  const tier4_control_msgs::msg::GateMode::SharedPtr msg)
{
  gate_mode_cmd_ = msg;
}


void LeoVehicleInterfaceCanSender::vehicle_emergency_cmd_callback(
  const tier4_vehicle_msgs::msg::VehicleEmergencyStamped::SharedPtr msg)
{
  vehicle_emergency_cmd_ = msg;
}

void LeoVehicleInterfaceCanSender::diagnostic_callback(
  diagnostic_updater::DiagnosticStatusWrapper & stat)
{
}

}  // namespace leo_vehicle_interface

#include <rclcpp_components/register_node_macro.hpp>

RCLCPP_COMPONENTS_REGISTER_NODE(leo_vehicle_interface::LeoVehicleInterfaceCanSender)