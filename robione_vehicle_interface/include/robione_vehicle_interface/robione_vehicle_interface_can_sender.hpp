#include "rclcpp/rclcpp.hpp"

#include <diagnostic_updater/diagnostic_updater.hpp>

#include "can_msgs/msg/frame.hpp"
#include <autoware_adapi_v1_msgs/msg/operation_mode_state.hpp>
#include <autoware_adapi_v1_msgs/msg/route_state.hpp>
#include <autoware_control_msgs/msg/control.hpp>
#include <autoware_system_msgs/msg/autoware_state.hpp>
#include <autoware_vehicle_msgs/msg/engage.hpp>
#include <autoware_vehicle_msgs/msg/gear_command.hpp>
#include <autoware_vehicle_msgs/msg/hazard_lights_command.hpp>
#include <autoware_vehicle_msgs/msg/turn_indicators_command.hpp>
#include <autoware_vehicle_msgs/srv/control_mode_command.hpp>
#include <robeff_msgs/msg/gui_to_drc.hpp>
#include <robeff_msgs/msg/sick_zone.hpp>
#include <robione_vehicle_interface_msgs/msg/vehicle_commands.hpp>
#include <robione_vehicle_interface_msgs/msg/vehicle_motion_commands.hpp>
#include <tier4_control_msgs/msg/gate_mode.hpp>
#include <tier4_vehicle_msgs/msg/actuation_command_stamped.hpp>
#include <tier4_vehicle_msgs/msg/vehicle_emergency_stamped.hpp>

namespace robione_vehicle_interface {
class RobioneVehicleInterfaceCanSender : public rclcpp::Node {
public:
  explicit RobioneVehicleInterfaceCanSender(const rclcpp::NodeOptions &options);
  ~RobioneVehicleInterfaceCanSender() override = default;

private:
  void canFrameCallback(const can_msgs::msg::Frame::SharedPtr msg);

  // params
  std::string base_frame_id_;
  float steer_rate_;
  float velocity_limit_;
  float msg_timeout_;

  // diagnostics
  diagnostic_updater::Updater diag_updater_;

  // diagnostic callback
  void diagnostic_callback(diagnostic_updater::DiagnosticStatusWrapper &stat);

  // publishers for debug
  rclcpp::Publisher<
      robione_vehicle_interface_msgs::msg::VehicleMotionCommands>::SharedPtr
      vehicle_motion_cmd_pub_;
  rclcpp::Publisher<robione_vehicle_interface_msgs::msg::VehicleCommands>::
      SharedPtr vehicle_cmd_pub_;

  // subscriptions
  rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr can_frame_pub_;

  // robeff_msgs subscription
  rclcpp::Subscription<robeff_msgs::msg::GuiToDrc>::SharedPtr gui_to_drc_sub_;
  rclcpp::Subscription<robeff_msgs::msg::SickZone>::SharedPtr sick_zone_sub_;

  // From Autoware
  rclcpp::Subscription<autoware_control_msgs::msg::Control>::SharedPtr
      control_cmd_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::GearCommand>::SharedPtr
      gear_cmd_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::TurnIndicatorsCommand>::
      SharedPtr turn_indicators_cmd_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::HazardLightsCommand>::
      SharedPtr hazard_lights_cmd_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::Engage>::SharedPtr
      engage_cmd_sub_;
  rclcpp::Subscription<tier4_control_msgs::msg::GateMode>::SharedPtr
      gate_mode_cmd_sub_;
  rclcpp::Subscription<tier4_vehicle_msgs::msg::VehicleEmergencyStamped>::
      SharedPtr vehicle_emergency_cmd_sub_;
  rclcpp::Subscription<autoware_adapi_v1_msgs::msg::RouteState>::SharedPtr
      sub_route_state_;

  // Callbacks
  void control_cmd_callback(
      const autoware_control_msgs::msg::Control::SharedPtr msg);
  void gear_cmd_callback(
      const autoware_vehicle_msgs::msg::GearCommand::SharedPtr msg);
  void turn_indicators_cmd_callback(
      const autoware_vehicle_msgs::msg::TurnIndicatorsCommand::SharedPtr msg);
  void hazard_lights_cmd_callback(
      const autoware_vehicle_msgs::msg::HazardLightsCommand::SharedPtr msg);
  void
  engage_cmd_callback(const autoware_vehicle_msgs::msg::Engage::SharedPtr msg);
  void gate_mode_cmd_callback(
      const tier4_control_msgs::msg::GateMode::SharedPtr msg);
  void vehicle_emergency_cmd_callback(
      const tier4_vehicle_msgs::msg::VehicleEmergencyStamped::SharedPtr msg);
  void route_state_callback(
      const autoware_adapi_v1_msgs::msg::RouteState::ConstSharedPtr msg);
  void
  gui_to_drc_callback(const robeff_msgs::msg::GuiToDrc::ConstSharedPtr msg);
  void
  sick_zone_callback(const robeff_msgs::msg::SickZone::ConstSharedPtr msg);

  // Received pointers
  autoware_control_msgs::msg::Control::SharedPtr control_cmd_{nullptr};
  autoware_vehicle_msgs::msg::GearCommand::SharedPtr gear_cmd_{nullptr};
  autoware_vehicle_msgs::msg::TurnIndicatorsCommand::SharedPtr
      turn_indicators_cmd_{nullptr};
  autoware_vehicle_msgs::msg::HazardLightsCommand::SharedPtr hazard_lights_cmd_{
      nullptr};
  autoware_vehicle_msgs::msg::Engage::SharedPtr engage_cmd_{nullptr};
  tier4_control_msgs::msg::GateMode::SharedPtr gate_mode_cmd_{nullptr};
  tier4_vehicle_msgs::msg::VehicleEmergencyStamped::SharedPtr
      vehicle_emergency_cmd_{nullptr};
  autoware_adapi_v1_msgs::msg::RouteState::ConstSharedPtr route_state_ptr_{
      nullptr};
  // Timer for can frame publishing
  rclcpp::TimerBase::SharedPtr data_publish_can_timer_;

  // Timer callback
  void data_publish_timer_callback();

  // Timeout checkers
  rclcpp::Time control_cmd_timeout_;
  rclcpp::Time arrived_timer_;
  bool is_control_cmd_timeout_ = false;
  bool is_arrived_triggered = false;
  bool is_restricted_area_detect = false;
};
} // namespace robione_vehicle_interface