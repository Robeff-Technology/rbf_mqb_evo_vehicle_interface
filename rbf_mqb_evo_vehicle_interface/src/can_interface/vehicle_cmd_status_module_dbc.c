// Generator version : v3.1
// DBC filename      : vehicle_cmd_status_dbc.dbc
#include "vehicle_cmd_status_module_dbc.h"


// DBC file version
#if (VER_VEHICLE_CMD_STATUS_MODULE_DBC_MAJ != (0U)) || (VER_VEHICLE_CMD_STATUS_MODULE_DBC_MIN != (0U))
#error The VEHICLE_CMD_STATUS_MODULE_DBC dbc source files have different versions
#endif

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS
// Function prototypes to be called each time CAN frame is unpacked
// FMon function may detect RC, CRC or DLC violation
#include "vehicle_cmd_status_module_dbc-fmon.h"

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

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

uint32_t Unpack_VCU_CTRL_CMD_SI_vehicle_cmd_status_module_dbc(VCU_CTRL_CMD_SI_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->TireAngleRad_Cmd_ro = (int16_t) __ext_sig__(( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) ), 16);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->TireAngleRad_Cmd_phys = (sigfloat_t)(VEHICLE_CMD_STATUS_MODULE_DBC_TireAngleRad_Cmd_ro_fromS(_m->TireAngleRad_Cmd_ro));
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _m->VehicleSpeedMS_Cmd_ro = (int16_t) __ext_sig__(( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) ), 16);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->VehicleSpeedMS_Cmd_phys = (sigfloat_t)(VEHICLE_CMD_STATUS_MODULE_DBC_VehicleSpeedMS_Cmd_ro_fromS(_m->VehicleSpeedMS_Cmd_ro));
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _m->AutonomousEnable = (uint8_t) ( (_d[4] & (0x01U)) );
  _m->EmergencyActive = (uint8_t) ( ((_d[4] >> 1U) & (0x01U)) );
  _m->Reserved_1 = (uint8_t) ( ((_d[4] >> 2U) & (0x01U)) );
  _m->GearReq = (uint8_t) ( ((_d[4] >> 3U) & (0x1FU)) );
  _m->Reserved_2 = (uint8_t) ( (_d[5] & (0x01U)) );
  _m->Reserved_3 = (uint8_t) ( ((_d[5] >> 1U) & (0x01U)) );
  _m->Reserved_4 = (uint8_t) ( ((_d[5] >> 2U) & (0x01U)) );
  _m->Reserved_5 = (uint8_t) ( ((_d[5] >> 3U) & (0x01U)) );
  _m->Reserved = (uint8_t) ( ((_d[5] >> 4U) & (0x0FU)) );
  _m->AliveCounter = (uint8_t) ( (_d[6] & (0xFFU)) );
  _m->CRC8 = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VCU_CTRL_CMD_SI_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VCU_CTRL_CMD_SI_vehicle_cmd_status_module_dbc(&_m->mon1, VCU_CTRL_CMD_SI_CANID);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  return VCU_CTRL_CMD_SI_CANID;
}

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Pack_VCU_CTRL_CMD_SI_vehicle_cmd_status_module_dbc(VCU_CTRL_CMD_SI_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_CTRL_CMD_SI_DLC); cframe->Data[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->TireAngleRad_Cmd_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_TireAngleRad_Cmd_ro_toS(_m->TireAngleRad_Cmd_phys);
  _m->VehicleSpeedMS_Cmd_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_VehicleSpeedMS_Cmd_ro_toS(_m->VehicleSpeedMS_Cmd_phys);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->TireAngleRad_Cmd_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->TireAngleRad_Cmd_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->VehicleSpeedMS_Cmd_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->VehicleSpeedMS_Cmd_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->AutonomousEnable & (0x01U)) | ((_m->EmergencyActive & (0x01U)) << 1U) | ((_m->Reserved_1 & (0x01U)) << 2U) | ((_m->GearReq & (0x1FU)) << 3U) );
  cframe->Data[5] |= (uint8_t) ( (_m->Reserved_2 & (0x01U)) | ((_m->Reserved_3 & (0x01U)) << 1U) | ((_m->Reserved_4 & (0x01U)) << 2U) | ((_m->Reserved_5 & (0x01U)) << 3U) | ((_m->Reserved & (0x0FU)) << 4U) );
  cframe->Data[6] |= (uint8_t) ( (_m->AliveCounter & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->CRC8 & (0xFFU)) );

  cframe->MsgId = (uint32_t) VCU_CTRL_CMD_SI_CANID;
  cframe->DLC = (uint8_t) VCU_CTRL_CMD_SI_DLC;
  cframe->IDE = (uint8_t) VCU_CTRL_CMD_SI_IDE;
  return VCU_CTRL_CMD_SI_CANID;
}

