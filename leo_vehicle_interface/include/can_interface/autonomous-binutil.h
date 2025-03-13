// Generator version : v3.1
// DBC filename      : autonomous_module.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "dbccodeconf.h"

#include "autonomous.h"

typedef struct
{
  LONGITUDINAL_COMMANDS_JOY_t LONGITUDINAL_COMMANDS_JOY;
  VEHICLE_COMMANDS_JOY_t VEHICLE_COMMANDS_JOY;
  FRONT_WHEEL_COMMANDS_JOY_t FRONT_WHEEL_COMMANDS_JOY;
  VEHICLE_INFO_t VEHICLE_INFO;
  VEHICLE_SIGNAL_STATUS_t VEHICLE_SIGNAL_STATUS;
  MOTION_INFO_t MOTION_INFO;
  MOTOR_INFO_t MOTOR_INFO;
  VEHICLE_ERRORS_t VEHICLE_ERRORS;
  WHEEL_SPEEDS_t WHEEL_SPEEDS;
  DYNAMIC_SENSOR_FRAME_t DYNAMIC_SENSOR_FRAME;
  CONTROL_MECHANISM_VOLTS_t CONTROL_MECHANISM_VOLTS;
  CONTROL_MECHANISM_TEMPS_t CONTROL_MECHANISM_TEMPS;
  THROTTLE_MODULE_STATUS_t THROTTLE_MODULE_STATUS;
  LONGITUDINAL_COMMANDS_t LONGITUDINAL_COMMANDS;
  VEHICLE_COMMANDS_t VEHICLE_COMMANDS;
  FRONT_WHEEL_COMMANDS_t FRONT_WHEEL_COMMANDS;
} autonomous_rx_t;

// There is no any TX mapped massage.

uint32_t autonomous_Receive(autonomous_rx_t* m, const uint8_t* d, uint32_t msgid, uint8_t dlc);

#ifdef __DEF_AUTONOMOUS__

extern autonomous_rx_t autonomous_rx;

#endif // __DEF_AUTONOMOUS__

#ifdef __cplusplus
}
#endif
