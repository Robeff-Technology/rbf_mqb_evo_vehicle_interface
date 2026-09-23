// Generator version : v3.1
// DBC filename      : vehicle_cmd_status_dbc.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// DBC file version
#define VER_VEHICLE_CMD_STATUS_MODULE_DBC_MAJ (0U)
#define VER_VEHICLE_CMD_STATUS_MODULE_DBC_MIN (0U)

// include current dbc-driver compilation config
#include "vehicle_cmd_status_module_dbc-config.h"

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS
// This file must define:
// base monitor struct
#include "canmonitorutil.h"

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS


// DLC maximum value which is used as the limit for frame's data buffer size.
// Client can set its own value (not sure why) in driver-config
// or can test it on some limit specified by application
// e.g.: static_assert(TESTDB_MAX_DLC_VALUE <= APPLICATION_FRAME_DATA_SIZE, "Max DLC value in the driver is too big")
#ifndef VEHICLE_CMD_STATUS_MODULE_DBC_MAX_DLC_VALUE
// The value which was found out by generator (real max value)
#define VEHICLE_CMD_STATUS_MODULE_DBC_MAX_DLC_VALUE 8U
#endif

// The limit is used for setting frame's data bytes
#define VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(msgDlc) (((msgDlc) <= (VEHICLE_CMD_STATUS_MODULE_DBC_MAX_DLC_VALUE)) ? (msgDlc) : (VEHICLE_CMD_STATUS_MODULE_DBC_MAX_DLC_VALUE))

// Initial byte value to be filles in data bytes of the frame before pack signals
// User can define its own custom value in driver-config file
#ifndef VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE
#define VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE 0U
#endif


// def @SPEED_CONTROL_MSG CAN Message (67764225 0x40a0001)
#define SPEED_CONTROL_MSG_IDE (1U)
#define SPEED_CONTROL_MSG_DLC (8U)
#define SPEED_CONTROL_MSG_CANID (0x40a0001U)
// signal: @SC_TireAngleRad_Cmd_ro
#define VEHICLE_CMD_STATUS_MODULE_DBC_SC_TireAngleRad_Cmd_ro_CovFactor (0.001)
#define VEHICLE_CMD_STATUS_MODULE_DBC_SC_TireAngleRad_Cmd_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.001)) )
#define VEHICLE_CMD_STATUS_MODULE_DBC_SC_TireAngleRad_Cmd_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @SC_VehicleSpeedMS_Cmd_ro
#define VEHICLE_CMD_STATUS_MODULE_DBC_SC_VehicleSpeedMS_Cmd_ro_CovFactor (0.01)
#define VEHICLE_CMD_STATUS_MODULE_DBC_SC_VehicleSpeedMS_Cmd_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.01)) )
#define VEHICLE_CMD_STATUS_MODULE_DBC_SC_VehicleSpeedMS_Cmd_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )

// Value tables for @SC_Emergency signal

#ifndef SC_Emergency_SPEED_CONTROL_MSG_NONE
#define SC_Emergency_SPEED_CONTROL_MSG_NONE (0)
#endif

#ifndef SC_Emergency_SPEED_CONTROL_MSG_EMERGENCY
#define SC_Emergency_SPEED_CONTROL_MSG_EMERGENCY (1)
#endif


// Value tables for @SC_Gear signal

#ifndef SC_Gear_SPEED_CONTROL_MSG_NONE
#define SC_Gear_SPEED_CONTROL_MSG_NONE (0)
#endif

#ifndef SC_Gear_SPEED_CONTROL_MSG_NEUTRAL
#define SC_Gear_SPEED_CONTROL_MSG_NEUTRAL (1)
#endif

#ifndef SC_Gear_SPEED_CONTROL_MSG_DRIVE
#define SC_Gear_SPEED_CONTROL_MSG_DRIVE (2)
#endif

#ifndef SC_Gear_SPEED_CONTROL_MSG_REVERSE
#define SC_Gear_SPEED_CONTROL_MSG_REVERSE (20)
#endif