#else

uint32_t Pack_VCU_CTRL_CMD_SI_vehicle_cmd_status_module_dbc(VCU_CTRL_CMD_SI_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_CTRL_CMD_SI_DLC); _d[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->TireAngleRad_Cmd_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_TireAngleRad_Cmd_ro_toS(_m->TireAngleRad_Cmd_phys);
  _m->VehicleSpeedMS_Cmd_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_VehicleSpeedMS_Cmd_ro_toS(_m->VehicleSpeedMS_Cmd_phys);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->TireAngleRad_Cmd_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->TireAngleRad_Cmd_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->VehicleSpeedMS_Cmd_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->VehicleSpeedMS_Cmd_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->AutonomousEnable & (0x01U)) | ((_m->EmergencyActive & (0x01U)) << 1U) | ((_m->Reserved_1 & (0x01U)) << 2U) | ((_m->GearReq & (0x1FU)) << 3U) );
  _d[5] |= (uint8_t) ( (_m->Reserved_2 & (0x01U)) | ((_m->Reserved_3 & (0x01U)) << 1U) | ((_m->Reserved_4 & (0x01U)) << 2U) | ((_m->Reserved_5 & (0x01U)) << 3U) | ((_m->Reserved & (0x0FU)) << 4U) );
  _d[6] |= (uint8_t) ( (_m->AliveCounter & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->CRC8 & (0xFFU)) );

  *_len = (uint8_t) VCU_CTRL_CMD_SI_DLC;
  *_ide = (uint8_t) VCU_CTRL_CMD_SI_IDE;
  return VCU_CTRL_CMD_SI_CANID;
}

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_REMOTE_CONTROL_MSG_vehicle_cmd_status_module_dbc(REMOTE_CONTROL_MSG_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->RC_Throttle_ro = (int16_t) __ext_sig__(( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) ), 16);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->RC_Throttle_phys = (sigfloat_t)(VEHICLE_CMD_STATUS_MODULE_DBC_RC_Throttle_ro_fromS(_m->RC_Throttle_ro));
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _m->RC_Steering_ro = (int16_t) __ext_sig__(( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) ), 16);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->RC_Steering_phys = (sigfloat_t)(VEHICLE_CMD_STATUS_MODULE_DBC_RC_Steering_ro_fromS(_m->RC_Steering_ro));
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _m->RC_Gear = (uint8_t) ( (_d[4] & (0x03U)) );
  _m->RC_Handbrake = (uint8_t) ( ((_d[4] >> 2U) & (0x01U)) );
  _m->RC_Emergency = (uint8_t) ( ((_d[4] >> 3U) & (0x01U)) );
  _m->RC_Enable = (uint8_t) ( ((_d[4] >> 4U) & (0x01U)) );
  _m->RC_AliveCounter = (uint8_t) ( (_d[6] & (0xFFU)) );
  _m->RC_Crc8 = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < REMOTE_CONTROL_MSG_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_REMOTE_CONTROL_MSG_vehicle_cmd_status_module_dbc(&_m->mon1, REMOTE_CONTROL_MSG_CANID);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  return REMOTE_CONTROL_MSG_CANID;
}

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Pack_REMOTE_CONTROL_MSG_vehicle_cmd_status_module_dbc(REMOTE_CONTROL_MSG_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(REMOTE_CONTROL_MSG_DLC); cframe->Data[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->RC_Throttle_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_RC_Throttle_ro_toS(_m->RC_Throttle_phys);
  _m->RC_Steering_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_RC_Steering_ro_toS(_m->RC_Steering_phys);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->RC_Throttle_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->RC_Throttle_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->RC_Steering_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->RC_Steering_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->RC_Gear & (0x03U)) | ((_m->RC_Handbrake & (0x01U)) << 2U) | ((_m->RC_Emergency & (0x01U)) << 3U) | ((_m->RC_Enable & (0x01U)) << 4U) );
  cframe->Data[6] |= (uint8_t) ( (_m->RC_AliveCounter & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->RC_Crc8 & (0xFFU)) );

  cframe->MsgId = (uint32_t) REMOTE_CONTROL_MSG_CANID;
  cframe->DLC = (uint8_t) REMOTE_CONTROL_MSG_DLC;
  cframe->IDE = (uint8_t) REMOTE_CONTROL_MSG_IDE;
  return REMOTE_CONTROL_MSG_CANID;
}

