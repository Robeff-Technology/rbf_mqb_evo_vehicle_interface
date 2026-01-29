// Generator version : v3.1
// DBC filename      : pc_vcu_can_500k_v1.dbc
#include "pc_vcu-binutil.h"

// DBC file version
#if (VER_PC_VCU_MAJ != (0U)) || (VER_PC_VCU_MIN != (0U))
#error The PC_VCU binutil source file has inconsistency with core dbc lib!
#endif

#ifdef __DEF_PC_VCU__

pc_vcu_rx_t pc_vcu_rx;

#endif  // __DEF_PC_VCU__

uint32_t pc_vcu_Receive(pc_vcu_rx_t * _m, const uint8_t * _d, uint32_t _id, uint8_t dlc_)
{
  uint32_t recid = 0;
  if ((_id >= 0x1DEF0410U) && (_id < 0x1DEFB000U)) {
    if (_id == 0x1DEF0410U) {
      recid = Unpack_VCU_STAT_MOTION_SI_pc_vcu(&(_m->VCU_STAT_MOTION_SI), _d, dlc_);
    } else if (_id == 0x1DEF0411U) {
      recid = Unpack_VCU_STAT_VEHICLE_STATE_pc_vcu(&(_m->VCU_STAT_VEHICLE_STATE), _d, dlc_);
    }
  } else {
    if (_id == 0x1DEFB000U) {
      recid = Unpack_VCU_CTRL_CMD_SI_pc_vcu(&(_m->VCU_CTRL_CMD_SI), _d, dlc_);
    } else if (_id == 0x1DEFB001U) {
      recid = Unpack_SAFE_STAT_ROS2_HEARTBEAT_pc_vcu(&(_m->SAFE_STAT_ROS2_HEARTBEAT), _d, dlc_);
    }
  }

  return recid;
}