#ifndef SC_Gear_SPEED_CONTROL_MSG_PARK
#define SC_Gear_SPEED_CONTROL_MSG_PARK (22)
#endif


typedef struct
{
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

  // Target tire steering angle (+left / ?right)
  int16_t SC_TireAngleRad_Cmd_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'rad'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t SC_TireAngleRad_Cmd_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  // Target longitudinal vehicle speed
  int16_t SC_VehicleSpeedMS_Cmd_ro;             //  [-] Bits=16 Factor= 0.01            Unit:'m/s'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t SC_VehicleSpeedMS_Cmd_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  // Enables autonomous motion commands
  uint8_t SC_Enable : 1;              //      Bits= 1 Unit:'-'

  // Emergency stop request (highest priority)
  //  0 : "NONE"
  //  1 : "EMERGENCY"
  uint8_t SC_Emergency : 1;               //      Bits= 1 Unit:'-'

  uint8_t SC_Reserved_1 : 1;                    //      Bits= 1 Unit:'-'

  // Gear request code (expanded field)
  //  0 : "NONE"
  //  1 : "NEUTRAL"
  //  2 : "DRIVE"
  //  20 : "REVERSE"
  //  22 : "PARK"
  uint8_t SC_Gear : 5;                       //      Bits= 5 Unit:'-'

  // Must be sent as 0
  uint8_t SC_Reserved_2 : 1;                    //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t SC_Reserved_3 : 1;                    //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t SC_Reserved_4 : 1;                    //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t SC_Reserved_5 : 1;                    //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t SC_Reserved : 4;                      //      Bits= 4 Unit:'-'

  // Rolling counter (0?255)
  uint8_t SC_AliveCounter;                      //      Bits= 8 Unit:'-'

  // CRC-8 AUTOSAR over Byte0?Byte6
  uint8_t SC_Crc8;                              //      Bits= 8 Unit:'-'

#else

  // Target tire steering angle (+left / ?right)
  int16_t SC_TireAngleRad_Cmd_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'rad'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t SC_TireAngleRad_Cmd_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  // Target longitudinal vehicle speed
  int16_t SC_VehicleSpeedMS_Cmd_ro;             //  [-] Bits=16 Factor= 0.01            Unit:'m/s'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t SC_VehicleSpeedMS_Cmd_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  // Enables autonomous motion commands
  uint8_t SC_Enable;                  //      Bits= 1 Unit:'-'

  // Emergency stop request (highest priority)
  //  0 : "NONE"
  //  1 : "EMERGENCY"
  uint8_t SC_Emergency;                   //      Bits= 1 Unit:'-'

  uint8_t SC_Reserved_1;                        //      Bits= 1 Unit:'-'

  // Gear request code (expanded field)
  //  0 : "NONE"
  //  1 : "NEUTRAL"
  //  2 : "DRIVE"
  //  20 : "REVERSE"
  //  22 : "PARK"
  uint8_t SC_Gear;                           //      Bits= 5 Unit:'-'

  // Must be sent as 0
  uint8_t SC_Reserved_2;                        //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t SC_Reserved_3;                        //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t SC_Reserved_4;                        //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t SC_Reserved_5;                        //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t SC_Reserved;                          //      Bits= 4 Unit:'-'

  // Rolling counter (0?255)
  uint8_t SC_AliveCounter;                      //      Bits= 8 Unit:'-'

  // CRC-8 AUTOSAR over Byte0?Byte6
  uint8_t SC_Crc8;                              //      Bits= 8 Unit:'-'

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

} SPEED_CONTROL_MSG_t;

// PC/UI -> VCU: clear a latched driver intervention. Reception of this frame (any payload value) is the ONLY way to clear an intervention and re-permit entering an autonomous mode - not auto-cleared by mode transitions anymore.
// def @CLEAR_INTERVENTION_CMD CAN Message (67764226 0x40a0002)
#define CLEAR_INTERVENTION_CMD_IDE (1U)
#define CLEAR_INTERVENTION_CMD_DLC (1U)
#define CLEAR_INTERVENTION_CMD_CANID (0x40a0002U)

