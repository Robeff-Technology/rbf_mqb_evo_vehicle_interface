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
    NONE = GearReq_VCU_CTRL_CMD_SI_NONE,
    NEUTRAL = GearReq_VCU_CTRL_CMD_SI_NEUTRAL,
    DRIVE = GearReq_VCU_CTRL_CMD_SI_DRIVE,
    REVERSE = GearReq_VCU_CTRL_CMD_SI_REVERSE,
    PARK = GearReq_VCU_CTRL_CMD_SI_PARK,
  };

  // -------------------------------------------------------------------------
  // Setters (physical units)
  // -------------------------------------------------------------------------
  void set_tire_angle_rad_cmd(double rad) { msg_.TireAngleRad_Cmd_phys = rad; }

  void set_vehicle_speed_ms_cmd(double ms) { msg_.VehicleSpeedMS_Cmd_phys = ms; }

  void set_autonomous_enable(bool enable) { msg_.AutonomousEnable = enable; }
  void set_emergency_active(bool active) { msg_.EmergencyActive = active ? 1U : 0U; }

  void set_gear_req(GearReq gear) { msg_.GearReq = static_cast<uint8_t>(gear); }
  void set_gear_req_raw(uint8_t gear) { msg_.GearReq = gear; }

  void set_communication_fault(bool fault)
  {
    autoware_comm_fault_ = fault;
    can_comm_fault_ = fault;
  }
  void set_autoware_comm_fault(bool fault) { autoware_comm_fault_ = fault; }
  void set_can_comm_fault(bool fault) { can_comm_fault_ = fault; }

  void set_alive_counter(uint8_t counter) { msg_.AliveCounter = counter; }

  // -------------------------------------------------------------------------
  // Getters (physical units)
  // -------------------------------------------------------------------------
  double get_tire_angle_rad_cmd() const { return msg_.TireAngleRad_Cmd_phys; }

  double get_vehicle_speed_ms_cmd() const { return msg_.VehicleSpeedMS_Cmd_phys; }

  bool get_autonomous_enable() const { return msg_.AutonomousEnable != 0U; }
  bool get_emergency_active() const { return msg_.EmergencyActive != 0U; }
  uint8_t get_gear_req() const { return msg_.GearReq; }

  uint8_t get_alive_counter() const { return msg_.AliveCounter; }

  void * get_message_struct() override { return &msg_; }
  uint32_t get_can_id() const override { return VCU_CTRL_CMD_SI_CANID; }

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
    // otherwise a transient fault would latch AutonomousEnable/GearReq forever.
    VCU_CTRL_CMD_SI_t tx = msg_;

    if (autoware_comm_fault_ || can_comm_fault_) {
      tx.VehicleSpeedMS_Cmd_phys = 0.0;

      // AutonomousEnable is intentionally NOT cleared here: the VCU must stay in
      // autonomous mode so it can act on the safe-stop request below.
      tx.EmergencyActive = 1U;

      tx.GearReq = static_cast<uint8_t>(GearReq::PARK);
    }

    tx.Reserved = 0U;

    // pack without CRC first
    Pack_VCU_CTRL_CMD_SI_vehicle_cmd_status_module_dbc(&tx, frame_out.data(), &len, &ide);

    // compute CRC over Byte0..Byte6
    tx.CRC8 = crc8_autosar(frame_out.data(), VCU_CTRL_CMD_SI_DLC - 1U);

    // repack including CRC
    Pack_VCU_CTRL_CMD_SI_vehicle_cmd_status_module_dbc(&tx, frame_out.data(), &len, &ide);

    // increment after sending so first frame uses 0
    msg_.AliveCounter = static_cast<uint8_t>((msg_.AliveCounter + 1U) & 0xFFU);
    return get_can_id();
  }

private:
  VCU_CTRL_CMD_SI_t msg_;
  bool autoware_comm_fault_{false};
  bool can_comm_fault_{false};
};
}  // namespace CanMsgBuilder