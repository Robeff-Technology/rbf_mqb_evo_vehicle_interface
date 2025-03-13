// Generator version : v3.1
// DBC filename      : flux_pds.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "dbccodeconf.h"

#include "flux.h"

typedef struct
{
  CHANNEL_STATUS_MSG_t CHANNEL_STATUS_MSG;
  CURRENTS_1_MSG_t CURRENTS_1_MSG;
  CURRENTS_2_MSG_t CURRENTS_2_MSG;
  CURRENTS_3_MSG_t CURRENTS_3_MSG;
  CONSUMPTION_1_MSG_t CONSUMPTION_1_MSG;
  CONSUMPTION_2_MSG_t CONSUMPTION_2_MSG;
  CONSUMPTION_3_MSG_t CONSUMPTION_3_MSG;
  BUS_STATUS_MSG_t BUS_STATUS_MSG;
  TEMPERATURES_MSG_t TEMPERATURES_MSG;
} flux_rx_t;

// There is no any TX mapped massage.

uint32_t flux_Receive(flux_rx_t* m, const uint8_t* d, uint32_t msgid, uint8_t dlc);

#ifdef __DEF_FLUX__

extern flux_rx_t flux_rx;

#endif // __DEF_FLUX__

#ifdef __cplusplus
}
#endif
