#include "robione_vehicle_interface/autoware_socketcan_bridge.hpp"

#include "rclcpp/rclcpp.hpp"

#include <cmath>

namespace robione_vehicle_interface
{

VEHICLE_COMMANDS_t vehicle_cmd_{};
VEHICLE_MOTION_COMMANDS_t vehicle_motion_cmd_{};

const double degree_to_radian = M_PI / 180.0;
const double radian_to_degree = 180.0 / M_PI;

const double mps_to_kph = 3.6;
const double kph_to_mps = 1.0 / mps_to_kph;

autoware_vehicle_msgs::msg::ControlModeReport
AutowareSocketcanBridge::convert_to_autoware_control_mode_report(
  const VEHICLE_STATUS_t & control_mode_report)
{
  autoware_vehicle_msgs::msg::ControlModeReport control_mode_report_msg;
  control_mode_report_msg.stamp = rclcpp::Clock().now();

  if (control_mode_report.mode == mode_VEHICLE_STATUS_CONTROLLER_AUTONOMOUS) {
    control_mode_report_msg.mode = autoware_vehicle_msgs::msg::ControlModeReport::AUTONOMOUS;
  } else {
    control_mode_report_msg.mode = autoware_vehicle_msgs::msg::ControlModeReport::MANUAL;
  }
  return control_mode_report_msg;
}

autoware_vehicle_msgs::msg::GearReport AutowareSocketcanBridge::convert_to_autoware_gear_report(
  const VEHICLE_STATUS_t & gear_report)
{
  autoware_vehicle_msgs::msg::GearReport gear_report_msg;
  gear_report_msg.stamp = rclcpp::Clock().now();

  if (gear_report.gear == gear_VEHICLE_STATUS_GEAR_D) {
    gear_report_msg.report = autoware_vehicle_msgs::msg::GearReport::DRIVE;
  } else if (gear_report.gear == gear_VEHICLE_STATUS_GEAR_R) {
    gear_report_msg.report = autoware_vehicle_msgs::msg::GearReport::REVERSE;
  } else if (gear_report.gear == gear_VEHICLE_STATUS_GEAR_P) {
    gear_report_msg.report = autoware_vehicle_msgs::msg::GearReport::PARK;
  } else if (gear_report.gear == gear_VEHICLE_STATUS_GEAR_N) {
    gear_report_msg.report = autoware_vehicle_msgs::msg::GearReport::NEUTRAL;
  } else {
    gear_report_msg.report = autoware_vehicle_msgs::msg::GearReport::NONE;
  }

  return gear_report_msg;
}

autoware_vehicle_msgs::msg::HazardLightsReport
AutowareSocketcanBridge::convert_to_autoware_hazard_light_report(
  const VEHICLE_STATUS_t & hazard_lights_report)
{
  autoware_vehicle_msgs::msg::HazardLightsReport hazard_lights_report_msg;
  hazard_lights_report_msg.stamp = rclcpp::Clock().now();

  if (hazard_lights_report.blinker == blinker_VEHICLE_STATUS_HAZARD_LIGHT) {
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
  const VEHICLE_STATUS_t & turn_indicators_report)
{
  autoware_vehicle_msgs::msg::TurnIndicatorsReport turn_indicators_report_msg;
  turn_indicators_report_msg.stamp = rclcpp::Clock().now();

  if (turn_indicators_report.blinker == blinker_VEHICLE_STATUS_BLINKER_RIGHT) {
    turn_indicators_report_msg.report =
      autoware_vehicle_msgs::msg::TurnIndicatorsReport::ENABLE_RIGHT;
  } else if (turn_indicators_report.blinker == blinker_VEHICLE_STATUS_BLINKER_LEFT) {
    turn_indicators_report_msg.report =
      autoware_vehicle_msgs::msg::TurnIndicatorsReport::ENABLE_LEFT;
  } else {
    turn_indicators_report_msg.report = autoware_vehicle_msgs::msg::TurnIndicatorsReport::DISABLE;
  }

  return turn_indicators_report_msg;
}

autoware_vehicle_msgs::msg::VelocityReport
AutowareSocketcanBridge::convert_to_autoware_velocity_report(
  const VEHICLE_INFO_t & vehicle_info,
  std::string base_link)
{
  autoware_vehicle_msgs::msg::VelocityReport velocity_report_msg;
  velocity_report_msg.header.frame_id = base_link;
  velocity_report_msg.header.stamp = rclcpp::Clock().now();

  velocity_report_msg.longitudinal_velocity = vehicle_info.vehicle_velocity_phys;

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

/* ## Is this necessary? There is nothing about throttle and brake in DBC file
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
*/

robione_vehicle_interface_msgs::msg::VehicleMotionCommands
AutowareSocketcanBridge::convert_to_vehicle_motion_cmd()
{
  robione_vehicle_interface_msgs::msg::VehicleMotionCommands vehicle_motion_cmd_msg;
  vehicle_motion_cmd_msg.stamp = rclcpp::Clock().now();

  vehicle_motion_cmd_msg.set_front_wheel_tire_angle = vehicle_motion_cmd_.set_front_wheel_tire_angle_phys;
  vehicle_motion_cmd_msg.set_front_wheel_angle_rate = vehicle_motion_cmd_.set_front_wheel_angle_rate_phys;
  vehicle_motion_cmd_msg.set_velocity = vehicle_motion_cmd_.set_velocity_phys;
  vehicle_motion_cmd_msg.set_limit_velocity = vehicle_motion_cmd_.set_limit_velocity_phys;

  return vehicle_motion_cmd_msg;
}

robione_vehicle_interface_msgs::msg::VehicleCommands AutowareSocketcanBridge::convert_to_vehicle_cmd()
{
  robione_vehicle_interface_msgs::msg::VehicleCommands vehicle_cmd_msg;
  vehicle_cmd_msg.stamp = rclcpp::Clock().now();

  vehicle_cmd_msg.set_autonomous = vehicle_cmd_.set_autonomous;
  vehicle_cmd_msg.blinker = vehicle_cmd_.blinker;
  vehicle_cmd_msg.headlight = vehicle_cmd_.headlight;
  vehicle_cmd_msg.gear = vehicle_cmd_.gear;
  vehicle_cmd_msg.handbrake = vehicle_cmd_.hand_brake;
  vehicle_cmd_msg.emergency = vehicle_cmd_.emergency_request;
  vehicle_cmd_msg.horn = vehicle_cmd_.horn;

  return vehicle_cmd_msg;
}

can_msgs::msg::Frame AutowareSocketcanBridge::convert_autoware_to_vehicle_motion_cmd(
  const autoware_control_msgs::msg::Control & control_cmd, float velocity_limit, float tire_rate)
{
  uint8_t len, ide;
  auto frame = can_msgs::msg::Frame();
  frame.header.stamp = rclcpp::Clock().now();

  vehicle_motion_cmd_.set_velocity_phys = control_cmd.longitudinal.velocity;
  vehicle_motion_cmd_.set_limit_velocity_phys = velocity_limit;
  vehicle_motion_cmd_.set_front_wheel_tire_angle_phys = control_cmd.lateral.steering_tire_angle;
  
  // Check if tire rate is defined
  if (control_cmd.lateral.is_defined_steering_tire_rotation_rate == false) {
    vehicle_motion_cmd_.set_front_wheel_angle_rate_phys = tire_rate;
  } else {
    vehicle_motion_cmd_.set_front_wheel_angle_rate_phys = control_cmd.lateral.steering_tire_rotation_rate;
  }

  frame.id = Pack_VEHICLE_MOTION_COMMANDS_vcu(&vehicle_motion_cmd_, frame.data.data(), &len, &ide);
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
  autoware_vehicle_msgs::msg::Engage & engage_cmd,
  bool horn_activate)
{
  uint8_t len, ide;
  auto frame = can_msgs::msg::Frame();
  frame.header.stamp = rclcpp::Clock().now();

  vehicle_cmd_.set_autonomous = 1;
  vehicle_cmd_.horn = horn_activate;
  vehicle_cmd_.blinker = blinker_VEHICLE_COMMANDS_NO_BLINKER;
  // Set Blinker
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

  // Set Headlight
  vehicle_cmd_.headlight = headlight_VEHICLE_COMMANDS_HEADLIGHT_CLOSE;

  // Set Handbrake
  vehicle_cmd_.hand_brake = hand_brake_VEHICLE_COMMANDS_HANDBRAKE_RELEASE;

  // Set Gear
  switch (gear_cmd.command) {
    case autoware_vehicle_msgs::msg::GearCommand::DRIVE:
      vehicle_cmd_.gear = gear_VEHICLE_COMMANDS_GEAR_D;
      break;
    case autoware_vehicle_msgs::msg::GearCommand::REVERSE:
      vehicle_cmd_.gear = gear_VEHICLE_COMMANDS_GEAR_R;
      break;
    case autoware_vehicle_msgs::msg::GearCommand::PARK:
      vehicle_cmd_.gear = gear_VEHICLE_COMMANDS_GEAR_P;
      vehicle_cmd_.hand_brake = hand_brake_VEHICLE_COMMANDS_HANDBRAKE_PRESS;
      break;
    case autoware_vehicle_msgs::msg::GearCommand::NEUTRAL:
      vehicle_cmd_.gear = gear_VEHICLE_COMMANDS_GEAR_N;
      vehicle_cmd_.hand_brake = hand_brake_VEHICLE_COMMANDS_HANDBRAKE_PRESS;
      break;
    default:
      break;
  }
  


  // Set Emergency Request
  vehicle_cmd_.emergency_request = vehicle_emergency_cmd.emergency;

  // Set Horn
  vehicle_cmd_.horn = horn_VEHICLE_COMMANDS_HORN_CLOSE;

  frame.id = Pack_VEHICLE_COMMANDS_vcu(&vehicle_cmd_, frame.data.data(), &len, &ide);
  frame.is_extended = ide;
  frame.is_rtr = false;
  frame.dlc = len;

  return frame;
}

can_msgs::msg::Frame AutowareSocketcanBridge::convert_vehicle_interface_life_signal()
{
  uint8_t len, ide;
  auto frame = can_msgs::msg::Frame();
  frame.header.stamp = rclcpp::Clock().now();
  VEHICLE_INTERFACE_LIFE_SIGNAL_t vehicle_interface_life_signal;
  vehicle_interface_life_signal.life_signal = rclcpp::Clock().now().nanoseconds();

  frame.id = Pack_VEHICLE_INTERFACE_LIFE_SIGNAL_vcu(&vehicle_interface_life_signal, frame.data.data(), &len, &ide);
  frame.is_extended = ide;
  frame.is_rtr = false;
  frame.dlc = len;

  return frame;
}

}  // namespace robione_vehicle_interface