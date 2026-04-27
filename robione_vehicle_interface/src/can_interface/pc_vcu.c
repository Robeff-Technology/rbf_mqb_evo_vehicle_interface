// Generator version : v3.1
// DBC filename      : pc_vcu_can_500k_v1.dbc
#include "pc_vcu.h"


// DBC file version
#if (VER_PC_VCU_MAJ != (0U)) || (VER_PC_VCU_MIN != (0U))
#error The PC_VCU dbc source files have different versions
#endif

#ifdef PC_VCU_USE_DIAG_MONITORS
// Function prototypes to be called each time CAN frame is unpacked
// FMon function may detect RC, CRC or DLC violation
#include "pc_vcu-fmon.h"

#endif // PC_VCU_USE_DIAG_MONITORS

// This macro guard for the case when you need to enable
// using diag monitors but there is no necessity in proper
// SysTick provider. For providing one you need define macro
// before this line - in dbccodeconf.h

#ifndef GetSystemTick
#define GetSystemTick() (0u)
#endif

// This macro guard is for the case when you want to build
// app with enabled optoin auto CSM, but don't yet have
// proper getframehash implementation

#ifndef GetFrameHash
#define GetFrameHash(a,b,c,d,e) (0u)
#endif

// This function performs extension of sign for the signals
// whose bit width value is not aligned to one of power of 2 or less than 8.
// The types 'bitext_t' and 'ubitext_t' define the biggest bit width which
// can be correctly handled. You need to select type which can contain
// n+1 bits where n is the largest signed signal width. For example if
// the most wide signed signal has a width of 31 bits you need to set
// bitext_t as int32_t and ubitext_t as uint32_t
// Defined these typedefs in @dbccodeconf.h or locally in 'dbcdrvname'-config.h
static bitext_t __ext_sig__(ubitext_t val, uint8_t bits)
{
  ubitext_t const m = (ubitext_t) (1u << (bits - 1u));
  return ((val ^ m) - m);
}

uint32_t Unpack_SAFETY_MANAGER_STATUS_pc_vcu(SAFETY_MANAGER_STATUS_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->SM_CurrentLevel = (uint8_t) ( (_d[0] & (0x03U)) );
  _m->SM_PreviousLevel = (uint8_t) ( ((_d[0] >> 2U) & (0x03U)) );
  _m->SM_EmergencyStopActive = (uint8_t) ( ((_d[0] >> 4U) & (0x01U)) );
  _m->SM_LastErrorLevel = (uint8_t) ( ((_d[0] >> 5U) & (0x03U)) );
  _m->SM_Err_EmergencyButton = (uint8_t) ( (_d[1] & (0x01U)) );
  _m->SM_ErrRCEmergency = (uint8_t) ( ((_d[1] >> 1U) & (0x01U)) );
  _m->SM_ErrGPIO = (uint8_t) ( ((_d[1] >> 2U) & (0x01U)) );
  _m->SM_ErrSysMon = (uint8_t) ( ((_d[1] >> 3U) & (0x01U)) );
  _m->SM_ErrSteer = (uint8_t) ( ((_d[1] >> 4U) & (0x01U)) );
  _m->SM_ErrBrake = (uint8_t) ( ((_d[1] >> 5U) & (0x01U)) );
  _m->SM_ErrRC = (uint8_t) ( ((_d[1] >> 6U) & (0x01U)) );
  _m->SM_Err_PCVCU = (uint8_t) ( ((_d[1] >> 7U) & (0x01U)) );
  _m->SM_LastErrorSource = (uint8_t) ( (_d[2] & (0x0FU)) );
  _m->SM_CriticalErrorCount = (uint8_t) ( ((_d[2] >> 4U) & (0x0FU)) );
  _m->SM_WarningCount = (uint8_t) ( (_d[3] & (0xFFU)) );
  _m->SM_ErrorCount = (uint8_t) ( (_d[4] & (0xFFU)) );
  _m->SM_CriticalCount = (uint8_t) ( (_d[5] & (0xFFU)) );
  _m->SM_ErrBattery = (uint8_t) ( (_d[6] & (0x01U)) );
  _m->SM_ErrSafety = (uint8_t) ( ((_d[6] >> 1U) & (0x01U)) );
  _m->SM_ErrBBW = (uint8_t) ( ((_d[6] >> 2U) & (0x01U)) );

#ifdef PC_VCU_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SAFETY_MANAGER_STATUS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SAFETY_MANAGER_STATUS_pc_vcu(&_m->mon1, SAFETY_MANAGER_STATUS_CANID);
#endif // PC_VCU_USE_DIAG_MONITORS

  return SAFETY_MANAGER_STATUS_CANID;
}

#ifdef PC_VCU_USE_CANSTRUCT

uint32_t Pack_SAFETY_MANAGER_STATUS_pc_vcu(SAFETY_MANAGER_STATUS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(SAFETY_MANAGER_STATUS_DLC); cframe->Data[i++] = PC_VCU_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->SM_CurrentLevel & (0x03U)) | ((_m->SM_PreviousLevel & (0x03U)) << 2U) | ((_m->SM_EmergencyStopActive & (0x01U)) << 4U) | ((_m->SM_LastErrorLevel & (0x03U)) << 5U) );
  cframe->Data[1] |= (uint8_t) ( (_m->SM_Err_EmergencyButton & (0x01U)) | ((_m->SM_ErrRCEmergency & (0x01U)) << 1U) | ((_m->SM_ErrGPIO & (0x01U)) << 2U) | ((_m->SM_ErrSysMon & (0x01U)) << 3U) | ((_m->SM_ErrSteer & (0x01U)) << 4U) | ((_m->SM_ErrBrake & (0x01U)) << 5U) | ((_m->SM_ErrRC & (0x01U)) << 6U) | ((_m->SM_Err_PCVCU & (0x01U)) << 7U) );
  cframe->Data[2] |= (uint8_t) ( (_m->SM_LastErrorSource & (0x0FU)) | ((_m->SM_CriticalErrorCount & (0x0FU)) << 4U) );
  cframe->Data[3] |= (uint8_t) ( (_m->SM_WarningCount & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->SM_ErrorCount & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->SM_CriticalCount & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->SM_ErrBattery & (0x01U)) | ((_m->SM_ErrSafety & (0x01U)) << 1U) | ((_m->SM_ErrBBW & (0x01U)) << 2U) );

  cframe->MsgId = (uint32_t) SAFETY_MANAGER_STATUS_CANID;
  cframe->DLC = (uint8_t) SAFETY_MANAGER_STATUS_DLC;
  cframe->IDE = (uint8_t) SAFETY_MANAGER_STATUS_IDE;
  return SAFETY_MANAGER_STATUS_CANID;
}

#else

