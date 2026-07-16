#pragma once

#include "rclcpp/rclcpp.hpp"

#include "can_msgs/msg/frame.hpp"

#include <array>
#include <cstdint>

namespace CanMsgBuilder
{

class ICanMessageBuilder
{
public:
  virtual ~ICanMessageBuilder() = default;

  /// @brief Return internal struct pointer (DBC packer fills it)
  virtual void * get_message_struct() = 0;

  /// @brief Return CAN identifier
  virtual uint32_t get_can_id() const = 0;

  can_msgs::msg::Frame build_can_frame()
  {
    can_msgs::msg::Frame frame;
    frame.header.frame_id = "can";
    frame.header.stamp = now();

    std::array<uint8_t, 8> payload{};
    frame.id = build(payload);

    frame.dlc = 8;
    frame.is_rtr = false;
    frame.is_error = false;
    frame.is_extended = frame.id > 0x7FF;
    frame.data = payload;

    return frame;
  }

protected:
  /// @brief Low-level builder that fills raw CAN data array
  virtual uint32_t build(std::array<uint8_t, 8> & out_data) = 0;

  /// @brief Timestamp helper for derived classes
  static rclcpp::Time now() { return rclcpp::Clock().now(); }
};

}  // namespace CanMsgBuilder