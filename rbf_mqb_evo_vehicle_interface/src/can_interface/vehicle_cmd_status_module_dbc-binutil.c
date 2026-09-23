// Generator version : v3.1
// DBC filename      : vehicle_cmd_status_dbc.dbc
#include "vehicle_cmd_status_module_dbc-binutil.h"

// DBC file version
#if (VER_VEHICLE_CMD_STATUS_MODULE_DBC_MAJ != (0U)) || (VER_VEHICLE_CMD_STATUS_MODULE_DBC_MIN != (0U))
#error The VEHICLE_CMD_STATUS_MODULE_DBC binutil source file has inconsistency with core dbc lib!
#endif

#ifdef __DEF_VEHICLE_CMD_STATUS_MODULE_DBC__

vehicle_cmd_status_module_dbc_rx_t vehicle_cmd_status_module_dbc_rx;

#endif // __DEF_VEHICLE_CMD_STATUS_MODULE_DBC__

uint32_t vehicle_cmd_status_module_dbc_Receive(vehicle_cmd_status_module_dbc_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_)
{
 uint32_t recid = 0;
 if ((_id >= 0x40A0001U) && (_id < 0xC150010U)) {
  if (_id == 0x40A0001U) {
   recid = Unpack_SPEED_CONTROL_MSG_vehicle_cmd_status_module_dbc(&(_m->SPEED_CONTROL_MSG), _d, dlc_);
  } else if (_id == 0x40A0002U) {
   recid = Unpack_CLEAR_INTERVENTION_CMD_vehicle_cmd_status_module_dbc(&(_m->CLEAR_INTERVENTION_CMD), _d, dlc_);
  } else {
   if (_id == 0x4331002U) {
    recid = Unpack_DIRECT_CONTROL_MSG_vehicle_cmd_status_module_dbc(&(_m->DIRECT_CONTROL_MSG), _d, dlc_);
   } else if (_id == 0x80A000FU) {
    recid = Unpack_SAFE_STAT_ROS2_HEARTBEAT_vehicle_cmd_status_module_dbc(&(_m->SAFE_STAT_ROS2_HEARTBEAT), _d, dlc_);
   }
  }
 } else {
  if (_id == 0xC150010U) {
   recid = Unpack_VCU_STAT_MOTION_SI_vehicle_cmd_status_module_dbc(&(_m->VCU_STAT_MOTION_SI), _d, dlc_);
  } else {
   if (_id == 0xC150011U) {
    recid = Unpack_VCU_STAT_VEHICLE_STATE_vehicle_cmd_status_module_dbc(&(_m->VCU_STAT_VEHICLE_STATE), _d, dlc_);
   } else if (_id == 0xC150012U) {
    recid = Unpack_VCU_STAT_COMM_STATUS_vehicle_cmd_status_module_dbc(&(_m->VCU_STAT_COMM_STATUS), _d, dlc_);
   } else if (_id == 0xC150013U) {
    recid = Unpack_VCU_STAT_DYNAMICS_SI_vehicle_cmd_status_module_dbc(&(_m->VCU_STAT_DYNAMICS_SI), _d, dlc_);
   } else if (_id == 0xC150014U) {
    recid = Unpack_VCU_STAT_QUEUE_DROPS_vehicle_cmd_status_module_dbc(&(_m->VCU_STAT_QUEUE_DROPS), _d, dlc_);
   } else if (_id == 0xC150015U) {
    recid = Unpack_VCU_STAT_TX_DROPS_vehicle_cmd_status_module_dbc(&(_m->VCU_STAT_TX_DROPS), _d, dlc_);
   }
  }
 }

 return recid;
}

