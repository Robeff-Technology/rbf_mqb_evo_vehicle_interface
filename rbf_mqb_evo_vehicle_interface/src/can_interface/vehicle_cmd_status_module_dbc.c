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

uint32_t Unpack_SPEED_CONTROL_MSG_vehicle_cmd_status_module_dbc(SPEED_CONTROL_MSG_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->SC_TireAngleRad_Cmd_ro = (int16_t) __ext_sig__(( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) ), 16);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->SC_TireAngleRad_Cmd_phys = (sigfloat_t)(VEHICLE_CMD_STATUS_MODULE_DBC_SC_TireAngleRad_Cmd_ro_fromS(_m->SC_TireAngleRad_Cmd_ro));
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _m->SC_VehicleSpeedMS_Cmd_ro = (int16_t) __ext_sig__(( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) ), 16);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->SC_VehicleSpeedMS_Cmd_phys = (sigfloat_t)(VEHICLE_CMD_STATUS_MODULE_DBC_SC_VehicleSpeedMS_Cmd_ro_fromS(_m->SC_VehicleSpeedMS_Cmd_ro));
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _m->SC_Enable = (uint8_t) ( (_d[4] & (0x01U)) );
  _m->SC_Emergency = (uint8_t) ( ((_d[4] >> 1U) & (0x01U)) );
  _m->SC_Reserved_1 = (uint8_t) ( ((_d[4] >> 2U) & (0x01U)) );
  _m->SC_Gear = (uint8_t) ( ((_d[4] >> 3U) & (0x1FU)) );
  _m->SC_Reserved_2 = (uint8_t) ( (_d[5] & (0x01U)) );
  _m->SC_Reserved_3 = (uint8_t) ( ((_d[5] >> 1U) & (0x01U)) );
  _m->SC_Reserved_4 = (uint8_t) ( ((_d[5] >> 2U) & (0x01U)) );
  _m->SC_Reserved_5 = (uint8_t) ( ((_d[5] >> 3U) & (0x01U)) );
  _m->SC_Reserved = (uint8_t) ( ((_d[5] >> 4U) & (0x0FU)) );
  _m->SC_AliveCounter = (uint8_t) ( (_d[6] & (0xFFU)) );
  _m->SC_Crc8 = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SPEED_CONTROL_MSG_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SPEED_CONTROL_MSG_vehicle_cmd_status_module_dbc(&_m->mon1, SPEED_CONTROL_MSG_CANID);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  return SPEED_CONTROL_MSG_CANID;
}

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Pack_SPEED_CONTROL_MSG_vehicle_cmd_status_module_dbc(SPEED_CONTROL_MSG_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(SPEED_CONTROL_MSG_DLC); cframe->Data[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->SC_TireAngleRad_Cmd_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_SC_TireAngleRad_Cmd_ro_toS(_m->SC_TireAngleRad_Cmd_phys);
  _m->SC_VehicleSpeedMS_Cmd_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_SC_VehicleSpeedMS_Cmd_ro_toS(_m->SC_VehicleSpeedMS_Cmd_phys);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->SC_TireAngleRad_Cmd_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->SC_TireAngleRad_Cmd_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->SC_VehicleSpeedMS_Cmd_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->SC_VehicleSpeedMS_Cmd_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->SC_Enable & (0x01U)) | ((_m->SC_Emergency & (0x01U)) << 1U) | ((_m->SC_Reserved_1 & (0x01U)) << 2U) | ((_m->SC_Gear & (0x1FU)) << 3U) );
  cframe->Data[5] |= (uint8_t) ( (_m->SC_Reserved_2 & (0x01U)) | ((_m->SC_Reserved_3 & (0x01U)) << 1U) | ((_m->SC_Reserved_4 & (0x01U)) << 2U) | ((_m->SC_Reserved_5 & (0x01U)) << 3U) | ((_m->SC_Reserved & (0x0FU)) << 4U) );
  cframe->Data[6] |= (uint8_t) ( (_m->SC_AliveCounter & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->SC_Crc8 & (0xFFU)) );

  cframe->MsgId = (uint32_t) SPEED_CONTROL_MSG_CANID;
  cframe->DLC = (uint8_t) SPEED_CONTROL_MSG_DLC;
  cframe->IDE = (uint8_t) SPEED_CONTROL_MSG_IDE;
  return SPEED_CONTROL_MSG_CANID;
}

#else