uint32_t Pack_SAFETY_MANAGER_STATUS_pc_vcu(SAFETY_MANAGER_STATUS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(SAFETY_MANAGER_STATUS_DLC); _d[i++] = PC_VCU_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->SM_CurrentLevel & (0x03U)) | ((_m->SM_PreviousLevel & (0x03U)) << 2U) | ((_m->SM_EmergencyStopActive & (0x01U)) << 4U) | ((_m->SM_LastErrorLevel & (0x03U)) << 5U) );
  _d[1] |= (uint8_t) ( (_m->SM_Err_EmergencyButton & (0x01U)) | ((_m->SM_ErrRCEmergency & (0x01U)) << 1U) | ((_m->SM_ErrGPIO & (0x01U)) << 2U) | ((_m->SM_ErrSysMon & (0x01U)) << 3U) | ((_m->SM_ErrSteer & (0x01U)) << 4U) | ((_m->SM_ErrBrake & (0x01U)) << 5U) | ((_m->SM_ErrRC & (0x01U)) << 6U) | ((_m->SM_Err_PCVCU & (0x01U)) << 7U) );
  _d[2] |= (uint8_t) ( (_m->SM_LastErrorSource & (0x0FU)) | ((_m->SM_CriticalErrorCount & (0x0FU)) << 4U) );
  _d[3] |= (uint8_t) ( (_m->SM_WarningCount & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->SM_ErrorCount & (0xFFU)) );
  _d[5] |= (uint8_t) ( (_m->SM_CriticalCount & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->SM_ErrBattery & (0x01U)) | ((_m->SM_ErrSafety & (0x01U)) << 1U) | ((_m->SM_ErrBBW & (0x01U)) << 2U) );

  *_len = (uint8_t) SAFETY_MANAGER_STATUS_DLC;
  *_ide = (uint8_t) SAFETY_MANAGER_STATUS_IDE;
  return SAFETY_MANAGER_STATUS_CANID;
}

#endif // PC_VCU_USE_CANSTRUCT

uint32_t Unpack_VCU_CTRL_CMD_SI_pc_vcu(VCU_CTRL_CMD_SI_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->TireAngleRad_Cmd_ro = (int16_t) __ext_sig__(( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) ), 16);
#ifdef PC_VCU_USE_SIGFLOAT
  _m->TireAngleRad_Cmd_phys = (sigfloat_t)(PC_VCU_TireAngleRad_Cmd_ro_fromS(_m->TireAngleRad_Cmd_ro));
#endif // PC_VCU_USE_SIGFLOAT

  _m->VehicleSpeedMS_Cmd_ro = (int16_t) __ext_sig__(( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) ), 16);
#ifdef PC_VCU_USE_SIGFLOAT
  _m->VehicleSpeedMS_Cmd_phys = (sigfloat_t)(PC_VCU_VehicleSpeedMS_Cmd_ro_fromS(_m->VehicleSpeedMS_Cmd_ro));
#endif // PC_VCU_USE_SIGFLOAT

  _m->AutonomousEnable = (uint8_t) ( (_d[4] & (0x01U)) );
  _m->EmergencyActive = (uint8_t) ( ((_d[4] >> 1U) & (0x01U)) );
  _m->SafetyDisable = (uint8_t) ( ((_d[4] >> 2U) & (0x01U)) );
  _m->GearReq = (uint8_t) ( ((_d[4] >> 3U) & (0x1FU)) );
  _m->TurnLeft = (uint8_t) ( (_d[5] & (0x01U)) );
  _m->TurnRight = (uint8_t) ( ((_d[5] >> 1U) & (0x01U)) );
  _m->Hazard = (uint8_t) ( ((_d[5] >> 2U) & (0x01U)) );
  _m->Horn = (uint8_t) ( ((_d[5] >> 3U) & (0x01U)) );
  _m->Reserved = (uint8_t) ( ((_d[5] >> 4U) & (0x0FU)) );
  _m->AliveCounter = (uint8_t) ( (_d[6] & (0xFFU)) );
  _m->CRC8 = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef PC_VCU_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VCU_CTRL_CMD_SI_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VCU_CTRL_CMD_SI_pc_vcu(&_m->mon1, VCU_CTRL_CMD_SI_CANID);
#endif // PC_VCU_USE_DIAG_MONITORS

  return VCU_CTRL_CMD_SI_CANID;
}

#ifdef PC_VCU_USE_CANSTRUCT

uint32_t Pack_VCU_CTRL_CMD_SI_pc_vcu(VCU_CTRL_CMD_SI_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(VCU_CTRL_CMD_SI_DLC); cframe->Data[i++] = PC_VCU_INITIAL_BYTE_VALUE);

#ifdef PC_VCU_USE_SIGFLOAT
  _m->TireAngleRad_Cmd_ro = (int16_t) PC_VCU_TireAngleRad_Cmd_ro_toS(_m->TireAngleRad_Cmd_phys);
  _m->VehicleSpeedMS_Cmd_ro = (int16_t) PC_VCU_VehicleSpeedMS_Cmd_ro_toS(_m->VehicleSpeedMS_Cmd_phys);
#endif // PC_VCU_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->TireAngleRad_Cmd_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->TireAngleRad_Cmd_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->VehicleSpeedMS_Cmd_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->VehicleSpeedMS_Cmd_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->AutonomousEnable & (0x01U)) | ((_m->EmergencyActive & (0x01U)) << 1U) | ((_m->SafetyDisable & (0x01U)) << 2U) | ((_m->GearReq & (0x1FU)) << 3U) );
  cframe->Data[5] |= (uint8_t) ( (_m->TurnLeft & (0x01U)) | ((_m->TurnRight & (0x01U)) << 1U) | ((_m->Hazard & (0x01U)) << 2U) | ((_m->Horn & (0x01U)) << 3U) | ((_m->Reserved & (0x0FU)) << 4U) );
  cframe->Data[6] |= (uint8_t) ( (_m->AliveCounter & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->CRC8 & (0xFFU)) );

  cframe->MsgId = (uint32_t) VCU_CTRL_CMD_SI_CANID;
  cframe->DLC = (uint8_t) VCU_CTRL_CMD_SI_DLC;
  cframe->IDE = (uint8_t) VCU_CTRL_CMD_SI_IDE;
  return VCU_CTRL_CMD_SI_CANID;
}

#else

uint32_t Pack_VCU_CTRL_CMD_SI_pc_vcu(VCU_CTRL_CMD_SI_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(VCU_CTRL_CMD_SI_DLC); _d[i++] = PC_VCU_INITIAL_BYTE_VALUE);

#ifdef PC_VCU_USE_SIGFLOAT
  _m->TireAngleRad_Cmd_ro = (int16_t) PC_VCU_TireAngleRad_Cmd_ro_toS(_m->TireAngleRad_Cmd_phys);
  _m->VehicleSpeedMS_Cmd_ro = (int16_t) PC_VCU_VehicleSpeedMS_Cmd_ro_toS(_m->VehicleSpeedMS_Cmd_phys);
#endif // PC_VCU_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->TireAngleRad_Cmd_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->TireAngleRad_Cmd_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->VehicleSpeedMS_Cmd_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->VehicleSpeedMS_Cmd_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->AutonomousEnable & (0x01U)) | ((_m->EmergencyActive & (0x01U)) << 1U) | ((_m->SafetyDisable & (0x01U)) << 2U) | ((_m->GearReq & (0x1FU)) << 3U) );
  _d[5] |= (uint8_t) ( (_m->TurnLeft & (0x01U)) | ((_m->TurnRight & (0x01U)) << 1U) | ((_m->Hazard & (0x01U)) << 2U) | ((_m->Horn & (0x01U)) << 3U) | ((_m->Reserved & (0x0FU)) << 4U) );
  _d[6] |= (uint8_t) ( (_m->AliveCounter & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->CRC8 & (0xFFU)) );

  *_len = (uint8_t) VCU_CTRL_CMD_SI_DLC;
  *_ide = (uint8_t) VCU_CTRL_CMD_SI_IDE;
  return VCU_CTRL_CMD_SI_CANID;
}

