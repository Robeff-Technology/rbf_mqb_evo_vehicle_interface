#pragma once

#include "can_interface/vehicle_cmd_status_module_dbc.h"
#include "crc.hpp"
#include "rbf_mqb_evo_vehicle_interface/can_msg_builder/can_msg_builder_interface.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstring>

namespace CanMsgBuilder
{
class VcuCtrlCmdSi : public ICanMessageBuilder
{
public:
  /// @brief Constructor
  /// @param max_throttle Maximum physical throttle value (e.g. pedal voltage or
  /// %)
  /// @param max_brake Maximum physical brake value
  explicit VcuCtrlCmdSi() { std::memset(&msg_, 0, sizeof(msg_)); }

  enum class GearReq : uint8_t {
    NONE = SC_Gear_SPEED_CONTROL_MSG_NONE,
    NEUTRAL = SC_Gear_SPEED_CONTROL_MSG_NEUTRAL,
    DRIVE = SC_Gear_SPEED_CONTROL_MSG_DRIVE,
    REVERSE = SC_Gear_SPEED_CONTROL_MSG_REVERSE,
    PARK = SC_Gear_SPEED_CONTROL_MSG_PARK,
  };

  // -------------------------------------------------------------------------
  // Setters (physical units)
  // -------------------------------------------------------------------------
  void set_tire_angle_rad_cmd(double rad) { msg_.SC_TireAngleRad_Cmd_phys = rad; }

  void set_vehicle_speed_ms_cmd(double ms) { msg_.SC_VehicleSpeedMS_Cmd_phys = ms; }

  void set_autonomous_enable(bool enable) { msg_.SC_Enable = enable; }
  void set_emergency_active(bool active) { msg_.SC_Emergency = active ? 1U : 0U; }

  void set_gear_req(GearReq gear) { msg_.SC_Gear = static_cast<uint8_t>(gear); }
  void set_gear_req_raw(uint8_t gear) { msg_.SC_Gear = gear; }

  void set_communication_fault(bool fault)
  {
    autoware_comm_fault_ = fault;
    can_comm_fault_ = fault;
  }
  void set_autoware_comm_fault(bool fault) { autoware_comm_fault_ = fault; }
  void set_can_comm_fault(bool fault) { can_comm_fault_ = fault; }

  void set_alive_counter(uint8_t counter) { msg_.SC_AliveCounter = counter; }

  // -------------------------------------------------------------------------
  // Getters (physical units)
  // -------------------------------------------------------------------------
  double get_tire_angle_rad_cmd() const { return msg_.SC_TireAngleRad_Cmd_phys; }

  double get_vehicle_speed_ms_cmd() const { return msg_.SC_VehicleSpeedMS_Cmd_phys; }

  bool get_autonomous_enable() const { return msg_.SC_Enable != 0U; }
  bool get_emergency_active() const { return msg_.SC_Emergency != 0U; }
  uint8_t get_gear_req() const { return msg_.SC_Gear; }

  uint8_t get_alive_counter() const { return msg_.SC_AliveCounter; }

  void * get_message_struct() override { return &msg_; }
  uint32_t get_can_id() const override { return SPEED_CONTROL_MSG_CANID; }

protected:
  // =========================================================================
  // Internal Data Builder
  // =========================================================================

  /**
   * @brief Packs custom gas/brake message into CAN frame buffer.
   *
   * @param frame_out Output CAN payload array.
   * @return CAN ID for this message.
   */
  uint32_t build(std::array<uint8_t, 8> & frame_out) override
  {
    uint8_t len = 0U;
    uint8_t ide = 0U;

    // Work on a copy so the fault override never destroys the commanded state:
    // otherwise a transient fault would latch SC_Enable/SC_Gear forever.
    SPEED_CONTROL_MSG_t tx = msg_;

    if (autoware_comm_fault_ || can_comm_fault_) {
      tx.SC_VehicleSpeedMS_Cmd_phys = 0.0;

      // SC_Enable is intentionally NOT cleared here: the VCU must stay in
      // autonomous mode so it can act on the safe-stop request below.
      tx.SC_Emergency = 1U;

      tx.SC_Gear = static_cast<uint8_t>(GearReq::PARK);
    }

    tx.SC_Reserved = 0U;

    // pack without CRC first
    Pack_SPEED_CONTROL_MSG_vehicle_cmd_status_module_dbc(&tx, frame_out.data(), &len, &ide);

    // compute CRC over Byte0..Byte6
    tx.SC_Crc8 = crc8_autosar(frame_out.data(), SPEED_CONTROL_MSG_DLC - 1U);

    // repack including CRC
    Pack_SPEED_CONTROL_MSG_vehicle_cmd_status_module_dbc(&tx, frame_out.data(), &len, &ide);

    // increment after sending so first frame uses 0
    msg_.SC_AliveCounter = static_cast<uint8_t>((msg_.SC_AliveCounter + 1U) & 0xFFU);
    return get_can_id();
  }

private:
  SPEED_CONTROL_MSG_t msg_;
  bool autoware_comm_fault_{false};
  bool can_comm_fault_{false};
};
}  // namespace CanMsgBuilder