uint32_t Pack_SPEED_CONTROL_MSG_vehicle_cmd_status_module_dbc(SPEED_CONTROL_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(SPEED_CONTROL_MSG_DLC); _d[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->SC_TireAngleRad_Cmd_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_SC_TireAngleRad_Cmd_ro_toS(_m->SC_TireAngleRad_Cmd_phys);
  _m->SC_VehicleSpeedMS_Cmd_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_SC_VehicleSpeedMS_Cmd_ro_toS(_m->SC_VehicleSpeedMS_Cmd_phys);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->SC_TireAngleRad_Cmd_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->SC_TireAngleRad_Cmd_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->SC_VehicleSpeedMS_Cmd_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->SC_VehicleSpeedMS_Cmd_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->SC_Enable & (0x01U)) | ((_m->SC_Emergency & (0x01U)) << 1U) | ((_m->SC_Reserved_1 & (0x01U)) << 2U) | ((_m->SC_Gear & (0x1FU)) << 3U) );
  _d[5] |= (uint8_t) ( (_m->SC_Reserved_2 & (0x01U)) | ((_m->SC_Reserved_3 & (0x01U)) << 1U) | ((_m->SC_Reserved_4 & (0x01U)) << 2U) | ((_m->SC_Reserved_5 & (0x01U)) << 3U) | ((_m->SC_Reserved & (0x0FU)) << 4U) );
  _d[6] |= (uint8_t) ( (_m->SC_AliveCounter & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->SC_Crc8 & (0xFFU)) );

  *_len = (uint8_t) SPEED_CONTROL_MSG_DLC;
  *_ide = (uint8_t) SPEED_CONTROL_MSG_IDE;
  return SPEED_CONTROL_MSG_CANID;
}

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_CLEAR_INTERVENTION_CMD_vehicle_cmd_status_module_dbc(CLEAR_INTERVENTION_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ClearInterventionCmd = (uint8_t) ( (_d[0] & (0xFFU)) );

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CLEAR_INTERVENTION_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CLEAR_INTERVENTION_CMD_vehicle_cmd_status_module_dbc(&_m->mon1, CLEAR_INTERVENTION_CMD_CANID);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  return CLEAR_INTERVENTION_CMD_CANID;
}

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Pack_CLEAR_INTERVENTION_CMD_vehicle_cmd_status_module_dbc(CLEAR_INTERVENTION_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(CLEAR_INTERVENTION_CMD_DLC); cframe->Data[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->ClearInterventionCmd & (0xFFU)) );

  cframe->MsgId = (uint32_t) CLEAR_INTERVENTION_CMD_CANID;
  cframe->DLC = (uint8_t) CLEAR_INTERVENTION_CMD_DLC;
  cframe->IDE = (uint8_t) CLEAR_INTERVENTION_CMD_IDE;
  return CLEAR_INTERVENTION_CMD_CANID;
}

#else

uint32_t Pack_CLEAR_INTERVENTION_CMD_vehicle_cmd_status_module_dbc(CLEAR_INTERVENTION_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(CLEAR_INTERVENTION_CMD_DLC); _d[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->ClearInterventionCmd & (0xFFU)) );

  *_len = (uint8_t) CLEAR_INTERVENTION_CMD_DLC;
  *_ide = (uint8_t) CLEAR_INTERVENTION_CMD_IDE;
  return CLEAR_INTERVENTION_CMD_CANID;
}

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_DIRECT_CONTROL_MSG_vehicle_cmd_status_module_dbc(DIRECT_CONTROL_MSG_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->DC_Throttle_ro = (int16_t) __ext_sig__(( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) ), 16);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->DC_Throttle_phys = (sigfloat_t)(VEHICLE_CMD_STATUS_MODULE_DBC_DC_Throttle_ro_fromS(_m->DC_Throttle_ro));
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _m->DC_Steering_ro = (int16_t) __ext_sig__(( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) ), 16);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->DC_Steering_phys = (sigfloat_t)(VEHICLE_CMD_STATUS_MODULE_DBC_DC_Steering_ro_fromS(_m->DC_Steering_ro));
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _m->DC_Gear = (uint8_t) ( (_d[4] & (0x03U)) );
  _m->DC_Handbrake = (uint8_t) ( ((_d[4] >> 2U) & (0x01U)) );
  _m->DC_Emergency = (uint8_t) ( ((_d[4] >> 3U) & (0x01U)) );
  _m->DC_Enable = (uint8_t) ( ((_d[4] >> 4U) & (0x01U)) );
  _m->DC_AliveCounter = (uint8_t) ( (_d[6] & (0xFFU)) );
  _m->DC_Crc8 = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DIRECT_CONTROL_MSG_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DIRECT_CONTROL_MSG_vehicle_cmd_status_module_dbc(&_m->mon1, DIRECT_CONTROL_MSG_CANID);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  return DIRECT_CONTROL_MSG_CANID;
}

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Pack_DIRECT_CONTROL_MSG_vehicle_cmd_status_module_dbc(DIRECT_CONTROL_MSG_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(DIRECT_CONTROL_MSG_DLC); cframe->Data[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->DC_Throttle_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_DC_Throttle_ro_toS(_m->DC_Throttle_phys);
  _m->DC_Steering_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_DC_Steering_ro_toS(_m->DC_Steering_phys);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->DC_Throttle_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->DC_Throttle_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->DC_Steering_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->DC_Steering_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->DC_Gear & (0x03U)) | ((_m->DC_Handbrake & (0x01U)) << 2U) | ((_m->DC_Emergency & (0x01U)) << 3U) | ((_m->DC_Enable & (0x01U)) << 4U) );
  cframe->Data[6] |= (uint8_t) ( (_m->DC_AliveCounter & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->DC_Crc8 & (0xFFU)) );

  cframe->MsgId = (uint32_t) DIRECT_CONTROL_MSG_CANID;
  cframe->DLC = (uint8_t) DIRECT_CONTROL_MSG_DLC;
  cframe->IDE = (uint8_t) DIRECT_CONTROL_MSG_IDE;
  return DIRECT_CONTROL_MSG_CANID;
}

