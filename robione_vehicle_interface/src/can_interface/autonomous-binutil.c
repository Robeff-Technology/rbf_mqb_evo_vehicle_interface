// Generator version : v3.1
// DBC filename      : autonomous_module.dbc
#include "autonomous-binutil.h"

// DBC file version
#if (VER_AUTONOMOUS_MAJ != (0U)) || (VER_AUTONOMOUS_MIN != (0U))
#error The AUTONOMOUS binutil source file has inconsistency with core dbc lib!
#endif

#ifdef __DEF_AUTONOMOUS__

autonomous_rx_t autonomous_rx;

#endif // __DEF_AUTONOMOUS__

uint32_t autonomous_Receive(autonomous_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_)
{
 uint32_t recid = 0;
 if ((_id >= 0x401U) && (_id < 0x1DEF0416U)) {
  if ((_id >= 0x401U) && (_id < 0x1DEF0412U)) {
   if ((_id >= 0x401U) && (_id < 0x403U)) {
    if (_id == 0x401U) {
     recid = Unpack_LONGITUDINAL_COMMANDS_JOY_autonomous(&(_m->LONGITUDINAL_COMMANDS_JOY), _d, dlc_);
    } else if (_id == 0x402U) {
     recid = Unpack_VEHICLE_COMMANDS_JOY_autonomous(&(_m->VEHICLE_COMMANDS_JOY), _d, dlc_);
    }
   } else {
    if (_id == 0x403U) {
     recid = Unpack_FRONT_WHEEL_COMMANDS_JOY_autonomous(&(_m->FRONT_WHEEL_COMMANDS_JOY), _d, dlc_);
    } else if (_id == 0x1DEF0411U) {
     recid = Unpack_VEHICLE_INFO_autonomous(&(_m->VEHICLE_INFO), _d, dlc_);
    }
   }
  } else {
   if ((_id >= 0x1DEF0412U) && (_id < 0x1DEF0414U)) {
    if (_id == 0x1DEF0412U) {
     recid = Unpack_VEHICLE_SIGNAL_STATUS_autonomous(&(_m->VEHICLE_SIGNAL_STATUS), _d, dlc_);
    } else if (_id == 0x1DEF0413U) {
     recid = Unpack_MOTION_INFO_autonomous(&(_m->MOTION_INFO), _d, dlc_);
    }
   } else {
    if (_id == 0x1DEF0414U) {
     recid = Unpack_MOTOR_INFO_autonomous(&(_m->MOTOR_INFO), _d, dlc_);
    } else if (_id == 0x1DEF0415U) {
     recid = Unpack_VEHICLE_ERRORS_autonomous(&(_m->VEHICLE_ERRORS), _d, dlc_);
    }
   }
  }
 } else {
  if ((_id >= 0x1DEF0416U) && (_id < 0x1DEF0420U)) {
   if ((_id >= 0x1DEF0416U) && (_id < 0x1DEF0418U)) {
    if (_id == 0x1DEF0416U) {
     recid = Unpack_WHEEL_SPEEDS_autonomous(&(_m->WHEEL_SPEEDS), _d, dlc_);
    } else if (_id == 0x1DEF0417U) {
     recid = Unpack_DYNAMIC_SENSOR_FRAME_autonomous(&(_m->DYNAMIC_SENSOR_FRAME), _d, dlc_);
    }
   } else {
    if (_id == 0x1DEF0418U) {
     recid = Unpack_CONTROL_MECHANISM_VOLTS_autonomous(&(_m->CONTROL_MECHANISM_VOLTS), _d, dlc_);
    } else if (_id == 0x1DEF0419U) {
     recid = Unpack_CONTROL_MECHANISM_TEMPS_autonomous(&(_m->CONTROL_MECHANISM_TEMPS), _d, dlc_);
    }
   }
  } else {
   if ((_id >= 0x1DEF0420U) && (_id < 0x1DEFB001U)) {
    if (_id == 0x1DEF0420U) {
     recid = Unpack_THROTTLE_MODULE_STATUS_autonomous(&(_m->THROTTLE_MODULE_STATUS), _d, dlc_);
    } else if (_id == 0x1DEFB000U) {
     recid = Unpack_LONGITUDINAL_COMMANDS_autonomous(&(_m->LONGITUDINAL_COMMANDS), _d, dlc_);
    }
   } else {
    if (_id == 0x1DEFB001U) {
     recid = Unpack_VEHICLE_COMMANDS_autonomous(&(_m->VEHICLE_COMMANDS), _d, dlc_);
    } else if (_id == 0x1DEFB002U) {
     recid = Unpack_FRONT_WHEEL_COMMANDS_autonomous(&(_m->FRONT_WHEEL_COMMANDS), _d, dlc_);
    }
   }
  }
 }

 return recid;
}

