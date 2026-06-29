// Generator version : v3.1
// DBC filename      : pc_vcu_can_500k_v1.dbc
#include "pc_vcu-binutil.h"

// DBC file version
#if (VER_PC_VCU_MAJ != (0U)) || (VER_PC_VCU_MIN != (0U))
#error The PC_VCU binutil source file has inconsistency with core dbc lib!
#endif

#ifdef __DEF_PC_VCU__

pc_vcu_rx_t pc_vcu_rx;

#endif // __DEF_PC_VCU__

uint32_t pc_vcu_Receive(pc_vcu_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_)
{
 uint32_t recid = 0;
 if ((_id >= 0x10001U) && (_id < 0xC150010U)) {
  if ((_id >= 0x10001U) && (_id < 0x40A0001U)) {
   if (_id == 0x10001U) {
    recid = Unpack_SAFETY_MANAGER_STATUS_pc_vcu(&(_m->SAFETY_MANAGER_STATUS), _d, dlc_);
   } else if (_id == 0x510E1U) {
    recid = Unpack_BATTERY_STATUS_pc_vcu(&(_m->BATTERY_STATUS), _d, dlc_);
   }
  } else {
   if (_id == 0x40A0001U) {
    recid = Unpack_VCU_CTRL_CMD_SI_pc_vcu(&(_m->VCU_CTRL_CMD_SI), _d, dlc_);
   } else if (_id == 0x80A000FU) {
    recid = Unpack_SAFE_STAT_ROS2_HEARTBEAT_pc_vcu(&(_m->SAFE_STAT_ROS2_HEARTBEAT), _d, dlc_);
   }
  }
 } else {
  if ((_id >= 0xC150010U) && (_id < 0x10120001U)) {
   if (_id == 0xC150010U) {
    recid = Unpack_VCU_STAT_MOTION_SI_pc_vcu(&(_m->VCU_STAT_MOTION_SI), _d, dlc_);
   } else if (_id == 0xC150011U) {
    recid = Unpack_VCU_STAT_VEHICLE_STATE_pc_vcu(&(_m->VCU_STAT_VEHICLE_STATE), _d, dlc_);
   }
  } else {
   if (_id == 0x10120001U) {
    recid = Unpack_MCU_MODULE_STATUS_pc_vcu(&(_m->MCU_MODULE_STATUS), _d, dlc_);
   } else {
    if (_id == 0x10300100U) {
     recid = Unpack_DTC_ERROR_STATUS_pc_vcu(&(_m->DTC_ERROR_STATUS), _d, dlc_);
    } else if (_id == 0x10300101U) {
     recid = Unpack_DTC_ERROR_STATUS_1_pc_vcu(&(_m->DTC_ERROR_STATUS_1), _d, dlc_);
    }
   }
  }
 }

 return recid;
}

