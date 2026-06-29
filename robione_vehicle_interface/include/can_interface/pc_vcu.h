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


// def @SAFETY_MANAGER_STATUS CAN Message (65537 0x10001)
#define SAFETY_MANAGER_STATUS_IDE (1U)
#define SAFETY_MANAGER_STATUS_DLC (8U)
#define SAFETY_MANAGER_STATUS_CANID (0x10001U)

// Value tables for @SM_CurrentLevel signal

#ifndef SM_CurrentLevel_SAFETY_MANAGER_STATUS_None
#define SM_CurrentLevel_SAFETY_MANAGER_STATUS_None (0)
#endif

#ifndef SM_CurrentLevel_SAFETY_MANAGER_STATUS_Warning
#define SM_CurrentLevel_SAFETY_MANAGER_STATUS_Warning (1)
#endif

#ifndef SM_CurrentLevel_SAFETY_MANAGER_STATUS_Error
#define SM_CurrentLevel_SAFETY_MANAGER_STATUS_Error (2)
#endif

#ifndef SM_CurrentLevel_SAFETY_MANAGER_STATUS_Critical
#define SM_CurrentLevel_SAFETY_MANAGER_STATUS_Critical (3)
#endif


// Value tables for @SM_PreviousLevel signal

#ifndef SM_PreviousLevel_SAFETY_MANAGER_STATUS_None
#define SM_PreviousLevel_SAFETY_MANAGER_STATUS_None (0)
#endif

#ifndef SM_PreviousLevel_SAFETY_MANAGER_STATUS_Warning
#define SM_PreviousLevel_SAFETY_MANAGER_STATUS_Warning (1)
#endif

#ifndef SM_PreviousLevel_SAFETY_MANAGER_STATUS_Error
#define SM_PreviousLevel_SAFETY_MANAGER_STATUS_Error (2)
#endif

#ifndef SM_PreviousLevel_SAFETY_MANAGER_STATUS_Critical
#define SM_PreviousLevel_SAFETY_MANAGER_STATUS_Critical (3)
#endif


// Value tables for @SM_EmergencyStopActive signal

#ifndef SM_EmergencyStopActive_SAFETY_MANAGER_STATUS_Inactive
#define SM_EmergencyStopActive_SAFETY_MANAGER_STATUS_Inactive (0)
#endif

#ifndef SM_EmergencyStopActive_SAFETY_MANAGER_STATUS_Active
#define SM_EmergencyStopActive_SAFETY_MANAGER_STATUS_Active (1)
#endif


// Value tables for @SM_LastErrorLevel signal

#ifndef SM_LastErrorLevel_SAFETY_MANAGER_STATUS_None
#define SM_LastErrorLevel_SAFETY_MANAGER_STATUS_None (0)
#endif

#ifndef SM_LastErrorLevel_SAFETY_MANAGER_STATUS_Warning
#define SM_LastErrorLevel_SAFETY_MANAGER_STATUS_Warning (1)
#endif

#ifndef SM_LastErrorLevel_SAFETY_MANAGER_STATUS_Error
#define SM_LastErrorLevel_SAFETY_MANAGER_STATUS_Error (2)
#endif

#ifndef SM_LastErrorLevel_SAFETY_MANAGER_STATUS_Critical
#define SM_LastErrorLevel_SAFETY_MANAGER_STATUS_Critical (3)
#endif


// Value tables for @SM_Err_EmergencyButton signal

#ifndef SM_Err_EmergencyButton_SAFETY_MANAGER_STATUS_Normal
#define SM_Err_EmergencyButton_SAFETY_MANAGER_STATUS_Normal (0)
#endif

#ifndef SM_Err_EmergencyButton_SAFETY_MANAGER_STATUS_Pressed
#define SM_Err_EmergencyButton_SAFETY_MANAGER_STATUS_Pressed (1)
#endif


// Value tables for @SM_ErrRCEmergency signal

#ifndef SM_ErrRCEmergency_SAFETY_MANAGER_STATUS_Normal
#define SM_ErrRCEmergency_SAFETY_MANAGER_STATUS_Normal (0)
#endif

#ifndef SM_ErrRCEmergency_SAFETY_MANAGER_STATUS_Active
#define SM_ErrRCEmergency_SAFETY_MANAGER_STATUS_Active (1)
#endif


// Value tables for @SM_ErrGPIO signal

#ifndef SM_ErrGPIO_SAFETY_MANAGER_STATUS_Normal
#define SM_ErrGPIO_SAFETY_MANAGER_STATUS_Normal (0)
#endif

#ifndef SM_ErrGPIO_SAFETY_MANAGER_STATUS_Error
#define SM_ErrGPIO_SAFETY_MANAGER_STATUS_Error (1)
#endif


// Value tables for @SM_ErrSysMon signal

#ifndef SM_ErrSysMon_SAFETY_MANAGER_STATUS_Normal
#define SM_ErrSysMon_SAFETY_MANAGER_STATUS_Normal (0)
#endif

#ifndef SM_ErrSysMon_SAFETY_MANAGER_STATUS_Error
#define SM_ErrSysMon_SAFETY_MANAGER_STATUS_Error (1)
#endif


// Value tables for @SM_ErrSteer signal

#ifndef SM_ErrSteer_SAFETY_MANAGER_STATUS_Normal
#define SM_ErrSteer_SAFETY_MANAGER_STATUS_Normal (0)
#endif

#ifndef SM_ErrSteer_SAFETY_MANAGER_STATUS_Error
#define SM_ErrSteer_SAFETY_MANAGER_STATUS_Error (1)
#endif


// Value tables for @SM_ErrBrake signal

#ifndef SM_ErrBrake_SAFETY_MANAGER_STATUS_Normal
#define SM_ErrBrake_SAFETY_MANAGER_STATUS_Normal (0)
#endif

#ifndef SM_ErrBrake_SAFETY_MANAGER_STATUS_Error
#define SM_ErrBrake_SAFETY_MANAGER_STATUS_Error (1)
#endif


// Value tables for @SM_ErrRC signal

#ifndef SM_ErrRC_SAFETY_MANAGER_STATUS_Normal
#define SM_ErrRC_SAFETY_MANAGER_STATUS_Normal (0)
#endif

#ifndef SM_ErrRC_SAFETY_MANAGER_STATUS_Error
#define SM_ErrRC_SAFETY_MANAGER_STATUS_Error (1)
#endif


// Value tables for @SM_Err_PCVCU signal

#ifndef SM_Err_PCVCU_SAFETY_MANAGER_STATUS_Normal
#define SM_Err_PCVCU_SAFETY_MANAGER_STATUS_Normal (0)
#endif

