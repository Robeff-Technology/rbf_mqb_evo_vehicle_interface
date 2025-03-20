// Generator version : v3.1
// DBC filename      : robione_autonomous_pc.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "dbccodeconf.h"

#include "vcu.h"

typedef struct
{
  VEHICLE_INFO_t VEHICLE_INFO;
  VEHICLE_STATUS_t VEHICLE_STATUS;
  VEHICLE_MOTION_COMMANDS_t VEHICLE_MOTION_COMMANDS;
  VEHICLE_COMMANDS_t VEHICLE_COMMANDS;
} vcu_rx_t;

// There is no any TX mapped massage.

uint32_t vcu_Receive(vcu_rx_t* m, const uint8_t* d, uint32_t msgid, uint8_t dlc);

#ifdef __DEF_VCU__

extern vcu_rx_t vcu_rx;

#endif // __DEF_VCU__

#ifdef __cplusplus
}
#endif
