#include "can_interface/pc_vcu.h"
#include "robione_vehicle_interface/can_msg_builder/crc.hpp"

#include <rclcpp/rclcpp.hpp>

#include <can_msgs/msg/frame.hpp>

#include <array>
#include <string>

namespace
{
can_msgs::msg::Frame make_motion_frame(
  int16_t tire_angle_raw, int16_t speed_raw, uint8_t alive, bool corrupt_crc)
{
  VCU_STAT_MOTION_SI_t msg{};
  msg.TireAngleRad_Act_ro = tire_angle_raw;
  msg.VehicleSpeedMS_Act_ro = speed_raw;
  msg.Reserved = 0U;
  msg.AliveCounter = alive;
  msg.CRC8 = 0U;

  uint8_t data[8] = {0U};
  uint8_t len = 0U;
  uint8_t ide = 0U;
  Pack_VCU_STAT_MOTION_SI_pc_vcu(&msg, data, &len, &ide);

  uint8_t crc = crc8_autosar(data, 7U);
  if (corrupt_crc) {
    crc ^= 0xFFU;
  }
  data[7] = crc;

  can_msgs::msg::Frame frame;
  frame.id = VCU_STAT_MOTION_SI_CANID;
  frame.is_extended = true;
  frame.dlc = 8U;
  frame.data = {data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]};
  return frame;
}

can_msgs::msg::Frame make_vehicle_state_frame(
  uint8_t gear, bool left, bool right, bool hazard, uint8_t control_mode, uint8_t safety_state,
  uint8_t alive, bool corrupt_crc)
{
  VCU_STAT_VEHICLE_STATE_t msg{};
  msg.GearAct = gear;
  msg.Reserved = 0U;
  msg.TurnLeft_Stat = left ? 1U : 0U;
  msg.TurnRight_Stat = right ? 1U : 0U;
  msg.Hazard_Stat = hazard ? 1U : 0U;
  msg.Horn_Stat = 0U;
  msg.Reserved_1 = 0U;
  msg.ControlMode = control_mode;
  msg.SafetyState = safety_state;
  msg.BatterySoC = 80U;
  msg.FaultSummary = 0U;
  msg.AliveCounter = alive;
  msg.CRC8 = 0U;

  uint8_t data[8] = {0U};
  uint8_t len = 0U;
  uint8_t ide = 0U;
  Pack_VCU_STAT_VEHICLE_STATE_pc_vcu(&msg, data, &len, &ide);

  uint8_t crc = crc8_autosar(data, 7U);
  if (corrupt_crc) {
    crc ^= 0xFFU;
  }
  data[7] = crc;

  can_msgs::msg::Frame frame;
  frame.id = VCU_STAT_VEHICLE_STATE_CANID;
  frame.is_extended = true;
  frame.dlc = 8U;
  frame.data = {data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]};
  return frame;
}
}  // namespace

class CanRxTestPublisher : public rclcpp::Node
{
public:
  CanRxTestPublisher() : rclcpp::Node("can_rx_test_publisher")
  {
    declare_parameter("publish_topic", "/from_can_bus");
    declare_parameter("good_crc", true);
    declare_parameter("good_alive", true);
    declare_parameter("publish_rate_hz", 50.0);
    declare_parameter("vehicle_state_rate_hz", 10.0);

    publish_topic_ = get_parameter("publish_topic").as_string();
    good_crc_ = get_parameter("good_crc").as_bool();
    good_alive_ = get_parameter("good_alive").as_bool();
    const auto rate = get_parameter("publish_rate_hz").as_double();
    const auto state_rate = get_parameter("vehicle_state_rate_hz").as_double();

    publisher_ = create_publisher<can_msgs::msg::Frame>(publish_topic_, rclcpp::QoS(10));

    const auto period = std::chrono::duration<double>(1.0 / std::max(1.0, rate));
    motion_timer_ = create_wall_timer(period, std::bind(&CanRxTestPublisher::on_motion_timer, this));

    const auto state_period = std::chrono::duration<double>(1.0 / std::max(1.0, state_rate));
    state_timer_ = create_wall_timer(
      state_period, std::bind(&CanRxTestPublisher::on_state_timer, this));
  }

private:
  void on_motion_timer()
  {
    const auto alive = alive_counter_motion_;
    const bool corrupt_crc = !good_crc_;

    auto motion_frame = make_motion_frame(100, 200, alive, corrupt_crc);
    motion_frame.header.stamp = now();
    motion_frame.header.frame_id = "can";
    publisher_->publish(motion_frame);

    alive_counter_motion_ =
      static_cast<uint8_t>(alive_counter_motion_ + (good_alive_ ? 1U : 2U));
  }

  void on_state_timer()
  {
    const auto alive = alive_counter_state_;
    const bool corrupt_crc = !good_crc_;

    auto state_frame = make_vehicle_state_frame(2U, true, false, false, 1U, 0U, alive, corrupt_crc);
    state_frame.header.stamp = now();
    state_frame.header.frame_id = "can";
    publisher_->publish(state_frame);

    alive_counter_state_ =
      static_cast<uint8_t>(alive_counter_state_ + (good_alive_ ? 1U : 2U));
  }

  std::string publish_topic_;
  bool good_crc_{true};
  bool good_alive_{true};
  uint8_t alive_counter_motion_{0U};
  uint8_t alive_counter_state_{0U};

  rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr motion_timer_;
  rclcpp::TimerBase::SharedPtr state_timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CanRxTestPublisher>());
  rclcpp::shutdown();
  return 0;
}
