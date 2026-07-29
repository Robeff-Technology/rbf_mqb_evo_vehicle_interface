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


// def @VCU_CTRL_CMD_SI CAN Message (67764225 0x40a0001)
#define VCU_CTRL_CMD_SI_IDE (1U)
#define VCU_CTRL_CMD_SI_DLC (8U)
#define VCU_CTRL_CMD_SI_CANID (0x40a0001U)
// signal: @TireAngleRad_Cmd_ro
#define VEHICLE_CMD_STATUS_MODULE_DBC_TireAngleRad_Cmd_ro_CovFactor (0.001)
#define VEHICLE_CMD_STATUS_MODULE_DBC_TireAngleRad_Cmd_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.001)) )
#define VEHICLE_CMD_STATUS_MODULE_DBC_TireAngleRad_Cmd_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @VehicleSpeedMS_Cmd_ro
#define VEHICLE_CMD_STATUS_MODULE_DBC_VehicleSpeedMS_Cmd_ro_CovFactor (0.01)
#define VEHICLE_CMD_STATUS_MODULE_DBC_VehicleSpeedMS_Cmd_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.01)) )
#define VEHICLE_CMD_STATUS_MODULE_DBC_VehicleSpeedMS_Cmd_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )

// Value tables for @GearReq signal

#ifndef GearReq_VCU_CTRL_CMD_SI_NONE
#define GearReq_VCU_CTRL_CMD_SI_NONE (0)
#endif

#ifndef GearReq_VCU_CTRL_CMD_SI_NEUTRAL
#define GearReq_VCU_CTRL_CMD_SI_NEUTRAL (1)
#endif

#ifndef GearReq_VCU_CTRL_CMD_SI_DRIVE
#define GearReq_VCU_CTRL_CMD_SI_DRIVE (2)
#endif

#ifndef GearReq_VCU_CTRL_CMD_SI_REVERSE
#define GearReq_VCU_CTRL_CMD_SI_REVERSE (20)
#endif

#ifndef GearReq_VCU_CTRL_CMD_SI_PARK
#define GearReq_VCU_CTRL_CMD_SI_PARK (22)
#endif


typedef struct
{
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

  // Target tire steering angle (+left / ?right)
  int16_t TireAngleRad_Cmd_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'rad'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t TireAngleRad_Cmd_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  // Target longitudinal vehicle speed
  int16_t VehicleSpeedMS_Cmd_ro;             //  [-] Bits=16 Factor= 0.01            Unit:'m/s'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t VehicleSpeedMS_Cmd_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  // Enables autonomous motion commands
  uint8_t AutonomousEnable : 1;              //      Bits= 1 Unit:'-'

  // Emergency stop request (highest priority)
  uint8_t EmergencyActive : 1;               //      Bits= 1 Unit:'-'

  uint8_t Reserved_1 : 1;                    //      Bits= 1 Unit:'-'

  // Gear request code (expanded field)
  //  0 : "NONE"
  //  1 : "NEUTRAL"
  //  2 : "DRIVE"
  //  20 : "REVERSE"
  //  22 : "PARK"
  uint8_t GearReq : 5;                       //      Bits= 5 Unit:'-'

  // Must be sent as 0
  uint8_t Reserved_2 : 1;                    //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t Reserved_3 : 1;                    //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t Reserved_4 : 1;                    //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t Reserved_5 : 1;                    //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t Reserved : 4;                      //      Bits= 4 Unit:'-'

  // Rolling counter (0?255)
  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  // CRC-8 AUTOSAR over Byte0?Byte6
  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

#else

  // Target tire steering angle (+left / ?right)
  int16_t TireAngleRad_Cmd_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'rad'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t TireAngleRad_Cmd_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  // Target longitudinal vehicle speed
  int16_t VehicleSpeedMS_Cmd_ro;             //  [-] Bits=16 Factor= 0.01            Unit:'m/s'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t VehicleSpeedMS_Cmd_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  // Enables autonomous motion commands
  uint8_t AutonomousEnable;                  //      Bits= 1 Unit:'-'

  // Emergency stop request (highest priority)
  uint8_t EmergencyActive;                   //      Bits= 1 Unit:'-'

  uint8_t Reserved_1;                        //      Bits= 1 Unit:'-'

  // Gear request code (expanded field)
  //  0 : "NONE"
  //  1 : "NEUTRAL"
  //  2 : "DRIVE"
  //  20 : "REVERSE"
  //  22 : "PARK"
  uint8_t GearReq;                           //      Bits= 5 Unit:'-'

  // Must be sent as 0
  uint8_t Reserved_2;                        //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t Reserved_3;                        //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t Reserved_4;                        //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t Reserved_5;                        //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t Reserved;                          //      Bits= 4 Unit:'-'

  // Rolling counter (0?255)
  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  // CRC-8 AUTOSAR over Byte0?Byte6
  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

} VCU_CTRL_CMD_SI_t;