#else

uint32_t Pack_DIRECT_CONTROL_MSG_vehicle_cmd_status_module_dbc(DIRECT_CONTROL_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(DIRECT_CONTROL_MSG_DLC); _d[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->DC_Throttle_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_DC_Throttle_ro_toS(_m->DC_Throttle_phys);
  _m->DC_Steering_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_DC_Steering_ro_toS(_m->DC_Steering_phys);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->DC_Throttle_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->DC_Throttle_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->DC_Steering_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->DC_Steering_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->DC_Gear & (0x03U)) | ((_m->DC_Handbrake & (0x01U)) << 2U) | ((_m->DC_Emergency & (0x01U)) << 3U) | ((_m->DC_Enable & (0x01U)) << 4U) );
  _d[6] |= (uint8_t) ( (_m->DC_AliveCounter & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->DC_Crc8 & (0xFFU)) );

  *_len = (uint8_t) DIRECT_CONTROL_MSG_DLC;
  *_ide = (uint8_t) DIRECT_CONTROL_MSG_IDE;
  return DIRECT_CONTROL_MSG_CANID;
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
  _m->DcCommPeriod = (uint16_t) ( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );
  _m->ScCommPeriod = (uint16_t) ( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) );
  _m->ErrCommDirectControl = (uint8_t) ( (_d[4] & (0x01U)) );
  _m->ErrCommSpeedControl = (uint8_t) ( ((_d[4] >> 1U) & (0x01U)) );

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

  cframe->Data[0] |= (uint8_t) ( (_m->DcCommPeriod & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->DcCommPeriod >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->ScCommPeriod & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->ScCommPeriod >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->ErrCommDirectControl & (0x01U)) | ((_m->ErrCommSpeedControl & (0x01U)) << 1U) );

  cframe->MsgId = (uint32_t) VCU_STAT_COMM_STATUS_CANID;
  cframe->DLC = (uint8_t) VCU_STAT_COMM_STATUS_DLC;
  cframe->IDE = (uint8_t) VCU_STAT_COMM_STATUS_IDE;
  return VCU_STAT_COMM_STATUS_CANID;
}

#else

