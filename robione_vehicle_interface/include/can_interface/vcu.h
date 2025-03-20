// Generator version : v3.1
// DBC filename      : robione_autonomous_pc.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// DBC file version
#define VER_VCU_MAJ (0U)
#define VER_VCU_MIN (0U)

// include current dbc-driver compilation config
#include "vcu-config.h"

#ifdef VCU_USE_DIAG_MONITORS
// This file must define:
// base monitor struct
#include "canmonitorutil.h"

#endif // VCU_USE_DIAG_MONITORS


// DLC maximum value which is used as the limit for frame's data buffer size.
// Client can set its own value (not sure why) in driver-config
// or can test it on some limit specified by application
// e.g.: static_assert(TESTDB_MAX_DLC_VALUE <= APPLICATION_FRAME_DATA_SIZE, "Max DLC value in the driver is too big")
#ifndef VCU_MAX_DLC_VALUE
// The value which was found out by generator (real max value)
#define VCU_MAX_DLC_VALUE 8U
#endif

// The limit is used for setting frame's data bytes
#define VCU_VALIDATE_DLC(msgDlc) (((msgDlc) <= (VCU_MAX_DLC_VALUE)) ? (msgDlc) : (VCU_MAX_DLC_VALUE))

// Initial byte value to be filles in data bytes of the frame before pack signals
// User can define its own custom value in driver-config file
#ifndef VCU_INITIAL_BYTE_VALUE
#define VCU_INITIAL_BYTE_VALUE 0U
#endif


// def @VEHICLE_INFO CAN Message (502203409 0x1def0411)
#define VEHICLE_INFO_IDE (1U)
#define VEHICLE_INFO_DLC (8U)
#define VEHICLE_INFO_CANID (0x1def0411U)
// signal: @vehicle_velocity_ro
#define VCU_vehicle_velocity_ro_CovFactor (0.001)
#define VCU_vehicle_velocity_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.001)) )
#define VCU_vehicle_velocity_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @steering_wheel_angle_ro
#define VCU_steering_wheel_angle_ro_CovFactor (0.02)
#define VCU_steering_wheel_angle_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.02)) )
#define VCU_steering_wheel_angle_ro_fromS(x) ( (((x) * (0.02)) + (0.0)) )
// signal: @steering_wheel_speed_ro
#define VCU_steering_wheel_speed_ro_CovFactor (5)
#define VCU_steering_wheel_speed_ro_toS(x) ( (int16_t) ((x) / (5)) )
#define VCU_steering_wheel_speed_ro_fromS(x) ( ((x) * (5)) )
// signal: @steering_tire_angle_ro
#define VCU_steering_tire_angle_ro_CovFactor (0.00307)
#define VCU_steering_tire_angle_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.00307)) )
#define VCU_steering_tire_angle_ro_fromS(x) ( (((x) * (0.00307)) + (0.0)) )

typedef struct
{
#ifdef VCU_USE_BITS_SIGNAL

  // Actual vehicle velocity with its direction. < 0 -> reverse moving >0 -> forward moving
  int16_t vehicle_velocity_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'m/s'

#ifdef VCU_USE_SIGFLOAT
  sigfloat_t vehicle_velocity_phys;
#endif // VCU_USE_SIGFLOAT

  // actual wheel angle from epas
  int16_t steering_wheel_angle_ro;           //  [-] Bits=16 Factor= 0.02            Unit:'degree'

#ifdef VCU_USE_SIGFLOAT
  sigfloat_t steering_wheel_angle_phys;
#endif // VCU_USE_SIGFLOAT

  // -
  int16_t steering_wheel_speed_ro;           //  [-] Bits=10 Factor= 5               Unit:'degree/second'

#ifdef VCU_USE_SIGFLOAT
  int16_t steering_wheel_speed_phys;
#endif // VCU_USE_SIGFLOAT

  // Steering input by driver, torque
  int16_t steering_wheel_torque;             //  [-] Bits=11 Unit:'CentiNewton/m'

  // actual tire angle of the vehicle
  int16_t steering_tire_angle_ro;            //  [-] Bits=11 Factor= 0.00307         Unit:'radian'

#ifdef VCU_USE_SIGFLOAT
  sigfloat_t steering_tire_angle_phys;
#endif // VCU_USE_SIGFLOAT

#else

  // Actual vehicle velocity with its direction. < 0 -> reverse moving >0 -> forward moving
  int16_t vehicle_velocity_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'m/s'

#ifdef VCU_USE_SIGFLOAT
  sigfloat_t vehicle_velocity_phys;
#endif // VCU_USE_SIGFLOAT

  // actual wheel angle from epas
  int16_t steering_wheel_angle_ro;           //  [-] Bits=16 Factor= 0.02            Unit:'degree'

#ifdef VCU_USE_SIGFLOAT
  sigfloat_t steering_wheel_angle_phys;
#endif // VCU_USE_SIGFLOAT

  // -
  int16_t steering_wheel_speed_ro;           //  [-] Bits=10 Factor= 5               Unit:'degree/second'

#ifdef VCU_USE_SIGFLOAT
  int16_t steering_wheel_speed_phys;
#endif // VCU_USE_SIGFLOAT

  // Steering input by driver, torque
  int16_t steering_wheel_torque;             //  [-] Bits=11 Unit:'CentiNewton/m'

  // actual tire angle of the vehicle
  int16_t steering_tire_angle_ro;            //  [-] Bits=11 Factor= 0.00307         Unit:'radian'

#ifdef VCU_USE_SIGFLOAT
  sigfloat_t steering_tire_angle_phys;
#endif // VCU_USE_SIGFLOAT

#endif // VCU_USE_BITS_SIGNAL

#ifdef VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VCU_USE_DIAG_MONITORS

} VEHICLE_INFO_t;