typedef struct
{
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

  // Any value triggers the clear; payload is not otherwise interpreted.
  uint8_t ClearInterventionCmd;               //      Bits= 8 Unit:'-'

#else

  // Any value triggers the clear; payload is not otherwise interpreted.
  uint8_t ClearInterventionCmd;               //      Bits= 8 Unit:'-'

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

} CLEAR_INTERVENTION_CMD_t;

// def @DIRECT_CONTROL_MSG CAN Message (70455298 0x4331002)
#define DIRECT_CONTROL_MSG_IDE (1U)
#define DIRECT_CONTROL_MSG_DLC (8U)
#define DIRECT_CONTROL_MSG_CANID (0x4331002U)
// signal: @DC_Throttle_ro
#define VEHICLE_CMD_STATUS_MODULE_DBC_DC_Throttle_ro_CovFactor (0.001)
#define VEHICLE_CMD_STATUS_MODULE_DBC_DC_Throttle_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.001)) )
#define VEHICLE_CMD_STATUS_MODULE_DBC_DC_Throttle_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @DC_Steering_ro
#define VEHICLE_CMD_STATUS_MODULE_DBC_DC_Steering_ro_CovFactor (0.001)
#define VEHICLE_CMD_STATUS_MODULE_DBC_DC_Steering_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.001)) )
#define VEHICLE_CMD_STATUS_MODULE_DBC_DC_Steering_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )

// Value tables for @DC_Gear signal

#ifndef DC_Gear_DIRECT_CONTROL_MSG_P
#define DC_Gear_DIRECT_CONTROL_MSG_P (0)
#endif

#ifndef DC_Gear_DIRECT_CONTROL_MSG_R
#define DC_Gear_DIRECT_CONTROL_MSG_R (1)
#endif

#ifndef DC_Gear_DIRECT_CONTROL_MSG_N
#define DC_Gear_DIRECT_CONTROL_MSG_N (2)
#endif

#ifndef DC_Gear_DIRECT_CONTROL_MSG_D
#define DC_Gear_DIRECT_CONTROL_MSG_D (3)
#endif


// Value tables for @DC_Handbrake signal

#ifndef DC_Handbrake_DIRECT_CONTROL_MSG_RELEASE
#define DC_Handbrake_DIRECT_CONTROL_MSG_RELEASE (0)
#endif

#ifndef DC_Handbrake_DIRECT_CONTROL_MSG_HANDLE
#define DC_Handbrake_DIRECT_CONTROL_MSG_HANDLE (1)
#endif


// Value tables for @DC_Emergency signal

#ifndef DC_Emergency_DIRECT_CONTROL_MSG_NONE
#define DC_Emergency_DIRECT_CONTROL_MSG_NONE (0)
#endif

#ifndef DC_Emergency_DIRECT_CONTROL_MSG_EMERGENCY
#define DC_Emergency_DIRECT_CONTROL_MSG_EMERGENCY (1)
#endif


typedef struct
{
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

  int16_t DC_Throttle_ro;                    //  [-] Bits=16 Factor= 0.001           Unit:'-'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t DC_Throttle_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  int16_t DC_Steering_ro;                    //  [-] Bits=16 Factor= 0.001           Unit:'-'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t DC_Steering_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  //  0 : "P"
  //  1 : "R"
  //  2 : "N"
  //  3 : "D"
  uint8_t DC_Gear : 2;                       //      Bits= 2 Unit:'-'

  //  0 : "RELEASE"
  //  1 : "HANDLE"
  uint8_t DC_Handbrake : 1;                  //      Bits= 1 Unit:'-'

  //  0 : "NONE"
  //  1 : "EMERGENCY"
  uint8_t DC_Emergency : 1;                  //      Bits= 1 Unit:'-'

  // -
  uint8_t DC_Enable : 1;                     //      Bits= 1 Unit:'-'

  uint8_t DC_AliveCounter;                   //      Bits= 8 Unit:'-'

  uint8_t DC_Crc8;                           //      Bits= 8 Unit:'-'

#else

  int16_t DC_Throttle_ro;                    //  [-] Bits=16 Factor= 0.001           Unit:'-'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t DC_Throttle_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  int16_t DC_Steering_ro;                    //  [-] Bits=16 Factor= 0.001           Unit:'-'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t DC_Steering_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  //  0 : "P"
  //  1 : "R"
  //  2 : "N"
  //  3 : "D"
  uint8_t DC_Gear;                           //      Bits= 2 Unit:'-'

  //  0 : "RELEASE"
  //  1 : "HANDLE"
  uint8_t DC_Handbrake;                      //      Bits= 1 Unit:'-'

  //  0 : "NONE"
  //  1 : "EMERGENCY"
  uint8_t DC_Emergency;                      //      Bits= 1 Unit:'-'

  // -
  uint8_t DC_Enable;                         //      Bits= 1 Unit:'-'

  uint8_t DC_AliveCounter;                   //      Bits= 8 Unit:'-'

  uint8_t DC_Crc8;                           //      Bits= 8 Unit:'-'

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

} DIRECT_CONTROL_MSG_t;