uint32_t Pack_VCU_STAT_COMM_STATUS_vehicle_cmd_status_module_dbc(VCU_STAT_COMM_STATUS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_STAT_COMM_STATUS_DLC); _d[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->DcCommPeriod & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->DcCommPeriod >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->ScCommPeriod & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->ScCommPeriod >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->ErrCommDirectControl & (0x01U)) | ((_m->ErrCommSpeedControl & (0x01U)) << 1U) );

  *_len = (uint8_t) VCU_STAT_COMM_STATUS_DLC;
  *_ide = (uint8_t) VCU_STAT_COMM_STATUS_IDE;
  return VCU_STAT_COMM_STATUS_CANID;
}

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_DYNAMICS_SI_vehicle_cmd_status_module_dbc(VCU_STAT_DYNAMICS_SI_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->LateralAccelMS2_ro = (int16_t) __ext_sig__(( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) ), 16);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->LateralAccelMS2_phys = (sigfloat_t)(VEHICLE_CMD_STATUS_MODULE_DBC_LateralAccelMS2_ro_fromS(_m->LateralAccelMS2_ro));
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _m->LongitudinalAccelMS2_ro = (int16_t) __ext_sig__(( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) ), 16);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->LongitudinalAccelMS2_phys = (sigfloat_t)(VEHICLE_CMD_STATUS_MODULE_DBC_LongitudinalAccelMS2_ro_fromS(_m->LongitudinalAccelMS2_ro));
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _m->YawRateDegS_ro = (int16_t) __ext_sig__(( ((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) ), 16);
#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->YawRateDegS_phys = (sigfloat_t)(VEHICLE_CMD_STATUS_MODULE_DBC_YawRateDegS_ro_fromS(_m->YawRateDegS_ro));
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VCU_STAT_DYNAMICS_SI_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VCU_STAT_DYNAMICS_SI_vehicle_cmd_status_module_dbc(&_m->mon1, VCU_STAT_DYNAMICS_SI_CANID);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  return VCU_STAT_DYNAMICS_SI_CANID;
}

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Pack_VCU_STAT_DYNAMICS_SI_vehicle_cmd_status_module_dbc(VCU_STAT_DYNAMICS_SI_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_STAT_DYNAMICS_SI_DLC); cframe->Data[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->LateralAccelMS2_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_LateralAccelMS2_ro_toS(_m->LateralAccelMS2_phys);
  _m->LongitudinalAccelMS2_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_LongitudinalAccelMS2_ro_toS(_m->LongitudinalAccelMS2_phys);
  _m->YawRateDegS_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_YawRateDegS_ro_toS(_m->YawRateDegS_phys);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->LateralAccelMS2_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->LateralAccelMS2_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->LongitudinalAccelMS2_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->LongitudinalAccelMS2_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->YawRateDegS_ro & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->YawRateDegS_ro >> 8U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) VCU_STAT_DYNAMICS_SI_CANID;
  cframe->DLC = (uint8_t) VCU_STAT_DYNAMICS_SI_DLC;
  cframe->IDE = (uint8_t) VCU_STAT_DYNAMICS_SI_IDE;
  return VCU_STAT_DYNAMICS_SI_CANID;
}

#else