// def @VEHICLE_STATUS CAN Message (502203410 0x1def0412)
#define VEHICLE_STATUS_IDE (1U)
#define VEHICLE_STATUS_DLC (8U)
#define VEHICLE_STATUS_CANID (0x1def0412U)

// Value tables for @blinker signal

#ifndef blinker_VEHICLE_STATUS_BLINKER_CLOSED
#define blinker_VEHICLE_STATUS_BLINKER_CLOSED (0)
#endif

#ifndef blinker_VEHICLE_STATUS_BLINKER_RIGHT
#define blinker_VEHICLE_STATUS_BLINKER_RIGHT (1)
#endif

#ifndef blinker_VEHICLE_STATUS_BLINKER_LEFT
#define blinker_VEHICLE_STATUS_BLINKER_LEFT (2)
#endif

#ifndef blinker_VEHICLE_STATUS_HAZARD_LIGHT
#define blinker_VEHICLE_STATUS_HAZARD_LIGHT (3)
#endif


// Value tables for @headlight signal

#ifndef headlight_VEHICLE_STATUS_BEAM_OFF
#define headlight_VEHICLE_STATUS_BEAM_OFF (0)
#endif

#ifndef headlight_VEHICLE_STATUS_HIGHBEAM_ON
#define headlight_VEHICLE_STATUS_HIGHBEAM_ON (1)
#endif

#ifndef headlight_VEHICLE_STATUS_LOWBEAM_ON
#define headlight_VEHICLE_STATUS_LOWBEAM_ON (2)
#endif


// Value tables for @gear signal

#ifndef gear_VEHICLE_STATUS_GEAR_UNKNOWN
#define gear_VEHICLE_STATUS_GEAR_UNKNOWN (0)
#endif

#ifndef gear_VEHICLE_STATUS_GEAR_P
#define gear_VEHICLE_STATUS_GEAR_P (1)
#endif

#ifndef gear_VEHICLE_STATUS_GEAR_R
#define gear_VEHICLE_STATUS_GEAR_R (2)
#endif

#ifndef gear_VEHICLE_STATUS_GEAR_N
#define gear_VEHICLE_STATUS_GEAR_N (3)
#endif

#ifndef gear_VEHICLE_STATUS_GEAR_D
#define gear_VEHICLE_STATUS_GEAR_D (4)
#endif


// Value tables for @mode signal

#ifndef mode_VEHICLE_STATUS_CONTROLLER_NONE
#define mode_VEHICLE_STATUS_CONTROLLER_NONE (0)
#endif

#ifndef mode_VEHICLE_STATUS_CONTROLLER_REMOTE_JOYSTICK
#define mode_VEHICLE_STATUS_CONTROLLER_REMOTE_JOYSTICK (1)
#endif

#ifndef mode_VEHICLE_STATUS_CONTROLLER_AUTONOMOUS
#define mode_VEHICLE_STATUS_CONTROLLER_AUTONOMOUS (2)
#endif

#ifndef mode_VEHICLE_STATUS_CONTROLLER_INTERNET
#define mode_VEHICLE_STATUS_CONTROLLER_INTERNET (3)
#endif