// def @REMOTE_CONTROL_MSG CAN Message (70455298 0x4331002)
#define REMOTE_CONTROL_MSG_IDE (1U)
#define REMOTE_CONTROL_MSG_DLC (8U)
#define REMOTE_CONTROL_MSG_CANID (0x4331002U)
// signal: @RC_Throttle_ro
#define VEHICLE_CMD_STATUS_MODULE_DBC_RC_Throttle_ro_CovFactor (0.001)
#define VEHICLE_CMD_STATUS_MODULE_DBC_RC_Throttle_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.001)) )
#define VEHICLE_CMD_STATUS_MODULE_DBC_RC_Throttle_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @RC_Steering_ro
#define VEHICLE_CMD_STATUS_MODULE_DBC_RC_Steering_ro_CovFactor (0.001)
#define VEHICLE_CMD_STATUS_MODULE_DBC_RC_Steering_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.001)) )
#define VEHICLE_CMD_STATUS_MODULE_DBC_RC_Steering_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )

// Value tables for @RC_Gear signal

#ifndef RC_Gear_REMOTE_CONTROL_MSG_P
#define RC_Gear_REMOTE_CONTROL_MSG_P (0)
#endif

#ifndef RC_Gear_REMOTE_CONTROL_MSG_R
#define RC_Gear_REMOTE_CONTROL_MSG_R (1)
#endif

#ifndef RC_Gear_REMOTE_CONTROL_MSG_N
#define RC_Gear_REMOTE_CONTROL_MSG_N (2)
#endif

#ifndef RC_Gear_REMOTE_CONTROL_MSG_D
#define RC_Gear_REMOTE_CONTROL_MSG_D (3)
#endif


// Value tables for @RC_Handbrake signal

#ifndef RC_Handbrake_REMOTE_CONTROL_MSG_RELEASE
#define RC_Handbrake_REMOTE_CONTROL_MSG_RELEASE (0)
#endif

#ifndef RC_Handbrake_REMOTE_CONTROL_MSG_HANDLE
#define RC_Handbrake_REMOTE_CONTROL_MSG_HANDLE (1)
#endif


// Value tables for @RC_Emergency signal

#ifndef RC_Emergency_REMOTE_CONTROL_MSG_NONE
#define RC_Emergency_REMOTE_CONTROL_MSG_NONE (0)
#endif

#ifndef RC_Emergency_REMOTE_CONTROL_MSG_EMERGENCY
#define RC_Emergency_REMOTE_CONTROL_MSG_EMERGENCY (1)
#endif


typedef struct
{
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

  int16_t RC_Throttle_ro;                    //  [-] Bits=16 Factor= 0.001           Unit:'-'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t RC_Throttle_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  int16_t RC_Steering_ro;                    //  [-] Bits=16 Factor= 0.001           Unit:'-'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t RC_Steering_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  //  0 : "P"
  //  1 : "R"
  //  2 : "N"
  //  3 : "D"
  uint8_t RC_Gear : 2;                       //      Bits= 2 Unit:'-'

  //  0 : "RELEASE"
  //  1 : "HANDLE"
  uint8_t RC_Handbrake : 1;                  //      Bits= 1 Unit:'-'

  //  0 : "NONE"
  //  1 : "EMERGENCY"
  uint8_t RC_Emergency : 1;                  //      Bits= 1 Unit:'-'

  // -
  uint8_t RC_Enable : 1;                     //      Bits= 1 Unit:'-'

  uint8_t RC_AliveCounter;                   //      Bits= 8 Unit:'-'

  uint8_t RC_Crc8;                           //      Bits= 8 Unit:'-'

#else

  int16_t RC_Throttle_ro;                    //  [-] Bits=16 Factor= 0.001           Unit:'-'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t RC_Throttle_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  int16_t RC_Steering_ro;                    //  [-] Bits=16 Factor= 0.001           Unit:'-'

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  sigfloat_t RC_Steering_phys;
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  //  0 : "P"
  //  1 : "R"
  //  2 : "N"
  //  3 : "D"
  uint8_t RC_Gear;                           //      Bits= 2 Unit:'-'

  //  0 : "RELEASE"
  //  1 : "HANDLE"
  uint8_t RC_Handbrake;                      //      Bits= 1 Unit:'-'

  //  0 : "NONE"
  //  1 : "EMERGENCY"
  uint8_t RC_Emergency;                      //      Bits= 1 Unit:'-'

  // -
  uint8_t RC_Enable;                         //      Bits= 1 Unit:'-'

  uint8_t RC_AliveCounter;                   //      Bits= 8 Unit:'-'

  uint8_t RC_Crc8;                           //      Bits= 8 Unit:'-'

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

} REMOTE_CONTROL_MSG_t;

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