#ifndef SM_Err_PCVCU_SAFETY_MANAGER_STATUS_Error
#define SM_Err_PCVCU_SAFETY_MANAGER_STATUS_Error (1)
#endif


// Value tables for @SM_LastErrorSource signal

#ifndef SM_LastErrorSource_SAFETY_MANAGER_STATUS_None
#define SM_LastErrorSource_SAFETY_MANAGER_STATUS_None (0)
#endif

#ifndef SM_LastErrorSource_SAFETY_MANAGER_STATUS_EmergencyButton
#define SM_LastErrorSource_SAFETY_MANAGER_STATUS_EmergencyButton (1)
#endif

#ifndef SM_LastErrorSource_SAFETY_MANAGER_STATUS_RC_Emergency
#define SM_LastErrorSource_SAFETY_MANAGER_STATUS_RC_Emergency (2)
#endif

#ifndef SM_LastErrorSource_SAFETY_MANAGER_STATUS_GPIO
#define SM_LastErrorSource_SAFETY_MANAGER_STATUS_GPIO (3)
#endif

#ifndef SM_LastErrorSource_SAFETY_MANAGER_STATUS_SysMon
#define SM_LastErrorSource_SAFETY_MANAGER_STATUS_SysMon (4)
#endif

#ifndef SM_LastErrorSource_SAFETY_MANAGER_STATUS_Steer
#define SM_LastErrorSource_SAFETY_MANAGER_STATUS_Steer (5)
#endif

#ifndef SM_LastErrorSource_SAFETY_MANAGER_STATUS_Brake
#define SM_LastErrorSource_SAFETY_MANAGER_STATUS_Brake (6)
#endif

#ifndef SM_LastErrorSource_SAFETY_MANAGER_STATUS_MCU
#define SM_LastErrorSource_SAFETY_MANAGER_STATUS_MCU (7)
#endif

#ifndef SM_LastErrorSource_SAFETY_MANAGER_STATUS_RC
#define SM_LastErrorSource_SAFETY_MANAGER_STATUS_RC (8)
#endif

#ifndef SM_LastErrorSource_SAFETY_MANAGER_STATUS_PC_VCU
#define SM_LastErrorSource_SAFETY_MANAGER_STATUS_PC_VCU (9)
#endif

#ifndef SM_LastErrorSource_SAFETY_MANAGER_STATUS_BATTERY
#define SM_LastErrorSource_SAFETY_MANAGER_STATUS_BATTERY (10)
#endif

#ifndef SM_LastErrorSource_SAFETY_MANAGER_STATUS_SAFETY
#define SM_LastErrorSource_SAFETY_MANAGER_STATUS_SAFETY (11)
#endif

#ifndef SM_LastErrorSource_SAFETY_MANAGER_STATUS_BBW
#define SM_LastErrorSource_SAFETY_MANAGER_STATUS_BBW (12)
#endif