// Value tables for @hand_brake signal

#ifndef hand_brake_VEHICLE_STATUS_HANDBRAKE_RELEASED
#define hand_brake_VEHICLE_STATUS_HANDBRAKE_RELEASED (0)
#endif

#ifndef hand_brake_VEHICLE_STATUS_HANDBRAKE_PRESSED
#define hand_brake_VEHICLE_STATUS_HANDBRAKE_PRESSED (1)
#endif


typedef struct
{
#ifdef VCU_USE_BITS_SIGNAL

  // battery voltage of the vehicle
  uint8_t battery_voltage;                   //      Bits= 8 Unit:'V'

  // battery soc of the vehicle
  uint8_t battery_soc;                       //      Bits= 8 Unit:'%'

  // Blinker status.0->Close, 1-> Right blinker, 2-> left blinker, 3-> hazardLight
  //  0 : "BLINKER_CLOSED"
  //  1 : "BLINKER_RIGHT"
  //  2 : "BLINKER_LEFT"
  //  3 : "HAZARD_LIGHT"
  uint8_t blinker;                           //      Bits= 8 Unit:'-'

  // Headlight status. Beam off ->0 1->Highbeam on 2->lowbeam on
  //  0 : "BEAM_OFF"
  //  1 : "HIGHBEAM_ON"
  //  2 : "LOWBEAM_ON"
  uint8_t headlight;                         //      Bits= 8 Unit:'-'

  // Gear status. P-R-N-D (1-2-3-4)
  //  0 : "GEAR_UNKNOWN"
  //  1 : "GEAR_P"
  //  2 : "GEAR_R"
  //  3 : "GEAR_N"
  //  4 : "GEAR_D"
  uint8_t gear;                              //      Bits= 8 Unit:'-'

  // current robione mode .0-> none 1->remote 2-> autonomous 3->internet
  //  0 : "CONTROLLER_NONE"
  //  1 : "CONTROLLER_REMOTE_JOYSTICK"
  //  2 : "CONTROLLER_AUTONOMOUS"
  //  3 : "CONTROLLER_INTERNET"
  uint8_t mode;                              //      Bits= 8 Unit:'-'

  // Handbrake status. 0-> released, 1-> pressed
  //  0 : "HANDBRAKE_RELEASED"
  //  1 : "HANDBRAKE_PRESSED"
  uint8_t hand_brake;                        //      Bits= 8 Unit:'-'

#else

  // battery voltage of the vehicle
  uint8_t battery_voltage;                   //      Bits= 8 Unit:'V'

  // battery soc of the vehicle
  uint8_t battery_soc;                       //      Bits= 8 Unit:'%'

  // Blinker status.0->Close, 1-> Right blinker, 2-> left blinker, 3-> hazardLight
  //  0 : "BLINKER_CLOSED"
  //  1 : "BLINKER_RIGHT"
  //  2 : "BLINKER_LEFT"
  //  3 : "HAZARD_LIGHT"
  uint8_t blinker;                           //      Bits= 8 Unit:'-'

  // Headlight status. Beam off ->0 1->Highbeam on 2->lowbeam on
  //  0 : "BEAM_OFF"
  //  1 : "HIGHBEAM_ON"
  //  2 : "LOWBEAM_ON"
  uint8_t headlight;                         //      Bits= 8 Unit:'-'

  // Gear status. P-R-N-D (1-2-3-4)
  //  0 : "GEAR_UNKNOWN"
  //  1 : "GEAR_P"
  //  2 : "GEAR_R"
  //  3 : "GEAR_N"
  //  4 : "GEAR_D"
  uint8_t gear;                              //      Bits= 8 Unit:'-'

  // current robione mode .0-> none 1->remote 2-> autonomous 3->internet
  //  0 : "CONTROLLER_NONE"
  //  1 : "CONTROLLER_REMOTE_JOYSTICK"
  //  2 : "CONTROLLER_AUTONOMOUS"
  //  3 : "CONTROLLER_INTERNET"
  uint8_t mode;                              //      Bits= 8 Unit:'-'

  // Handbrake status. 0-> released, 1-> pressed
  //  0 : "HANDBRAKE_RELEASED"
  //  1 : "HANDBRAKE_PRESSED"
  uint8_t hand_brake;                        //      Bits= 8 Unit:'-'

#endif // VCU_USE_BITS_SIGNAL

#ifdef VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VCU_USE_DIAG_MONITORS

} VEHICLE_STATUS_t;

