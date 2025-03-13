// Generator version : v3.1
// DBC filename      : flux_pds.dbc
#include "flux-binutil.h"

// DBC file version
#if (VER_FLUX_MAJ != (0U)) || (VER_FLUX_MIN != (0U))
#error The FLUX binutil source file has inconsistency with core dbc lib!
#endif

#ifdef __DEF_FLUX__

flux_rx_t flux_rx;

#endif // __DEF_FLUX__

uint32_t flux_Receive(flux_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_)
{
 uint32_t recid = 0;
 if ((_id >= 0x120U) && (_id < 0x12DU)) {
  if ((_id >= 0x120U) && (_id < 0x128U)) {
   if (_id == 0x120U) {
    recid = Unpack_CHANNEL_STATUS_MSG_flux(&(_m->CHANNEL_STATUS_MSG), _d, dlc_);
   } else if (_id == 0x124U) {
    recid = Unpack_CURRENTS_1_MSG_flux(&(_m->CURRENTS_1_MSG), _d, dlc_);
   }
  } else {
   if (_id == 0x128U) {
    recid = Unpack_CURRENTS_2_MSG_flux(&(_m->CURRENTS_2_MSG), _d, dlc_);
   } else if (_id == 0x12CU) {
    recid = Unpack_CURRENTS_3_MSG_flux(&(_m->CURRENTS_3_MSG), _d, dlc_);
   }
  }
 } else {
  if ((_id >= 0x12DU) && (_id < 0x12FU)) {
   if (_id == 0x12DU) {
    recid = Unpack_CONSUMPTION_1_MSG_flux(&(_m->CONSUMPTION_1_MSG), _d, dlc_);
   } else if (_id == 0x12EU) {
    recid = Unpack_CONSUMPTION_2_MSG_flux(&(_m->CONSUMPTION_2_MSG), _d, dlc_);
   }
  } else {
   if (_id == 0x12FU) {
    recid = Unpack_CONSUMPTION_3_MSG_flux(&(_m->CONSUMPTION_3_MSG), _d, dlc_);
   } else {
    if (_id == 0x13CU) {
     recid = Unpack_BUS_STATUS_MSG_flux(&(_m->BUS_STATUS_MSG), _d, dlc_);
    } else if (_id == 0x13DU) {
     recid = Unpack_TEMPERATURES_MSG_flux(&(_m->TEMPERATURES_MSG), _d, dlc_);
    }
   }
  }
 }

 return recid;
}

