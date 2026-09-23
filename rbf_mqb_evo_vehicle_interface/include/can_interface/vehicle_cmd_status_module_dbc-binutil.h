// Generator version : v3.1
// DBC filename      : vehicle_cmd_status_dbc.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "dbccodeconf.h"

#include "vehicle_cmd_status_module_dbc.h"

typedef struct
{
  SPEED_CONTROL_MSG_t SPEED_CONTROL_MSG;
  CLEAR_INTERVENTION_CMD_t CLEAR_INTERVENTION_CMD;
  DIRECT_CONTROL_MSG_t DIRECT_CONTROL_MSG;
  SAFE_STAT_ROS2_HEARTBEAT_t SAFE_STAT_ROS2_HEARTBEAT;
  VCU_STAT_MOTION_SI_t VCU_STAT_MOTION_SI;
  VCU_STAT_VEHICLE_STATE_t VCU_STAT_VEHICLE_STATE;
  VCU_STAT_COMM_STATUS_t VCU_STAT_COMM_STATUS;
  VCU_STAT_DYNAMICS_SI_t VCU_STAT_DYNAMICS_SI;
  VCU_STAT_QUEUE_DROPS_t VCU_STAT_QUEUE_DROPS;
  VCU_STAT_TX_DROPS_t VCU_STAT_TX_DROPS;
} vehicle_cmd_status_module_dbc_rx_t;

// There is no any TX mapped massage.

uint32_t vehicle_cmd_status_module_dbc_Receive(vehicle_cmd_status_module_dbc_rx_t* m, const uint8_t* d, uint32_t msgid, uint8_t dlc);

#ifdef __DEF_VEHICLE_CMD_STATUS_MODULE_DBC__

extern vehicle_cmd_status_module_dbc_rx_t vehicle_cmd_status_module_dbc_rx;

#endif // __DEF_VEHICLE_CMD_STATUS_MODULE_DBC__

#ifdef __cplusplus
}
#endif