// def @VEHICLE_MOTION_COMMANDS CAN Message (502247424 0x1defb000)
#define VEHICLE_MOTION_COMMANDS_IDE (1U)
#define VEHICLE_MOTION_COMMANDS_DLC (8U)
#define VEHICLE_MOTION_COMMANDS_CANID (0x1defb000U)
// signal: @set_velocity_ro
#define VCU_set_velocity_ro_CovFactor (0.001)
#define VCU_set_velocity_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.001)) )
#define VCU_set_velocity_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @set_limit_velocity_ro
#define VCU_set_limit_velocity_ro_CovFactor (0.001)
#define VCU_set_limit_velocity_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.001)) )
#define VCU_set_limit_velocity_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @set_front_wheel_tire_angle_ro
#define VCU_set_front_wheel_tire_angle_ro_CovFactor (0.0001)
#define VCU_set_front_wheel_tire_angle_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.0001)) )
#define VCU_set_front_wheel_tire_angle_ro_fromS(x) ( (((x) * (0.0001)) + (0.0)) )
// signal: @set_front_wheel_angle_rate_ro
#define VCU_set_front_wheel_angle_rate_ro_CovFactor (0.1)
#define VCU_set_front_wheel_angle_rate_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.1)) )
#define VCU_set_front_wheel_angle_rate_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )

typedef struct
{
#ifdef VCU_USE_BITS_SIGNAL

  //  Sets the vehicle speed.
  int16_t set_velocity_ro;                     //  [-] Bits=16 Factor= 0.001           Unit:'m/s'

#ifdef VCU_USE_SIGFLOAT
  sigfloat_t set_velocity_phys;
#endif // VCU_USE_SIGFLOAT

  // Defines the speed limit. Users can change continuously this limit.
  int16_t set_limit_velocity_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'m/s'

#ifdef VCU_USE_SIGFLOAT
  sigfloat_t set_limit_velocity_phys;
#endif // VCU_USE_SIGFLOAT

  // set tire angle
  int16_t set_front_wheel_tire_angle_ro;       //  [-] Bits=16 Factor= 0.0001          Unit:'rad'

#ifdef VCU_USE_SIGFLOAT
  sigfloat_t set_front_wheel_tire_angle_phys;
#endif // VCU_USE_SIGFLOAT

  // set tire angle rate
  int16_t set_front_wheel_angle_rate_ro;       //  [-] Bits=16 Factor= 0.1             Unit:'rad/s'

#ifdef VCU_USE_SIGFLOAT
  sigfloat_t set_front_wheel_angle_rate_phys;
#endif // VCU_USE_SIGFLOAT

#else

  //  Sets the vehicle speed.
  int16_t set_velocity_ro;                     //  [-] Bits=16 Factor= 0.001           Unit:'m/s'

#ifdef VCU_USE_SIGFLOAT
  sigfloat_t set_velocity_phys;
#endif // VCU_USE_SIGFLOAT

  // Defines the speed limit. Users can change continuously this limit.
  int16_t set_limit_velocity_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'m/s'

#ifdef VCU_USE_SIGFLOAT
  sigfloat_t set_limit_velocity_phys;
#endif // VCU_USE_SIGFLOAT

  // set tire angle
  int16_t set_front_wheel_tire_angle_ro;       //  [-] Bits=16 Factor= 0.0001          Unit:'rad'

#ifdef VCU_USE_SIGFLOAT
  sigfloat_t set_front_wheel_tire_angle_phys;
#endif // VCU_USE_SIGFLOAT

  // set tire angle rate
  int16_t set_front_wheel_angle_rate_ro;       //  [-] Bits=16 Factor= 0.1             Unit:'rad/s'

#ifdef VCU_USE_SIGFLOAT
  sigfloat_t set_front_wheel_angle_rate_phys;
#endif // VCU_USE_SIGFLOAT

#endif // VCU_USE_BITS_SIGNAL

#ifdef VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VCU_USE_DIAG_MONITORS

} VEHICLE_MOTION_COMMANDS_t;

// def @VEHICLE_COMMANDS CAN Message (502247425 0x1defb001)
#define VEHICLE_COMMANDS_IDE (1U)
#define VEHICLE_COMMANDS_DLC (8U)
#define VEHICLE_COMMANDS_CANID (0x1defb001U)

// Value tables for @set_autonomous signal