#endif // PC_VCU_USE_CANSTRUCT

uint32_t Unpack_SAFE_STAT_ROS2_HEARTBEAT_pc_vcu(SAFE_STAT_ROS2_HEARTBEAT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ROS_Time_ms = (uint64_t) ( ((uint64_t)(_d[5] & (0xFFU)) << 40U) | ((uint64_t)(_d[4] & (0xFFU)) << 32U) | ((_d[3] & (0xFFU)) << 24U) | ((_d[2] & (0xFFU)) << 16U) | ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );
  _m->AliveCounter = (uint8_t) ( (_d[6] & (0xFFU)) );
  _m->CRC8 = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef PC_VCU_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SAFE_STAT_ROS2_HEARTBEAT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SAFE_STAT_ROS2_HEARTBEAT_pc_vcu(&_m->mon1, SAFE_STAT_ROS2_HEARTBEAT_CANID);
#endif // PC_VCU_USE_DIAG_MONITORS

  return SAFE_STAT_ROS2_HEARTBEAT_CANID;
}

#ifdef PC_VCU_USE_CANSTRUCT

uint32_t Pack_SAFE_STAT_ROS2_HEARTBEAT_pc_vcu(SAFE_STAT_ROS2_HEARTBEAT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(SAFE_STAT_ROS2_HEARTBEAT_DLC); cframe->Data[i++] = PC_VCU_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->ROS_Time_ms & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->ROS_Time_ms >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->ROS_Time_ms >> 16U) & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->ROS_Time_ms >> 24U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->ROS_Time_ms >> 32U) & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->ROS_Time_ms >> 40U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->AliveCounter & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->CRC8 & (0xFFU)) );

  cframe->MsgId = (uint32_t) SAFE_STAT_ROS2_HEARTBEAT_CANID;
  cframe->DLC = (uint8_t) SAFE_STAT_ROS2_HEARTBEAT_DLC;
  cframe->IDE = (uint8_t) SAFE_STAT_ROS2_HEARTBEAT_IDE;
  return SAFE_STAT_ROS2_HEARTBEAT_CANID;
}

#else

uint32_t Pack_SAFE_STAT_ROS2_HEARTBEAT_pc_vcu(SAFE_STAT_ROS2_HEARTBEAT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(SAFE_STAT_ROS2_HEARTBEAT_DLC); _d[i++] = PC_VCU_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->ROS_Time_ms & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->ROS_Time_ms >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( ((_m->ROS_Time_ms >> 16U) & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->ROS_Time_ms >> 24U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( ((_m->ROS_Time_ms >> 32U) & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->ROS_Time_ms >> 40U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->AliveCounter & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->CRC8 & (0xFFU)) );

  *_len = (uint8_t) SAFE_STAT_ROS2_HEARTBEAT_DLC;
  *_ide = (uint8_t) SAFE_STAT_ROS2_HEARTBEAT_IDE;
  return SAFE_STAT_ROS2_HEARTBEAT_CANID;
}

#endif // PC_VCU_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_MOTION_SI_pc_vcu(VCU_STAT_MOTION_SI_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->TireAngleRad_Act_ro = (int16_t) __ext_sig__(( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) ), 16);
#ifdef PC_VCU_USE_SIGFLOAT
  _m->TireAngleRad_Act_phys = (sigfloat_t)(PC_VCU_TireAngleRad_Act_ro_fromS(_m->TireAngleRad_Act_ro));
#endif // PC_VCU_USE_SIGFLOAT

  _m->VehicleSpeedMS_Act_ro = (int16_t) __ext_sig__(( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) ), 16);
#ifdef PC_VCU_USE_SIGFLOAT
  _m->VehicleSpeedMS_Act_phys = (sigfloat_t)(PC_VCU_VehicleSpeedMS_Act_ro_fromS(_m->VehicleSpeedMS_Act_ro));
#endif // PC_VCU_USE_SIGFLOAT

  _m->SteerAngleDeg_Act = (int16_t) __ext_sig__(( ((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) ), 16);
  _m->AliveCounter = (uint8_t) ( (_d[6] & (0xFFU)) );
  _m->CRC8 = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef PC_VCU_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VCU_STAT_MOTION_SI_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VCU_STAT_MOTION_SI_pc_vcu(&_m->mon1, VCU_STAT_MOTION_SI_CANID);
#endif // PC_VCU_USE_DIAG_MONITORS

  return VCU_STAT_MOTION_SI_CANID;
}

#ifdef PC_VCU_USE_CANSTRUCT

uint32_t Pack_VCU_STAT_MOTION_SI_pc_vcu(VCU_STAT_MOTION_SI_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(VCU_STAT_MOTION_SI_DLC); cframe->Data[i++] = PC_VCU_INITIAL_BYTE_VALUE);

#ifdef PC_VCU_USE_SIGFLOAT
  _m->TireAngleRad_Act_ro = (int16_t) PC_VCU_TireAngleRad_Act_ro_toS(_m->TireAngleRad_Act_phys);
  _m->VehicleSpeedMS_Act_ro = (int16_t) PC_VCU_VehicleSpeedMS_Act_ro_toS(_m->VehicleSpeedMS_Act_phys);
#endif // PC_VCU_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->TireAngleRad_Act_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->TireAngleRad_Act_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->VehicleSpeedMS_Act_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->VehicleSpeedMS_Act_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->SteerAngleDeg_Act & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->SteerAngleDeg_Act >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->AliveCounter & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->CRC8 & (0xFFU)) );

  cframe->MsgId = (uint32_t) VCU_STAT_MOTION_SI_CANID;
  cframe->DLC = (uint8_t) VCU_STAT_MOTION_SI_DLC;
  cframe->IDE = (uint8_t) VCU_STAT_MOTION_SI_IDE;
  return VCU_STAT_MOTION_SI_CANID;
}

#else

uint32_t Pack_VCU_STAT_MOTION_SI_pc_vcu(VCU_STAT_MOTION_SI_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(VCU_STAT_MOTION_SI_DLC); _d[i++] = PC_VCU_INITIAL_BYTE_VALUE);

#ifdef PC_VCU_USE_SIGFLOAT
  _m->TireAngleRad_Act_ro = (int16_t) PC_VCU_TireAngleRad_Act_ro_toS(_m->TireAngleRad_Act_phys);
  _m->VehicleSpeedMS_Act_ro = (int16_t) PC_VCU_VehicleSpeedMS_Act_ro_toS(_m->VehicleSpeedMS_Act_phys);
#endif // PC_VCU_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->TireAngleRad_Act_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->TireAngleRad_Act_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->VehicleSpeedMS_Act_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->VehicleSpeedMS_Act_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->SteerAngleDeg_Act & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->SteerAngleDeg_Act >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->AliveCounter & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->CRC8 & (0xFFU)) );

  *_len = (uint8_t) VCU_STAT_MOTION_SI_DLC;
  *_ide = (uint8_t) VCU_STAT_MOTION_SI_IDE;
  return VCU_STAT_MOTION_SI_CANID;
}