typedef struct
{
#ifdef PC_VCU_USE_BITS_SIGNAL

  // Current safety severity level: 0=None, 1=Warning, 2=Error, 3=Critical
  //  0 : "None"
  //  1 : "Warning"
  //  2 : "Error"
  //  3 : "Critical"
  uint8_t SM_CurrentLevel : 2;               //      Bits= 2 Unit:'-'

  // Previous safety severity level
  //  0 : "None"
  //  1 : "Warning"
  //  2 : "Error"
  //  3 : "Critical"
  uint8_t SM_PreviousLevel : 2;              //      Bits= 2 Unit:'-'

  // Emergency stop has been triggered
  //  0 : "Inactive"
  //  1 : "Active"
  uint8_t SM_EmergencyStopActive : 1;        //      Bits= 1 Unit:'-'

  // Severity level of the last error that occurred
  //  0 : "None"
  //  1 : "Warning"
  //  2 : "Error"
  //  3 : "Critical"
  uint8_t SM_LastErrorLevel : 2;             //      Bits= 2 Unit:'-'

  // Physical emergency button pressed
  //  0 : "Normal"
  //  1 : "Pressed"
  uint8_t SM_Err_EmergencyButton : 1;        //      Bits= 1 Unit:'-'

  // Remote control emergency signal active
  //  0 : "Normal"
  //  1 : "Active"
  uint8_t SM_ErrRCEmergency : 1;             //      Bits= 1 Unit:'-'

  // GPIO module error detected
  //  0 : "Normal"
  //  1 : "Error"
  uint8_t SM_ErrGPIO : 1;                    //      Bits= 1 Unit:'-'

  // System monitor error detected
  //  0 : "Normal"
  //  1 : "Error"
  uint8_t SM_ErrSysMon : 1;                  //      Bits= 1 Unit:'-'

  // Steering module error detected
  //  0 : "Normal"
  //  1 : "Error"
  uint8_t SM_ErrSteer : 1;                   //      Bits= 1 Unit:'-'

  // Brake module error detected
  //  0 : "Normal"
  //  1 : "Error"
  uint8_t SM_ErrBrake : 1;                   //      Bits= 1 Unit:'-'

  // Remote control module error detected
  //  0 : "Normal"
  //  1 : "Error"
  uint8_t SM_ErrRC : 1;                      //      Bits= 1 Unit:'-'

  // PC VCU communication error detected
  //  0 : "Normal"
  //  1 : "Error"
  uint8_t SM_Err_PCVCU : 1;                  //      Bits= 1 Unit:'-'

  // Source of the last error: 0=None, 1=EmergBtn, 2=RC_Emg, 3=GPIO, 4=SysMon, 5=Steer, 6=Brake, 7=RC, 8=PC_VCU
  //  0 : "None"
  //  1 : "EmergencyButton"
  //  2 : "RC_Emergency"
  //  3 : "GPIO"
  //  4 : "SysMon"
  //  5 : "Steer"
  //  6 : "Brake"
  //  7 : "MCU"
  //  8 : "RC"
  //  9 : "PC_VCU"
  //  10 : "BATTERY"
  //  11 : "SAFETY"
  //  12 : "BBW"
  uint8_t SM_LastErrorSource : 4;            //      Bits= 4 Unit:'-'

  // Consecutive critical error count (max threshold=3)
  uint8_t SM_CriticalErrorCount : 4;         //      Bits= 4 Unit:'-'

  // Total warning events since startup (saturates at 255)
  uint8_t SM_WarningCount;                   //      Bits= 8 Unit:'-'

  // Total error events since startup (saturates at 255)
  uint8_t SM_ErrorCount;                     //      Bits= 8 Unit:'-'

  // Total critical events since startup (saturates at 255)
  uint8_t SM_CriticalCount;                  //      Bits= 8 Unit:'-'

  uint8_t SM_ErrBattery : 1;                 //      Bits= 1 Unit:'-'

  uint8_t SM_ErrSafety : 1;                  //      Bits= 1 Unit:'-'

  uint8_t SM_ErrBBW : 1;                     //      Bits= 1 Unit:'-'

#else

  // Current safety severity level: 0=None, 1=Warning, 2=Error, 3=Critical
  //  0 : "None"
  //  1 : "Warning"
  //  2 : "Error"
  //  3 : "Critical"
  uint8_t SM_CurrentLevel;                   //      Bits= 2 Unit:'-'

  // Previous safety severity level
  //  0 : "None"
  //  1 : "Warning"
  //  2 : "Error"
  //  3 : "Critical"
  uint8_t SM_PreviousLevel;                  //      Bits= 2 Unit:'-'

  // Emergency stop has been triggered
  //  0 : "Inactive"
  //  1 : "Active"
  uint8_t SM_EmergencyStopActive;            //      Bits= 1 Unit:'-'

  // Severity level of the last error that occurred
  //  0 : "None"
  //  1 : "Warning"
  //  2 : "Error"
  //  3 : "Critical"
  uint8_t SM_LastErrorLevel;                 //      Bits= 2 Unit:'-'

  // Physical emergency button pressed
  //  0 : "Normal"
  //  1 : "Pressed"
  uint8_t SM_Err_EmergencyButton;            //      Bits= 1 Unit:'-'

  // Remote control emergency signal active
  //  0 : "Normal"
  //  1 : "Active"
  uint8_t SM_ErrRCEmergency;                 //      Bits= 1 Unit:'-'

  // GPIO module error detected
  //  0 : "Normal"
  //  1 : "Error"
  uint8_t SM_ErrGPIO;                        //      Bits= 1 Unit:'-'

  // System monitor error detected
  //  0 : "Normal"
  //  1 : "Error"
  uint8_t SM_ErrSysMon;                      //      Bits= 1 Unit:'-'

  // Steering module error detected
  //  0 : "Normal"
  //  1 : "Error"
  uint8_t SM_ErrSteer;                       //      Bits= 1 Unit:'-'

  // Brake module error detected
  //  0 : "Normal"
  //  1 : "Error"
  uint8_t SM_ErrBrake;                       //      Bits= 1 Unit:'-'

  // Remote control module error detected
  //  0 : "Normal"
  //  1 : "Error"
  uint8_t SM_ErrRC;                          //      Bits= 1 Unit:'-'

  // PC VCU communication error detected
  //  0 : "Normal"
  //  1 : "Error"
  uint8_t SM_Err_PCVCU;                      //      Bits= 1 Unit:'-'

  // Source of the last error: 0=None, 1=EmergBtn, 2=RC_Emg, 3=GPIO, 4=SysMon, 5=Steer, 6=Brake, 7=RC, 8=PC_VCU
  //  0 : "None"
  //  1 : "EmergencyButton"
  //  2 : "RC_Emergency"
  //  3 : "GPIO"
  //  4 : "SysMon"
  //  5 : "Steer"
  //  6 : "Brake"
  //  7 : "MCU"
  //  8 : "RC"
  //  9 : "PC_VCU"
  //  10 : "BATTERY"
  //  11 : "SAFETY"
  //  12 : "BBW"
  uint8_t SM_LastErrorSource;                //      Bits= 4 Unit:'-'

  // Consecutive critical error count (max threshold=3)
  uint8_t SM_CriticalErrorCount;             //      Bits= 4 Unit:'-'

  // Total warning events since startup (saturates at 255)
  uint8_t SM_WarningCount;                   //      Bits= 8 Unit:'-'

  // Total error events since startup (saturates at 255)
  uint8_t SM_ErrorCount;                     //      Bits= 8 Unit:'-'

  // Total critical events since startup (saturates at 255)
  uint8_t SM_CriticalCount;                  //      Bits= 8 Unit:'-'

  uint8_t SM_ErrBattery;                     //      Bits= 1 Unit:'-'

  uint8_t SM_ErrSafety;                      //      Bits= 1 Unit:'-'

  uint8_t SM_ErrBBW;                         //      Bits= 1 Unit:'-'

#endif // PC_VCU_USE_BITS_SIGNAL

#ifdef PC_VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // PC_VCU_USE_DIAG_MONITORS

} SAFETY_MANAGER_STATUS_t;

// def @BATTERY_STATUS CAN Message (332001 0x510e1)
#define BATTERY_STATUS_IDE (1U)
#define BATTERY_STATUS_DLC (8U)
#define BATTERY_STATUS_CANID (0x510e1U)

// Value tables for @BM_Charging signal

#ifndef BM_Charging_BATTERY_STATUS_NOT_CHARGING
#define BM_Charging_BATTERY_STATUS_NOT_CHARGING (0)
#endif

#ifndef BM_Charging_BATTERY_STATUS_CHARGING
#define BM_Charging_BATTERY_STATUS_CHARGING (1)
#endif


// Value tables for @BM_Status signal

#ifndef BM_Status_BATTERY_STATUS_BATTERY_MODULE_IDLE
#define BM_Status_BATTERY_STATUS_BATTERY_MODULE_IDLE (0)
#endif

#ifndef BM_Status_BATTERY_STATUS_BATTERY_MODULE_ACTIVE
#define BM_Status_BATTERY_STATUS_BATTERY_MODULE_ACTIVE (1)
#endif

#ifndef BM_Status_BATTERY_STATUS_BATTERY_MODULE_ERROR
#define BM_Status_BATTERY_STATUS_BATTERY_MODULE_ERROR (2)
#endif

// signal: @BM_Temperature_ro
#define PC_VCU_BM_Temperature_ro_CovFactor (1)
#define PC_VCU_BM_Temperature_ro_toS(x) ( (int8_t) ((x) - (-50)) )
#define PC_VCU_BM_Temperature_ro_fromS(x) ( ((x) + (-50)) )

// Value tables for @BM_RemainingTimeToCharge signal

#ifndef BM_RemainingTimeToCharge_BATTERY_STATUS_CALCULATION_ERROR
#define BM_RemainingTimeToCharge_BATTERY_STATUS_CALCULATION_ERROR (65535)
#endif

// signal: @BM_Power_ro
#define PC_VCU_BM_Power_ro_CovFactor (0.01)
#define PC_VCU_BM_Power_ro_toS(x) ( (int16_t) (((x) - (0.0)) / (0.01)) )
#define PC_VCU_BM_Power_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )

typedef struct
{
#ifdef PC_VCU_USE_BITS_SIGNAL

  //  0 : "NOT_CHARGING"
  //  1 : "CHARGING"
  uint8_t BM_Charging : 1;                   //      Bits= 1 Unit:'-'

  uint8_t BM_CommFault : 1;                  //      Bits= 1 Unit:'-'

  uint8_t BM_InternalFault : 1;              //      Bits= 1 Unit:'-'

  //  0 : "BATTERY_MODULE_IDLE"
  //  1 : "BATTERY_MODULE_ACTIVE"
  //  2 : "BATTERY_MODULE_ERROR"
  uint8_t BM_Status : 2;                     //      Bits= 2 Unit:'-'

  uint8_t BM_FramePeriod;                    //      Bits= 8 Unit:'-'

  uint8_t BM_SOC;                            //      Bits= 8 Unit:'%'

  int8_t BM_Temperature_ro;                  //  [-] Bits= 8 Offset= -50                Unit:'-'

#ifdef PC_VCU_USE_SIGFLOAT
  int16_t BM_Temperature_phys;
#endif // PC_VCU_USE_SIGFLOAT

  //  65535 : "CALCULATION_ERROR"
  uint16_t BM_RemainingTimeToCharge;         //      Bits=16 Unit:'minute'

  int16_t BM_Power_ro;                       //  [-] Bits=16 Factor= 0.01            Unit:'-'

#ifdef PC_VCU_USE_SIGFLOAT
  sigfloat_t BM_Power_phys;
#endif // PC_VCU_USE_SIGFLOAT

#else

  //  0 : "NOT_CHARGING"
  //  1 : "CHARGING"
  uint8_t BM_Charging;                       //      Bits= 1 Unit:'-'

  uint8_t BM_CommFault;                      //      Bits= 1 Unit:'-'

  uint8_t BM_InternalFault;                  //      Bits= 1 Unit:'-'

  //  0 : "BATTERY_MODULE_IDLE"
  //  1 : "BATTERY_MODULE_ACTIVE"
  //  2 : "BATTERY_MODULE_ERROR"
  uint8_t BM_Status;                         //      Bits= 2 Unit:'-'

  uint8_t BM_FramePeriod;                    //      Bits= 8 Unit:'-'

  uint8_t BM_SOC;                            //      Bits= 8 Unit:'%'

  int8_t BM_Temperature_ro;                  //  [-] Bits= 8 Offset= -50                Unit:'-'

#ifdef PC_VCU_USE_SIGFLOAT
  int16_t BM_Temperature_phys;
#endif // PC_VCU_USE_SIGFLOAT

  //  65535 : "CALCULATION_ERROR"
  uint16_t BM_RemainingTimeToCharge;         //      Bits=16 Unit:'minute'

  int16_t BM_Power_ro;                       //  [-] Bits=16 Factor= 0.01            Unit:'-'

#ifdef PC_VCU_USE_SIGFLOAT
  sigfloat_t BM_Power_phys;
#endif // PC_VCU_USE_SIGFLOAT

#endif // PC_VCU_USE_BITS_SIGNAL

#ifdef PC_VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // PC_VCU_USE_DIAG_MONITORS

} BATTERY_STATUS_t;

// def @VCU_CTRL_CMD_SI CAN Message (67764225 0x40a0001)
#define VCU_CTRL_CMD_SI_IDE (1U)
#define VCU_CTRL_CMD_SI_DLC (8U)
#define VCU_CTRL_CMD_SI_CANID (0x40a0001U)
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
  uint8_t AutonomousEnable : 1;              //      Bits= 1 Unit:'-'

  // Emergency stop request (highest priority)
  uint8_t EmergencyActive : 1;               //      Bits= 1 Unit:'-'

  // 1 = disable internal ECU safety checks
  uint8_t SafetyDisable : 1;                 //      Bits= 1 Unit:'-'

  // Gear request code (expanded field)
  //  0 : "NONE"
  //  1 : "NEUTRAL"
  //  2 : "DRIVE"
  //  20 : "REVERSE"
  //  22 : "PARK"
  uint8_t GearReq : 5;                       //      Bits= 5 Unit:'-'

  // Left turn indicator request
  uint8_t TurnLeft : 1;                      //      Bits= 1 Unit:'-'

  // Right turn indicator request
  uint8_t TurnRight : 1;                     //      Bits= 1 Unit:'-'

  // Hazard lights (overrides turn signals)
  uint8_t Hazard : 1;                        //      Bits= 1 Unit:'-'

  // Horn command (momentary)
  uint8_t Horn : 1;                          //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t Reserved : 4;                      //      Bits= 4 Unit:'-'

  // Rolling counter (0?255)
  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  // CRC-8 AUTOSAR over Byte0?Byte6
  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

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
  uint8_t AutonomousEnable;                  //      Bits= 1 Unit:'-'

  // Emergency stop request (highest priority)
  uint8_t EmergencyActive;                   //      Bits= 1 Unit:'-'

  // 1 = disable internal ECU safety checks
  uint8_t SafetyDisable;                     //      Bits= 1 Unit:'-'

  // Gear request code (expanded field)
  //  0 : "NONE"
  //  1 : "NEUTRAL"
  //  2 : "DRIVE"
  //  20 : "REVERSE"
  //  22 : "PARK"
  uint8_t GearReq;                           //      Bits= 5 Unit:'-'

  // Left turn indicator request
  uint8_t TurnLeft;                          //      Bits= 1 Unit:'-'

  // Right turn indicator request
  uint8_t TurnRight;                         //      Bits= 1 Unit:'-'

  // Hazard lights (overrides turn signals)
  uint8_t Hazard;                            //      Bits= 1 Unit:'-'

  // Horn command (momentary)
  uint8_t Horn;                              //      Bits= 1 Unit:'-'

  // Must be sent as 0
  uint8_t Reserved;                          //      Bits= 4 Unit:'-'

  // Rolling counter (0?255)
  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  // CRC-8 AUTOSAR over Byte0?Byte6
  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

#endif // PC_VCU_USE_BITS_SIGNAL

#ifdef PC_VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // PC_VCU_USE_DIAG_MONITORS

} VCU_CTRL_CMD_SI_t;

// def @SAFE_STAT_ROS2_HEARTBEAT CAN Message (134873103 0x80a000f)
#define SAFE_STAT_ROS2_HEARTBEAT_IDE (1U)
#define SAFE_STAT_ROS2_HEARTBEAT_DLC (8U)
#define SAFE_STAT_ROS2_HEARTBEAT_CANID (0x80a000fU)