#ifndef set_autonomous_VEHICLE_COMMANDS_AUTONOMOUS_OFF
#define set_autonomous_VEHICLE_COMMANDS_AUTONOMOUS_OFF (0)
#endif

#ifndef set_autonomous_VEHICLE_COMMANDS_AUTONOMOUS_ON
#define set_autonomous_VEHICLE_COMMANDS_AUTONOMOUS_ON (1)
#endif


// Value tables for @blinker signal

#ifndef blinker_VEHICLE_COMMANDS_NO_BLINKER
#define blinker_VEHICLE_COMMANDS_NO_BLINKER (0)
#endif

#ifndef blinker_VEHICLE_COMMANDS_BLINKER_LEFT
#define blinker_VEHICLE_COMMANDS_BLINKER_LEFT (1)
#endif

#ifndef blinker_VEHICLE_COMMANDS_BLINKER_RIGHT
#define blinker_VEHICLE_COMMANDS_BLINKER_RIGHT (2)
#endif

#ifndef blinker_VEHICLE_COMMANDS_BLINKER_HAZARD
#define blinker_VEHICLE_COMMANDS_BLINKER_HAZARD (3)
#endif


// Value tables for @headlight signal

#ifndef headlight_VEHICLE_COMMANDS_HEADLIGHT_CLOSE
#define headlight_VEHICLE_COMMANDS_HEADLIGHT_CLOSE (0)
#endif

#ifndef headlight_VEHICLE_COMMANDS_HEADLIGHT_LOW
#define headlight_VEHICLE_COMMANDS_HEADLIGHT_LOW (1)
#endif

#ifndef headlight_VEHICLE_COMMANDS_HEADLIGHT_HIGH
#define headlight_VEHICLE_COMMANDS_HEADLIGHT_HIGH (2)
#endif


// Value tables for @gear signal

#ifndef gear_VEHICLE_COMMANDS_GEAR_P
#define gear_VEHICLE_COMMANDS_GEAR_P (0)
#endif

#ifndef gear_VEHICLE_COMMANDS_GEAR_R
#define gear_VEHICLE_COMMANDS_GEAR_R (1)
#endif

#ifndef gear_VEHICLE_COMMANDS_GEAR_N
#define gear_VEHICLE_COMMANDS_GEAR_N (2)
#endif

#ifndef gear_VEHICLE_COMMANDS_GEAR_D
#define gear_VEHICLE_COMMANDS_GEAR_D (3)
#endif


// Value tables for @hand_brake signal

#ifndef hand_brake_VEHICLE_COMMANDS_HANDBRAKE_PRESS
#define hand_brake_VEHICLE_COMMANDS_HANDBRAKE_PRESS (0)
#endif

#ifndef hand_brake_VEHICLE_COMMANDS_HANDBRAKE_RELEASE
#define hand_brake_VEHICLE_COMMANDS_HANDBRAKE_RELEASE (1)
#endif


// Value tables for @emergency_request signal

#ifndef emergency_request_VEHICLE_COMMANDS_EMERGENCY_CLEAR
#define emergency_request_VEHICLE_COMMANDS_EMERGENCY_CLEAR (0)
#endif

#ifndef emergency_request_VEHICLE_COMMANDS_EMERGENCY_SET
#define emergency_request_VEHICLE_COMMANDS_EMERGENCY_SET (1)
#endif


// Value tables for @horn signal

#ifndef horn_VEHICLE_COMMANDS_HORN_CLOSE
#define horn_VEHICLE_COMMANDS_HORN_CLOSE (0)
#endif

#ifndef horn_VEHICLE_COMMANDS_HORN_OPEN
#define horn_VEHICLE_COMMANDS_HORN_OPEN (1)
#endif


