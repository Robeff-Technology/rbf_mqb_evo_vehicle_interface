// Generator version : v3.1
// DBC filename      : pc_vcu_can_500k_v1.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// DBC file version
#define VER_PC_VCU_MAJ (0U)
#define VER_PC_VCU_MIN (0U)

// include current dbc-driver compilation config
#include "pc_vcu-config.h"

#ifdef PC_VCU_USE_DIAG_MONITORS
// This file must define:
// base monitor struct
#include "canmonitorutil.h"

#endif // PC_VCU_USE_DIAG_MONITORS


// DLC maximum value which is used as the limit for frame's data buffer size.
// Client can set its own value (not sure why) in driver-config
// or can test it on some limit specified by application
// e.g.: static_assert(TESTDB_MAX_DLC_VALUE <= APPLICATION_FRAME_DATA_SIZE, "Max DLC value in the driver is too big")
#ifndef PC_VCU_MAX_DLC_VALUE
// The value which was found out by generator (real max value)
#define PC_VCU_MAX_DLC_VALUE 8U
#endif

// The limit is used for setting frame's data bytes
#define PC_VCU_VALIDATE_DLC(msgDlc) (((msgDlc) <= (PC_VCU_MAX_DLC_VALUE)) ? (msgDlc) : (PC_VCU_MAX_DLC_VALUE))

// Initial byte value to be filles in data bytes of the frame before pack signals
// User can define its own custom value in driver-config file
#ifndef PC_VCU_INITIAL_BYTE_VALUE
#define PC_VCU_INITIAL_BYTE_VALUE 0U
#endif


// 50 Hz
// def @VCU_STAT_MOTION_SI CAN Message (502203408 0x1def0410)
#define VCU_STAT_MOTION_SI_IDE (1U)
#define VCU_STAT_MOTION_SI_DLC (8U)
#define VCU_STAT_MOTION_SI_CANID (0x1def0410U)
// signal: @TireAngleRad_Act_ro
#define PC_VCU_TireAngleRad_Act_ro_CovFactor (0.001)
#define PC_VCU_TireAngleRad_Act_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.001)) )
#define PC_VCU_TireAngleRad_Act_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @VehicleSpeedMS_Act_ro
#define PC_VCU_VehicleSpeedMS_Act_ro_CovFactor (0.01)
#define PC_VCU_VehicleSpeedMS_Act_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.01)) )
#define PC_VCU_VehicleSpeedMS_Act_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )

typedef struct
{
#ifdef PC_VCU_USE_BITS_SIGNAL

  int16_t TireAngleRad_Act_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'rad'

#ifdef PC_VCU_USE_SIGFLOAT
  sigfloat_t TireAngleRad_Act_phys;
#endif // PC_VCU_USE_SIGFLOAT

  int16_t VehicleSpeedMS_Act_ro;             //  [-] Bits=16 Factor= 0.01            Unit:'m/s'

#ifdef PC_VCU_USE_SIGFLOAT
  sigfloat_t VehicleSpeedMS_Act_phys;
#endif // PC_VCU_USE_SIGFLOAT

  uint16_t Reserved;                         //      Bits=16

  uint8_t AliveCounter;                      //      Bits= 8

  uint8_t CRC8;                              //      Bits= 8

#else

  int16_t TireAngleRad_Act_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'rad'

#ifdef PC_VCU_USE_SIGFLOAT
  sigfloat_t TireAngleRad_Act_phys;
#endif // PC_VCU_USE_SIGFLOAT

  int16_t VehicleSpeedMS_Act_ro;             //  [-] Bits=16 Factor= 0.01            Unit:'m/s'

#ifdef PC_VCU_USE_SIGFLOAT
  sigfloat_t VehicleSpeedMS_Act_phys;
#endif // PC_VCU_USE_SIGFLOAT

  uint16_t Reserved;                         //      Bits=16

  uint8_t AliveCounter;                      //      Bits= 8

  uint8_t CRC8;                              //      Bits= 8

#endif // PC_VCU_USE_BITS_SIGNAL

#ifdef PC_VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // PC_VCU_USE_DIAG_MONITORS

} VCU_STAT_MOTION_SI_t;

// 10 Hz
// def @VCU_STAT_VEHICLE_STATE CAN Message (502203409 0x1def0411)
#define VCU_STAT_VEHICLE_STATE_IDE (1U)
#define VCU_STAT_VEHICLE_STATE_DLC (8U)
#define VCU_STAT_VEHICLE_STATE_CANID (0x1def0411U)

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
#ifdef PC_VCU_USE_BITS_SIGNAL

  //  0 : "NONE"
  //  1 : "NEUTRAL"
  //  2 : "DRIVE"
  //  20 : "REVERSE"
  //  22 : "PARK"
  uint8_t GearAct : 4;                       //      Bits= 4

  uint8_t Reserved : 4;                      //      Bits= 4

  uint8_t TurnLeft_Stat : 1;                 //      Bits= 1

  uint8_t TurnRight_Stat : 1;                //      Bits= 1

  uint8_t Hazard_Stat : 1;                   //      Bits= 1

  uint8_t Horn_Stat : 1;                     //      Bits= 1

  uint8_t Reserved_1 : 4;                    //      Bits= 4

  uint8_t ControlMode;                       //      Bits= 8

  uint8_t SafetyState;                       //      Bits= 8

  uint8_t BatterySoC;                        //      Bits= 8

  uint8_t FaultSummary;                      //      Bits= 8

  uint8_t AliveCounter;                      //      Bits= 8

  uint8_t CRC8;                              //      Bits= 8

