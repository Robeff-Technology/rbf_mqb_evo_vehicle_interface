// Generator version : v3.1
// DBC filename      : robione_autonomous_pc.dbc
#include "vcu.h"


// DBC file version
#if (VER_VCU_MAJ != (0U)) || (VER_VCU_MIN != (0U))
#error The VCU dbc source files have different versions
#endif

#ifdef VCU_USE_DIAG_MONITORS
// Function prototypes to be called each time CAN frame is unpacked
// FMon function may detect RC, CRC or DLC violation
#include "vcu-fmon.h"

#endif // VCU_USE_DIAG_MONITORS

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

uint32_t Unpack_VEHICLE_INFO_vcu(VEHICLE_INFO_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->vehicle_velocity_ro = (int16_t) __ext_sig__(( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) ), 16);
#ifdef VCU_USE_SIGFLOAT
  _m->vehicle_velocity_phys = (sigfloat_t)(VCU_vehicle_velocity_ro_fromS(_m->vehicle_velocity_ro));
#endif // VCU_USE_SIGFLOAT

  _m->steering_wheel_angle_ro = (int16_t) __ext_sig__(( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) ), 16);
#ifdef VCU_USE_SIGFLOAT
  _m->steering_wheel_angle_phys = (sigfloat_t)(VCU_steering_wheel_angle_ro_fromS(_m->steering_wheel_angle_ro));
#endif // VCU_USE_SIGFLOAT

  _m->steering_wheel_speed_ro = (int16_t) __ext_sig__(( ((_d[5] & (0x03U)) << 8U) | (_d[4] & (0xFFU)) ), 10);
#ifdef VCU_USE_SIGFLOAT
  _m->steering_wheel_speed_phys = (int16_t) VCU_steering_wheel_speed_ro_fromS(_m->steering_wheel_speed_ro);
#endif // VCU_USE_SIGFLOAT

  _m->steering_wheel_torque = (int16_t) __ext_sig__(( ((_d[6] & (0x1FU)) << 6U) | ((_d[5] >> 2U) & (0x3FU)) ), 11);
  _m->steering_tire_angle_ro = (int16_t) __ext_sig__(( ((_d[7] & (0xFFU)) << 3U) | ((_d[6] >> 5U) & (0x07U)) ), 11);
#ifdef VCU_USE_SIGFLOAT
  _m->steering_tire_angle_phys = (sigfloat_t)(VCU_steering_tire_angle_ro_fromS(_m->steering_tire_angle_ro));
#endif // VCU_USE_SIGFLOAT

#ifdef VCU_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEHICLE_INFO_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEHICLE_INFO_vcu(&_m->mon1, VEHICLE_INFO_CANID);
#endif // VCU_USE_DIAG_MONITORS

  return VEHICLE_INFO_CANID;
}

#ifdef VCU_USE_CANSTRUCT

uint32_t Pack_VEHICLE_INFO_vcu(VEHICLE_INFO_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VCU_VALIDATE_DLC(VEHICLE_INFO_DLC); cframe->Data[i++] = VCU_INITIAL_BYTE_VALUE);

#ifdef VCU_USE_SIGFLOAT
  _m->vehicle_velocity_ro = (int16_t) VCU_vehicle_velocity_ro_toS(_m->vehicle_velocity_phys);
  _m->steering_wheel_angle_ro = (int16_t) VCU_steering_wheel_angle_ro_toS(_m->steering_wheel_angle_phys);
  _m->steering_wheel_speed_ro = (int16_t) VCU_steering_wheel_speed_ro_toS(_m->steering_wheel_speed_phys);
  _m->steering_tire_angle_ro = (int16_t) VCU_steering_tire_angle_ro_toS(_m->steering_tire_angle_phys);