// def @SAFE_STAT_ROS2_HEARTBEAT CAN Message (134873103 0x80a000f)
#define SAFE_STAT_ROS2_HEARTBEAT_IDE (1U)
#define SAFE_STAT_ROS2_HEARTBEAT_DLC (8U)
#define SAFE_STAT_ROS2_HEARTBEAT_CANID (0x80a000fU)

typedef struct
{
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

  // ROS 2 time in milliseconds
  uint64_t ROS_Time_ms;                      //      Bits=48 Unit:'ms'

  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

#else

  // ROS 2 time in milliseconds
  uint64_t ROS_Time_ms;                      //      Bits=48 Unit:'ms'

  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

} SAFE_STAT_ROS2_HEARTBEAT_t;

// def @VCU_STAT_MOTION_SI CAN Message (202702864 0xc150010)
#define VCU_STAT_MOTION_SI_IDE (1U)
#define VCU_STAT_MOTION_SI_DLC (8U)
#define VCU_STAT_MOTION_SI_CANID (0xc150010U)
// signal: @TireAngleRad_Act_ro
#define VEHICLE_CMD_STATUS_MODULE_DBC_TireAngleRad_Act_ro_CovFactor (0.001)
#define VEHICLE_CMD_STATUS_MODULE_DBC_TireAngleRad_Act_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.001)) )
#define VEHICLE_CMD_STATUS_MODULE_DBC_TireAngleRad_Act_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @VehicleSpeedMS_Act_ro
#define VEHICLE_CMD_STATUS_MODULE_DBC_VehicleSpeedMS_Act_ro_CovFactor (0.01)
#define VEHICLE_CMD_STATUS_MODULE_DBC_VehicleSpeedMS_Act_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.01)) )
#define VEHICLE_CMD_STATUS_MODULE_DBC_VehicleSpeedMS_Act_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )

typedef struct
{
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

  int16_t TireAngleRad_Act_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'rad'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t TireAngleRad_Act_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  int16_t VehicleSpeedMS_Act_ro;             //  [-] Bits=16 Factor= 0.01            Unit:'m/s'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t VehicleSpeedMS_Act_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  // Measured steer angle
  int16_t SteerAngleDeg_Act;                 //  [-] Bits=16 Unit:'degree'

  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

#else

  int16_t TireAngleRad_Act_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'rad'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t TireAngleRad_Act_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  int16_t VehicleSpeedMS_Act_ro;             //  [-] Bits=16 Factor= 0.01            Unit:'m/s'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t VehicleSpeedMS_Act_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  // Measured steer angle
  int16_t SteerAngleDeg_Act;                 //  [-] Bits=16 Unit:'degree'

  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

} VCU_STAT_MOTION_SI_t;

// def @VCU_STAT_VEHICLE_STATE CAN Message (202702865 0xc150011)
#define VCU_STAT_VEHICLE_STATE_IDE (1U)
#define VCU_STAT_VEHICLE_STATE_DLC (8U)
#define VCU_STAT_VEHICLE_STATE_CANID (0xc150011U)

// Value tables for @GearAct signal