typedef struct
{
#ifdef VCU_USE_BITS_SIGNAL

  // Controls whether the vehicle is in autonomous mode or not.
  //  0 : "AUTONOMOUS_OFF"
  //  1 : "AUTONOMOUS_ON"
  uint8_t set_autonomous : 1;                //      Bits= 1 Unit:'-'

  // Controls the blinkers
  //  0 : "NO_BLINKER"
  //  1 : "BLINKER_LEFT"
  //  2 : "BLINKER_RIGHT"
  //  3 : "BLINKER_HAZARD"
  uint8_t blinker;                           //      Bits= 8 Unit:'-'

  // Controls the headlight status (low/high beams).
  //  0 : "HEADLIGHT_CLOSE"
  //  1 : "HEADLIGHT_LOW"
  //  2 : "HEADLIGHT_HIGH"
  uint8_t headlight;                         //      Bits= 8 Unit:'-'

  // Set gear position.Gear changes when speed arrives at 0.
  //  0 : "GEAR_P"
  //  1 : "GEAR_R"
  //  2 : "GEAR_N"
  //  3 : "GEAR_D"
  uint8_t gear;                              //      Bits= 8 Unit:'-'

  // Set handbrake.
  //  0 : "HANDBRAKE_PRESS"
  //  1 : "HANDBRAKE_RELEASE"
  uint8_t hand_brake;                        //      Bits= 8 Unit:'-'

  // Set emergency braking.
  //  0 : "EMERGENCY_CLEAR"
  //  1 : "EMERGENCY_SET"
  uint8_t emergency_request;                 //      Bits= 8 Unit:'-'

  // horn signal
  //  0 : "HORN_CLOSE"
  //  1 : "HORN_OPEN"
  uint8_t horn : 1;                          //      Bits= 1 Unit:'-'

  // -
  uint32_t reserved;                         //      Bits=23 Unit:'-'

#else

  // Controls whether the vehicle is in autonomous mode or not.
  //  0 : "AUTONOMOUS_OFF"
  //  1 : "AUTONOMOUS_ON"
  uint8_t set_autonomous;                    //      Bits= 1 Unit:'-'

  // Controls the blinkers
  //  0 : "NO_BLINKER"
  //  1 : "BLINKER_LEFT"
  //  2 : "BLINKER_RIGHT"
  //  3 : "BLINKER_HAZARD"
  uint8_t blinker;                           //      Bits= 8 Unit:'-'

  // Controls the headlight status (low/high beams).
  //  0 : "HEADLIGHT_CLOSE"
  //  1 : "HEADLIGHT_LOW"
  //  2 : "HEADLIGHT_HIGH"
  uint8_t headlight;                         //      Bits= 8 Unit:'-'

  // Set gear position.Gear changes when speed arrives at 0.
  //  0 : "GEAR_P"
  //  1 : "GEAR_R"
  //  2 : "GEAR_N"
  //  3 : "GEAR_D"
  uint8_t gear;                              //      Bits= 8 Unit:'-'

  // Set handbrake.
  //  0 : "HANDBRAKE_PRESS"
  //  1 : "HANDBRAKE_RELEASE"
  uint8_t hand_brake;                        //      Bits= 8 Unit:'-'

  // Set emergency braking.
  //  0 : "EMERGENCY_CLEAR"
  //  1 : "EMERGENCY_SET"
  uint8_t emergency_request;                 //      Bits= 8 Unit:'-'

  // horn signal
  //  0 : "HORN_CLOSE"
  //  1 : "HORN_OPEN"
  uint8_t horn;                              //      Bits= 1 Unit:'-'

  // -
  uint32_t reserved;                         //      Bits=23 Unit:'-'

#endif // VCU_USE_BITS_SIGNAL

#ifdef VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VCU_USE_DIAG_MONITORS

} VEHICLE_COMMANDS_t;

// Function signatures

uint32_t Unpack_VEHICLE_INFO_VCU(VEHICLE_INFO_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VCU_USE_CANSTRUCT
uint32_t Pack_VEHICLE_INFO_VCU(VEHICLE_INFO_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEHICLE_INFO_VCU(VEHICLE_INFO_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VCU_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_STATUS_VCU(VEHICLE_STATUS_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VCU_USE_CANSTRUCT
uint32_t Pack_VEHICLE_STATUS_VCU(VEHICLE_STATUS_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEHICLE_STATUS_VCU(VEHICLE_STATUS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VCU_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_MOTION_COMMANDS_VCU(VEHICLE_MOTION_COMMANDS_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VCU_USE_CANSTRUCT
uint32_t Pack_VEHICLE_MOTION_COMMANDS_VCU(VEHICLE_MOTION_COMMANDS_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEHICLE_MOTION_COMMANDS_VCU(VEHICLE_MOTION_COMMANDS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VCU_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_COMMANDS_VCU(VEHICLE_COMMANDS_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VCU_USE_CANSTRUCT
uint32_t Pack_VEHICLE_COMMANDS_VCU(VEHICLE_COMMANDS_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEHICLE_COMMANDS_VCU(VEHICLE_COMMANDS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VCU_USE_CANSTRUCT

#ifdef __cplusplus
}
#endif