#endif // PC_VCU_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_VEHICLE_STATE_pc_vcu(VCU_STAT_VEHICLE_STATE_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->GearAct = (uint8_t) ( (_d[0] & (0x1FU)) );
  _m->Reserved = (uint8_t) ( ((_d[0] >> 5U) & (0x07U)) );
  _m->TurnLeft_Stat = (uint8_t) ( (_d[1] & (0x01U)) );
  _m->TurnRight_Stat = (uint8_t) ( ((_d[1] >> 1U) & (0x01U)) );
  _m->Hazard_Stat = (uint8_t) ( ((_d[1] >> 2U) & (0x01U)) );
  _m->Horn_Stat = (uint8_t) ( ((_d[1] >> 3U) & (0x01U)) );
  _m->Reserved_1 = (uint8_t) ( ((_d[1] >> 4U) & (0x0FU)) );
  _m->ControlMode = (uint8_t) ( (_d[2] & (0xFFU)) );
  _m->SafetyState = (uint8_t) ( (_d[3] & (0xFFU)) );
  _m->BatterySoC = (uint8_t) ( (_d[4] & (0xFFU)) );
  _m->FaultSummary = (uint8_t) ( (_d[5] & (0xFFU)) );
  _m->AliveCounter = (uint8_t) ( (_d[6] & (0xFFU)) );
  _m->CRC8 = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef PC_VCU_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VCU_STAT_VEHICLE_STATE_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VCU_STAT_VEHICLE_STATE_pc_vcu(&_m->mon1, VCU_STAT_VEHICLE_STATE_CANID);
#endif // PC_VCU_USE_DIAG_MONITORS

  return VCU_STAT_VEHICLE_STATE_CANID;
}

#ifdef PC_VCU_USE_CANSTRUCT

uint32_t Pack_VCU_STAT_VEHICLE_STATE_pc_vcu(VCU_STAT_VEHICLE_STATE_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(VCU_STAT_VEHICLE_STATE_DLC); cframe->Data[i++] = PC_VCU_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->GearAct & (0x1FU)) | ((_m->Reserved & (0x07U)) << 5U) );
  cframe->Data[1] |= (uint8_t) ( (_m->TurnLeft_Stat & (0x01U)) | ((_m->TurnRight_Stat & (0x01U)) << 1U) | ((_m->Hazard_Stat & (0x01U)) << 2U) | ((_m->Horn_Stat & (0x01U)) << 3U) | ((_m->Reserved_1 & (0x0FU)) << 4U) );
  cframe->Data[2] |= (uint8_t) ( (_m->ControlMode & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->SafetyState & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->BatterySoC & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->FaultSummary & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->AliveCounter & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->CRC8 & (0xFFU)) );

  cframe->MsgId = (uint32_t) VCU_STAT_VEHICLE_STATE_CANID;
  cframe->DLC = (uint8_t) VCU_STAT_VEHICLE_STATE_DLC;
  cframe->IDE = (uint8_t) VCU_STAT_VEHICLE_STATE_IDE;
  return VCU_STAT_VEHICLE_STATE_CANID;
}

#else

uint32_t Pack_VCU_STAT_VEHICLE_STATE_pc_vcu(VCU_STAT_VEHICLE_STATE_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(VCU_STAT_VEHICLE_STATE_DLC); _d[i++] = PC_VCU_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->GearAct & (0x1FU)) | ((_m->Reserved & (0x07U)) << 5U) );
  _d[1] |= (uint8_t) ( (_m->TurnLeft_Stat & (0x01U)) | ((_m->TurnRight_Stat & (0x01U)) << 1U) | ((_m->Hazard_Stat & (0x01U)) << 2U) | ((_m->Horn_Stat & (0x01U)) << 3U) | ((_m->Reserved_1 & (0x0FU)) << 4U) );
  _d[2] |= (uint8_t) ( (_m->ControlMode & (0xFFU)) );
  _d[3] |= (uint8_t) ( (_m->SafetyState & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->BatterySoC & (0xFFU)) );
  _d[5] |= (uint8_t) ( (_m->FaultSummary & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->AliveCounter & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->CRC8 & (0xFFU)) );

  *_len = (uint8_t) VCU_STAT_VEHICLE_STATE_DLC;
  *_ide = (uint8_t) VCU_STAT_VEHICLE_STATE_IDE;
  return VCU_STAT_VEHICLE_STATE_CANID;
}

#endif // PC_VCU_USE_CANSTRUCT