#else

uint32_t Pack_REMOTE_CONTROL_MSG_vehicle_cmd_status_module_dbc(REMOTE_CONTROL_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(REMOTE_CONTROL_MSG_DLC); _d[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->RC_Throttle_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_RC_Throttle_ro_toS(_m->RC_Throttle_phys);
  _m->RC_Steering_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_RC_Steering_ro_toS(_m->RC_Steering_phys);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->RC_Throttle_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->RC_Throttle_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->RC_Steering_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->RC_Steering_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->RC_Gear & (0x03U)) | ((_m->RC_Handbrake & (0x01U)) << 2U) | ((_m->RC_Emergency & (0x01U)) << 3U) | ((_m->RC_Enable & (0x01U)) << 4U) );
  _d[6] |= (uint8_t) ( (_m->RC_AliveCounter & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->RC_Crc8 & (0xFFU)) );

  *_len = (uint8_t) REMOTE_CONTROL_MSG_DLC;
  *_ide = (uint8_t) REMOTE_CONTROL_MSG_IDE;
  return REMOTE_CONTROL_MSG_CANID;
}

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_SAFE_STAT_ROS2_HEARTBEAT_vehicle_cmd_status_module_dbc(SAFE_STAT_ROS2_HEARTBEAT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ROS_Time_ms = (uint64_t) ( ((uint64_t)(_d[5] & (0xFFU)) << 40U) | ((uint64_t)(_d[4] & (0xFFU)) << 32U) | ((_d[3] & (0xFFU)) << 24U) | ((_d[2] & (0xFFU)) << 16U) | ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );
  _m->AliveCounter = (uint8_t) ( (_d[6] & (0xFFU)) );
  _m->CRC8 = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SAFE_STAT_ROS2_HEARTBEAT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SAFE_STAT_ROS2_HEARTBEAT_vehicle_cmd_status_module_dbc(&_m->mon1, SAFE_STAT_ROS2_HEARTBEAT_CANID);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  return SAFE_STAT_ROS2_HEARTBEAT_CANID;
}

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Pack_SAFE_STAT_ROS2_HEARTBEAT_vehicle_cmd_status_module_dbc(SAFE_STAT_ROS2_HEARTBEAT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(SAFE_STAT_ROS2_HEARTBEAT_DLC); cframe->Data[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

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

uint32_t Pack_SAFE_STAT_ROS2_HEARTBEAT_vehicle_cmd_status_module_dbc(SAFE_STAT_ROS2_HEARTBEAT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(SAFE_STAT_ROS2_HEARTBEAT_DLC); _d[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

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

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_MOTION_SI_vehicle_cmd_status_module_dbc(VCU_STAT_MOTION_SI_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->TireAngleRad_Act_ro = (int16_t) __ext_sig__(( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) ), 16);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->TireAngleRad_Act_phys = (sigfloat_t)(VEHICLE_CMD_STATUS_MODULE_DBC_TireAngleRad_Act_ro_fromS(_m->TireAngleRad_Act_ro));
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _m->VehicleSpeedMS_Act_ro = (int16_t) __ext_sig__(( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) ), 16);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->VehicleSpeedMS_Act_phys = (sigfloat_t)(VEHICLE_CMD_STATUS_MODULE_DBC_VehicleSpeedMS_Act_ro_fromS(_m->VehicleSpeedMS_Act_ro));
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _m->SteerAngleDeg_Act = (int16_t) __ext_sig__(( ((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) ), 16);
  _m->AliveCounter = (uint8_t) ( (_d[6] & (0xFFU)) );
  _m->CRC8 = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VCU_STAT_MOTION_SI_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VCU_STAT_MOTION_SI_vehicle_cmd_status_module_dbc(&_m->mon1, VCU_STAT_MOTION_SI_CANID);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  return VCU_STAT_MOTION_SI_CANID;
}

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Pack_VCU_STAT_MOTION_SI_vehicle_cmd_status_module_dbc(VCU_STAT_MOTION_SI_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_STAT_MOTION_SI_DLC); cframe->Data[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->TireAngleRad_Act_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_TireAngleRad_Act_ro_toS(_m->TireAngleRad_Act_phys);
  _m->VehicleSpeedMS_Act_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_VehicleSpeedMS_Act_ro_toS(_m->VehicleSpeedMS_Act_phys);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

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

uint32_t Pack_VCU_STAT_MOTION_SI_vehicle_cmd_status_module_dbc(VCU_STAT_MOTION_SI_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_STAT_MOTION_SI_DLC); _d[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->TireAngleRad_Act_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_TireAngleRad_Act_ro_toS(_m->TireAngleRad_Act_phys);
  _m->VehicleSpeedMS_Act_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_VehicleSpeedMS_Act_ro_toS(_m->VehicleSpeedMS_Act_phys);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

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

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_VEHICLE_STATE_vehicle_cmd_status_module_dbc(VCU_STAT_VEHICLE_STATE_t* _m, const uint8_t* _d, uint8_t dlc_)
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
  _m->Reserved_2 = (uint8_t) ( (_d[3] & (0xFFU)) );
  _m->Reserved_3 = (uint8_t) ( (_d[4] & (0xFFU)) );
  _m->Reserved_4 = (uint8_t) ( (_d[5] & (0xFFU)) );
  _m->AliveCounter = (uint8_t) ( (_d[6] & (0xFFU)) );
  _m->CRC8 = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VCU_STAT_VEHICLE_STATE_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VCU_STAT_VEHICLE_STATE_vehicle_cmd_status_module_dbc(&_m->mon1, VCU_STAT_VEHICLE_STATE_CANID);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  return VCU_STAT_VEHICLE_STATE_CANID;
}

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Pack_VCU_STAT_VEHICLE_STATE_vehicle_cmd_status_module_dbc(VCU_STAT_VEHICLE_STATE_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_STAT_VEHICLE_STATE_DLC); cframe->Data[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->GearAct & (0x1FU)) | ((_m->Reserved & (0x07U)) << 5U) );
  cframe->Data[1] |= (uint8_t) ( (_m->TurnLeft_Stat & (0x01U)) | ((_m->TurnRight_Stat & (0x01U)) << 1U) | ((_m->Hazard_Stat & (0x01U)) << 2U) | ((_m->Horn_Stat & (0x01U)) << 3U) | ((_m->Reserved_1 & (0x0FU)) << 4U) );
  cframe->Data[2] |= (uint8_t) ( (_m->ControlMode & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->Reserved_2 & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->Reserved_3 & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->Reserved_4 & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->AliveCounter & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->CRC8 & (0xFFU)) );

  cframe->MsgId = (uint32_t) VCU_STAT_VEHICLE_STATE_CANID;
  cframe->DLC = (uint8_t) VCU_STAT_VEHICLE_STATE_DLC;
  cframe->IDE = (uint8_t) VCU_STAT_VEHICLE_STATE_IDE;
  return VCU_STAT_VEHICLE_STATE_CANID;
}

#else

uint32_t Pack_VCU_STAT_VEHICLE_STATE_vehicle_cmd_status_module_dbc(VCU_STAT_VEHICLE_STATE_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_STAT_VEHICLE_STATE_DLC); _d[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->GearAct & (0x1FU)) | ((_m->Reserved & (0x07U)) << 5U) );
  _d[1] |= (uint8_t) ( (_m->TurnLeft_Stat & (0x01U)) | ((_m->TurnRight_Stat & (0x01U)) << 1U) | ((_m->Hazard_Stat & (0x01U)) << 2U) | ((_m->Horn_Stat & (0x01U)) << 3U) | ((_m->Reserved_1 & (0x0FU)) << 4U) );
  _d[2] |= (uint8_t) ( (_m->ControlMode & (0xFFU)) );
  _d[3] |= (uint8_t) ( (_m->Reserved_2 & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->Reserved_3 & (0xFFU)) );
  _d[5] |= (uint8_t) ( (_m->Reserved_4 & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->AliveCounter & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->CRC8 & (0xFFU)) );

  *_len = (uint8_t) VCU_STAT_VEHICLE_STATE_DLC;
  *_ide = (uint8_t) VCU_STAT_VEHICLE_STATE_IDE;
  return VCU_STAT_VEHICLE_STATE_CANID;
}

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_COMM_STATUS_vehicle_cmd_status_module_dbc(VCU_STAT_COMM_STATUS_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->RcCommPeriod = (uint16_t) ( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );
  _m->CmdCommPeriod = (uint16_t) ( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) );
  _m->ErrCommRemoteCtrl = (uint8_t) ( (_d[4] & (0x01U)) );
  _m->ErrCommVcuCtrlCmd = (uint8_t) ( ((_d[4] >> 1U) & (0x01U)) );

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VCU_STAT_COMM_STATUS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VCU_STAT_COMM_STATUS_vehicle_cmd_status_module_dbc(&_m->mon1, VCU_STAT_COMM_STATUS_CANID);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  return VCU_STAT_COMM_STATUS_CANID;
}

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Pack_VCU_STAT_COMM_STATUS_vehicle_cmd_status_module_dbc(VCU_STAT_COMM_STATUS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_STAT_COMM_STATUS_DLC); cframe->Data[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->RcCommPeriod & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->RcCommPeriod >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->CmdCommPeriod & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->CmdCommPeriod >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->ErrCommRemoteCtrl & (0x01U)) | ((_m->ErrCommVcuCtrlCmd & (0x01U)) << 1U) );

  cframe->MsgId = (uint32_t) VCU_STAT_COMM_STATUS_CANID;
  cframe->DLC = (uint8_t) VCU_STAT_COMM_STATUS_DLC;
  cframe->IDE = (uint8_t) VCU_STAT_COMM_STATUS_IDE;
  return VCU_STAT_COMM_STATUS_CANID;
}

#else

uint32_t Pack_VCU_STAT_COMM_STATUS_vehicle_cmd_status_module_dbc(VCU_STAT_COMM_STATUS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_STAT_COMM_STATUS_DLC); _d[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->RcCommPeriod & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->RcCommPeriod >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->CmdCommPeriod & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->CmdCommPeriod >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->ErrCommRemoteCtrl & (0x01U)) | ((_m->ErrCommVcuCtrlCmd & (0x01U)) << 1U) );

  *_len = (uint8_t) VCU_STAT_COMM_STATUS_DLC;
  *_ide = (uint8_t) VCU_STAT_COMM_STATUS_IDE;
  return VCU_STAT_COMM_STATUS_CANID;
}

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

