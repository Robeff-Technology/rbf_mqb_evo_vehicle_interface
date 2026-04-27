// Generator version : v3.1
// DBC filename      : pc_vcu_can_500k_v1.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "dbccodeconf.h"

#include "pc_vcu.h"

typedef struct
{
  SAFETY_MANAGER_STATUS_t SAFETY_MANAGER_STATUS;
  VCU_CTRL_CMD_SI_t VCU_CTRL_CMD_SI;
  SAFE_STAT_ROS2_HEARTBEAT_t SAFE_STAT_ROS2_HEARTBEAT;
  VCU_STAT_MOTION_SI_t VCU_STAT_MOTION_SI;
  VCU_STAT_VEHICLE_STATE_t VCU_STAT_VEHICLE_STATE;
  MCU_MODULE_STATUS_t MCU_MODULE_STATUS;
  DTC_ERROR_STATUS_t DTC_ERROR_STATUS;
  DTC_ERROR_STATUS_1_t DTC_ERROR_STATUS_1;
} pc_vcu_rx_t;

// There is no any TX mapped massage.

uint32_t pc_vcu_Receive(pc_vcu_rx_t* m, const uint8_t* d, uint32_t msgid, uint8_t dlc);

#ifdef __DEF_PC_VCU__

extern pc_vcu_rx_t pc_vcu_rx;

#endif // __DEF_PC_VCU__

#ifdef __cplusplus
}
#endif