// Vehicle control module CAN comm period monitor: measured average periods of REMOTE_CONTROL_MSG and VCU_CTRL_CMD_SI, plus their message-rate error flags.
// def @VCU_STAT_COMM_STATUS CAN Message (202702866 0xc150012)
#define VCU_STAT_COMM_STATUS_IDE (1U)
#define VCU_STAT_COMM_STATUS_DLC (5U)
#define VCU_STAT_COMM_STATUS_CANID (0xc150012U)

typedef struct
{
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

  // Measured average period of REMOTE_CONTROL_MSG in milliseconds. 0 = no messages received.
  uint16_t RcCommPeriod;                     //      Bits=16 Unit:'ms'

  // Measured average period of VCU_CTRL_CMD_SI in milliseconds. 0 = no messages received.
  uint16_t CmdCommPeriod;                    //      Bits=16 Unit:'ms'

  // 1 if REMOTE_CONTROL_MSG frame rate is outside expected limits.
  uint8_t ErrCommRemoteCtrl : 1;             //      Bits= 1 Unit:'-'

  // 1 if VCU_CTRL_CMD_SI frame rate is outside expected limits.
  uint8_t ErrCommVcuCtrlCmd : 1;             //      Bits= 1 Unit:'-'

#else

  // Measured average period of REMOTE_CONTROL_MSG in milliseconds. 0 = no messages received.
  uint16_t RcCommPeriod;                     //      Bits=16 Unit:'ms'

  // Measured average period of VCU_CTRL_CMD_SI in milliseconds. 0 = no messages received.
  uint16_t CmdCommPeriod;                    //      Bits=16 Unit:'ms'

  // 1 if REMOTE_CONTROL_MSG frame rate is outside expected limits.
  uint8_t ErrCommRemoteCtrl;                 //      Bits= 1 Unit:'-'

  // 1 if VCU_CTRL_CMD_SI frame rate is outside expected limits.
  uint8_t ErrCommVcuCtrlCmd;                 //      Bits= 1 Unit:'-'

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_BITS_SIGNAL

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

} VCU_STAT_COMM_STATUS_t;

// Function signatures

uint32_t Unpack_VCU_CTRL_CMD_SI_vehicle_cmd_status_module_dbc(VCU_CTRL_CMD_SI_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT
uint32_t Pack_VCU_CTRL_CMD_SI_vehicle_cmd_status_module_dbc(VCU_CTRL_CMD_SI_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VCU_CTRL_CMD_SI_vehicle_cmd_status_module_dbc(VCU_CTRL_CMD_SI_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_REMOTE_CONTROL_MSG_vehicle_cmd_status_module_dbc(REMOTE_CONTROL_MSG_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT
uint32_t Pack_REMOTE_CONTROL_MSG_vehicle_cmd_status_module_dbc(REMOTE_CONTROL_MSG_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_REMOTE_CONTROL_MSG_vehicle_cmd_status_module_dbc(REMOTE_CONTROL_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
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

// --- Manually maintained (not part of the generated DBC output) ---------------
// def @CLEAR_INTERVENTION_CMD CAN Message (67764226 0x40a0002)
// Payload carries no signals: all 8 data bytes are sent as zero.
#define CLEAR_INTERVENTION_CMD_IDE (1U)
#define CLEAR_INTERVENTION_CMD_DLC (8U)
#define CLEAR_INTERVENTION_CMD_CANID (0x40a0002U)

#ifdef __cplusplus
}
#endif
