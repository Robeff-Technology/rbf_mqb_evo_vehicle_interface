// Copyright 2025 Robeff.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef ROBIONE_VEHICLE_INTERFACE_CAN_RECV_HPP
#define ROBIONE_VEHICLE_INTERFACE_CAN_RECV_HPP

#include "can_interface/vcu-binutil.h"
#include "rclcpp/rclcpp.hpp"

#include <diagnostic_updater/diagnostic_updater.hpp>

#include "can_msgs/msg/frame.hpp"
#include <autoware_adapi_v1_msgs/msg/operation_mode_state.hpp>
#include <autoware_adapi_v1_msgs/msg/route_state.hpp>
#include "robione_vehicle_interface_msgs/msg/vehicle_info.hpp"
#include "robione_vehicle_interface_msgs/msg/vehicle_status.hpp"
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
#include <robeff_msgs/msg/sick_zone.hpp>
#include <robeff_msgs/msg/tablet_feedback.hpp>
#include <robione_vehicle_interface_msgs/msg/vehicle_commands.hpp>
#include <robione_vehicle_interface_msgs/msg/vehicle_motion_commands.hpp>
#include <diagnostic_msgs/msg/diagnostic_status.hpp>
#include <tier4_control_msgs/msg/gate_mode.hpp>
#include <tier4_vehicle_msgs/msg/actuation_command_stamped.hpp>
#include <tier4_vehicle_msgs/msg/actuation_status_stamped.hpp>
#include <tier4_vehicle_msgs/msg/steering_wheel_status_stamped.hpp>
#include <tier4_vehicle_msgs/msg/vehicle_emergency_stamped.hpp>

#include <linux/can.h>

#include <bitset>
#include <string>
#include <vector>

// TODO List
// -> Constructor'lari birlestir
// -> Destructor

namespace robione_vehicle_interface
{
class RobioneVehicleInterface : public rclcpp::Node
{
public:

  explicit RobioneVehicleInterface(const rclcpp::NodeOptions & options);

  ~RobioneVehicleInterface() override = default;

  /**
   * @brief It receives interface message from socketcan ROS2 bridge
   */
  void can_receive_callback(can_msgs::msg::Frame::SharedPtr msg);

private:

  void canFrameCallback(const can_msgs::msg::Frame::SharedPtr msg);

  // params
  //  receiver
  double can_recv_timeout_threshold_;
  unsigned int data_publish_rate_;
  std::string base_frame_id_;

  //  sender
  float steer_rate_;
  float velocity_limit_;
  float msg_timeout_;

  // from CAN interface
  rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr can_frame_sub_;
  
  // diagnostics
  diagnostic_updater::Updater diag_updater_sender_;
  diagnostic_updater::Updater diag_updater_receiver_;
  // ASK IF THE DESIGN AND NAMING ARE TRUE
  
  // diagnostic callback
  void sender_diagnostic_callback(diagnostic_updater::DiagnosticStatusWrapper & stat);
  void receiver_diagnostic_callback(diagnostic_updater::DiagnosticStatusWrapper & stat);

  rclcpp::Publisher<robione_vehicle_interface_msgs::msg::VehicleInfo>::SharedPtr vehicle_info_pub_;
  rclcpp::Publisher<robione_vehicle_interface_msgs::msg::VehicleStatus>::SharedPtr
    vehicle_status_pub_;

  vcu_rx_t vcu_rx_; // receiver

  void publish_vehicle_info(const VEHICLE_INFO_t & vehicle_info);
  void publish_vehicle_status(const VEHICLE_STATUS_t & vehicle_signal_status);
  // void publish_wheel_speeds(const WHEEL_SPEEDS_t & wheel_speeds); ? IS IT NECESSARY

  
  // receive messages timestamp
  rclcpp::Time receive_time_vehicle_info_;
  rclcpp::Time receive_time_vehicle_status_;

  // subscriptions
  rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr can_frame_pub_;
  
  // robeff_msgs subscription
  rclcpp::Subscription<robeff_msgs::msg::TabletFeedback>::SharedPtr tablet_feedback_sub_;
  rclcpp::Subscription<robeff_msgs::msg::SickZone>::SharedPtr sick_zone_sub_;