#ifndef GearAct_VCU_STAT_VEHICLE_STATE_NONE
#define GearAct_VCU_STAT_VEHICLE_STATE_NONE (0)
#endif

#ifndef GearAct_VCU_STAT_VEHICLE_STATE_NEUTRAL
#define GearAct_VCU_STAT_VEHICLE_STATE_NEUTRAL (1)
#endif

#ifndef GearAct_VCU_STAT_VEHICLE_STATE_DRIVE
#define GearAct_VCU_STAT_VEHICLE_STATE_DRIVE (2)
#endif

#ifndef GearAct_VCU_STAT_VEHICLE_STATE_REVERSE
#define GearAct_VCU_STAT_VEHICLE_STATE_REVERSE (20)
#endif

#ifndef GearAct_VCU_STAT_VEHICLE_STATE_PARK
#define GearAct_VCU_STAT_VEHICLE_STATE_PARK (22)
#endif


typedef struct
{
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

  //  0 : "NONE"
  //  1 : "NEUTRAL"
  //  2 : "DRIVE"
  //  20 : "REVERSE"
  //  22 : "PARK"
  uint8_t GearAct : 5;                       //      Bits= 5 Unit:'-'

  uint8_t Reserved : 3;                      //      Bits= 3 Unit:'-'

  uint8_t TurnLeft_Stat : 1;                 //      Bits= 1 Unit:'-'

  uint8_t TurnRight_Stat : 1;                //      Bits= 1 Unit:'-'

  uint8_t Hazard_Stat : 1;                   //      Bits= 1 Unit:'-'

  uint8_t Horn_Stat : 1;                     //      Bits= 1 Unit:'-'

  uint8_t Reserved_1 : 4;                    //      Bits= 4 Unit:'-'

  uint8_t ControlMode;                       //      Bits= 8 Unit:'-'

  uint8_t Reserved_2;                        //      Bits= 8 Unit:'-'

  uint8_t Reserved_3;                        //      Bits= 8 Unit:'-'

  uint8_t Reserved_4;                        //      Bits= 8 Unit:'-'

  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

#else

  //  0 : "NONE"
  //  1 : "NEUTRAL"
  //  2 : "DRIVE"
  //  20 : "REVERSE"
  //  22 : "PARK"
  uint8_t GearAct;                           //      Bits= 5 Unit:'-'

  uint8_t Reserved;                          //      Bits= 3 Unit:'-'

  uint8_t TurnLeft_Stat;                     //      Bits= 1 Unit:'-'

  uint8_t TurnRight_Stat;                    //      Bits= 1 Unit:'-'

  uint8_t Hazard_Stat;                       //      Bits= 1 Unit:'-'

  uint8_t Horn_Stat;                         //      Bits= 1 Unit:'-'

  uint8_t Reserved_1;                        //      Bits= 4 Unit:'-'

  uint8_t ControlMode;                       //      Bits= 8 Unit:'-'

  uint8_t Reserved_2;                        //      Bits= 8 Unit:'-'

  uint8_t Reserved_3;                        //      Bits= 8 Unit:'-'

  uint8_t Reserved_4;                        //      Bits= 8 Unit:'-'

  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

} VCU_STAT_VEHICLE_STATE_t;

// Vehicle control module CAN comm period monitor: measured average periods of DIRECT_CONTROL_MSG and SPEED_CONTROL_MSG, plus their message-rate error flags.
// def @VCU_STAT_COMM_STATUS CAN Message (202702866 0xc150012)
#define VCU_STAT_COMM_STATUS_IDE (1U)
#define VCU_STAT_COMM_STATUS_DLC (5U)
#define VCU_STAT_COMM_STATUS_CANID (0xc150012U)