uint32_t Unpack_MCU_MODULE_STATUS_pc_vcu(MCU_MODULE_STATUS_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MCU_ModuleStatus = (uint8_t) ( (_d[0] & (0x03U)) );
  _m->MCU_Gear = (uint8_t) ( ((_d[0] >> 2U) & (0x0FU)) );
  _m->MCU_ErrCommFault = (uint8_t) ( ((_d[0] >> 6U) & (0x01U)) );
  _m->MCU_ErrZapiInternal = (uint8_t) ( ((_d[0] >> 7U) & (0x01U)) );
  _m->MCU_ZapiAlarmCode = (uint16_t) ( ((_d[2] & (0xFFU)) << 8U) | (_d[1] & (0xFFU)) );
  _m->MCU_FramePeriod = (uint8_t) ( (_d[3] & (0xFFU)) );
  _m->MCU_Odometer_ro = (uint32_t) ( ((_d[7] & (0xFFU)) << 24U) | ((_d[6] & (0xFFU)) << 16U) | ((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) );
#ifdef PC_VCU_USE_SIGFLOAT
  _m->MCU_Odometer_phys = (sigfloat_t)(PC_VCU_MCU_Odometer_ro_fromS(_m->MCU_Odometer_ro));
#endif // PC_VCU_USE_SIGFLOAT

#ifdef PC_VCU_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < MCU_MODULE_STATUS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_MCU_MODULE_STATUS_pc_vcu(&_m->mon1, MCU_MODULE_STATUS_CANID);
#endif // PC_VCU_USE_DIAG_MONITORS

  return MCU_MODULE_STATUS_CANID;
}

#ifdef PC_VCU_USE_CANSTRUCT

uint32_t Pack_MCU_MODULE_STATUS_pc_vcu(MCU_MODULE_STATUS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(MCU_MODULE_STATUS_DLC); cframe->Data[i++] = PC_VCU_INITIAL_BYTE_VALUE);

#ifdef PC_VCU_USE_SIGFLOAT
  _m->MCU_Odometer_ro = (uint32_t) PC_VCU_MCU_Odometer_ro_toS(_m->MCU_Odometer_phys);
#endif // PC_VCU_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->MCU_ModuleStatus & (0x03U)) | ((_m->MCU_Gear & (0x0FU)) << 2U) | ((_m->MCU_ErrCommFault & (0x01U)) << 6U) | ((_m->MCU_ErrZapiInternal & (0x01U)) << 7U) );
  cframe->Data[1] |= (uint8_t) ( (_m->MCU_ZapiAlarmCode & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->MCU_ZapiAlarmCode >> 8U) & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->MCU_FramePeriod & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->MCU_Odometer_ro & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->MCU_Odometer_ro >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( ((_m->MCU_Odometer_ro >> 16U) & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->MCU_Odometer_ro >> 24U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) MCU_MODULE_STATUS_CANID;
  cframe->DLC = (uint8_t) MCU_MODULE_STATUS_DLC;
  cframe->IDE = (uint8_t) MCU_MODULE_STATUS_IDE;
  return MCU_MODULE_STATUS_CANID;
}

#else

uint32_t Pack_MCU_MODULE_STATUS_pc_vcu(MCU_MODULE_STATUS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(MCU_MODULE_STATUS_DLC); _d[i++] = PC_VCU_INITIAL_BYTE_VALUE);

#ifdef PC_VCU_USE_SIGFLOAT
  _m->MCU_Odometer_ro = (uint32_t) PC_VCU_MCU_Odometer_ro_toS(_m->MCU_Odometer_phys);
#endif // PC_VCU_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->MCU_ModuleStatus & (0x03U)) | ((_m->MCU_Gear & (0x0FU)) << 2U) | ((_m->MCU_ErrCommFault & (0x01U)) << 6U) | ((_m->MCU_ErrZapiInternal & (0x01U)) << 7U) );
  _d[1] |= (uint8_t) ( (_m->MCU_ZapiAlarmCode & (0xFFU)) );
  _d[2] |= (uint8_t) ( ((_m->MCU_ZapiAlarmCode >> 8U) & (0xFFU)) );
  _d[3] |= (uint8_t) ( (_m->MCU_FramePeriod & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->MCU_Odometer_ro & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->MCU_Odometer_ro >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( ((_m->MCU_Odometer_ro >> 16U) & (0xFFU)) );
  _d[7] |= (uint8_t) ( ((_m->MCU_Odometer_ro >> 24U) & (0xFFU)) );

  *_len = (uint8_t) MCU_MODULE_STATUS_DLC;
  *_ide = (uint8_t) MCU_MODULE_STATUS_IDE;
  return MCU_MODULE_STATUS_CANID;
}

#endif // PC_VCU_USE_CANSTRUCT

uint32_t Unpack_DTC_ERROR_STATUS_pc_vcu(DTC_ERROR_STATUS_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->SYS_T1_HI = (uint8_t) ( (_d[0] & (0x01U)) );
  _m->SYS_T1_LO = (uint8_t) ( ((_d[0] >> 1U) & (0x01U)) );
  _m->SYS_T2_HI = (uint8_t) ( ((_d[0] >> 2U) & (0x01U)) );
  _m->SYS_T2_LO = (uint8_t) ( ((_d[0] >> 3U) & (0x01U)) );
  _m->SYS_KL30_HI = (uint8_t) ( ((_d[0] >> 4U) & (0x01U)) );
  _m->SYS_KL30_LO = (uint8_t) ( ((_d[0] >> 5U) & (0x01U)) );
  _m->SYS_KL30_2_HI = (uint8_t) ( ((_d[0] >> 6U) & (0x01U)) );
  _m->SYS_KL_30_LO = (uint8_t) ( ((_d[0] >> 7U) & (0x01U)) );
  _m->SYS_5V8_HI = (uint8_t) ( (_d[1] & (0x01U)) );
  _m->SYS_5V8_LO = (uint8_t) ( ((_d[1] >> 1U) & (0x01U)) );
  _m->SYS_5VD_HI = (uint8_t) ( ((_d[1] >> 2U) & (0x01U)) );
  _m->SYS_5VD_LO = (uint8_t) ( ((_d[1] >> 3U) & (0x01U)) );
  _m->SYS_STACK = (uint8_t) ( ((_d[1] >> 4U) & (0x01U)) );
  _m->BRK_HSD_OC = (uint8_t) ( ((_d[1] >> 5U) & (0x01U)) );
  _m->BRK_HSD_OL = (uint8_t) ( ((_d[1] >> 6U) & (0x01U)) );
  _m->BRK_HSD_ERR = (uint8_t) ( ((_d[1] >> 7U) & (0x01U)) );
  _m->BRK_EBS_WARN = (uint8_t) ( (_d[2] & (0x01U)) );
  _m->BRK_EBS_CRIT = (uint8_t) ( ((_d[2] >> 1U) & (0x01U)) );
  _m->BRK_COM_ERR = (uint8_t) ( ((_d[2] >> 2U) & (0x01U)) );
  _m->BRK_ECU_ERR = (uint8_t) ( ((_d[2] >> 3U) & (0x01U)) );
  _m->BRK_DRV_ERR = (uint8_t) ( ((_d[2] >> 4U) & (0x01U)) );
  _m->STR_HSD_OC = (uint8_t) ( ((_d[2] >> 5U) & (0x01U)) );
  _m->STR_HSD_OL = (uint8_t) ( ((_d[2] >> 6U) & (0x01U)) );
  _m->STR_HSD_ERR = (uint8_t) ( ((_d[2] >> 7U) & (0x01U)) );
  _m->STR_DRV_FLT = (uint8_t) ( (_d[3] & (0x01U)) );
  _m->STR_MOT_STALL = (uint8_t) ( ((_d[3] >> 1U) & (0x01U)) );
  _m->STR_CAL_ERR = (uint8_t) ( ((_d[3] >> 2U) & (0x01U)) );
  _m->STR_COM_INT = (uint8_t) ( ((_d[3] >> 3U) & (0x01U)) );
  _m->STR_EEP_ERR = (uint8_t) ( ((_d[3] >> 4U) & (0x01U)) );
  _m->STR_CTRL_ERR = (uint8_t) ( ((_d[3] >> 5U) & (0x01U)) );
  _m->STR_ANG_SENS = (uint8_t) ( ((_d[3] >> 6U) & (0x01U)) );
  _m->STR_TRQ_SENS = (uint8_t) ( ((_d[3] >> 7U) & (0x01U)) );
  _m->STR_OT_SEV = (uint8_t) ( (_d[4] & (0x01U)) );
  _m->STR_OT_NORM = (uint8_t) ( ((_d[4] >> 1U) & (0x01U)) );
  _m->STR_UV_ERR = (uint8_t) ( ((_d[4] >> 2U) & (0x01U)) );
  _m->STR_OV_ERR = (uint8_t) ( ((_d[4] >> 3U) & (0x01U)) );
  _m->STR_CAN_TO = (uint8_t) ( ((_d[4] >> 4U) & (0x01U)) );
  _m->RC_FRM_ERR = (uint8_t) ( ((_d[4] >> 5U) & (0x01U)) );
  _m->RC_FRM_LST = (uint8_t) ( ((_d[4] >> 6U) & (0x01U)) );
  _m->RC_FRM_FS = (uint8_t) ( ((_d[4] >> 7U) & (0x01U)) );
  _m->RC_EMG_ACT = (uint8_t) ( (_d[5] & (0x01U)) );
  _m->RC_REM_EMG = (uint8_t) ( ((_d[5] >> 1U) & (0x01U)) );
  _m->RC_COM_ERR = (uint8_t) ( ((_d[5] >> 2U) & (0x01U)) );
  _m->MCU_ALM_ACT = (uint8_t) ( ((_d[5] >> 3U) & (0x01U)) );
  _m->MCU_COM_ERR = (uint8_t) ( ((_d[5] >> 4U) & (0x01U)) );
  _m->SAFE_VCU_COM_FLT = (uint8_t) ( ((_d[5] >> 5U) & (0x01U)) );
  _m->SAFE_VCU_EMG_ACT = (uint8_t) ( ((_d[5] >> 6U) & (0x01U)) );
  _m->JK_UNIT_OVER_VOLTAGE = (uint8_t) ( ((_d[5] >> 7U) & (0x01U)) );
  _m->JK_UNIT_UNDER_VOLTAGE = (uint8_t) ( (_d[6] & (0x01U)) );
  _m->JK_TOTAL_VOLTAGE_OVER_VOLTAGE = (uint8_t) ( ((_d[6] >> 1U) & (0x01U)) );
  _m->JK_TOTAL_VOLTAGE_UNDER_VOLTAGE = (uint8_t) ( ((_d[6] >> 2U) & (0x01U)) );
  _m->JK_LARGE_PRESSURE_DIFF_OF_MON = (uint8_t) ( ((_d[6] >> 3U) & (0x01U)) );
  _m->JK_DISCHARGE_OVER_CURRENT = (uint8_t) ( ((_d[6] >> 4U) & (0x01U)) );
  _m->JK_CHARGE_OVER_CURRENT = (uint8_t) ( ((_d[6] >> 5U) & (0x01U)) );
  _m->JK_TEMPERATURE_IS_TOO_HIGH = (uint8_t) ( ((_d[6] >> 6U) & (0x01U)) );
  _m->JK_TEMPERATURE_IS_TOO_LOW = (uint8_t) ( ((_d[6] >> 7U) & (0x01U)) );
  _m->JK_EXCESSIVE_TEMPERATURE_DIFF = (uint8_t) ( (_d[7] & (0x01U)) );
  _m->JK_SOC_TOO_LOW = (uint8_t) ( ((_d[7] >> 1U) & (0x01U)) );
  _m->JK_INSULATION_IS_TOO_LOW = (uint8_t) ( ((_d[7] >> 2U) & (0x01U)) );
  _m->JK_HIGH_VOLTAGE_INTERLOCK_FAULT = (uint8_t) ( ((_d[7] >> 3U) & (0x01U)) );
  _m->JK_EXTERNAL_COMMUNICATION_FAIL = (uint8_t) ( ((_d[7] >> 4U) & (0x01U)) );
  _m->JK_INTERNAL_COMMUNICATION_FAIL = (uint8_t) ( ((_d[7] >> 5U) & (0x01U)) );
  _m->ASPS_HSD_OC = (uint8_t) ( ((_d[7] >> 6U) & (0x01U)) );
  _m->ASPS_HSD_OL = (uint8_t) ( ((_d[7] >> 7U) & (0x01U)) );

#ifdef PC_VCU_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DTC_ERROR_STATUS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DTC_ERROR_STATUS_pc_vcu(&_m->mon1, DTC_ERROR_STATUS_CANID);
#endif // PC_VCU_USE_DIAG_MONITORS

  return DTC_ERROR_STATUS_CANID;
}

#ifdef PC_VCU_USE_CANSTRUCT

uint32_t Pack_DTC_ERROR_STATUS_pc_vcu(DTC_ERROR_STATUS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(DTC_ERROR_STATUS_DLC); cframe->Data[i++] = PC_VCU_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->SYS_T1_HI & (0x01U)) | ((_m->SYS_T1_LO & (0x01U)) << 1U) | ((_m->SYS_T2_HI & (0x01U)) << 2U) | ((_m->SYS_T2_LO & (0x01U)) << 3U) | ((_m->SYS_KL30_HI & (0x01U)) << 4U) | ((_m->SYS_KL30_LO & (0x01U)) << 5U) | ((_m->SYS_KL30_2_HI & (0x01U)) << 6U) | ((_m->SYS_KL_30_LO & (0x01U)) << 7U) );
  cframe->Data[1] |= (uint8_t) ( (_m->SYS_5V8_HI & (0x01U)) | ((_m->SYS_5V8_LO & (0x01U)) << 1U) | ((_m->SYS_5VD_HI & (0x01U)) << 2U) | ((_m->SYS_5VD_LO & (0x01U)) << 3U) | ((_m->SYS_STACK & (0x01U)) << 4U) | ((_m->BRK_HSD_OC & (0x01U)) << 5U) | ((_m->BRK_HSD_OL & (0x01U)) << 6U) | ((_m->BRK_HSD_ERR & (0x01U)) << 7U) );
  cframe->Data[2] |= (uint8_t) ( (_m->BRK_EBS_WARN & (0x01U)) | ((_m->BRK_EBS_CRIT & (0x01U)) << 1U) | ((_m->BRK_COM_ERR & (0x01U)) << 2U) | ((_m->BRK_ECU_ERR & (0x01U)) << 3U) | ((_m->BRK_DRV_ERR & (0x01U)) << 4U) | ((_m->STR_HSD_OC & (0x01U)) << 5U) | ((_m->STR_HSD_OL & (0x01U)) << 6U) | ((_m->STR_HSD_ERR & (0x01U)) << 7U) );
  cframe->Data[3] |= (uint8_t) ( (_m->STR_DRV_FLT & (0x01U)) | ((_m->STR_MOT_STALL & (0x01U)) << 1U) | ((_m->STR_CAL_ERR & (0x01U)) << 2U) | ((_m->STR_COM_INT & (0x01U)) << 3U) | ((_m->STR_EEP_ERR & (0x01U)) << 4U) | ((_m->STR_CTRL_ERR & (0x01U)) << 5U) | ((_m->STR_ANG_SENS & (0x01U)) << 6U) | ((_m->STR_TRQ_SENS & (0x01U)) << 7U) );
  cframe->Data[4] |= (uint8_t) ( (_m->STR_OT_SEV & (0x01U)) | ((_m->STR_OT_NORM & (0x01U)) << 1U) | ((_m->STR_UV_ERR & (0x01U)) << 2U) | ((_m->STR_OV_ERR & (0x01U)) << 3U) | ((_m->STR_CAN_TO & (0x01U)) << 4U) | ((_m->RC_FRM_ERR & (0x01U)) << 5U) | ((_m->RC_FRM_LST & (0x01U)) << 6U) | ((_m->RC_FRM_FS & (0x01U)) << 7U) );
  cframe->Data[5] |= (uint8_t) ( (_m->RC_EMG_ACT & (0x01U)) | ((_m->RC_REM_EMG & (0x01U)) << 1U) | ((_m->RC_COM_ERR & (0x01U)) << 2U) | ((_m->MCU_ALM_ACT & (0x01U)) << 3U) | ((_m->MCU_COM_ERR & (0x01U)) << 4U) | ((_m->SAFE_VCU_COM_FLT & (0x01U)) << 5U) | ((_m->SAFE_VCU_EMG_ACT & (0x01U)) << 6U) | ((_m->JK_UNIT_OVER_VOLTAGE & (0x01U)) << 7U) );
  cframe->Data[6] |= (uint8_t) ( (_m->JK_UNIT_UNDER_VOLTAGE & (0x01U)) | ((_m->JK_TOTAL_VOLTAGE_OVER_VOLTAGE & (0x01U)) << 1U) | ((_m->JK_TOTAL_VOLTAGE_UNDER_VOLTAGE & (0x01U)) << 2U) | ((_m->JK_LARGE_PRESSURE_DIFF_OF_MON & (0x01U)) << 3U) | ((_m->JK_DISCHARGE_OVER_CURRENT & (0x01U)) << 4U) | ((_m->JK_CHARGE_OVER_CURRENT & (0x01U)) << 5U) | ((_m->JK_TEMPERATURE_IS_TOO_HIGH & (0x01U)) << 6U) | ((_m->JK_TEMPERATURE_IS_TOO_LOW & (0x01U)) << 7U) );
  cframe->Data[7] |= (uint8_t) ( (_m->JK_EXCESSIVE_TEMPERATURE_DIFF & (0x01U)) | ((_m->JK_SOC_TOO_LOW & (0x01U)) << 1U) | ((_m->JK_INSULATION_IS_TOO_LOW & (0x01U)) << 2U) | ((_m->JK_HIGH_VOLTAGE_INTERLOCK_FAULT & (0x01U)) << 3U) | ((_m->JK_EXTERNAL_COMMUNICATION_FAIL & (0x01U)) << 4U) | ((_m->JK_INTERNAL_COMMUNICATION_FAIL & (0x01U)) << 5U) | ((_m->ASPS_HSD_OC & (0x01U)) << 6U) | ((_m->ASPS_HSD_OL & (0x01U)) << 7U) );

  cframe->MsgId = (uint32_t) DTC_ERROR_STATUS_CANID;
  cframe->DLC = (uint8_t) DTC_ERROR_STATUS_DLC;
  cframe->IDE = (uint8_t) DTC_ERROR_STATUS_IDE;
  return DTC_ERROR_STATUS_CANID;
}

#else

uint32_t Pack_DTC_ERROR_STATUS_pc_vcu(DTC_ERROR_STATUS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(DTC_ERROR_STATUS_DLC); _d[i++] = PC_VCU_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->SYS_T1_HI & (0x01U)) | ((_m->SYS_T1_LO & (0x01U)) << 1U) | ((_m->SYS_T2_HI & (0x01U)) << 2U) | ((_m->SYS_T2_LO & (0x01U)) << 3U) | ((_m->SYS_KL30_HI & (0x01U)) << 4U) | ((_m->SYS_KL30_LO & (0x01U)) << 5U) | ((_m->SYS_KL30_2_HI & (0x01U)) << 6U) | ((_m->SYS_KL_30_LO & (0x01U)) << 7U) );
  _d[1] |= (uint8_t) ( (_m->SYS_5V8_HI & (0x01U)) | ((_m->SYS_5V8_LO & (0x01U)) << 1U) | ((_m->SYS_5VD_HI & (0x01U)) << 2U) | ((_m->SYS_5VD_LO & (0x01U)) << 3U) | ((_m->SYS_STACK & (0x01U)) << 4U) | ((_m->BRK_HSD_OC & (0x01U)) << 5U) | ((_m->BRK_HSD_OL & (0x01U)) << 6U) | ((_m->BRK_HSD_ERR & (0x01U)) << 7U) );
  _d[2] |= (uint8_t) ( (_m->BRK_EBS_WARN & (0x01U)) | ((_m->BRK_EBS_CRIT & (0x01U)) << 1U) | ((_m->BRK_COM_ERR & (0x01U)) << 2U) | ((_m->BRK_ECU_ERR & (0x01U)) << 3U) | ((_m->BRK_DRV_ERR & (0x01U)) << 4U) | ((_m->STR_HSD_OC & (0x01U)) << 5U) | ((_m->STR_HSD_OL & (0x01U)) << 6U) | ((_m->STR_HSD_ERR & (0x01U)) << 7U) );
  _d[3] |= (uint8_t) ( (_m->STR_DRV_FLT & (0x01U)) | ((_m->STR_MOT_STALL & (0x01U)) << 1U) | ((_m->STR_CAL_ERR & (0x01U)) << 2U) | ((_m->STR_COM_INT & (0x01U)) << 3U) | ((_m->STR_EEP_ERR & (0x01U)) << 4U) | ((_m->STR_CTRL_ERR & (0x01U)) << 5U) | ((_m->STR_ANG_SENS & (0x01U)) << 6U) | ((_m->STR_TRQ_SENS & (0x01U)) << 7U) );
  _d[4] |= (uint8_t) ( (_m->STR_OT_SEV & (0x01U)) | ((_m->STR_OT_NORM & (0x01U)) << 1U) | ((_m->STR_UV_ERR & (0x01U)) << 2U) | ((_m->STR_OV_ERR & (0x01U)) << 3U) | ((_m->STR_CAN_TO & (0x01U)) << 4U) | ((_m->RC_FRM_ERR & (0x01U)) << 5U) | ((_m->RC_FRM_LST & (0x01U)) << 6U) | ((_m->RC_FRM_FS & (0x01U)) << 7U) );
  _d[5] |= (uint8_t) ( (_m->RC_EMG_ACT & (0x01U)) | ((_m->RC_REM_EMG & (0x01U)) << 1U) | ((_m->RC_COM_ERR & (0x01U)) << 2U) | ((_m->MCU_ALM_ACT & (0x01U)) << 3U) | ((_m->MCU_COM_ERR & (0x01U)) << 4U) | ((_m->SAFE_VCU_COM_FLT & (0x01U)) << 5U) | ((_m->SAFE_VCU_EMG_ACT & (0x01U)) << 6U) | ((_m->JK_UNIT_OVER_VOLTAGE & (0x01U)) << 7U) );
  _d[6] |= (uint8_t) ( (_m->JK_UNIT_UNDER_VOLTAGE & (0x01U)) | ((_m->JK_TOTAL_VOLTAGE_OVER_VOLTAGE & (0x01U)) << 1U) | ((_m->JK_TOTAL_VOLTAGE_UNDER_VOLTAGE & (0x01U)) << 2U) | ((_m->JK_LARGE_PRESSURE_DIFF_OF_MON & (0x01U)) << 3U) | ((_m->JK_DISCHARGE_OVER_CURRENT & (0x01U)) << 4U) | ((_m->JK_CHARGE_OVER_CURRENT & (0x01U)) << 5U) | ((_m->JK_TEMPERATURE_IS_TOO_HIGH & (0x01U)) << 6U) | ((_m->JK_TEMPERATURE_IS_TOO_LOW & (0x01U)) << 7U) );
  _d[7] |= (uint8_t) ( (_m->JK_EXCESSIVE_TEMPERATURE_DIFF & (0x01U)) | ((_m->JK_SOC_TOO_LOW & (0x01U)) << 1U) | ((_m->JK_INSULATION_IS_TOO_LOW & (0x01U)) << 2U) | ((_m->JK_HIGH_VOLTAGE_INTERLOCK_FAULT & (0x01U)) << 3U) | ((_m->JK_EXTERNAL_COMMUNICATION_FAIL & (0x01U)) << 4U) | ((_m->JK_INTERNAL_COMMUNICATION_FAIL & (0x01U)) << 5U) | ((_m->ASPS_HSD_OC & (0x01U)) << 6U) | ((_m->ASPS_HSD_OL & (0x01U)) << 7U) );

  *_len = (uint8_t) DTC_ERROR_STATUS_DLC;
  *_ide = (uint8_t) DTC_ERROR_STATUS_IDE;
  return DTC_ERROR_STATUS_CANID;
}