typedef struct
{
#ifdef PC_VCU_USE_BITS_SIGNAL

  // ROS 2 time in milliseconds
  uint64_t ROS_Time_ms;                      //      Bits=48 Unit:'ms'

  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

#else

  // ROS 2 time in milliseconds
  uint64_t ROS_Time_ms;                      //      Bits=48 Unit:'ms'

  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

#endif // PC_VCU_USE_BITS_SIGNAL

#ifdef PC_VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // PC_VCU_USE_DIAG_MONITORS

} SAFE_STAT_ROS2_HEARTBEAT_t;

// def @VCU_STAT_MOTION_SI CAN Message (202702864 0xc150010)
#define VCU_STAT_MOTION_SI_IDE (1U)
#define VCU_STAT_MOTION_SI_DLC (8U)
#define VCU_STAT_MOTION_SI_CANID (0xc150010U)
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

  // Measured steer angle
  int16_t SteerAngleDeg_Act;                 //  [-] Bits=16 Unit:'degree'

  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

#else

  int16_t TireAngleRad_Act_ro;               //  [-] Bits=16 Factor= 0.001           Unit:'rad'

#ifdef PC_VCU_USE_SIGFLOAT
  sigfloat_t TireAngleRad_Act_phys;
#endif // PC_VCU_USE_SIGFLOAT

  int16_t VehicleSpeedMS_Act_ro;             //  [-] Bits=16 Factor= 0.01            Unit:'m/s'

#ifdef PC_VCU_USE_SIGFLOAT
  sigfloat_t VehicleSpeedMS_Act_phys;
#endif // PC_VCU_USE_SIGFLOAT

  // Measured steer angle
  int16_t SteerAngleDeg_Act;                 //  [-] Bits=16 Unit:'degree'

  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

#endif // PC_VCU_USE_BITS_SIGNAL

#ifdef PC_VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // PC_VCU_USE_DIAG_MONITORS

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
#ifdef PC_VCU_USE_BITS_SIGNAL

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

  uint8_t SafetyState;                       //      Bits= 8 Unit:'-'

  uint8_t BatterySoC;                        //      Bits= 8 Unit:'-'

  uint8_t FaultSummary;                      //      Bits= 8 Unit:'-'

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

  uint8_t SafetyState;                       //      Bits= 8 Unit:'-'

  uint8_t BatterySoC;                        //      Bits= 8 Unit:'-'

  uint8_t FaultSummary;                      //      Bits= 8 Unit:'-'

  uint8_t AliveCounter;                      //      Bits= 8 Unit:'-'

  uint8_t CRC8;                              //      Bits= 8 Unit:'-'

#endif // PC_VCU_USE_BITS_SIGNAL

#ifdef PC_VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // PC_VCU_USE_DIAG_MONITORS

} VCU_STAT_VEHICLE_STATE_t;

// def @MCU_MODULE_STATUS CAN Message (269615105 0x10120001)
#define MCU_MODULE_STATUS_IDE (1U)
#define MCU_MODULE_STATUS_DLC (8U)
#define MCU_MODULE_STATUS_CANID (0x10120001U)

// Value tables for @MCU_Gear signal

#ifndef MCU_Gear_MCU_MODULE_STATUS_NONE
#define MCU_Gear_MCU_MODULE_STATUS_NONE (0)
#endif

#ifndef MCU_Gear_MCU_MODULE_STATUS_P
#define MCU_Gear_MCU_MODULE_STATUS_P (1)
#endif

#ifndef MCU_Gear_MCU_MODULE_STATUS_R
#define MCU_Gear_MCU_MODULE_STATUS_R (2)
#endif

#ifndef MCU_Gear_MCU_MODULE_STATUS_N
#define MCU_Gear_MCU_MODULE_STATUS_N (3)
#endif

#ifndef MCU_Gear_MCU_MODULE_STATUS_D
#define MCU_Gear_MCU_MODULE_STATUS_D (4)
#endif

// signal: @MCU_Odometer_ro
#define PC_VCU_MCU_Odometer_ro_CovFactor (0.1)
#define PC_VCU_MCU_Odometer_ro_toS(x) ( (uint32_t) (((x) - (0.0)) / (0.1)) )
#define PC_VCU_MCU_Odometer_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )

typedef struct
{
#ifdef PC_VCU_USE_BITS_SIGNAL

  //  MCU_MODULE_IDLE = 0, MCU_MODULE_ACTIVE = 1, MCU_MODULE_ERROR= 3
  uint8_t MCU_ModuleStatus : 2;              //      Bits= 2 Unit:'-'

  //  0 : "NONE"
  //  1 : "P"
  //  2 : "R"
  //  3 : "N"
  //  4 : "D"
  uint8_t MCU_Gear : 4;                      //      Bits= 4 Unit:'-'

  // -
  uint8_t MCU_ErrCommFault : 1;              //      Bits= 1 Unit:'-'

  // -
  uint8_t MCU_ErrZapiInternal : 1;           //      Bits= 1 Unit:'-'

  // -
  uint16_t MCU_ZapiAlarmCode;                //      Bits=16 Unit:'-'

  // -
  uint8_t MCU_FramePeriod;                   //      Bits= 8 Unit:'ms'

  // -
  uint32_t MCU_Odometer_ro;                  //      Bits=32 Factor= 0.1             Unit:'km'

#ifdef PC_VCU_USE_SIGFLOAT
  sigfloat_t MCU_Odometer_phys;
#endif // PC_VCU_USE_SIGFLOAT

#else

  //  MCU_MODULE_IDLE = 0, MCU_MODULE_ACTIVE = 1, MCU_MODULE_ERROR= 3
  uint8_t MCU_ModuleStatus;                  //      Bits= 2 Unit:'-'

  //  0 : "NONE"
  //  1 : "P"
  //  2 : "R"
  //  3 : "N"
  //  4 : "D"
  uint8_t MCU_Gear;                          //      Bits= 4 Unit:'-'

  // -
  uint8_t MCU_ErrCommFault;                  //      Bits= 1 Unit:'-'

  // -
  uint8_t MCU_ErrZapiInternal;               //      Bits= 1 Unit:'-'

  // -
  uint16_t MCU_ZapiAlarmCode;                //      Bits=16 Unit:'-'

  // -
  uint8_t MCU_FramePeriod;                   //      Bits= 8 Unit:'ms'

  // -
  uint32_t MCU_Odometer_ro;                  //      Bits=32 Factor= 0.1             Unit:'km'

#ifdef PC_VCU_USE_SIGFLOAT
  sigfloat_t MCU_Odometer_phys;
#endif // PC_VCU_USE_SIGFLOAT

#endif // PC_VCU_USE_BITS_SIGNAL

#ifdef PC_VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // PC_VCU_USE_DIAG_MONITORS

} MCU_MODULE_STATUS_t;