typedef struct
{
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

  // Measured average period of DIRECT_CONTROL_MSG in milliseconds. 0 = no messages received.
  uint16_t DcCommPeriod;                     //      Bits=16 Unit:'ms'

  // Measured average period of SPEED_CONTROL_MSG in milliseconds. 0 = no messages received.
  uint16_t ScCommPeriod;                    //      Bits=16 Unit:'ms'

  // 1 if DIRECT_CONTROL_MSG frame rate is outside expected limits.
  uint8_t ErrCommDirectControl : 1;             //      Bits= 1 Unit:'-'

  // 1 if SPEED_CONTROL_MSG frame rate is outside expected limits.
  uint8_t ErrCommSpeedControl : 1;             //      Bits= 1 Unit:'-'

#else

  // Measured average period of DIRECT_CONTROL_MSG in milliseconds. 0 = no messages received.
  uint16_t DcCommPeriod;                     //      Bits=16 Unit:'ms'

  // Measured average period of SPEED_CONTROL_MSG in milliseconds. 0 = no messages received.
  uint16_t ScCommPeriod;                    //      Bits=16 Unit:'ms'

  // 1 if DIRECT_CONTROL_MSG frame rate is outside expected limits.
  uint8_t ErrCommDirectControl;                 //      Bits= 1 Unit:'-'

  // 1 if SPEED_CONTROL_MSG frame rate is outside expected limits.
  uint8_t ErrCommSpeedControl;                 //      Bits= 1 Unit:'-'

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

} VCU_STAT_COMM_STATUS_t;

// Vehicle dynamics repacked from the raw vehicle-bus ESC_50 (0x102) CAN-FD frame into a classic 8-byte extended-ID message, since the PC/OBD-facing bus does not support CAN-FD.
// def @VCU_STAT_DYNAMICS_SI CAN Message (202702867 0xc150013)
#define VCU_STAT_DYNAMICS_SI_IDE (1U)
#define VCU_STAT_DYNAMICS_SI_DLC (6U)
#define VCU_STAT_DYNAMICS_SI_CANID (0xc150013U)
// signal: @LateralAccelMS2_ro (same factor/offset as vehicle ESC_50 Lateral_Accel)
#define VEHICLE_CMD_STATUS_MODULE_DBC_LateralAccelMS2_ro_CovFactor (0.15)
#define VEHICLE_CMD_STATUS_MODULE_DBC_LateralAccelMS2_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.15)) )
#define VEHICLE_CMD_STATUS_MODULE_DBC_LateralAccelMS2_ro_fromS(x) ( (((x) * (0.15)) + (0.0)) )
// signal: @LongitudinalAccelMS2_ro (same factor/offset as vehicle ESC_50 Longitudinal_Accel)
#define VEHICLE_CMD_STATUS_MODULE_DBC_LongitudinalAccelMS2_ro_CovFactor (0.03125)
#define VEHICLE_CMD_STATUS_MODULE_DBC_LongitudinalAccelMS2_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.03125)) )
#define VEHICLE_CMD_STATUS_MODULE_DBC_LongitudinalAccelMS2_ro_fromS(x) ( (((x) * (0.03125)) + (0.0)) )
// signal: @YawRateDegS_ro
#define VEHICLE_CMD_STATUS_MODULE_DBC_YawRateDegS_ro_CovFactor (0.01)
#define VEHICLE_CMD_STATUS_MODULE_DBC_YawRateDegS_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.01)) )
#define VEHICLE_CMD_STATUS_MODULE_DBC_YawRateDegS_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )

typedef struct
{
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

  int16_t LateralAccelMS2_ro;                //  [-] Bits=16 Factor= 0.15             Unit:'m/s2'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t LateralAccelMS2_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  int16_t LongitudinalAccelMS2_ro;           //  [-] Bits=16 Factor= 0.03125          Unit:'m/s2'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t LongitudinalAccelMS2_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  int16_t YawRateDegS_ro;                    //  [-] Bits=16 Factor= 0.01            Unit:'deg/s'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t YawRateDegS_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

#else

  int16_t LateralAccelMS2_ro;                //  [-] Bits=16 Factor= 0.15             Unit:'m/s2'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t LateralAccelMS2_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  int16_t LongitudinalAccelMS2_ro;           //  [-] Bits=16 Factor= 0.03125          Unit:'m/s2'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t LongitudinalAccelMS2_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  int16_t YawRateDegS_ro;                    //  [-] Bits=16 Factor= 0.01            Unit:'deg/s'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t YawRateDegS_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

} VCU_STAT_DYNAMICS_SI_t;