#endif // PC_VCU_USE_CANSTRUCT

uint32_t Unpack_DTC_ERROR_STATUS_1_pc_vcu(DTC_ERROR_STATUS_1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ASPS_HSD_ERR = (uint8_t) ( (_d[0] & (0x01U)) );
  _m->GPIO_PC_IGNITION_ERR = (uint8_t) ( ((_d[0] >> 1U) & (0x01U)) );
  _m->BMS_COMM_ERR = (uint8_t) ( ((_d[0] >> 2U) & (0x01U)) );
  _m->BBW_COMM_ERR = (uint8_t) ( ((_d[0] >> 3U) & (0x01U)) );
  _m->BBW_UV_ERR = (uint8_t) ( ((_d[0] >> 4U) & (0x01U)) );
  _m->BBW_L_MOT_CONN = (uint8_t) ( ((_d[0] >> 5U) & (0x01U)) );
  _m->BBW_R_MOT_CONN = (uint8_t) ( ((_d[0] >> 6U) & (0x01U)) );
  _m->BBW_L_MOT_OC = (uint8_t) ( ((_d[0] >> 7U) & (0x01U)) );
  _m->BBW_R_MOT_OC = (uint8_t) ( (_d[1] & (0x01U)) );
  _m->BBW_TEMP_ERR = (uint8_t) ( ((_d[1] >> 1U) & (0x01U)) );
  _m->RB_BOARD_TEMP_WARN = (uint8_t) ( ((_d[1] >> 2U) & (0x01U)) );
  _m->RB_BOARD_TEMP_ERR = (uint8_t) ( ((_d[1] >> 3U) & (0x01U)) );
  _m->RB_COMM_TIMEOUT = (uint8_t) ( ((_d[1] >> 4U) & (0x01U)) );
  _m->RB_IC_COMM_WARN = (uint8_t) ( ((_d[1] >> 5U) & (0x01U)) );
  _m->RB_LSD_OVERTEMP_WARN = (uint8_t) ( ((_d[1] >> 6U) & (0x01U)) );
  _m->RB_IC_UNDERVOLT_WARN = (uint8_t) ( ((_d[1] >> 7U) & (0x01U)) );
  _m->GPIO_CHARGE_FLAP_ERR = (uint8_t) ( (_d[2] & (0x01U)) );
  _m->GPIO_EMG_BTN_ERR = (uint8_t) ( ((_d[2] >> 1U) & (0x01U)) );

#ifdef PC_VCU_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DTC_ERROR_STATUS_1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DTC_ERROR_STATUS_1_pc_vcu(&_m->mon1, DTC_ERROR_STATUS_1_CANID);
#endif // PC_VCU_USE_DIAG_MONITORS

  return DTC_ERROR_STATUS_1_CANID;
}