// def @DTC_ERROR_STATUS CAN Message (271581440 0x10300100)
#define DTC_ERROR_STATUS_IDE (1U)
#define DTC_ERROR_STATUS_DLC (8U)
#define DTC_ERROR_STATUS_CANID (0x10300100U)

typedef struct
{
#ifdef PC_VCU_USE_BITS_SIGNAL

  uint8_t SYS_T1_HI : 1;                         //      Bits= 1 Unit:'-'

  uint8_t SYS_T1_LO : 1;                         //      Bits= 1 Unit:'-'

  uint8_t SYS_T2_HI : 1;                         //      Bits= 1 Unit:'-'

  uint8_t SYS_T2_LO : 1;                         //      Bits= 1 Unit:'-'

  uint8_t SYS_KL30_HI : 1;                       //      Bits= 1 Unit:'-'

  uint8_t SYS_KL30_LO : 1;                       //      Bits= 1 Unit:'-'

  uint8_t SYS_KL30_2_HI : 1;                     //      Bits= 1 Unit:'-'

  uint8_t SYS_KL_30_LO : 1;                      //      Bits= 1 Unit:'-'

  uint8_t SYS_5V8_HI : 1;                        //      Bits= 1 Unit:'-'

  uint8_t SYS_5V8_LO : 1;                        //      Bits= 1 Unit:'-'

  uint8_t SYS_5VD_HI : 1;                        //      Bits= 1 Unit:'-'

  uint8_t SYS_5VD_LO : 1;                        //      Bits= 1 Unit:'-'

  uint8_t SYS_STACK : 1;                         //      Bits= 1 Unit:'-'

  uint8_t BRK_HSD_OC : 1;                        //      Bits= 1 Unit:'-'

  uint8_t BRK_HSD_OL : 1;                        //      Bits= 1 Unit:'-'

  uint8_t BRK_HSD_ERR : 1;                       //      Bits= 1 Unit:'-'

  uint8_t BRK_EBS_WARN : 1;                      //      Bits= 1 Unit:'-'

  uint8_t BRK_EBS_CRIT : 1;                      //      Bits= 1 Unit:'-'

  uint8_t BRK_COM_ERR : 1;                       //      Bits= 1 Unit:'-'

  uint8_t BRK_ECU_ERR : 1;                       //      Bits= 1 Unit:'-'

  uint8_t BRK_DRV_ERR : 1;                       //      Bits= 1 Unit:'-'

  uint8_t STR_HSD_OC : 1;                        //      Bits= 1 Unit:'-'

  uint8_t STR_HSD_OL : 1;                        //      Bits= 1 Unit:'-'

  uint8_t STR_HSD_ERR : 1;                       //      Bits= 1 Unit:'-'

  uint8_t STR_DRV_FLT : 1;                       //      Bits= 1 Unit:'-'

  uint8_t STR_MOT_STALL : 1;                     //      Bits= 1 Unit:'-'

  uint8_t STR_CAL_ERR : 1;                       //      Bits= 1 Unit:'-'

  uint8_t STR_COM_INT : 1;                       //      Bits= 1 Unit:'-'

  uint8_t STR_EEP_ERR : 1;                       //      Bits= 1 Unit:'-'

  uint8_t STR_CTRL_ERR : 1;                      //      Bits= 1 Unit:'-'

  uint8_t STR_ANG_SENS : 1;                      //      Bits= 1 Unit:'-'

  uint8_t STR_TRQ_SENS : 1;                      //      Bits= 1 Unit:'-'

  uint8_t STR_OT_SEV : 1;                        //      Bits= 1 Unit:'-'

  uint8_t STR_OT_NORM : 1;                       //      Bits= 1 Unit:'-'

  uint8_t STR_UV_ERR : 1;                        //      Bits= 1 Unit:'-'

  uint8_t STR_OV_ERR : 1;                        //      Bits= 1 Unit:'-'

  uint8_t STR_CAN_TO : 1;                        //      Bits= 1 Unit:'-'

  uint8_t RC_FRM_ERR : 1;                        //      Bits= 1 Unit:'-'

  uint8_t RC_FRM_LST : 1;                        //      Bits= 1 Unit:'-'

  uint8_t RC_FRM_FS : 1;                         //      Bits= 1 Unit:'-'

  uint8_t RC_EMG_ACT : 1;                        //      Bits= 1 Unit:'-'

  uint8_t RC_REM_EMG : 1;                        //      Bits= 1 Unit:'-'

  uint8_t RC_COM_ERR : 1;                        //      Bits= 1 Unit:'-'

  uint8_t MCU_ALM_ACT : 1;                       //      Bits= 1 Unit:'-'

  uint8_t MCU_COM_ERR : 1;                       //      Bits= 1 Unit:'-'

  uint8_t SAFE_VCU_COM_FLT : 1;                  //      Bits= 1 Unit:'-'

  uint8_t SAFE_VCU_EMG_ACT : 1;                  //      Bits= 1 Unit:'-'

  uint8_t JK_UNIT_OVER_VOLTAGE : 1;              //      Bits= 1 Unit:'-'

  uint8_t JK_UNIT_UNDER_VOLTAGE : 1;             //      Bits= 1 Unit:'-'

  uint8_t JK_TOTAL_VOLTAGE_OVER_VOLTAGE : 1;     //      Bits= 1 Unit:'-'

  uint8_t JK_TOTAL_VOLTAGE_UNDER_VOLTAGE : 1;    //      Bits= 1 Unit:'-'

  uint8_t JK_LARGE_PRESSURE_DIFF_OF_MON : 1;     //      Bits= 1 Unit:'-'

  uint8_t JK_DISCHARGE_OVER_CURRENT : 1;         //      Bits= 1 Unit:'-'

  uint8_t JK_CHARGE_OVER_CURRENT : 1;            //      Bits= 1 Unit:'-'

  uint8_t JK_TEMPERATURE_IS_TOO_HIGH : 1;        //      Bits= 1 Unit:'-'

  uint8_t JK_TEMPERATURE_IS_TOO_LOW : 1;         //      Bits= 1 Unit:'-'

  uint8_t JK_EXCESSIVE_TEMPERATURE_DIFF : 1;     //      Bits= 1 Unit:'-'

  uint8_t JK_SOC_TOO_LOW : 1;                    //      Bits= 1 Unit:'-'

  uint8_t JK_INSULATION_IS_TOO_LOW : 1;          //      Bits= 1 Unit:'-'

  uint8_t JK_HIGH_VOLTAGE_INTERLOCK_FAULT : 1;   //      Bits= 1 Unit:'-'

  uint8_t JK_EXTERNAL_COMMUNICATION_FAIL : 1;    //      Bits= 1 Unit:'-'

  uint8_t JK_INTERNAL_COMMUNICATION_FAIL : 1;    //      Bits= 1 Unit:'-'

  uint8_t ASPS_HSD_OC : 1;                       //      Bits= 1 Unit:'-'

  uint8_t ASPS_HSD_OL : 1;                       //      Bits= 1 Unit:'-'

#else

  uint8_t SYS_T1_HI;                             //      Bits= 1 Unit:'-'

  uint8_t SYS_T1_LO;                             //      Bits= 1 Unit:'-'

  uint8_t SYS_T2_HI;                             //      Bits= 1 Unit:'-'

  uint8_t SYS_T2_LO;                             //      Bits= 1 Unit:'-'

  uint8_t SYS_KL30_HI;                           //      Bits= 1 Unit:'-'

  uint8_t SYS_KL30_LO;                           //      Bits= 1 Unit:'-'

  uint8_t SYS_KL30_2_HI;                         //      Bits= 1 Unit:'-'

  uint8_t SYS_KL_30_LO;                          //      Bits= 1 Unit:'-'

  uint8_t SYS_5V8_HI;                            //      Bits= 1 Unit:'-'

  uint8_t SYS_5V8_LO;                            //      Bits= 1 Unit:'-'

  uint8_t SYS_5VD_HI;                            //      Bits= 1 Unit:'-'

  uint8_t SYS_5VD_LO;                            //      Bits= 1 Unit:'-'

  uint8_t SYS_STACK;                             //      Bits= 1 Unit:'-'

  uint8_t BRK_HSD_OC;                            //      Bits= 1 Unit:'-'

  uint8_t BRK_HSD_OL;                            //      Bits= 1 Unit:'-'

  uint8_t BRK_HSD_ERR;                           //      Bits= 1 Unit:'-'

  uint8_t BRK_EBS_WARN;                          //      Bits= 1 Unit:'-'

  uint8_t BRK_EBS_CRIT;                          //      Bits= 1 Unit:'-'

  uint8_t BRK_COM_ERR;                           //      Bits= 1 Unit:'-'

  uint8_t BRK_ECU_ERR;                           //      Bits= 1 Unit:'-'

  uint8_t BRK_DRV_ERR;                           //      Bits= 1 Unit:'-'

  uint8_t STR_HSD_OC;                            //      Bits= 1 Unit:'-'

  uint8_t STR_HSD_OL;                            //      Bits= 1 Unit:'-'

  uint8_t STR_HSD_ERR;                           //      Bits= 1 Unit:'-'

  uint8_t STR_DRV_FLT;                           //      Bits= 1 Unit:'-'

  uint8_t STR_MOT_STALL;                         //      Bits= 1 Unit:'-'

  uint8_t STR_CAL_ERR;                           //      Bits= 1 Unit:'-'

  uint8_t STR_COM_INT;                           //      Bits= 1 Unit:'-'

  uint8_t STR_EEP_ERR;                           //      Bits= 1 Unit:'-'

  uint8_t STR_CTRL_ERR;                          //      Bits= 1 Unit:'-'

  uint8_t STR_ANG_SENS;                          //      Bits= 1 Unit:'-'

  uint8_t STR_TRQ_SENS;                          //      Bits= 1 Unit:'-'

  uint8_t STR_OT_SEV;                            //      Bits= 1 Unit:'-'

  uint8_t STR_OT_NORM;                           //      Bits= 1 Unit:'-'

  uint8_t STR_UV_ERR;                            //      Bits= 1 Unit:'-'

  uint8_t STR_OV_ERR;                            //      Bits= 1 Unit:'-'

  uint8_t STR_CAN_TO;                            //      Bits= 1 Unit:'-'

  uint8_t RC_FRM_ERR;                            //      Bits= 1 Unit:'-'

  uint8_t RC_FRM_LST;                            //      Bits= 1 Unit:'-'

  uint8_t RC_FRM_FS;                             //      Bits= 1 Unit:'-'

  uint8_t RC_EMG_ACT;                            //      Bits= 1 Unit:'-'

  uint8_t RC_REM_EMG;                            //      Bits= 1 Unit:'-'

  uint8_t RC_COM_ERR;                            //      Bits= 1 Unit:'-'

  uint8_t MCU_ALM_ACT;                           //      Bits= 1 Unit:'-'

  uint8_t MCU_COM_ERR;                           //      Bits= 1 Unit:'-'

  uint8_t SAFE_VCU_COM_FLT;                      //      Bits= 1 Unit:'-'

  uint8_t SAFE_VCU_EMG_ACT;                      //      Bits= 1 Unit:'-'

  uint8_t JK_UNIT_OVER_VOLTAGE;                  //      Bits= 1 Unit:'-'

  uint8_t JK_UNIT_UNDER_VOLTAGE;                 //      Bits= 1 Unit:'-'

  uint8_t JK_TOTAL_VOLTAGE_OVER_VOLTAGE;         //      Bits= 1 Unit:'-'

  uint8_t JK_TOTAL_VOLTAGE_UNDER_VOLTAGE;        //      Bits= 1 Unit:'-'

  uint8_t JK_LARGE_PRESSURE_DIFF_OF_MON;         //      Bits= 1 Unit:'-'

  uint8_t JK_DISCHARGE_OVER_CURRENT;             //      Bits= 1 Unit:'-'

  uint8_t JK_CHARGE_OVER_CURRENT;                //      Bits= 1 Unit:'-'

  uint8_t JK_TEMPERATURE_IS_TOO_HIGH;            //      Bits= 1 Unit:'-'

  uint8_t JK_TEMPERATURE_IS_TOO_LOW;             //      Bits= 1 Unit:'-'

  uint8_t JK_EXCESSIVE_TEMPERATURE_DIFF;         //      Bits= 1 Unit:'-'

  uint8_t JK_SOC_TOO_LOW;                        //      Bits= 1 Unit:'-'

  uint8_t JK_INSULATION_IS_TOO_LOW;              //      Bits= 1 Unit:'-'

  uint8_t JK_HIGH_VOLTAGE_INTERLOCK_FAULT;       //      Bits= 1 Unit:'-'

  uint8_t JK_EXTERNAL_COMMUNICATION_FAIL;        //      Bits= 1 Unit:'-'

  uint8_t JK_INTERNAL_COMMUNICATION_FAIL;        //      Bits= 1 Unit:'-'

  uint8_t ASPS_HSD_OC;                           //      Bits= 1 Unit:'-'

  uint8_t ASPS_HSD_OL;                           //      Bits= 1 Unit:'-'

#endif // PC_VCU_USE_BITS_SIGNAL

#ifdef PC_VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // PC_VCU_USE_DIAG_MONITORS

} DTC_ERROR_STATUS_t;

