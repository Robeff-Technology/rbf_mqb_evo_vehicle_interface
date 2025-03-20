// Generator version : v3.1
// DBC filename      : robione_autonomous_pc.dbc
#include "vcu-binutil.h"

// DBC file version
#if (VER_VCU_MAJ != (0U)) || (VER_VCU_MIN != (0U))
#error The VCU binutil source file has inconsistency with core dbc lib!
#endif

#ifdef __DEF_VCU__

vcu_rx_t vcu_rx;

#endif // __DEF_VCU__

uint32_t vcu_Receive(vcu_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_)
{
 uint32_t recid = 0;
 if ((_id >= 0x1DEF0411U) && (_id < 0x1DEFB000U)) {
  if (_id == 0x1DEF0411U) {
   recid = Unpack_VEHICLE_INFO_VCU(&(_m->VEHICLE_INFO), _d, dlc_);
  } else if (_id == 0x1DEF0412U) {
   recid = Unpack_VEHICLE_STATUS_VCU(&(_m->VEHICLE_STATUS), _d, dlc_);
  }
 } else {
  if (_id == 0x1DEFB000U) {
   recid = Unpack_VEHICLE_MOTION_COMMANDS_VCU(&(_m->VEHICLE_MOTION_COMMANDS), _d, dlc_);
  } else if (_id == 0x1DEFB001U) {
   recid = Unpack_VEHICLE_COMMANDS_VCU(&(_m->VEHICLE_COMMANDS), _d, dlc_);
  }
 }

 return recid;
}