#ifdef PC_VCU_USE_CANSTRUCT

uint32_t Pack_DTC_ERROR_STATUS_1_pc_vcu(DTC_ERROR_STATUS_1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(DTC_ERROR_STATUS_1_DLC); cframe->Data[i++] = PC_VCU_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->ASPS_HSD_ERR & (0x01U)) | ((_m->GPIO_PC_IGNITION_ERR & (0x01U)) << 1U) | ((_m->BMS_COMM_ERR & (0x01U)) << 2U) | ((_m->BBW_COMM_ERR & (0x01U)) << 3U) | ((_m->BBW_UV_ERR & (0x01U)) << 4U) | ((_m->BBW_L_MOT_CONN & (0x01U)) << 5U) | ((_m->BBW_R_MOT_CONN & (0x01U)) << 6U) | ((_m->BBW_L_MOT_OC & (0x01U)) << 7U) );
  cframe->Data[1] |= (uint8_t) ( (_m->BBW_R_MOT_OC & (0x01U)) | ((_m->BBW_TEMP_ERR & (0x01U)) << 1U) | ((_m->RB_BOARD_TEMP_WARN & (0x01U)) << 2U) | ((_m->RB_BOARD_TEMP_ERR & (0x01U)) << 3U) | ((_m->RB_COMM_TIMEOUT & (0x01U)) << 4U) | ((_m->RB_IC_COMM_WARN & (0x01U)) << 5U) | ((_m->RB_LSD_OVERTEMP_WARN & (0x01U)) << 6U) | ((_m->RB_IC_UNDERVOLT_WARN & (0x01U)) << 7U) );
  cframe->Data[2] |= (uint8_t) ( (_m->GPIO_CHARGE_FLAP_ERR & (0x01U)) | ((_m->GPIO_EMG_BTN_ERR & (0x01U)) << 1U) );

  cframe->MsgId = (uint32_t) DTC_ERROR_STATUS_1_CANID;
  cframe->DLC = (uint8_t) DTC_ERROR_STATUS_1_DLC;
  cframe->IDE = (uint8_t) DTC_ERROR_STATUS_1_IDE;
  return DTC_ERROR_STATUS_1_CANID;
}