// def @DTC_ERROR_STATUS_1 CAN Message (271581441 0x10300101)
#define DTC_ERROR_STATUS_1_IDE (1U)
#define DTC_ERROR_STATUS_1_DLC (8U)
#define DTC_ERROR_STATUS_1_CANID (0x10300101U)

typedef struct
{
#ifdef PC_VCU_USE_BITS_SIGNAL

  uint8_t ASPS_HSD_ERR : 1;                  //      Bits= 1 Unit:'-'

  uint8_t GPIO_PC_IGNITION_ERR : 1;          //      Bits= 1 Unit:'-'

  uint8_t BMS_COMM_ERR : 1;                  //      Bits= 1 Unit:'-'

  uint8_t BBW_COMM_ERR : 1;                  //      Bits= 1 Unit:'-'

  uint8_t BBW_UV_ERR : 1;                    //      Bits= 1 Unit:'-'

  uint8_t BBW_L_MOT_CONN : 1;                //      Bits= 1 Unit:'-'

  uint8_t BBW_R_MOT_CONN : 1;                //      Bits= 1 Unit:'-'

  uint8_t BBW_L_MOT_OC : 1;                  //      Bits= 1 Unit:'-'

  uint8_t BBW_R_MOT_OC : 1;                  //      Bits= 1 Unit:'-'

  uint8_t BBW_TEMP_ERR : 1;                  //      Bits= 1 Unit:'-'

  uint8_t RB_BOARD_TEMP_WARN : 1;            //      Bits= 1 Unit:'-'

  uint8_t RB_BOARD_TEMP_ERR : 1;             //      Bits= 1 Unit:'-'

  uint8_t RB_COMM_TIMEOUT : 1;               //      Bits= 1 Unit:'-'

  uint8_t RB_IC_COMM_WARN : 1;               //      Bits= 1 Unit:'-'

  uint8_t RB_LSD_OVERTEMP_WARN : 1;          //      Bits= 1 Unit:'-'

  uint8_t RB_IC_UNDERVOLT_WARN : 1;          //      Bits= 1 Unit:'-'

  uint8_t GPIO_CHARGE_FLAP_ERR : 1;          //      Bits= 1 Unit:'-'

  uint8_t GPIO_EMG_BTN_ERR : 1;              //      Bits= 1 Unit:'-'

#else

  uint8_t ASPS_HSD_ERR;                      //      Bits= 1 Unit:'-'

  uint8_t GPIO_PC_IGNITION_ERR;              //      Bits= 1 Unit:'-'

  uint8_t BMS_COMM_ERR;                      //      Bits= 1 Unit:'-'

  uint8_t BBW_COMM_ERR;                      //      Bits= 1 Unit:'-'

  uint8_t BBW_UV_ERR;                        //      Bits= 1 Unit:'-'

  uint8_t BBW_L_MOT_CONN;                    //      Bits= 1 Unit:'-'

  uint8_t BBW_R_MOT_CONN;                    //      Bits= 1 Unit:'-'

  uint8_t BBW_L_MOT_OC;                      //      Bits= 1 Unit:'-'

  uint8_t BBW_R_MOT_OC;                      //      Bits= 1 Unit:'-'

  uint8_t BBW_TEMP_ERR;                      //      Bits= 1 Unit:'-'

  uint8_t RB_BOARD_TEMP_WARN;                //      Bits= 1 Unit:'-'

  uint8_t RB_BOARD_TEMP_ERR;                 //      Bits= 1 Unit:'-'

  uint8_t RB_COMM_TIMEOUT;                   //      Bits= 1 Unit:'-'

  uint8_t RB_IC_COMM_WARN;                   //      Bits= 1 Unit:'-'

  uint8_t RB_LSD_OVERTEMP_WARN;              //      Bits= 1 Unit:'-'

  uint8_t RB_IC_UNDERVOLT_WARN;              //      Bits= 1 Unit:'-'

  uint8_t GPIO_CHARGE_FLAP_ERR;              //      Bits= 1 Unit:'-'

  uint8_t GPIO_EMG_BTN_ERR;                  //      Bits= 1 Unit:'-'

#endif // PC_VCU_USE_BITS_SIGNAL

#ifdef PC_VCU_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // PC_VCU_USE_DIAG_MONITORS

} DTC_ERROR_STATUS_1_t;

