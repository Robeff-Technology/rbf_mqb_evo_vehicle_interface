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

#ifndef RBF_MQB_EVO_VEHICLE_INTERFACE_CAN_RECV_HPP
#define RBF_MQB_EVO_VEHICLE_INTERFACE_CAN_RECV_HPP

#include "can_interface/vehicle_cmd_status_module_dbc-binutil.h"
#include "rclcpp/rclcpp.hpp"
#include <diagnostic_updater/diagnostic_updater.hpp>
#include <rbf_mqb_evo_vehicle_interface/can_msg_builder/safe_stat_ros2_heartbeat.hpp>
#include <rbf_mqb_evo_vehicle_interface/can_msg_builder/vcu_ctrl_cmd_si.hpp>
#include <rbf_mqb_evo_vehicle_interface/can_msg_parser/can_msg_rx_validator.hpp>
#include <rbf_mqb_evo_vehicle_interface/can_msg_parser/vcu_stat_publisher.hpp>
#include <rbf_mqb_evo_vehicle_interface/param_loader.hpp>
#include <rbf_mqb_evo_vehicle_interface/scheduler.hpp>

#include "can_msgs/msg/frame.hpp"
#include <autoware_control_msgs/msg/control.hpp>
#include <autoware_vehicle_msgs/msg/control_mode_report.hpp>
#include <autoware_vehicle_msgs/msg/gear_command.hpp>
#include <autoware_vehicle_msgs/msg/gear_report.hpp>
#include <autoware_vehicle_msgs/msg/hazard_lights_report.hpp>
#include <autoware_vehicle_msgs/msg/steering_report.hpp>
#include <autoware_vehicle_msgs/msg/turn_indicators_report.hpp>
#include <autoware_vehicle_msgs/msg/velocity_report.hpp>
#include <diagnostic_msgs/msg/diagnostic_status.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <tier4_vehicle_msgs/msg/steering_wheel_status_stamped.hpp>
#include <tier4_vehicle_msgs/msg/vehicle_emergency_stamped.hpp>

#include <linux/can.h>

#include <bitset>
#include <string>
#include <unordered_map>
#include <vector>

// TODO List
// -> Constructor'lari birlestir
// -> Destructor

namespace rbf_mqb_evo_vehicle_interface
{

struct CanWatchdog
{
  rclcpp::Time last_rx = rclcpp::Time(static_cast<int64_t>(0), RCL_ROS_TIME);
  bool seen{false};
};

struct RateWatch
{
  rclcpp::Time last = rclcpp::Time(static_cast<int64_t>(0), RCL_ROS_TIME);
  bool seen{false};
  double last_hz{0.0};

  static constexpr size_t WINDOW_SIZE = 10;
  std::array<double, WINDOW_SIZE> dt_history{};
  size_t dt_index{0};
  size_t dt_count{0};
};

class RateMonitor
{
public:
  enum class Status : uint8_t {
    OK = 0,
    WARN_RATE_OUT_OF_RANGE = 1,
    ERROR_STALE = 2,
    ERROR_MISSING = 3,
  };

  RateMonitor() = default;

  RateMonitor(std::initializer_list<std::pair<std::string, double>> targets)
  {
    for (const auto & t : targets) {
      entries_[t.first].expected_hz = t.second;
    }
  }

  void add_target(const std::string & name, double expected_hz)
  {
    entries_[name].expected_hz = expected_hz;
  }

  bool any_seen() const
  {
    for (const auto & kv : entries_) {
      if (kv.second.watch.seen) {
        return true;
      }
    }
    return false;
  }

  void update(const std::string & name, const rclcpp::Time & now_time)
  {
    auto & entry = entries_[name];
    auto & w = entry.watch;

    if (w.seen) {
      const double dt = (now_time - w.last).seconds();
      if (dt > 0.0) {
        // Hareketli ortalama için dt'yi kaydet
        w.dt_history[w.dt_index] = dt;
        w.dt_index = (w.dt_index + 1) % w.WINDOW_SIZE;
        if (w.dt_count < w.WINDOW_SIZE) {
          w.dt_count++;
        }

        // Ortalama dt hesapla
        double sum_dt = 0.0;
        for (size_t i = 0; i < w.dt_count; ++i) {
          sum_dt += w.dt_history[i];
        }
        const double avg_dt = sum_dt / w.dt_count;
        
        // Ortalama dt'den frekans hesapla
        w.last_hz = 1.0 / avg_dt;
      }
    }

    w.last = now_time;
    w.seen = true;
  }

