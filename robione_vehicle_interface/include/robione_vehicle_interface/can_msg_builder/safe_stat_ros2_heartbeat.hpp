#pragma once

#include "can_interface/pc_vcu.h"
#include "crc.hpp"
#include "robione_vehicle_interface/can_msg_builder/can_msg_builder_interface.hpp"

#include <array>
#include <cstdint>
#include <cstring>

namespace CanMsgBuilder
{
class SafeStatRos2Heartbeat : public ICanMessageBuilder
{
public:
  explicit SafeStatRos2Heartbeat() { std::memset(&msg_, 0, sizeof(msg_)); }

  // -------------------------------------------------------------------------
  // Setters
  // -------------------------------------------------------------------------
  void set_ros_time_ms(uint64_t ms)
  {
    msg_.ROS_Time_ms = (ms & 0x0000FFFFFFFFFFFFULL);
  }

  void set_ros_time_from_now()
  {
    msg_.ROS_Time_ms = static_cast<uint64_t>(now().nanoseconds() / 1000000ULL);
  }

  void set_alive_counter(uint8_t counter) { msg_.AliveCounter = counter; }

  // -------------------------------------------------------------------------
  // Getters
  // -------------------------------------------------------------------------
  uint64_t get_ros_time_ms() const { return msg_.ROS_Time_ms; }
  uint8_t get_alive_counter() const { return msg_.AliveCounter; }
  uint8_t get_crc8() const { return msg_.CRC8; }

  void * get_message_struct() override { return &msg_; }
  uint32_t get_can_id() const override { return SAFE_STAT_ROS2_HEARTBEAT_CANID; }

protected:
  // =========================================================================
  // Internal Data Builder
  // =========================================================================

  /**
   * @brief Packs SAFE_STAT_ROS2_HEARTBEAT message into CAN frame buffer.
   *
   * @param frame_out Output CAN payload array.
   * @return CAN ID for this message.
   */
  uint32_t build(std::array<uint8_t, 8> & frame_out) override
  {
    uint8_t len = 0U;
    uint8_t ide = 0U;

    // pack without CRC first
    Pack_SAFE_STAT_ROS2_HEARTBEAT_pc_vcu(&msg_, frame_out.data(), &len, &ide);

    // compute CRC over Byte0..Byte6
    msg_.CRC8 = crc8_autosar(frame_out.data(), SAFE_STAT_ROS2_HEARTBEAT_DLC - 1U);

    // repack including CRC
    Pack_SAFE_STAT_ROS2_HEARTBEAT_pc_vcu(&msg_, frame_out.data(), &len, &ide);

    // increment after sending so first frame uses 0
    msg_.AliveCounter = static_cast<uint8_t>((msg_.AliveCounter + 1U) & 0xFFU);

    return get_can_id();
  }

private:
  SAFE_STAT_ROS2_HEARTBEAT_t msg_;
};
}  // namespace CanMsgBuilder
