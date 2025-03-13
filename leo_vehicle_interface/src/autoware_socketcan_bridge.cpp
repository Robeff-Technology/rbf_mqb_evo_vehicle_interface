#include "leo_vehicle_interface/autoware_socketcan_bridge.hpp"

#include "rclcpp/rclcpp.hpp"

#include <cmath>

namespace leo_vehicle_interface
{

FRONT_WHEEL_COMMANDS_t front_wheel_cmd_{};
LONGITUDINAL_COMMANDS_t longitudinal_cmd_{};
VEHICLE_COMMANDS_t vehicle_cmd_{};

const double degree_to_radian = M_PI / 180.0;
const double radian_to_degree = 180.0 / M_PI;

const double mps_to_kph = 3.6;
const double kph_to_mps = 1.0 / mps_to_kph;

autoware_vehicle_msgs::msg::ControlModeReport
AutowareSocketcanBridge::convert_to_autoware_control_mode_report(
  const VEHICLE_SIGNAL_STATUS_t & control_mode_report)
{
  autoware_vehicle_msgs::msg::ControlModeReport control_mode_report_msg;
  control_mode_report_msg.stamp = rclcpp::Clock().now();

  if (control_mode_report.mode == mode_VEHICLE_SIGNAL_STATUS_CONTROLLER_AUTONOMOUS) {
    control_mode_report_msg.mode = autoware_vehicle_msgs::msg::ControlModeReport::AUTONOMOUS;
  } else {
    control_mode_report_msg.mode = autoware_vehicle_msgs::msg::ControlModeReport::MANUAL;
  }
  return control_mode_report_msg;
}

autoware_vehicle_msgs::msg::GearReport AutowareSocketcanBridge::convert_to_autoware_gear_report(
  const VEHICLE_SIGNAL_STATUS_t & gear_report)
{
  autoware_vehicle_msgs::msg::GearReport gear_report_msg;
  gear_report_msg.stamp = rclcpp::Clock().now();

  if (gear_report.gear == gear_VEHICLE_SIGNAL_STATUS_D) {
    gear_report_msg.report = autoware_vehicle_msgs::msg::GearReport::DRIVE;
  } else if (gear_report.gear == gear_VEHICLE_SIGNAL_STATUS_R) {
    gear_report_msg.report = autoware_vehicle_msgs::msg::GearReport::REVERSE;
  } else if (gear_report.gear == gear_VEHICLE_SIGNAL_STATUS_P) {
    gear_report_msg.report = autoware_vehicle_msgs::msg::GearReport::PARK;
  } else if (gear_report.gear == gear_VEHICLE_SIGNAL_STATUS_N) {
    gear_report_msg.report = autoware_vehicle_msgs::msg::GearReport::NEUTRAL;
  } else {
    gear_report_msg.report = autoware_vehicle_msgs::msg::GearReport::NONE;
  }

  return gear_report_msg;
}

autoware_vehicle_msgs::msg::HazardLightsReport
AutowareSocketcanBridge::convert_to_autoware_hazard_light_report(
  const VEHICLE_SIGNAL_STATUS_t & hazard_lights_report)
{
  autoware_vehicle_msgs::msg::HazardLightsReport hazard_lights_report_msg;
  hazard_lights_report_msg.stamp = rclcpp::Clock().now();

  if (hazard_lights_report.blinker == blinker_VEHICLE_SIGNAL_STATUS_HAZARD_LIGHT) {
    hazard_lights_report_msg.report = autoware_vehicle_msgs::msg::HazardLightsReport::ENABLE;
  } else {
    hazard_lights_report_msg.report = autoware_vehicle_msgs::msg::HazardLightsReport::DISABLE;
  }

  return hazard_lights_report_msg;
}

autoware_vehicle_msgs::msg::SteeringReport
AutowareSocketcanBridge::convert_to_autoware_steering_report(const VEHICLE_INFO_t & steering_report)
{
  autoware_vehicle_msgs::msg::SteeringReport steering_report_msg;
  steering_report_msg.stamp = rclcpp::Clock().now();
  steering_report_msg.steering_tire_angle = steering_report.steering_tire_angle_phys;

  return steering_report_msg;
}

autoware_vehicle_msgs::msg::TurnIndicatorsReport
AutowareSocketcanBridge::convert_to_autoware_turn_indicators_report(
  const VEHICLE_SIGNAL_STATUS_t & turn_indicators_report)
{
  autoware_vehicle_msgs::msg::TurnIndicatorsReport turn_indicators_report_msg;
  turn_indicators_report_msg.stamp = rclcpp::Clock().now();

  if (turn_indicators_report.blinker == blinker_VEHICLE_SIGNAL_STATUS_RIGHT_BLINKER) {
    turn_indicators_report_msg.report =
      autoware_vehicle_msgs::msg::TurnIndicatorsReport::ENABLE_RIGHT;
  } else if (turn_indicators_report.blinker == blinker_VEHICLE_SIGNAL_STATUS_LEFT_BLINKER) {
    turn_indicators_report_msg.report =
      autoware_vehicle_msgs::msg::TurnIndicatorsReport::ENABLE_LEFT;
  } else {
    turn_indicators_report_msg.report = autoware_vehicle_msgs::msg::TurnIndicatorsReport::DISABLE;
  }

  return turn_indicators_report_msg;
}

autoware_vehicle_msgs::msg::VelocityReport
AutowareSocketcanBridge::convert_to_autoware_velocity_report(
  const VEHICLE_INFO_t & velocity_report, const VEHICLE_SIGNAL_STATUS_t & gear_report,
  std::string base_link)
{
  autoware_vehicle_msgs::msg::VelocityReport velocity_report_msg;
  velocity_report_msg.header.frame_id = base_link;
  velocity_report_msg.header.stamp = rclcpp::Clock().now();

  velocity_report_msg.longitudinal_velocity = gear_report.gear == gear_VEHICLE_SIGNAL_STATUS_R
                                                ? -velocity_report.vehicle_velocity_phys
                                                : velocity_report.vehicle_velocity_phys;

  velocity_report_msg.longitudinal_velocity =
    velocity_report_msg.longitudinal_velocity * kph_to_mps;
  return velocity_report_msg;
}

tier4_vehicle_msgs::msg::SteeringWheelStatusStamped
AutowareSocketcanBridge::convert_to_tier4_steering_wheel_status(
  const VEHICLE_INFO_t & steering_wheel_status)
{
  tier4_vehicle_msgs::msg::SteeringWheelStatusStamped steering_wheel_status_msg;
  steering_wheel_status_msg.stamp = rclcpp::Clock().now();

  steering_wheel_status_msg.data = steering_wheel_status.steering_wheel_angle_phys;

  return steering_wheel_status_msg;
}

tier4_vehicle_msgs::msg::ActuationStatusStamped
AutowareSocketcanBridge::convert_to_tier4_actuation_status(
  const MOTION_INFO_t & actuation_status, std::string base_link)
{
  tier4_vehicle_msgs::msg::ActuationStatusStamped actuation_status_msg;
  actuation_status_msg.header.stamp = rclcpp::Clock().now();
  actuation_status_msg.header.frame_id = base_link;

  actuation_status_msg.status.accel_status = actuation_status.throttle_phys;
  actuation_status_msg.status.brake_status = actuation_status.brake;

  return actuation_status_msg;
}

leo_vehicle_interface_msgs::msg::FrontWheelCommand
AutowareSocketcanBridge::convert_to_front_wheel_cmd()
{
  leo_vehicle_interface_msgs::msg::FrontWheelCommand front_wheel_cmd_msg;
  front_wheel_cmd_msg.stamp = rclcpp::Clock().now();

  front_wheel_cmd_msg.set_tire_angle = front_wheel_cmd_.set_front_wheel_tire_angle;
  front_wheel_cmd_msg.set_tire_angle_rate = front_wheel_cmd_.set_front_wheel_angle_rate;

  return front_wheel_cmd_msg;
}

leo_vehicle_interface_msgs::msg::LongitudinalCommand
AutowareSocketcanBridge::convert_to_longitudinal_cmd()
{
  leo_vehicle_interface_msgs::msg::LongitudinalCommand long_cmd_;
  long_cmd_.stamp = rclcpp::Clock().now();

  long_cmd_.set_velocity = longitudinal_cmd_.set_velocity;
  long_cmd_.set_limit_velocity = longitudinal_cmd_.set_limit_velocity;

  return long_cmd_;
}

leo_vehicle_interface_msgs::msg::VehicleCommand AutowareSocketcanBridge::convert_to_vehicle_cmd()
{
  leo_vehicle_interface_msgs::msg::VehicleCommand vehicle_cmd_msg;
  vehicle_cmd_msg.stamp = rclcpp::Clock().now();

  vehicle_cmd_msg.set_autonomous = vehicle_cmd_.set_autonomous;
  vehicle_cmd_msg.gear = vehicle_cmd_.gear;
  vehicle_cmd_msg.blinker = vehicle_cmd_.blinker;
  vehicle_cmd_msg.emergency = vehicle_cmd_.emergency_request;

  return vehicle_cmd_msg;
}

can_msgs::msg::Frame AutowareSocketcanBridge::convert_autoware_to_front_wheel_cmd(
  const autoware_control_msgs::msg::Control & control_cmd, float tire_rate)
{
  uint8_t len, ide;
  auto frame = can_msgs::msg::Frame();
  frame.header.stamp = rclcpp::Clock().now();

  front_wheel_cmd_.set_front_wheel_tire_angle = control_cmd.lateral.steering_tire_angle;

  if (control_cmd.lateral.is_defined_steering_tire_rotation_rate == false) {
    front_wheel_cmd_.set_front_wheel_angle_rate = tire_rate;
  } else {
    front_wheel_cmd_.set_front_wheel_angle_rate = control_cmd.lateral.steering_tire_rotation_rate;
  }

  frame.id = Pack_FRONT_WHEEL_COMMANDS_autonomous(&front_wheel_cmd_, frame.data.data(), &len, &ide);
  frame.is_extended = ide;
  frame.is_rtr = false;
  frame.dlc = len;

  return frame;
}

can_msgs::msg::Frame AutowareSocketcanBridge::convert_autoware_to_longitudinal_cmd(
  const autoware_control_msgs::msg::Control & control_cmd, float velocity_limit)
{
  uint8_t len, ide;
  auto frame = can_msgs::msg::Frame();
  frame.header.stamp = rclcpp::Clock().now();

  longitudinal_cmd_.set_velocity = control_cmd.longitudinal.velocity;
  longitudinal_cmd_.set_limit_velocity = velocity_limit;

  frame.id =
    Pack_LONGITUDINAL_COMMANDS_autonomous(&longitudinal_cmd_, frame.data.data(), &len, &ide);
  frame.is_extended = ide;
  frame.is_rtr = false;
  frame.dlc = len;

  return frame;
}

can_msgs::msg::Frame AutowareSocketcanBridge::convert_autoware_vehicle_cmd(
  autoware_vehicle_msgs::msg::GearCommand & gear_cmd,
  autoware_vehicle_msgs::msg::TurnIndicatorsCommand & turn_indicators_cmd,
  autoware_vehicle_msgs::msg::HazardLightsCommand & hazard_lights_cmd,
  tier4_vehicle_msgs::msg::VehicleEmergencyStamped & vehicle_emergency_cmd,
  tier4_control_msgs::msg::GateMode & gate_mode_cmd,
  autoware_vehicle_msgs::msg::Engage & engage_cmd)
{
  uint8_t len, ide;
  auto frame = can_msgs::msg::Frame();
  frame.header.stamp = rclcpp::Clock().now();

  if (engage_cmd.engage) {
    if (gate_mode_cmd.data == tier4_control_msgs::msg::GateMode::AUTO) {
      vehicle_cmd_.set_autonomous = 1;
    } else {
      vehicle_cmd_.set_autonomous = 0;
    }
  } else {
    vehicle_cmd_.set_autonomous = 0;
  }

  switch (gear_cmd.command) {
    case autoware_vehicle_msgs::msg::GearCommand::DRIVE:
      vehicle_cmd_.gear = gear_VEHICLE_COMMANDS_D;
      break;
    case autoware_vehicle_msgs::msg::GearCommand::REVERSE:
      vehicle_cmd_.gear = gear_VEHICLE_COMMANDS_R;
      break;
    case autoware_vehicle_msgs::msg::GearCommand::PARK:
      vehicle_cmd_.gear = gear_VEHICLE_COMMANDS_P;
      break;
    case autoware_vehicle_msgs::msg::GearCommand::NEUTRAL:
      vehicle_cmd_.gear = gear_VEHICLE_COMMANDS_N;
      break;
    default:
      break;
  }

  vehicle_cmd_.blinker = blinker_VEHICLE_COMMANDS_NO_BLINKER;

  if (
    turn_indicators_cmd.command ==
    autoware_vehicle_msgs::msg::TurnIndicatorsCommand::ENABLE_RIGHT) {
    vehicle_cmd_.blinker = blinker_VEHICLE_COMMANDS_BLINKER_RIGHT;
  } else if (
    turn_indicators_cmd.command == autoware_vehicle_msgs::msg::TurnIndicatorsCommand::ENABLE_LEFT) {
    vehicle_cmd_.blinker = blinker_VEHICLE_COMMANDS_BLINKER_LEFT;
  }
  if (hazard_lights_cmd.command == autoware_vehicle_msgs::msg::HazardLightsCommand::ENABLE) {
    vehicle_cmd_.blinker = blinker_VEHICLE_COMMANDS_BLINKER_HAZARD;
  }

  vehicle_cmd_.emergency_request = vehicle_emergency_cmd.emergency;

  frame.id = Pack_VEHICLE_COMMANDS_autonomous(&vehicle_cmd_, frame.data.data(), &len, &ide);
  frame.is_extended = ide;
  frame.is_rtr = false;
  frame.dlc = len;

  return frame;
}

}  // namespace leo_vehicle_interface