#else

  //  0 : "NONE"
  //  1 : "NEUTRAL"
  //  2 : "DRIVE"
  //  20 : "REVERSE"
  //  22 : "PARK"
  uint8_t GearAct;                           //      Bits= 4

  uint8_t Reserved;                          //      Bits= 4

  uint8_t TurnLeft_Stat;                     //      Bits= 1

  uint8_t TurnRight_Stat;                    //      Bits= 1

  uint8_t Hazard_Stat;                       //      Bits= 1

  uint8_t Horn_Stat;                         //      Bits= 1

  uint8_t Reserved_1;                        //      Bits= 4

  uint8_t ControlMode;                       //      Bits= 8

  uint8_t SafetyState;                       //      Bits= 8

  uint8_t BatterySoC;                        //      Bits= 8

  uint8_t FaultSummary;                      //      Bits= 8

  uint8_t AliveCounter;                      //      Bits= 8

  uint8_t CRC8;                              //      Bits= 8

#endif // PC_VCU_USE_BITS_SIGNAL

#ifdef PC_VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // PC_VCU_USE_DIAG_MONITORS

} VCU_STAT_VEHICLE_STATE_t;

// 50 Hz
// def @VCU_CTRL_CMD_SI CAN Message (502247424 0x1defb000)
#define VCU_CTRL_CMD_SI_IDE (1U)
#define VCU_CTRL_CMD_SI_DLC (8U)
#define VCU_CTRL_CMD_SI_CANID (0x1defb000U)
#define VCU_CTRL_CMD_SI_CYC (20U)
// signal: @TireAngleRad_Cmd_ro
#define PC_VCU_TireAngleRad_Cmd_ro_CovFactor (0.001)
#define PC_VCU_TireAngleRad_Cmd_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.001)) )
#define PC_VCU_TireAngleRad_Cmd_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @VehicleSpeedMS_Cmd_ro
#define PC_VCU_VehicleSpeedMS_Cmd_ro_CovFactor (0.01)
#define PC_VCU_VehicleSpeedMS_Cmd_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.01)) )
#define PC_VCU_VehicleSpeedMS_Cmd_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )

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
#ifdef PC_VCU_USE_BITS_SIGNAL

  // Target tire steering angle (+left / ?right)
  int16_t TireAngleRad_Cmd_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'rad'

#ifdef PC_VCU_USE_SIGFLOAT
  sigfloat_t TireAngleRad_Cmd_phys;
#endif // PC_VCU_USE_SIGFLOAT

  // Target longitudinal vehicle speed
  int16_t VehicleSpeedMS_Cmd_ro;             //  [-] Bits=16 Factor= 0.01            Unit:'m/s'

#ifdef PC_VCU_USE_SIGFLOAT
  sigfloat_t VehicleSpeedMS_Cmd_phys;
#endif // PC_VCU_USE_SIGFLOAT

  // Enables autonomous motion commands
  uint8_t AutonomousEnable : 1;              //      Bits= 1

  // Emergency stop request (highest priority)
  uint8_t EmergencyActive : 1;               //      Bits= 1

  // 1 = disable internal ECU safety checks
  uint8_t SafetyDisable : 1;                 //      Bits= 1

  // Gear request code (expanded field)
  //  0 : "NONE"
  //  1 : "NEUTRAL"
  //  2 : "DRIVE"
  //  20 : "REVERSE"
  //  22 : "PARK"
  uint8_t GearReq : 5;                       //      Bits= 5

  // Left turn indicator request
  uint8_t TurnLeft : 1;                      //      Bits= 1

  // Right turn indicator request
  uint8_t TurnRight : 1;                     //      Bits= 1

  // Hazard lights (overrides turn signals)
  uint8_t Hazard : 1;                        //      Bits= 1

  // Horn command (momentary)
  uint8_t Horn : 1;                          //      Bits= 1

  // Must be sent as 0
  uint8_t Reserved : 4;                      //      Bits= 4

  // Rolling counter (0?255)
  uint8_t AliveCounter;                      //      Bits= 8

  // CRC-8 AUTOSAR over Byte0?Byte6
  uint8_t CRC8;                              //      Bits= 8

#else

  // Target tire steering angle (+left / ?right)
  int16_t TireAngleRad_Cmd_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'rad'

#ifdef PC_VCU_USE_SIGFLOAT
  sigfloat_t TireAngleRad_Cmd_phys;