#endif // VCU_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->vehicle_velocity_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->vehicle_velocity_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->steering_wheel_angle_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->steering_wheel_angle_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->steering_wheel_speed_ro & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->steering_wheel_speed_ro >> 8U) & (0x03U)) | ((_m->steering_wheel_torque & (0x3FU)) << 2U) );
  cframe->Data[6] |= (uint8_t) ( ((_m->steering_wheel_torque >> 6U) & (0x1FU)) | ((_m->steering_tire_angle_ro & (0x07U)) << 5U) );
  cframe->Data[7] |= (uint8_t) ( ((_m->steering_tire_angle_ro >> 3U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEHICLE_INFO_CANID;
  cframe->DLC = (uint8_t) VEHICLE_INFO_DLC;
  cframe->IDE = (uint8_t) VEHICLE_INFO_IDE;
  return VEHICLE_INFO_CANID;
}

#else

uint32_t Pack_VEHICLE_INFO_vcu(VEHICLE_INFO_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VCU_VALIDATE_DLC(VEHICLE_INFO_DLC); _d[i++] = VCU_INITIAL_BYTE_VALUE);

#ifdef VCU_USE_SIGFLOAT
  _m->vehicle_velocity_ro = (int16_t) VCU_vehicle_velocity_ro_toS(_m->vehicle_velocity_phys);
  _m->steering_wheel_angle_ro = (int16_t) VCU_steering_wheel_angle_ro_toS(_m->steering_wheel_angle_phys);
  _m->steering_wheel_speed_ro = (int16_t) VCU_steering_wheel_speed_ro_toS(_m->steering_wheel_speed_phys);
  _m->steering_tire_angle_ro = (int16_t) VCU_steering_tire_angle_ro_toS(_m->steering_tire_angle_phys);
#endif // VCU_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->vehicle_velocity_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->vehicle_velocity_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->steering_wheel_angle_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->steering_wheel_angle_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->steering_wheel_speed_ro & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->steering_wheel_speed_ro >> 8U) & (0x03U)) | ((_m->steering_wheel_torque & (0x3FU)) << 2U) );
  _d[6] |= (uint8_t) ( ((_m->steering_wheel_torque >> 6U) & (0x1FU)) | ((_m->steering_tire_angle_ro & (0x07U)) << 5U) );
  _d[7] |= (uint8_t) ( ((_m->steering_tire_angle_ro >> 3U) & (0xFFU)) );

  *_len = (uint8_t) VEHICLE_INFO_DLC;
  *_ide = (uint8_t) VEHICLE_INFO_IDE;
  return VEHICLE_INFO_CANID;
}

#endif // VCU_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_STATUS_vcu(VEHICLE_STATUS_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->battery_voltage = (uint8_t) ( (_d[0] & (0xFFU)) );
  _m->battery_soc = (uint8_t) ( (_d[1] & (0xFFU)) );
  _m->blinker = (uint8_t) ( (_d[2] & (0xFFU)) );
  _m->headlight = (uint8_t) ( (_d[3] & (0xFFU)) );
  _m->gear = (uint8_t) ( (_d[4] & (0xFFU)) );
  _m->mode = (uint8_t) ( (_d[5] & (0xFFU)) );
  _m->hand_brake = (uint8_t) ( (_d[6] & (0xFFU)) );

#ifdef VCU_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEHICLE_STATUS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEHICLE_STATUS_vcu(&_m->mon1, VEHICLE_STATUS_CANID);
#endif // VCU_USE_DIAG_MONITORS

  return VEHICLE_STATUS_CANID;
}

#ifdef VCU_USE_CANSTRUCT

uint32_t Pack_VEHICLE_STATUS_vcu(VEHICLE_STATUS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VCU_VALIDATE_DLC(VEHICLE_STATUS_DLC); cframe->Data[i++] = VCU_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->battery_voltage & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( (_m->battery_soc & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->blinker & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->headlight & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->gear & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->mode & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->hand_brake & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEHICLE_STATUS_CANID;
  cframe->DLC = (uint8_t) VEHICLE_STATUS_DLC;
  cframe->IDE = (uint8_t) VEHICLE_STATUS_IDE;
  return VEHICLE_STATUS_CANID;
}

#else

uint32_t Pack_VEHICLE_STATUS_vcu(VEHICLE_STATUS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VCU_VALIDATE_DLC(VEHICLE_STATUS_DLC); _d[i++] = VCU_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->battery_voltage & (0xFFU)) );
  _d[1] |= (uint8_t) ( (_m->battery_soc & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->blinker & (0xFFU)) );
  _d[3] |= (uint8_t) ( (_m->headlight & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->gear & (0xFFU)) );
  _d[5] |= (uint8_t) ( (_m->mode & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->hand_brake & (0xFFU)) );

  *_len = (uint8_t) VEHICLE_STATUS_DLC;
  *_ide = (uint8_t) VEHICLE_STATUS_IDE;
  return VEHICLE_STATUS_CANID;
}

