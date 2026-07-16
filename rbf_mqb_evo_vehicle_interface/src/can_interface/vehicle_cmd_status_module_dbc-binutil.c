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
   recid = Unpack_VCU_CTRL_CMD_SI_vehicle_cmd_status_module_dbc(&(_m->VCU_CTRL_CMD_SI), _d, dlc_);
  } else {
   if (_id == 0x4331002U) {
    recid = Unpack_REMOTE_CONTROL_MSG_vehicle_cmd_status_module_dbc(&(_m->REMOTE_CONTROL_MSG), _d, dlc_);
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
   }
  }
 }

 return recid;
}

