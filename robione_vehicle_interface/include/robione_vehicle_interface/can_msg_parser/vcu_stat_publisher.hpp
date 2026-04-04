#pragma once

#include "can_interface/pc_vcu.h"

#include <rclcpp/rclcpp.hpp>

#include <autoware_vehicle_msgs/msg/control_mode_report.hpp>
#include <autoware_vehicle_msgs/msg/gear_report.hpp>
#include <autoware_vehicle_msgs/msg/hazard_lights_report.hpp>
#include <autoware_vehicle_msgs/msg/steering_report.hpp>
#include <autoware_vehicle_msgs/msg/turn_indicators_report.hpp>
#include <autoware_vehicle_msgs/msg/velocity_report.hpp>
#include <tier4_vehicle_msgs/msg/battery_status.hpp>
#include <tier4_vehicle_msgs/msg/steering_wheel_status_stamped.hpp>

namespace CanMsgParser
{
class VcuStatPublisher
{
public:
  void configure(
    rclcpp::Node & node,
    const rclcpp::Publisher<autoware_vehicle_msgs::msg::ControlModeReport>::SharedPtr &
      control_mode_pub,
    const rclcpp::Publisher<autoware_vehicle_msgs::msg::VelocityReport>::SharedPtr & velocity_pub,
    const rclcpp::Publisher<autoware_vehicle_msgs::msg::SteeringReport>::SharedPtr & steering_pub,
    const rclcpp::Publisher<autoware_vehicle_msgs::msg::GearReport>::SharedPtr & gear_pub,
    const rclcpp::Publisher<autoware_vehicle_msgs::msg::TurnIndicatorsReport>::SharedPtr & turn_pub,
    const rclcpp::Publisher<autoware_vehicle_msgs::msg::HazardLightsReport>::SharedPtr & hazard_pub,
    const rclcpp::Publisher<tier4_vehicle_msgs::msg::BatteryStatus>::SharedPtr & battery_pub,
    const rclcpp::Publisher<tier4_vehicle_msgs::msg::SteeringWheelStatusStamped>::SharedPtr &
      steer_st,
    const std::string & base_frame_id)
  {
    clock_ = node.get_clock();
    control_mode_pub_ = control_mode_pub;
    velocity_pub_ = velocity_pub;
    steering_pub_ = steering_pub;
    gear_pub_ = gear_pub;
    turn_pub_ = turn_pub;
    hazard_pub_ = hazard_pub;
    battery_pub_ = battery_pub;
    steer_st_ = steer_st;
    base_frame_id_ = base_frame_id;
  }

  void publish_motion(const VCU_STAT_MOTION_SI_t & stat) const
  {
    if (!velocity_pub_ || !steering_pub_ || !steer_st_) {
      return;
    }

    const auto stamp = clock_ ? clock_->now() : rclcpp::Clock().now();

    autoware_vehicle_msgs::msg::VelocityReport velocity_report;
    velocity_report.header.stamp = stamp;
    velocity_report.header.frame_id = base_frame_id_;
    velocity_report.longitudinal_velocity = static_cast<float>(stat.VehicleSpeedMS_Act_phys);
    velocity_report.lateral_velocity = 0.0F;
    velocity_report.heading_rate = 0.0F;
    velocity_pub_->publish(velocity_report);

    autoware_vehicle_msgs::msg::SteeringReport steering_report;
    steering_report.stamp = stamp;
    steering_report.steering_tire_angle = static_cast<float>(stat.TireAngleRad_Act_phys);
    steering_pub_->publish(steering_report);

    tier4_vehicle_msgs::msg::SteeringWheelStatusStamped steer_wheel_status;
    steer_wheel_status.stamp = stamp;
    steer_wheel_status.data = static_cast<float>(stat.SteerAngleDeg_Act);
    steer_st_->publish(steer_wheel_status);
  }

  void publish_vehicle_state(const VCU_STAT_VEHICLE_STATE_t & stat) const
  {
    if (!control_mode_pub_ || !gear_pub_ || !turn_pub_ || !hazard_pub_ || !battery_pub_) {
      return;
    }

    const auto stamp = clock_ ? clock_->now() : rclcpp::Clock().now();

    autoware_vehicle_msgs::msg::ControlModeReport control_mode_report;
    control_mode_report.stamp = stamp;
    control_mode_report.mode = map_control_mode(stat.ControlMode);
    control_mode_pub_->publish(control_mode_report);

    autoware_vehicle_msgs::msg::GearReport gear_report;
    gear_report.stamp = stamp;
    gear_report.report = stat.GearAct;
    gear_pub_->publish(gear_report);

    autoware_vehicle_msgs::msg::TurnIndicatorsReport turn_report;
    turn_report.stamp = stamp;
    if (stat.TurnLeft_Stat) {
      turn_report.report = autoware_vehicle_msgs::msg::TurnIndicatorsReport::ENABLE_LEFT;
    } else if (stat.TurnRight_Stat) {
      turn_report.report = autoware_vehicle_msgs::msg::TurnIndicatorsReport::ENABLE_RIGHT;
    } else {
      turn_report.report = autoware_vehicle_msgs::msg::TurnIndicatorsReport::DISABLE;
    }
    turn_pub_->publish(turn_report);

    autoware_vehicle_msgs::msg::HazardLightsReport hazard_report;
    hazard_report.stamp = stamp;
    hazard_report.report = stat.Hazard_Stat
                             ? autoware_vehicle_msgs::msg::HazardLightsReport::ENABLE
                             : autoware_vehicle_msgs::msg::HazardLightsReport::DISABLE;
    hazard_pub_->publish(hazard_report);

    tier4_vehicle_msgs::msg::BatteryStatus battery_status;
    battery_status.stamp = stamp;
    battery_status.energy_level = static_cast<float>(stat.BatterySoC) / 100.0F;
    battery_pub_->publish(battery_status);
  }

private:
  static uint8_t map_control_mode(uint8_t control_mode)
  {
    switch (control_mode) {
      case 1U:
        return autoware_vehicle_msgs::msg::ControlModeReport::MANUAL;
      case 2U:
        return autoware_vehicle_msgs::msg::ControlModeReport::AUTONOMOUS;
      case 0U:
      case 3U:
      case 4U:
        return autoware_vehicle_msgs::msg::ControlModeReport::DISENGAGED;
      default:
        return autoware_vehicle_msgs::msg::ControlModeReport::NO_COMMAND;
    }
  }

  rclcpp::Clock::SharedPtr clock_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::ControlModeReport>::SharedPtr control_mode_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::VelocityReport>::SharedPtr velocity_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::SteeringReport>::SharedPtr steering_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::GearReport>::SharedPtr gear_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::TurnIndicatorsReport>::SharedPtr turn_pub_;
  rclcpp::Publisher<autoware_vehicle_msgs::msg::HazardLightsReport>::SharedPtr hazard_pub_;
  rclcpp::Publisher<tier4_vehicle_msgs::msg::BatteryStatus>::SharedPtr battery_pub_;
  rclcpp::Publisher<tier4_vehicle_msgs::msg::SteeringWheelStatusStamped>::SharedPtr steer_st_;
  std::string base_frame_id_;
};
}  // namespace CanMsgParser
