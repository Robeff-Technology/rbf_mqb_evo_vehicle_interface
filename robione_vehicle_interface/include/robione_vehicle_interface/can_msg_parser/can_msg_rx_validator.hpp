#pragma once

#include "robione_vehicle_interface/can_msg_builder/crc.hpp"

#include "can_msgs/msg/frame.hpp"

#include <cstddef>
#include <cstdint>
#include <string>

namespace CanMsgParser
{
struct ValidationResult
{
  bool dlc_ok{true};
  bool crc_ok{true};
  bool alive_ok{true};
  bool first_alive{false};
  uint8_t expected_alive{0U};
  uint8_t received_alive{0U};
  uint8_t calculated_crc{0U};
  uint8_t received_crc{0U};

  bool ok() const { return dlc_ok && crc_ok && alive_ok; }
};

class AliveCrcValidator
{
public:
  AliveCrcValidator(
    uint32_t can_id, std::string name, uint8_t dlc, std::size_t alive_index = 6U,
    std::size_t crc_index = 7U)
  : can_id_{can_id},
    name_{std::move(name)},
    dlc_{dlc},
    alive_index_{alive_index},
    crc_index_{crc_index}
  {
  }

  const std::string & name() const { return name_; }
  uint32_t can_id() const { return can_id_; }
  uint32_t frame_count() const { return frame_count_; }
  uint32_t dlc_error_count() const { return dlc_error_count_; }
  uint32_t crc_error_count() const { return crc_error_count_; }
  uint32_t alive_error_count() const { return alive_error_count_; }

  ValidationResult validate(const can_msgs::msg::Frame & frame)
  {
    ValidationResult result;

    frame_count_++;

    if (frame.dlc < dlc_ || alive_index_ >= frame.data.size() || crc_index_ >= frame.data.size()) {
      result.dlc_ok = false;
      result.alive_ok = false;
      result.crc_ok = false;
      dlc_error_count_++;
      return result;
    }

    result.received_alive = frame.data[alive_index_];
    result.received_crc = frame.data[crc_index_];

    result.calculated_crc = crc8_autosar(frame.data.data(), crc_index_);
    result.crc_ok = (result.calculated_crc == result.received_crc);
    if (!result.crc_ok) {
      crc_error_count_++;
    }

    if (!alive_seen_) {
      alive_seen_ = true;
      last_alive_ = result.received_alive;
      result.first_alive = true;
      return result;
    }

    result.expected_alive = static_cast<uint8_t>(last_alive_ + 1U);
    result.alive_ok = (result.received_alive == result.expected_alive);
    if (!result.alive_ok) {
      alive_error_count_++;
    }
    last_alive_ = result.received_alive;

    return result;
  }

  std::string format_message(const ValidationResult & result) const
  {
    if (!result.dlc_ok) {
      return "dlc mismatch";
    }

    std::string msg;
    if (!result.crc_ok) {
      msg += "crc8 mismatch";
    }
    if (!result.alive_ok && !result.first_alive) {
      if (!msg.empty()) {
        msg += ", ";
      }
      msg += "alive counter mismatch";
    }

    if (msg.empty()) {
      msg = "ok";
    }

    return msg;
  }

private:
  uint32_t can_id_{0U};
  std::string name_;
  uint8_t dlc_{8U};
  std::size_t alive_index_{6U};
  std::size_t crc_index_{7U};

  bool alive_seen_{false};
  uint8_t last_alive_{0U};
  uint32_t frame_count_{0U};
  uint32_t dlc_error_count_{0U};
  uint32_t crc_error_count_{0U};
  uint32_t alive_error_count_{0U};
};
}  // namespace CanMsgParser