// CAN RX-to-task queue drop counters (main.c CAN_ENQUEUE) - visibility into otherwise-silent frame loss between the CAN ISR and vTaskCANReceiver.
// def @VCU_STAT_QUEUE_DROPS CAN Message (202702868 0xc150014)
#define VCU_STAT_QUEUE_DROPS_IDE (1U)
#define VCU_STAT_QUEUE_DROPS_DLC (8U)
#define VCU_STAT_QUEUE_DROPS_CANID (0xc150014U)

typedef struct
{
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

  // Frames dropped enqueueing into xQueue_Car (gateway/brake_booster/epas/abs/transmission manipulated buses) because the queue was full.
  uint32_t CarQueueDropCount;                //      Bits=32 Unit:'-'

  // Frames dropped enqueueing into xQueue_VehicleInterface (PC/OBD-facing bus) because the queue was full.
  uint32_t VehicleInterfaceQueueDropCount;    //      Bits=32 Unit:'-'

#else

  // Frames dropped enqueueing into xQueue_Car (gateway/brake_booster/epas/abs/transmission manipulated buses) because the queue was full.
  uint32_t CarQueueDropCount;                //      Bits=32 Unit:'-'

  // Frames dropped enqueueing into xQueue_VehicleInterface (PC/OBD-facing bus) because the queue was full.
  uint32_t VehicleInterfaceQueueDropCount;    //      Bits=32 Unit:'-'

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

} VCU_STAT_QUEUE_DROPS_t;

// Physical CAN TX drop counters (can_send_frame/can_echo_frame) - a dropped echo/command frame here is exactly the kind of gap that trips a real ECU's own comm-loss detection (e.g. vehicle cluster 'steering assistance data bus missing message').
// def @VCU_STAT_TX_DROPS CAN Message (202702869 0xc150015)
#define VCU_STAT_TX_DROPS_IDE (1U)
#define VCU_STAT_TX_DROPS_DLC (8U)
#define VCU_STAT_TX_DROPS_CANID (0xc150015U)

typedef struct
{
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

  // Frames that failed to transmit on GATEWAY_MANIPULATED_CAN (CAND1) because its TX queue was full.
  uint16_t GatewayTxDropCount;                //      Bits=16 Unit:'-'

  // Frames that failed to transmit on BRAKE_BOOSTER_MANIPULATED_CAN (CAND2) because its TX queue was full.
  uint16_t BrakeBoosterTxDropCount;           //      Bits=16 Unit:'-'

  // Frames that failed to transmit on ABS_MANIPULATED_CAN (CAND7) because its TX queue was full.
  uint16_t AbsTxDropCount;                    //      Bits=16 Unit:'-'

  // Frames that failed to transmit on EPAS_MANIPULATED_CAN (CAND4) because its TX queue was full.
  uint16_t EpasTxDropCount;                   //      Bits=16 Unit:'-'

#else

  // Frames that failed to transmit on GATEWAY_MANIPULATED_CAN (CAND1) because its TX queue was full.
  uint16_t GatewayTxDropCount;                //      Bits=16 Unit:'-'

  // Frames that failed to transmit on BRAKE_BOOSTER_MANIPULATED_CAN (CAND2) because its TX queue was full.
  uint16_t BrakeBoosterTxDropCount;           //      Bits=16 Unit:'-'

  // Frames that failed to transmit on ABS_MANIPULATED_CAN (CAND7) because its TX queue was full.
  uint16_t AbsTxDropCount;                    //      Bits=16 Unit:'-'

  // Frames that failed to transmit on EPAS_MANIPULATED_CAN (CAND4) because its TX queue was full.
  uint16_t EpasTxDropCount;                   //      Bits=16 Unit:'-'

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

} VCU_STAT_TX_DROPS_t;

// Function signatures