uint32_t Pack_VCU_STAT_DYNAMICS_SI_vehicle_cmd_status_module_dbc(VCU_STAT_DYNAMICS_SI_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_STAT_DYNAMICS_SI_DLC); _d[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT
  _m->LateralAccelMS2_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_LateralAccelMS2_ro_toS(_m->LateralAccelMS2_phys);
  _m->LongitudinalAccelMS2_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_LongitudinalAccelMS2_ro_toS(_m->LongitudinalAccelMS2_phys);
  _m->YawRateDegS_ro = (int16_t) VEHICLE_CMD_STATUS_MODULE_DBC_YawRateDegS_ro_toS(_m->YawRateDegS_phys);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->LateralAccelMS2_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->LateralAccelMS2_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->LongitudinalAccelMS2_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->LongitudinalAccelMS2_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->YawRateDegS_ro & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->YawRateDegS_ro >> 8U) & (0xFFU)) );

  *_len = (uint8_t) VCU_STAT_DYNAMICS_SI_DLC;
  *_ide = (uint8_t) VCU_STAT_DYNAMICS_SI_IDE;
  return VCU_STAT_DYNAMICS_SI_CANID;
}

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_QUEUE_DROPS_vehicle_cmd_status_module_dbc(VCU_STAT_QUEUE_DROPS_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->CarQueueDropCount = (uint32_t) ( ((_d[3] & (0xFFU)) << 24U) | ((_d[2] & (0xFFU)) << 16U) | ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );
  _m->VehicleInterfaceQueueDropCount = (uint32_t) ( ((_d[7] & (0xFFU)) << 24U) | ((_d[6] & (0xFFU)) << 16U) | ((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) );

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VCU_STAT_QUEUE_DROPS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VCU_STAT_QUEUE_DROPS_vehicle_cmd_status_module_dbc(&_m->mon1, VCU_STAT_QUEUE_DROPS_CANID);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  return VCU_STAT_QUEUE_DROPS_CANID;
}

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Pack_VCU_STAT_QUEUE_DROPS_vehicle_cmd_status_module_dbc(VCU_STAT_QUEUE_DROPS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_STAT_QUEUE_DROPS_DLC); cframe->Data[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->CarQueueDropCount & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->CarQueueDropCount >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->CarQueueDropCount >> 16U) & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->CarQueueDropCount >> 24U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->VehicleInterfaceQueueDropCount & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->VehicleInterfaceQueueDropCount >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( ((_m->VehicleInterfaceQueueDropCount >> 16U) & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->VehicleInterfaceQueueDropCount >> 24U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) VCU_STAT_QUEUE_DROPS_CANID;
  cframe->DLC = (uint8_t) VCU_STAT_QUEUE_DROPS_DLC;
  cframe->IDE = (uint8_t) VCU_STAT_QUEUE_DROPS_IDE;
  return VCU_STAT_QUEUE_DROPS_CANID;
}

#else

uint32_t Pack_VCU_STAT_QUEUE_DROPS_vehicle_cmd_status_module_dbc(VCU_STAT_QUEUE_DROPS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_STAT_QUEUE_DROPS_DLC); _d[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->CarQueueDropCount & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->CarQueueDropCount >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( ((_m->CarQueueDropCount >> 16U) & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->CarQueueDropCount >> 24U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->VehicleInterfaceQueueDropCount & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->VehicleInterfaceQueueDropCount >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( ((_m->VehicleInterfaceQueueDropCount >> 16U) & (0xFFU)) );
  _d[7] |= (uint8_t) ( ((_m->VehicleInterfaceQueueDropCount >> 24U) & (0xFFU)) );

  *_len = (uint8_t) VCU_STAT_QUEUE_DROPS_DLC;
  *_ide = (uint8_t) VCU_STAT_QUEUE_DROPS_IDE;
  return VCU_STAT_QUEUE_DROPS_CANID;
}

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Unpack_VCU_STAT_TX_DROPS_vehicle_cmd_status_module_dbc(VCU_STAT_TX_DROPS_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->GatewayTxDropCount = (uint16_t) ( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );
  _m->BrakeBoosterTxDropCount = (uint16_t) ( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) );
  _m->AbsTxDropCount = (uint16_t) ( ((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) );
  _m->EpasTxDropCount = (uint16_t) ( ((_d[7] & (0xFFU)) << 8U) | (_d[6] & (0xFFU)) );

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VCU_STAT_TX_DROPS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VCU_STAT_TX_DROPS_vehicle_cmd_status_module_dbc(&_m->mon1, VCU_STAT_TX_DROPS_CANID);
#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_DIAG_MONITORS

  return VCU_STAT_TX_DROPS_CANID;
}

#ifdef VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

uint32_t Pack_VCU_STAT_TX_DROPS_vehicle_cmd_status_module_dbc(VCU_STAT_TX_DROPS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_STAT_TX_DROPS_DLC); cframe->Data[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->GatewayTxDropCount & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->GatewayTxDropCount >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->BrakeBoosterTxDropCount & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->BrakeBoosterTxDropCount >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->AbsTxDropCount & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->AbsTxDropCount >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->EpasTxDropCount & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->EpasTxDropCount >> 8U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) VCU_STAT_TX_DROPS_CANID;
  cframe->DLC = (uint8_t) VCU_STAT_TX_DROPS_DLC;
  cframe->IDE = (uint8_t) VCU_STAT_TX_DROPS_IDE;
  return VCU_STAT_TX_DROPS_CANID;
}

#else

uint32_t Pack_VCU_STAT_TX_DROPS_vehicle_cmd_status_module_dbc(VCU_STAT_TX_DROPS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VEHICLE_CMD_STATUS_MODULE_DBC_VALIDATE_DLC(VCU_STAT_TX_DROPS_DLC); _d[i++] = VEHICLE_CMD_STATUS_MODULE_DBC_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->GatewayTxDropCount & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->GatewayTxDropCount >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->BrakeBoosterTxDropCount & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->BrakeBoosterTxDropCount >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->AbsTxDropCount & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->AbsTxDropCount >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->EpasTxDropCount & (0xFFU)) );
  _d[7] |= (uint8_t) ( ((_m->EpasTxDropCount >> 8U) & (0xFFU)) );

  *_len = (uint8_t) VCU_STAT_TX_DROPS_DLC;
  *_ide = (uint8_t) VCU_STAT_TX_DROPS_IDE;
  return VCU_STAT_TX_DROPS_CANID;
}

#endif // VEHICLE_CMD_STATUS_MODULE_DBC_USE_CANSTRUCT