  // From Autoware
  rclcpp::Subscription<autoware_control_msgs::msg::Control>::SharedPtr control_cmd_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::GearCommand>::SharedPtr gear_cmd_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::TurnIndicatorsCommand>::SharedPtr
    turn_indicators_cmd_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::HazardLightsCommand>::SharedPtr
    hazard_lights_cmd_sub_;
  rclcpp::Subscription<tier4_vehicle_msgs::msg::VehicleEmergencyStamped>::SharedPtr
    vehicle_emergency_cmd_sub_;
  rclcpp::Subscription<autoware_adapi_v1_msgs::msg::RouteState>::SharedPtr sub_route_state_;


  /* Publishers */

  // publishers for debug
  rclcpp::Publisher<robione_vehicle_interface_msgs::msg::VehicleMotionCommands>::SharedPtr
    vehicle_motion_cmd_pub_;
  rclcpp::Publisher<robione_vehicle_interface_msgs::msg::VehicleCommands>::SharedPtr
    vehicle_cmd_pub_;

  // To Autoware
  rclcpp::Publisher<autoware_vehicle_msgs::msg::ControlModeReport>::SharedPtr control_mode_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::VelocityReport>::SharedPtr vehicle_twist_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::SteeringReport>::SharedPtr steering_status_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::GearReport>::SharedPtr gear_status_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::TurnIndicatorsReport>::SharedPtr
    turn_indicators_status_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::HazardLightsReport>::SharedPtr
    hazard_lights_status_pub_;
  rclcpp::Publisher<tier4_vehicle_msgs::msg::SteeringWheelStatusStamped>::SharedPtr
    steering_wheel_status_pub_;


  // Timer
  rclcpp::TimerBase::SharedPtr data_publish_timer_;
  rclcpp::TimerBase::SharedPtr data_publish_can_timer_; // from sender
  // Timer callback
  void data_publish_timer_callback();
  void data_publish_can_timer_callback();
  // Check if timers can be reduced to one or not. If no, add a second timer so that they can work independantly


  // Callbacks
  void control_cmd_callback(const autoware_control_msgs::msg::Control::SharedPtr msg);
  void gear_cmd_callback(const autoware_vehicle_msgs::msg::GearCommand::SharedPtr msg);
  void turn_indicators_cmd_callback(
    const autoware_vehicle_msgs::msg::TurnIndicatorsCommand::SharedPtr msg);
  void hazard_lights_cmd_callback(
    const autoware_vehicle_msgs::msg::HazardLightsCommand::SharedPtr msg);
  void vehicle_emergency_cmd_callback(
    const tier4_vehicle_msgs::msg::VehicleEmergencyStamped::SharedPtr msg);
  void route_state_callback(const autoware_adapi_v1_msgs::msg::RouteState::ConstSharedPtr msg);
  void tablet_feedback_callback(const robeff_msgs::msg::TabletFeedback::ConstSharedPtr msg);
  void sick_zone_callback(const robeff_msgs::msg::SickZone::ConstSharedPtr msg);

  // Received pointers
  autoware_control_msgs::msg::Control::SharedPtr control_cmd_{nullptr};
  autoware_vehicle_msgs::msg::GearCommand::SharedPtr gear_cmd_{nullptr};
  autoware_vehicle_msgs::msg::TurnIndicatorsCommand::SharedPtr turn_indicators_cmd_{nullptr};
  autoware_vehicle_msgs::msg::HazardLightsCommand::SharedPtr hazard_lights_cmd_{nullptr};
  tier4_vehicle_msgs::msg::VehicleEmergencyStamped::SharedPtr vehicle_emergency_cmd_{nullptr};
  autoware_adapi_v1_msgs::msg::RouteState::ConstSharedPtr route_state_ptr_{nullptr};

  // Timeout checkers
  rclcpp::Time control_cmd_timeout_;
  rclcpp::Time arrived_timer_;
  bool is_control_cmd_timeout_ = false;
  bool is_arrived_triggered = false;
  bool is_restricted_area_detect = false;

};
}  // namespace robione_vehicle_interface

#endif  // ROBIONE_VEHICLE_INTERFACE_CAN_RECV_HPP