uint32_t Unpack_SPEED_CONTROL_MSG_vehicle_cmd_status_module_dbc(SPEED_CONTROL_MSG_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT
uint32_t Pack_SPEED_CONTROL_MSG_vehicle_cmd_status_module_dbc(SPEED_CONTROL_MSG_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_SPEED_CONTROL_MSG_vehicle_cmd_status_module_dbc(SPEED_CONTROL_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_CLEAR_INTERVENTION_CMD_vehicle_cmd_status_module_dbc(CLEAR_INTERVENTION_CMD_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT
uint32_t Pack_CLEAR_INTERVENTION_CMD_vehicle_cmd_status_module_dbc(CLEAR_INTERVENTION_CMD_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_CLEAR_INTERVENTION_CMD_vehicle_cmd_status_module_dbc(CLEAR_INTERVENTION_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_DIRECT_CONTROL_MSG_vehicle_cmd_status_module_dbc(DIRECT_CONTROL_MSG_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT
uint32_t Pack_DIRECT_CONTROL_MSG_vehicle_cmd_status_module_dbc(DIRECT_CONTROL_MSG_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_DIRECT_CONTROL_MSG_vehicle_cmd_status_module_dbc(DIRECT_CONTROL_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_SAFE_STAT_ROS2_HEARTBEAT_vehicle_cmd_status_module_dbc(SAFE_STAT_ROS2_HEARTBEAT_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT
uint32_t Pack_SAFE_STAT_ROS2_HEARTBEAT_vehicle_cmd_status_module_dbc(SAFE_STAT_ROS2_HEARTBEAT_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_SAFE_STAT_ROS2_HEARTBEAT_vehicle_cmd_status_module_dbc(SAFE_STAT_ROS2_HEARTBEAT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_MOTION_SI_vehicle_cmd_status_module_dbc(VCU_STAT_MOTION_SI_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT
uint32_t Pack_VCU_STAT_MOTION_SI_vehicle_cmd_status_module_dbc(VCU_STAT_MOTION_SI_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VCU_STAT_MOTION_SI_vehicle_cmd_status_module_dbc(VCU_STAT_MOTION_SI_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_VEHICLE_STATE_vehicle_cmd_status_module_dbc(VCU_STAT_VEHICLE_STATE_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT
uint32_t Pack_VCU_STAT_VEHICLE_STATE_vehicle_cmd_status_module_dbc(VCU_STAT_VEHICLE_STATE_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VCU_STAT_VEHICLE_STATE_vehicle_cmd_status_module_dbc(VCU_STAT_VEHICLE_STATE_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_COMM_STATUS_vehicle_cmd_status_module_dbc(VCU_STAT_COMM_STATUS_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT
uint32_t Pack_VCU_STAT_COMM_STATUS_vehicle_cmd_status_module_dbc(VCU_STAT_COMM_STATUS_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VCU_STAT_COMM_STATUS_vehicle_cmd_status_module_dbc(VCU_STAT_COMM_STATUS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_DYNAMICS_SI_vehicle_cmd_status_module_dbc(VCU_STAT_DYNAMICS_SI_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT
uint32_t Pack_VCU_STAT_DYNAMICS_SI_vehicle_cmd_status_module_dbc(VCU_STAT_DYNAMICS_SI_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VCU_STAT_DYNAMICS_SI_vehicle_cmd_status_module_dbc(VCU_STAT_DYNAMICS_SI_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_QUEUE_DROPS_vehicle_cmd_status_module_dbc(VCU_STAT_QUEUE_DROPS_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT
uint32_t Pack_VCU_STAT_QUEUE_DROPS_vehicle_cmd_status_module_dbc(VCU_STAT_QUEUE_DROPS_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VCU_STAT_QUEUE_DROPS_vehicle_cmd_status_module_dbc(VCU_STAT_QUEUE_DROPS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_TX_DROPS_vehicle_cmd_status_module_dbc(VCU_STAT_TX_DROPS_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT
uint32_t Pack_VCU_STAT_TX_DROPS_vehicle_cmd_status_module_dbc(VCU_STAT_TX_DROPS_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VCU_STAT_TX_DROPS_vehicle_cmd_status_module_dbc(VCU_STAT_TX_DROPS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

#ifdef __cplusplus
}
#endif
