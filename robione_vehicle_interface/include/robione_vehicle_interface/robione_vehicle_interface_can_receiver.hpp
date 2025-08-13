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

namespace robione_vehicle_interface
{
class RobioneVehicleInterfaceCanReceiver : public rclcpp::Node
{
public:
  explicit RobioneVehicleInterfaceCanReceiver(const rclcpp::NodeOptions & options);

  ~RobioneVehicleInterfaceCanReceiver() override = default;

  /**
   * @brief It receives interface message from socketcan ROS2 bridge
   */
  void can_receive_callback(can_msgs::msg::Frame::SharedPtr msg);

private:
  // from CAN interface
  rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr can_frame_sub_;

  // diagnostics
  diagnostic_updater::Updater diag_updater_;

  rclcpp::Publisher<robione_vehicle_interface_msgs::msg::VehicleInfo>::SharedPtr vehicle_info_pub_;
  rclcpp::Publisher<robione_vehicle_interface_msgs::msg::VehicleStatus>::SharedPtr
    vehicle_status_pub_;

  vcu_rx_t vcu_rx_;

  void publish_vehicle_info(const VEHICLE_INFO_t & vehicle_info);
  void publish_vehicle_status(const VEHICLE_STATUS_t & vehicle_signal_status);
  // void publish_wheel_speeds(const WHEEL_SPEEDS_t & wheel_speeds);

  // diagnostic callback
  void diagnostic_callback(diagnostic_updater::DiagnosticStatusWrapper & stat);

  // receive messages timestamp

  rclcpp::Time receive_time_vehicle_info_;
  rclcpp::Time receive_time_vehicle_status_;

  // params
  double can_recv_timeout_threshold_;
  unsigned int data_publish_rate_;
  std::string base_frame_id_;

  /* Publishers */
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
  // rclcpp::Publisher<tier4_vehicle_msgs::msg::ActuationStatusStamped>::SharedPtr
  //   actuation_status_pub_;
  // Timer
  rclcpp::TimerBase::SharedPtr data_publish_timer_;
  // Timer callback
  void data_publish_timer_callback();
};
}  // namespace robione_vehicle_interface
#endif  // ROBIONE_VEHICLE_INTERFACE_CAN_RECV_HPP