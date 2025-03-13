#include "can_interface/autonomous-binutil.h"

#include "can_msgs/msg/frame.hpp"
#include <autoware_adapi_v1_msgs/msg/operation_mode_state.hpp>
#include <autoware_control_msgs/msg/control.hpp>
#include <autoware_vehicle_msgs/msg/control_mode_report.hpp>
#include <autoware_vehicle_msgs/msg/engage.hpp>
#include <autoware_vehicle_msgs/msg/gear_command.hpp>
#include <autoware_vehicle_msgs/msg/gear_report.hpp>
#include <autoware_vehicle_msgs/msg/hazard_lights_command.hpp>
#include <autoware_vehicle_msgs/msg/hazard_lights_report.hpp>
#include <autoware_vehicle_msgs/msg/steering_report.hpp>
#include <autoware_vehicle_msgs/msg/turn_indicators_command.hpp>
#include <autoware_vehicle_msgs/msg/turn_indicators_report.hpp>
#include <autoware_vehicle_msgs/msg/velocity_report.hpp>
#include <diagnostic_msgs/msg/diagnostic_status.hpp>
#include <leo_vehicle_interface_msgs/msg/front_wheel_command.hpp>
#include <leo_vehicle_interface_msgs/msg/longitudinal_command.hpp>
#include <leo_vehicle_interface_msgs/msg/vehicle_command.hpp>
#include <tier4_control_msgs/msg/gate_mode.hpp>
#include <tier4_vehicle_msgs/msg/actuation_command_stamped.hpp>
#include <tier4_vehicle_msgs/msg/actuation_status_stamped.hpp>
#include <tier4_vehicle_msgs/msg/steering_wheel_status_stamped.hpp>
#include <tier4_vehicle_msgs/msg/vehicle_emergency_stamped.hpp>

#include <cstring>

namespace leo_vehicle_interface
{
class AutowareSocketcanBridge
{
public:
  static autoware_vehicle_msgs::msg::ControlModeReport convert_to_autoware_control_mode_report(
    const VEHICLE_SIGNAL_STATUS_t & control_mode_report);
  static autoware_vehicle_msgs::msg::GearReport convert_to_autoware_gear_report(
    const VEHICLE_SIGNAL_STATUS_t & gear_report);
  static autoware_vehicle_msgs::msg::HazardLightsReport convert_to_autoware_hazard_light_report(
    const VEHICLE_SIGNAL_STATUS_t & hazard_lights_report);
  static autoware_vehicle_msgs::msg::SteeringReport convert_to_autoware_steering_report(
    const VEHICLE_INFO_t & steering_report);
  static autoware_vehicle_msgs::msg::TurnIndicatorsReport
  convert_to_autoware_turn_indicators_report(
    const VEHICLE_SIGNAL_STATUS_t & turn_indicators_report);
  static autoware_vehicle_msgs::msg::VelocityReport convert_to_autoware_velocity_report(
    const VEHICLE_INFO_t & velocity_report, const VEHICLE_SIGNAL_STATUS_t & gear_report,
    std::string base_link);

  static tier4_vehicle_msgs::msg::SteeringWheelStatusStamped convert_to_tier4_steering_wheel_status(
    const VEHICLE_INFO_t & steering_wheel_status);
  static tier4_vehicle_msgs::msg::ActuationStatusStamped convert_to_tier4_actuation_status(
    const MOTION_INFO_t & actuation_status, std::string base_link);
  static tier4_vehicle_msgs::msg::VehicleEmergencyStamped convert_to_tier4_vehicle_emergency(
    const VEHICLE_INFO_t & vehicle_emergency);

  static can_msgs::msg::Frame convert_autoware_to_front_wheel_cmd(
    const autoware_control_msgs::msg::Control & control_cmd, float tire_rate);

  static can_msgs::msg::Frame convert_autoware_to_longitudinal_cmd(
    const autoware_control_msgs::msg::Control & control_cmd, float velocity_limit);

  static can_msgs::msg::Frame convert_autoware_vehicle_cmd(
    autoware_vehicle_msgs::msg::GearCommand & gear_cmd,
    autoware_vehicle_msgs::msg::TurnIndicatorsCommand & turn_indicators_cmd,
    autoware_vehicle_msgs::msg::HazardLightsCommand & hazard_lights_cmd,
    tier4_vehicle_msgs::msg::VehicleEmergencyStamped & vehicle_emergency_cmd,
    tier4_control_msgs::msg::GateMode & operation_mode_state,
    autoware_vehicle_msgs::msg::Engage & engage_cmd);

  static leo_vehicle_interface_msgs::msg::FrontWheelCommand convert_to_front_wheel_cmd();
  static leo_vehicle_interface_msgs::msg::LongitudinalCommand convert_to_longitudinal_cmd();
  static leo_vehicle_interface_msgs::msg::VehicleCommand convert_to_vehicle_cmd();
};
}  // namespace leo_vehicle_interface