#endif // VCU_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_INTERFACE_LIFE_SIGNAL_vcu(VEHICLE_INTERFACE_LIFE_SIGNAL_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->life_signal = (uint64_t) ( ((uint64_t)(_d[7] & (0xFFU)) << 56U) | ((uint64_t)(_d[6] & (0xFFU)) << 48U) | ((uint64_t)(_d[5] & (0xFFU)) << 40U) | ((uint64_t)(_d[4] & (0xFFU)) << 32U) | ((_d[3] & (0xFFU)) << 24U) | ((_d[2] & (0xFFU)) << 16U) | ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );

#ifdef VCU_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEHICLE_INTERFACE_LIFE_SIGNAL_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEHICLE_INTERFACE_LIFE_SIGNAL_vcu(&_m->mon1, VEHICLE_INTERFACE_LIFE_SIGNAL_CANID);
#endif // VCU_USE_DIAG_MONITORS

  return VEHICLE_INTERFACE_LIFE_SIGNAL_CANID;
}

#ifdef VCU_USE_CANSTRUCT

uint32_t Pack_VEHICLE_INTERFACE_LIFE_SIGNAL_vcu(VEHICLE_INTERFACE_LIFE_SIGNAL_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VCU_VALIDATE_DLC(VEHICLE_INTERFACE_LIFE_SIGNAL_DLC); cframe->Data[i++] = VCU_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->life_signal & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->life_signal >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->life_signal >> 16U) & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->life_signal >> 24U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->life_signal >> 32U) & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->life_signal >> 40U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( ((_m->life_signal >> 48U) & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->life_signal >> 56U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEHICLE_INTERFACE_LIFE_SIGNAL_CANID;
  cframe->DLC = (uint8_t) VEHICLE_INTERFACE_LIFE_SIGNAL_DLC;
  cframe->IDE = (uint8_t) VEHICLE_INTERFACE_LIFE_SIGNAL_IDE;
  return VEHICLE_INTERFACE_LIFE_SIGNAL_CANID;
}

#else

uint32_t Pack_VEHICLE_INTERFACE_LIFE_SIGNAL_vcu(VEHICLE_INTERFACE_LIFE_SIGNAL_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VCU_VALIDATE_DLC(VEHICLE_INTERFACE_LIFE_SIGNAL_DLC); _d[i++] = VCU_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->life_signal & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->life_signal >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( ((_m->life_signal >> 16U) & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->life_signal >> 24U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( ((_m->life_signal >> 32U) & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->life_signal >> 40U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( ((_m->life_signal >> 48U) & (0xFFU)) );
  _d[7] |= (uint8_t) ( ((_m->life_signal >> 56U) & (0xFFU)) );

  *_len = (uint8_t) VEHICLE_INTERFACE_LIFE_SIGNAL_DLC;
  *_ide = (uint8_t) VEHICLE_INTERFACE_LIFE_SIGNAL_IDE;
  return VEHICLE_INTERFACE_LIFE_SIGNAL_CANID;
}

#endif // VCU_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_MOTION_COMMANDS_vcu(VEHICLE_MOTION_COMMANDS_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->set_velocity_ro = (int16_t) __ext_sig__(( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) ), 16);
#ifdef VCU_USE_SIGFLOAT
  _m->set_velocity_phys = (sigfloat_t)(VCU_set_velocity_ro_fromS(_m->set_velocity_ro));
#endif // VCU_USE_SIGFLOAT

  _m->set_limit_velocity_ro = (int16_t) __ext_sig__(( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) ), 16);
#ifdef VCU_USE_SIGFLOAT
  _m->set_limit_velocity_phys = (sigfloat_t)(VCU_set_limit_velocity_ro_fromS(_m->set_limit_velocity_ro));
#endif // VCU_USE_SIGFLOAT

  _m->set_front_wheel_tire_angle_ro = (int16_t) __ext_sig__(( ((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) ), 16);
#ifdef VCU_USE_SIGFLOAT
  _m->set_front_wheel_tire_angle_phys = (sigfloat_t)(VCU_set_front_wheel_tire_angle_ro_fromS(_m->set_front_wheel_tire_angle_ro));
#endif // VCU_USE_SIGFLOAT

  _m->set_front_wheel_angle_rate_ro = (int16_t) __ext_sig__(( ((_d[7] & (0xFFU)) << 8U) | (_d[6] & (0xFFU)) ), 16);
#ifdef VCU_USE_SIGFLOAT
  _m->set_front_wheel_angle_rate_phys = (sigfloat_t)(VCU_set_front_wheel_angle_rate_ro_fromS(_m->set_front_wheel_angle_rate_ro));
#endif // VCU_USE_SIGFLOAT

#ifdef VCU_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEHICLE_MOTION_COMMANDS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEHICLE_MOTION_COMMANDS_vcu(&_m->mon1, VEHICLE_MOTION_COMMANDS_CANID);
#endif // VCU_USE_DIAG_MONITORS

  return VEHICLE_MOTION_COMMANDS_CANID;
}

#ifdef VCU_USE_CANSTRUCT

uint32_t Pack_VEHICLE_MOTION_COMMANDS_vcu(VEHICLE_MOTION_COMMANDS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VCU_VALIDATE_DLC(VEHICLE_MOTION_COMMANDS_DLC); cframe->Data[i++] = VCU_INITIAL_BYTE_VALUE);

#ifdef VCU_USE_SIGFLOAT
  _m->set_velocity_ro = (int16_t) VCU_set_velocity_ro_toS(_m->set_velocity_phys);
  _m->set_limit_velocity_ro = (int16_t) VCU_set_limit_velocity_ro_toS(_m->set_limit_velocity_phys);
  _m->set_front_wheel_tire_angle_ro = (int16_t) VCU_set_front_wheel_tire_angle_ro_toS(_m->set_front_wheel_tire_angle_phys);
  _m->set_front_wheel_angle_rate_ro = (int16_t) VCU_set_front_wheel_angle_rate_ro_toS(_m->set_front_wheel_angle_rate_phys);
#endif // VCU_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->set_velocity_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->set_velocity_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->set_limit_velocity_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->set_limit_velocity_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->set_front_wheel_tire_angle_ro & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->set_front_wheel_tire_angle_ro >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->set_front_wheel_angle_rate_ro & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->set_front_wheel_angle_rate_ro >> 8U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEHICLE_MOTION_COMMANDS_CANID;
  cframe->DLC = (uint8_t) VEHICLE_MOTION_COMMANDS_DLC;
  cframe->IDE = (uint8_t) VEHICLE_MOTION_COMMANDS_IDE;
  return VEHICLE_MOTION_COMMANDS_CANID;
}

#else

uint32_t Pack_VEHICLE_MOTION_COMMANDS_vcu(VEHICLE_MOTION_COMMANDS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VCU_VALIDATE_DLC(VEHICLE_MOTION_COMMANDS_DLC); _d[i++] = VCU_INITIAL_BYTE_VALUE);

#ifdef VCU_USE_SIGFLOAT
  _m->set_velocity_ro = (int16_t) VCU_set_velocity_ro_toS(_m->set_velocity_phys);
  _m->set_limit_velocity_ro = (int16_t) VCU_set_limit_velocity_ro_toS(_m->set_limit_velocity_phys);
  _m->set_front_wheel_tire_angle_ro = (int16_t) VCU_set_front_wheel_tire_angle_ro_toS(_m->set_front_wheel_tire_angle_phys);
  _m->set_front_wheel_angle_rate_ro = (int16_t) VCU_set_front_wheel_angle_rate_ro_toS(_m->set_front_wheel_angle_rate_phys);
#endif // VCU_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->set_velocity_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->set_velocity_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->set_limit_velocity_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->set_limit_velocity_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->set_front_wheel_tire_angle_ro & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->set_front_wheel_tire_angle_ro >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->set_front_wheel_angle_rate_ro & (0xFFU)) );
  _d[7] |= (uint8_t) ( ((_m->set_front_wheel_angle_rate_ro >> 8U) & (0xFFU)) );

  *_len = (uint8_t) VEHICLE_MOTION_COMMANDS_DLC;
  *_ide = (uint8_t) VEHICLE_MOTION_COMMANDS_IDE;
  return VEHICLE_MOTION_COMMANDS_CANID;
}

#endif // VCU_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_COMMANDS_vcu(VEHICLE_COMMANDS_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->set_autonomous = (uint8_t) ( (_d[0] & (0x01U)) );
  _m->blinker = (uint8_t) ( ((_d[1] & (0x01U)) << 7U) | ((_d[0] >> 1U) & (0x7FU)) );
  _m->headlight = (uint8_t) ( (_d[1] & (0xFFU)) );
  _m->gear = (uint8_t) ( (_d[2] & (0xFFU)) );
  _m->hand_brake = (uint8_t) ( (_d[3] & (0xFFU)) );
  _m->emergency_request = (uint8_t) ( (_d[4] & (0xFFU)) );
  _m->horn = (uint8_t) ( (_d[5] & (0x01U)) );
  _m->safety_inactive = (uint8_t) ( ((_d[5] >> 1U) & (0x01U)) );
  _m->reserved = (uint32_t) ( ((_d[7] & (0xFFU)) << 14U) | ((_d[6] & (0xFFU)) << 6U) | ((_d[5] >> 2U) & (0x3FU)) );

#ifdef VCU_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEHICLE_COMMANDS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEHICLE_COMMANDS_vcu(&_m->mon1, VEHICLE_COMMANDS_CANID);
#endif // VCU_USE_DIAG_MONITORS

  return VEHICLE_COMMANDS_CANID;
}

#ifdef VCU_USE_CANSTRUCT

uint32_t Pack_VEHICLE_COMMANDS_vcu(VEHICLE_COMMANDS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < VCU_VALIDATE_DLC(VEHICLE_COMMANDS_DLC); cframe->Data[i++] = VCU_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->set_autonomous & (0x01U)) | ((_m->blinker & (0x7FU)) << 1U) );
  cframe->Data[1] |= (uint8_t) ( ((_m->blinker >> 7U) & (0x01U)) | (_m->headlight & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->gear & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->hand_brake & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->emergency_request & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->horn & (0x01U)) | ((_m->safety_inactive & (0x01U)) << 1U) | ((_m->reserved & (0x3FU)) << 2U) );
  cframe->Data[6] |= (uint8_t) ( ((_m->reserved >> 6U) & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->reserved >> 14U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEHICLE_COMMANDS_CANID;
  cframe->DLC = (uint8_t) VEHICLE_COMMANDS_DLC;
  cframe->IDE = (uint8_t) VEHICLE_COMMANDS_IDE;
  return VEHICLE_COMMANDS_CANID;
}

#else

uint32_t Pack_VEHICLE_COMMANDS_vcu(VEHICLE_COMMANDS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < VCU_VALIDATE_DLC(VEHICLE_COMMANDS_DLC); _d[i++] = VCU_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->set_autonomous & (0x01U)) | ((_m->blinker & (0x7FU)) << 1U) );
  _d[1] |= (uint8_t) ( ((_m->blinker >> 7U) & (0x01U)) | (_m->headlight & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->gear & (0xFFU)) );
  _d[3] |= (uint8_t) ( (_m->hand_brake & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->emergency_request & (0xFFU)) );
  _d[5] |= (uint8_t) ( (_m->horn & (0x01U)) | ((_m->safety_inactive & (0x01U)) << 1U) | ((_m->reserved & (0x3FU)) << 2U) );
  _d[6] |= (uint8_t) ( ((_m->reserved >> 6U) & (0xFFU)) );
  _d[7] |= (uint8_t) ( ((_m->reserved >> 14U) & (0xFFU)) );

  *_len = (uint8_t) VEHICLE_COMMANDS_DLC;
  *_ide = (uint8_t) VEHICLE_COMMANDS_IDE;
  return VEHICLE_COMMANDS_CANID;
}

#endif // VCU_USE_CANSTRUCT