#else

uint32_t Pack_DTC_ERROR_STATUS_1_pc_vcu(DTC_ERROR_STATUS_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < PC_VCU_VALIDATE_DLC(DTC_ERROR_STATUS_1_DLC); _d[i++] = PC_VCU_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->ASPS_HSD_ERR & (0x01U)) | ((_m->GPIO_PC_IGNITION_ERR & (0x01U)) << 1U) | ((_m->BMS_COMM_ERR & (0x01U)) << 2U) | ((_m->BBW_COMM_ERR & (0x01U)) << 3U) | ((_m->BBW_UV_ERR & (0x01U)) << 4U) | ((_m->BBW_L_MOT_CONN & (0x01U)) << 5U) | ((_m->BBW_R_MOT_CONN & (0x01U)) << 6U) | ((_m->BBW_L_MOT_OC & (0x01U)) << 7U) );
  _d[1] |= (uint8_t) ( (_m->BBW_R_MOT_OC & (0x01U)) | ((_m->BBW_TEMP_ERR & (0x01U)) << 1U) | ((_m->RB_BOARD_TEMP_WARN & (0x01U)) << 2U) | ((_m->RB_BOARD_TEMP_ERR & (0x01U)) << 3U) | ((_m->RB_COMM_TIMEOUT & (0x01U)) << 4U) | ((_m->RB_IC_COMM_WARN & (0x01U)) << 5U) | ((_m->RB_LSD_OVERTEMP_WARN & (0x01U)) << 6U) | ((_m->RB_IC_UNDERVOLT_WARN & (0x01U)) << 7U) );
  _d[2] |= (uint8_t) ( (_m->GPIO_CHARGE_FLAP_ERR & (0x01U)) | ((_m->GPIO_EMG_BTN_ERR & (0x01U)) << 1U) );

  *_len = (uint8_t) DTC_ERROR_STATUS_1_DLC;
  *_ide = (uint8_t) DTC_ERROR_STATUS_1_IDE;
  return DTC_ERROR_STATUS_1_CANID;
}

#endif // PC_VCU_USE_CANSTRUCT

