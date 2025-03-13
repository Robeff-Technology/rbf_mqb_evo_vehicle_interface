// Copyright 2025 LeoDrive.
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

#ifndef LEO_VEHICLE_INTERFACE_CAN_RECV_HPP
#define LEO_VEHICLE_INTERFACE_CAN_RECV_HPP

#include "can_interface/flux-binutil.h"
#include "can_interface/autonomous-binutil.h"
#include "rclcpp/rclcpp.hpp"

#include <diagnostic_updater/diagnostic_updater.hpp>

#include "can_msgs/msg/frame.hpp"
#include "flux_pds_msgs/msg/bus_status.hpp"
#include "flux_pds_msgs/msg/channel_consumptions.hpp"
#include "flux_pds_msgs/msg/channel_currents.hpp"
#include "flux_pds_msgs/msg/channel_status.hpp"
#include "leo_vehicle_interface_msgs/msg/control_mechanism_temps.hpp"
#include "leo_vehicle_interface_msgs/msg/control_mechanism_volts.hpp"
#include "leo_vehicle_interface_msgs/msg/dynamic_sensor_frame.hpp"
#include "leo_vehicle_interface_msgs/msg/motion_info.hpp"
#include "leo_vehicle_interface_msgs/msg/motor_info.hpp"
#include "leo_vehicle_interface_msgs/msg/throttle_module_status.hpp"
#include "leo_vehicle_interface_msgs/msg/vehicle_errors.hpp"
#include "leo_vehicle_interface_msgs/msg/vehicle_info.hpp"
#include "leo_vehicle_interface_msgs/msg/vehicle_signal_status.hpp"
#include "leo_vehicle_interface_msgs/msg/wheel_speeds.hpp"
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

namespace leo_vehicle_interface
{
class LeoVehicleInterfaceCanReceiver : public rclcpp::Node
{
public:
  explicit LeoVehicleInterfaceCanReceiver(const rclcpp::NodeOptions & options);

  ~LeoVehicleInterfaceCanReceiver() override = default;

  /**
   * @brief It receives interface message from socketcan ROS2 bridge
   */
  void can_receive_callback(can_msgs::msg::Frame::SharedPtr msg);

private:
  // from CAN interface
  rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr can_frame_sub_;

  // diagnostics
  diagnostic_updater::Updater diag_updater_;

  // messages send to computer
  rclcpp::Publisher<leo_vehicle_interface_msgs::msg::ControlMechanismTemps>::SharedPtr
    control_mechanism_temps_pub_;
  rclcpp::Publisher<leo_vehicle_interface_msgs::msg::ControlMechanismVolts>::SharedPtr
    control_mechanism_volts_pub_;
  rclcpp::Publisher<leo_vehicle_interface_msgs::msg::DynamicSensorFrame>::SharedPtr
    dynamic_sensor_frame_pub_;
  rclcpp::Publisher<leo_vehicle_interface_msgs::msg::MotionInfo>::SharedPtr motion_info_pub_;
  rclcpp::Publisher<leo_vehicle_interface_msgs::msg::MotorInfo>::SharedPtr motor_info_pub_;
  rclcpp::Publisher<leo_vehicle_interface_msgs::msg::ThrottleModuleStatus>::SharedPtr
    throttle_module_status_pub_;
  rclcpp::Publisher<leo_vehicle_interface_msgs::msg::VehicleErrors>::SharedPtr vehicle_errors_pub_;
  rclcpp::Publisher<leo_vehicle_interface_msgs::msg::VehicleInfo>::SharedPtr vehicle_info_pub_;
  rclcpp::Publisher<leo_vehicle_interface_msgs::msg::VehicleSignalStatus>::SharedPtr
    vehicle_signal_status_pub_;
  rclcpp::Publisher<leo_vehicle_interface_msgs::msg::WheelSpeeds>::SharedPtr wheel_speeds_pub_;

  rclcpp::Publisher<flux_pds_msgs::msg::BusStatus>::SharedPtr flux_bus_status_pub_;
  rclcpp::Publisher<flux_pds_msgs::msg::ChannelConsumptions>::SharedPtr
    flux_channel_consumptions_pub_;
  rclcpp::Publisher<flux_pds_msgs::msg::ChannelCurrents>::SharedPtr flux_channel_currents_pub_;
  rclcpp::Publisher<flux_pds_msgs::msg::ChannelStatus>::SharedPtr flux_channel_status_pub_;

  autonomous_rx_t autonomous_rx_;
  flux_rx_t flux_rx_;

  // sending messages functions
  void publish_control_mechanism_temps(const CONTROL_MECHANISM_TEMPS_t & control_mechanism_temps);
  void publish_control_mechanism_volts(const CONTROL_MECHANISM_VOLTS_t & control_mechanism_volts);
  void publish_dynamic_sensor_frame(const DYNAMIC_SENSOR_FRAME_t & dynamic_sensor_frame);
  void publish_motion_info(const MOTION_INFO_t & motion_info);
  void publish_motor_info(const MOTOR_INFO_t & motor_info);
  void publish_throttle_module_status(const THROTTLE_MODULE_STATUS_t & throttle_module_status);
  void publish_vehicle_errors(const VEHICLE_ERRORS_t & vehicle_errors);
  void publish_vehicle_info(const VEHICLE_INFO_t & vehicle_info);
  void publish_vehicle_signal_status(const VEHICLE_SIGNAL_STATUS_t & vehicle_signal_status);
  void publish_wheel_speeds(const WHEEL_SPEEDS_t & wheel_speeds);

  void publish_flux_bus_status(const BUS_STATUS_MSG_t & bus_status);
  void publish_flux_channel_status(const CHANNEL_STATUS_MSG_t & channel_status);
  void publish_flux_channel_currents(
    const CURRENTS_1_MSG_t & currents_1, const CURRENTS_2_MSG_t & currents_2,
    const CURRENTS_3_MSG_t & currents_3);

  void publish_flux_channel_consumptions(
    const CONSUMPTION_1_MSG_t & consumptions_1, const CONSUMPTION_2_MSG_t & consumptions_2,
    const CONSUMPTION_3_MSG_t & consumptions_3);

  // diagnostic callback
  void diagnostic_callback(diagnostic_updater::DiagnosticStatusWrapper & stat);

  // receive messages timestamp
  rclcpp::Time receive_time_control_mechanism_temps_;
  rclcpp::Time receive_time_control_mechanism_volts_;
  rclcpp::Time receive_time_dynamic_sensor_frame_;
  rclcpp::Time receive_time_motion_info_;
  rclcpp::Time receive_time_motor_info_;
  rclcpp::Time receive_time_throttle_module_status_;

  rclcpp::Time receive_time_vehicle_errors_;
  rclcpp::Time receive_time_vehicle_info_;
  rclcpp::Time receive_time_vehicle_signal_status_;
  rclcpp::Time receive_time_wheel_speeds_;

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
  rclcpp::Publisher<tier4_vehicle_msgs::msg::ActuationStatusStamped>::SharedPtr
    actuation_status_pub_;
  // Timer
  rclcpp::TimerBase::SharedPtr data_publish_timer_;
  // Timer callback
  void data_publish_timer_callback();
};
}  // namespace leo_vehicle_interface
#endif  // LEO_VEHICLE_INTERFACE_CAN_RECV_HPP