#endif // PC_VCU_USE_SIGFLOAT

  // Target longitudinal vehicle speed
  int16_t VehicleSpeedMS_Cmd_ro;             //  [-] Bits=16 Factor= 0.01            Unit:'m/s'

#ifdef PC_VCU_USE_SIGFLOAT
  sigfloat_t VehicleSpeedMS_Cmd_phys;
#endif // PC_VCU_USE_SIGFLOAT

  // Enables autonomous motion commands
  uint8_t AutonomousEnable;                  //      Bits= 1

  // Emergency stop request (highest priority)
  uint8_t EmergencyActive;                   //      Bits= 1

  // 1 = disable internal ECU safety checks
  uint8_t SafetyDisable;                     //      Bits= 1

  // Gear request code (expanded field)
  //  0 : "NONE"
  //  1 : "NEUTRAL"
  //  2 : "DRIVE"
  //  20 : "REVERSE"
  //  22 : "PARK"
  uint8_t GearReq;                           //      Bits= 5

  // Left turn indicator request
  uint8_t TurnLeft;                          //      Bits= 1

  // Right turn indicator request
  uint8_t TurnRight;                         //      Bits= 1

  // Hazard lights (overrides turn signals)
  uint8_t Hazard;                            //      Bits= 1

  // Horn command (momentary)
  uint8_t Horn;                              //      Bits= 1

  // Must be sent as 0
  uint8_t Reserved;                          //      Bits= 4

  // Rolling counter (0?255)
  uint8_t AliveCounter;                      //      Bits= 8

  // CRC-8 AUTOSAR over Byte0?Byte6
  uint8_t CRC8;                              //      Bits= 8

#endif // PC_VCU_USE_BITS_SIGNAL

#ifdef PC_VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // PC_VCU_USE_DIAG_MONITORS

} VCU_CTRL_CMD_SI_t;

// 20 Hz
// def @SAFE_STAT_ROS2_HEARTBEAT CAN Message (502247425 0x1defb001)
#define SAFE_STAT_ROS2_HEARTBEAT_IDE (1U)
#define SAFE_STAT_ROS2_HEARTBEAT_DLC (8U)
#define SAFE_STAT_ROS2_HEARTBEAT_CANID (0x1defb001U)

typedef struct
{
#ifdef PC_VCU_USE_BITS_SIGNAL

  // ROS 2 time in milliseconds
  uint64_t ROS_Time_ms;                      //      Bits=48 Unit:'ms'

  uint8_t AliveCounter;                      //      Bits= 8

  uint8_t CRC8;                              //      Bits= 8

#else

  // ROS 2 time in milliseconds
  uint64_t ROS_Time_ms;                      //      Bits=48 Unit:'ms'

  uint8_t AliveCounter;                      //      Bits= 8

  uint8_t CRC8;                              //      Bits= 8

#endif // PC_VCU_USE_BITS_SIGNAL

#ifdef PC_VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // PC_VCU_USE_DIAG_MONITORS

} SAFE_STAT_ROS2_HEARTBEAT_t;

// Function signatures

uint32_t Unpack_VCU_STAT_MOTION_SI_pc_vcu(VCU_STAT_MOTION_SI_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef PC_VCU_USE_CANSTRUCT
uint32_t Pack_VCU_STAT_MOTION_SI_pc_vcu(VCU_STAT_MOTION_SI_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VCU_STAT_MOTION_SI_pc_vcu(VCU_STAT_MOTION_SI_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // PC_VCU_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_VEHICLE_STATE_pc_vcu(VCU_STAT_VEHICLE_STATE_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef PC_VCU_USE_CANSTRUCT
uint32_t Pack_VCU_STAT_VEHICLE_STATE_pc_vcu(VCU_STAT_VEHICLE_STATE_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VCU_STAT_VEHICLE_STATE_pc_vcu(VCU_STAT_VEHICLE_STATE_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // PC_VCU_USE_CANSTRUCT

uint32_t Unpack_VCU_CTRL_CMD_SI_pc_vcu(VCU_CTRL_CMD_SI_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef PC_VCU_USE_CANSTRUCT
uint32_t Pack_VCU_CTRL_CMD_SI_pc_vcu(VCU_CTRL_CMD_SI_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VCU_CTRL_CMD_SI_pc_vcu(VCU_CTRL_CMD_SI_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // PC_VCU_USE_CANSTRUCT

uint32_t Unpack_SAFE_STAT_ROS2_HEARTBEAT_pc_vcu(SAFE_STAT_ROS2_HEARTBEAT_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef PC_VCU_USE_CANSTRUCT
uint32_t Pack_SAFE_STAT_ROS2_HEARTBEAT_pc_vcu(SAFE_STAT_ROS2_HEARTBEAT_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_SAFE_STAT_ROS2_HEARTBEAT_pc_vcu(SAFE_STAT_ROS2_HEARTBEAT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // PC_VCU_USE_CANSTRUCT

#ifdef __cplusplus
}
#endif