  Status report(
    diagnostic_updater::DiagnosticStatusWrapper & stat, const rclcpp::Time & now_time,
    bool & generate_emergency, bool set_summary = true, bool skip_disabled = false) const
  {
    generate_emergency = false;
    Status status = Status::OK;
    if (set_summary) {
      stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Command rates ok");
    }

    if (entries_.empty()) {
      stat.add("rate_targets", "empty");
      return status;
    }

    for (const auto & kv : entries_) {
      const auto & name = kv.first;
      const auto & entry = kv.second;
      const auto & w = entry.watch;
      const double expected_hz = entry.expected_hz;

      if (expected_hz <= 0.0) {
        if (!skip_disabled) {
          stat.addf(name, "disabled (expected %.2f Hz)", expected_hz);
        }
        continue;
      }

      if (!w.seen) {
        stat.mergeSummary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "CMD missing");
        stat.addf(name, "never received (expected %.2f Hz)", expected_hz);
        status = Status::ERROR_MISSING;
        generate_emergency = true;
        continue;
      }

      const double age = (now_time - w.last).seconds();
      const double max_age = 2.0 / expected_hz;  // allow up to 2x period
      if (age > max_age) {
        stat.mergeSummary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "CMD stale");
        stat.addf(name, "stale: %.3fs (timeout %.3fs)", age, max_age);
        if (status != Status::ERROR_MISSING) {
          status = Status::ERROR_STALE;
        }
        generate_emergency = true;
        continue;
      }

      const double min_hz = expected_hz * 0.9;
      const double max_hz = expected_hz * 1.1;

      if (w.last_hz < min_hz || w.last_hz > max_hz) {
        generate_emergency = true;
        stat.mergeSummary(diagnostic_msgs::msg::DiagnosticStatus::WARN, "CMD rate out of range");
        stat.addf(
          name, "%.2f Hz (expected %.2f Hz, range %.2f-%.2f Hz)", w.last_hz, expected_hz, min_hz,
          max_hz);
        if (status == Status::OK) {
          status = Status::WARN_RATE_OUT_OF_RANGE;
        }
      } else {
        stat.addf(name, "%.2f Hz (expected %.2f Hz)", w.last_hz, expected_hz);
      }
    }

    return status;
  }

private:
  struct Entry
  {
    RateWatch watch;
    double expected_hz{0.0};
  };

  std::unordered_map<std::string, Entry> entries_;
};

class RbfMqbEvoVehicleInterface : public rclcpp::Node
{
public:
  explicit RbfMqbEvoVehicleInterface(const rclcpp::NodeOptions & options);

  ~RbfMqbEvoVehicleInterface() override = default;

  /**
   * @brief It receives interface message from socketcan ROS2 bridge
   */
  void can_receive_callback(can_msgs::msg::Frame::SharedPtr msg);

private:
  // Parameters
  ParamLoader params_;

  // Scheduler
  RateScheduler scheduler_;  // 100 Hz base tick
                             // Timer for can frame publishing
  rclcpp::TimerBase::SharedPtr timer_100Hz_;



  // from CAN interface
  rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr can_frame_sub_;

  vehicle_cmd_status_module_dbc_rx_t vehicle_cmd_status_module_dbc_rx_;  // receiver

  // Can Msg Builders
  CanMsgBuilder::VcuCtrlCmdSi vcu_ctrl_cmd_si_builder_;
  CanMsgBuilder::SafeStatRos2Heartbeat safe_stat_ros2_heartbeat_builder_;

  // CAN RX to Autoware publishers
  CanMsgParser::VcuStatPublisher vcu_stat_publisher_;

  // diagnostics
  diagnostic_updater::Updater diag_updater_;

  // CAN RX validators
  std::unordered_map<uint32_t, CanMsgParser::AliveCrcValidator> rx_validators_;
  std::unordered_map<uint32_t, CanWatchdog> can_watchdog_;
  // From Autoware
  rclcpp::Subscription<autoware_control_msgs::msg::Control>::SharedPtr control_cmd_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::GearCommand>::SharedPtr gear_cmd_sub_;
  rclcpp::Subscription<tier4_vehicle_msgs::msg::VehicleEmergencyStamped>::SharedPtr
    vehicle_emergency_cmd_sub_;

  /* Publishers */

  // Can Frame publisher
  rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr can_frame_pub_;

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

  /* Services */

  // Sends a single CLEAR_INTERVENTION_CMD CAN frame when triggered
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr clear_intervention_srv_;

  // Callbacks
  void control_cmd_callback(const autoware_control_msgs::msg::Control::SharedPtr msg);
  void gear_cmd_callback(const autoware_vehicle_msgs::msg::GearCommand::SharedPtr msg);
  void vehicle_emergency_cmd_callback(
    const tier4_vehicle_msgs::msg::VehicleEmergencyStamped::SharedPtr msg);
  void clear_intervention_callback(
    const std_srvs::srv::Trigger::Request::SharedPtr request,
    std_srvs::srv::Trigger::Response::SharedPtr response);

  // Init helpers
  void init_subscribers();
  void init_publishers();
  void init_services();

  // diagnostic callback
  void diagnostic_can_callback(diagnostic_updater::DiagnosticStatusWrapper & stat);
  void diagnostic_cmd_rate_callback(diagnostic_updater::DiagnosticStatusWrapper & stat);

  RateMonitor cmd_rate_monitor_;
  RateMonitor can_rate_monitor_;

  // Tasks
  void task_20ms();
  void task_50ms();
};
}  // namespace rbf_mqb_evo_vehicle_interface

#endif  // RBF_MQB_EVO_VEHICLE_INTERFACE_CAN_RECV_HPP