// Function signatures

uint32_t Unpack_SAFETY_MANAGER_STATUS_pc_vcu(SAFETY_MANAGER_STATUS_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef PC_VCU_USE_CANSTRUCT
uint32_t Pack_SAFETY_MANAGER_STATUS_pc_vcu(SAFETY_MANAGER_STATUS_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_SAFETY_MANAGER_STATUS_pc_vcu(SAFETY_MANAGER_STATUS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // PC_VCU_USE_CANSTRUCT

uint32_t Unpack_BATTERY_STATUS_pc_vcu(BATTERY_STATUS_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef PC_VCU_USE_CANSTRUCT
uint32_t Pack_BATTERY_STATUS_pc_vcu(BATTERY_STATUS_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_BATTERY_STATUS_pc_vcu(BATTERY_STATUS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
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

uint32_t Unpack_MCU_MODULE_STATUS_pc_vcu(MCU_MODULE_STATUS_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef PC_VCU_USE_CANSTRUCT
uint32_t Pack_MCU_MODULE_STATUS_pc_vcu(MCU_MODULE_STATUS_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_MCU_MODULE_STATUS_pc_vcu(MCU_MODULE_STATUS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // PC_VCU_USE_CANSTRUCT

uint32_t Unpack_DTC_ERROR_STATUS_pc_vcu(DTC_ERROR_STATUS_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef PC_VCU_USE_CANSTRUCT
uint32_t Pack_DTC_ERROR_STATUS_pc_vcu(DTC_ERROR_STATUS_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_DTC_ERROR_STATUS_pc_vcu(DTC_ERROR_STATUS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // PC_VCU_USE_CANSTRUCT

uint32_t Unpack_DTC_ERROR_STATUS_1_pc_vcu(DTC_ERROR_STATUS_1_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef PC_VCU_USE_CANSTRUCT
uint32_t Pack_DTC_ERROR_STATUS_1_pc_vcu(DTC_ERROR_STATUS_1_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_DTC_ERROR_STATUS_1_pc_vcu(DTC_ERROR_STATUS_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // PC_VCU_USE_CANSTRUCT

#ifdef __cplusplus
}
#endif
