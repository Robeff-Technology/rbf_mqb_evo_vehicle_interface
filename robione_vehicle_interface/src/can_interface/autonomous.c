// Generator version : v3.1
// DBC filename      : autonomous_module.dbc
#include "autonomous.h"

// DBC file version
#if (VER_AUTONOMOUS_MAJ != (0U)) || (VER_AUTONOMOUS_MIN != (0U))
#error The AUTONOMOUS dbc source files have different versions
#endif

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
// Function prototypes to be called each time CAN frame is unpacked
// FMon function may detect RC, CRC or DLC violation
#include "autonomous-fmon.h"

#endif // AUTONOMOUS_USE_DIAG_MONITORS

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
static bitext_t __ext_sig__(ubitext_t val, uint8_t bits) {
    ubitext_t const m = (ubitext_t) (1u << (bits - 1u));
    return ((val ^ m) - m);
}

uint32_t Unpack_LONGITUDINAL_COMMANDS_JOY_autonomous(LONGITUDINAL_COMMANDS_JOY_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;
    _m->set_gas_pedal_pos_ro = (uint16_t) (((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->set_gas_pedal_pos_phys = (sigfloat_t) (AUTONOMOUS_set_gas_pedal_pos_ro_fromS(_m->set_gas_pedal_pos_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->set_brake_force_ro = (uint16_t) (((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->set_brake_force_phys = (uint32_t) AUTONOMOUS_set_brake_force_ro_fromS(_m->set_brake_force_ro);
#endif // AUTONOMOUS_USE_SIGFLOAT

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < LONGITUDINAL_COMMANDS_JOY_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_LONGITUDINAL_COMMANDS_JOY_autonomous(&_m->mon1, LONGITUDINAL_COMMANDS_JOY_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return LONGITUDINAL_COMMANDS_JOY_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_LONGITUDINAL_COMMANDS_JOY_autonomous(LONGITUDINAL_COMMANDS_JOY_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(LONGITUDINAL_COMMANDS_JOY_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

#ifdef AUTONOMOUS_USE_SIGFLOAT
  _m->set_gas_pedal_pos_ro = (uint16_t) AUTONOMOUS_set_gas_pedal_pos_ro_toS(_m->set_gas_pedal_pos_phys);
  _m->set_brake_force_ro = (uint16_t) AUTONOMOUS_set_brake_force_ro_toS(_m->set_brake_force_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->set_gas_pedal_pos_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->set_gas_pedal_pos_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->set_brake_force_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->set_brake_force_ro >> 8U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) LONGITUDINAL_COMMANDS_JOY_CANID;
  cframe->DLC = (uint8_t) LONGITUDINAL_COMMANDS_JOY_DLC;
  cframe->IDE = (uint8_t) LONGITUDINAL_COMMANDS_JOY_IDE;
  return LONGITUDINAL_COMMANDS_JOY_CANID;
}

#else

uint32_t Pack_LONGITUDINAL_COMMANDS_JOY_autonomous(LONGITUDINAL_COMMANDS_JOY_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(LONGITUDINAL_COMMANDS_JOY_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->set_gas_pedal_pos_ro = (uint16_t) AUTONOMOUS_set_gas_pedal_pos_ro_toS(_m->set_gas_pedal_pos_phys);
    _m->set_brake_force_ro = (uint16_t) AUTONOMOUS_set_brake_force_ro_toS(_m->set_brake_force_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _d[0] |= (uint8_t) ((_m->set_gas_pedal_pos_ro & (0xFFU)));
    _d[1] |= (uint8_t) (((_m->set_gas_pedal_pos_ro >> 8U) & (0xFFU)));
    _d[2] |= (uint8_t) ((_m->set_brake_force_ro & (0xFFU)));
    _d[3] |= (uint8_t) (((_m->set_brake_force_ro >> 8U) & (0xFFU)));

    *_len = (uint8_t) LONGITUDINAL_COMMANDS_JOY_DLC;
    *_ide = (uint8_t) LONGITUDINAL_COMMANDS_JOY_IDE;
    return LONGITUDINAL_COMMANDS_JOY_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_COMMANDS_JOY_autonomous(VEHICLE_COMMANDS_JOY_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;
    _m->blinker = (uint8_t) ((_d[0] & (0xFFU)));
    _m->headlight = (uint8_t) ((_d[1] & (0xFFU)));
    _m->gear = (uint8_t) ((_d[3] & (0xFFU)));
    _m->mode = (uint8_t) ((_d[4] & (0xFFU)));
    _m->hand_brake = (uint8_t) ((_d[5] & (0xFFU)));

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEHICLE_COMMANDS_JOY_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEHICLE_COMMANDS_JOY_autonomous(&_m->mon1, VEHICLE_COMMANDS_JOY_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return VEHICLE_COMMANDS_JOY_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_VEHICLE_COMMANDS_JOY_autonomous(VEHICLE_COMMANDS_JOY_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(VEHICLE_COMMANDS_JOY_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->blinker & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( (_m->headlight & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->gear & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->mode & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->hand_brake & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEHICLE_COMMANDS_JOY_CANID;
  cframe->DLC = (uint8_t) VEHICLE_COMMANDS_JOY_DLC;
  cframe->IDE = (uint8_t) VEHICLE_COMMANDS_JOY_IDE;
  return VEHICLE_COMMANDS_JOY_CANID;
}

#else

uint32_t Pack_VEHICLE_COMMANDS_JOY_autonomous(VEHICLE_COMMANDS_JOY_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(VEHICLE_COMMANDS_JOY_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

    _d[0] |= (uint8_t) ((_m->blinker & (0xFFU)));
    _d[1] |= (uint8_t) ((_m->headlight & (0xFFU)));
    _d[3] |= (uint8_t) ((_m->gear & (0xFFU)));
    _d[4] |= (uint8_t) ((_m->mode & (0xFFU)));
    _d[5] |= (uint8_t) ((_m->hand_brake & (0xFFU)));

    *_len = (uint8_t) VEHICLE_COMMANDS_JOY_DLC;
    *_ide = (uint8_t) VEHICLE_COMMANDS_JOY_IDE;
    return VEHICLE_COMMANDS_JOY_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_FRONT_WHEEL_COMMANDS_JOY_autonomous(FRONT_WHEEL_COMMANDS_JOY_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;
    _m->set_steering_wheel_angle_ro = (int16_t) __ext_sig__((((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU))), 16);
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->set_steering_wheel_angle_phys = (sigfloat_t) (AUTONOMOUS_set_steering_wheel_angle_ro_fromS(_m->set_steering_wheel_angle_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->set_steering_wheel_torque = (uint8_t) ((_d[2] & (0xFFU)));

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < FRONT_WHEEL_COMMANDS_JOY_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_FRONT_WHEEL_COMMANDS_JOY_autonomous(&_m->mon1, FRONT_WHEEL_COMMANDS_JOY_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return FRONT_WHEEL_COMMANDS_JOY_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_FRONT_WHEEL_COMMANDS_JOY_autonomous(FRONT_WHEEL_COMMANDS_JOY_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(FRONT_WHEEL_COMMANDS_JOY_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

#ifdef AUTONOMOUS_USE_SIGFLOAT
  _m->set_steering_wheel_angle_ro = (int16_t) AUTONOMOUS_set_steering_wheel_angle_ro_toS(_m->set_steering_wheel_angle_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->set_steering_wheel_angle_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->set_steering_wheel_angle_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->set_steering_wheel_torque & (0xFFU)) );

  cframe->MsgId = (uint32_t) FRONT_WHEEL_COMMANDS_JOY_CANID;
  cframe->DLC = (uint8_t) FRONT_WHEEL_COMMANDS_JOY_DLC;
  cframe->IDE = (uint8_t) FRONT_WHEEL_COMMANDS_JOY_IDE;
  return FRONT_WHEEL_COMMANDS_JOY_CANID;
}

#else

uint32_t Pack_FRONT_WHEEL_COMMANDS_JOY_autonomous(FRONT_WHEEL_COMMANDS_JOY_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(FRONT_WHEEL_COMMANDS_JOY_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->set_steering_wheel_angle_ro = (int16_t) AUTONOMOUS_set_steering_wheel_angle_ro_toS(_m->set_steering_wheel_angle_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _d[0] |= (uint8_t) ((_m->set_steering_wheel_angle_ro & (0xFFU)));
    _d[1] |= (uint8_t) (((_m->set_steering_wheel_angle_ro >> 8U) & (0xFFU)));
    _d[2] |= (uint8_t) ((_m->set_steering_wheel_torque & (0xFFU)));

    *_len = (uint8_t) FRONT_WHEEL_COMMANDS_JOY_DLC;
    *_ide = (uint8_t) FRONT_WHEEL_COMMANDS_JOY_IDE;
    return FRONT_WHEEL_COMMANDS_JOY_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_INFO_autonomous(VEHICLE_INFO_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;
    _m->vehicle_velocity_ro = (uint16_t) (((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->vehicle_velocity_phys = (sigfloat_t) (AUTONOMOUS_vehicle_velocity_ro_fromS(_m->vehicle_velocity_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->steering_wheel_angle_ro = (int16_t) __ext_sig__((((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU))), 16);
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->steering_wheel_angle_phys = (sigfloat_t) (AUTONOMOUS_steering_wheel_angle_ro_fromS(_m->steering_wheel_angle_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->steering_wheel_speed_ro = (int16_t) __ext_sig__((((_d[5] & (0x03U)) << 8U) | (_d[4] & (0xFFU))), 10);
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->steering_wheel_speed_phys = (int16_t) AUTONOMOUS_steering_wheel_speed_ro_fromS(_m->steering_wheel_speed_ro);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->steering_wheel_torque = (int16_t) __ext_sig__((((_d[6] & (0x1FU)) << 6U) | ((_d[5] >> 2U) & (0x3FU))), 11);
    _m->steering_tire_angle_ro = (int16_t) __ext_sig__((((_d[7] & (0xFFU)) << 3U) | ((_d[6] >> 5U) & (0x07U))), 11);
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->steering_tire_angle_phys = (sigfloat_t) (AUTONOMOUS_steering_tire_angle_ro_fromS(_m->steering_tire_angle_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEHICLE_INFO_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEHICLE_INFO_autonomous(&_m->mon1, VEHICLE_INFO_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return VEHICLE_INFO_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_VEHICLE_INFO_autonomous(VEHICLE_INFO_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(VEHICLE_INFO_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

#ifdef AUTONOMOUS_USE_SIGFLOAT
  _m->vehicle_velocity_ro = (uint16_t) AUTONOMOUS_vehicle_velocity_ro_toS(_m->vehicle_velocity_phys);
  _m->steering_wheel_angle_ro = (int16_t) AUTONOMOUS_steering_wheel_angle_ro_toS(_m->steering_wheel_angle_phys);
  _m->steering_wheel_speed_ro = (int16_t) AUTONOMOUS_steering_wheel_speed_ro_toS(_m->steering_wheel_speed_phys);
  _m->steering_tire_angle_ro = (int16_t) AUTONOMOUS_steering_tire_angle_ro_toS(_m->steering_tire_angle_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

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

uint32_t Pack_VEHICLE_INFO_autonomous(VEHICLE_INFO_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(VEHICLE_INFO_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->vehicle_velocity_ro = (uint16_t) AUTONOMOUS_vehicle_velocity_ro_toS(_m->vehicle_velocity_phys);
    _m->steering_wheel_angle_ro = (int16_t) AUTONOMOUS_steering_wheel_angle_ro_toS(_m->steering_wheel_angle_phys);
    _m->steering_wheel_speed_ro = (int16_t) AUTONOMOUS_steering_wheel_speed_ro_toS(_m->steering_wheel_speed_phys);
    _m->steering_tire_angle_ro = (int16_t) AUTONOMOUS_steering_tire_angle_ro_toS(_m->steering_tire_angle_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _d[0] |= (uint8_t) ((_m->vehicle_velocity_ro & (0xFFU)));
    _d[1] |= (uint8_t) (((_m->vehicle_velocity_ro >> 8U) & (0xFFU)));
    _d[2] |= (uint8_t) ((_m->steering_wheel_angle_ro & (0xFFU)));
    _d[3] |= (uint8_t) (((_m->steering_wheel_angle_ro >> 8U) & (0xFFU)));
    _d[4] |= (uint8_t) ((_m->steering_wheel_speed_ro & (0xFFU)));
    _d[5] |= (uint8_t) (((_m->steering_wheel_speed_ro >> 8U) & (0x03U)) | ((_m->steering_wheel_torque & (0x3FU)) << 2U));
    _d[6] |= (uint8_t) (((_m->steering_wheel_torque >> 6U) & (0x1FU)) | ((_m->steering_tire_angle_ro & (0x07U)) << 5U));
    _d[7] |= (uint8_t) (((_m->steering_tire_angle_ro >> 3U) & (0xFFU)));

    *_len = (uint8_t) VEHICLE_INFO_DLC;
    *_ide = (uint8_t) VEHICLE_INFO_IDE;
    return VEHICLE_INFO_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_SIGNAL_STATUS_autonomous(VEHICLE_SIGNAL_STATUS_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;
    _m->fuel = (uint8_t) ((_d[0] & (0xFFU)));
    _m->blinker = (uint8_t) ((_d[1] & (0xFFU)));
    _m->headlight = (uint8_t) ((_d[2] & (0xFFU)));
    _m->gear = (uint8_t) ((_d[4] & (0xFFU)));
    _m->target_gear_level = (uint8_t) ((_d[5] & (0xFFU)));
    _m->hand_brake = (uint8_t) ((_d[6] & (0x07U)));
    _m->mode = (uint8_t) ((_d[7] & (0x03U)));

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEHICLE_SIGNAL_STATUS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEHICLE_SIGNAL_STATUS_autonomous(&_m->mon1, VEHICLE_SIGNAL_STATUS_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return VEHICLE_SIGNAL_STATUS_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_VEHICLE_SIGNAL_STATUS_autonomous(VEHICLE_SIGNAL_STATUS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(VEHICLE_SIGNAL_STATUS_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->fuel & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( (_m->blinker & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->headlight & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->gear & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->target_gear_level & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->hand_brake & (0x07U)) );
  cframe->Data[7] |= (uint8_t) ( (_m->mode & (0x03U)) );

  cframe->MsgId = (uint32_t) VEHICLE_SIGNAL_STATUS_CANID;
  cframe->DLC = (uint8_t) VEHICLE_SIGNAL_STATUS_DLC;
  cframe->IDE = (uint8_t) VEHICLE_SIGNAL_STATUS_IDE;
  return VEHICLE_SIGNAL_STATUS_CANID;
}

#else

uint32_t Pack_VEHICLE_SIGNAL_STATUS_autonomous(VEHICLE_SIGNAL_STATUS_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(VEHICLE_SIGNAL_STATUS_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

    _d[0] |= (uint8_t) ((_m->fuel & (0xFFU)));
    _d[1] |= (uint8_t) ((_m->blinker & (0xFFU)));
    _d[2] |= (uint8_t) ((_m->headlight & (0xFFU)));
    _d[4] |= (uint8_t) ((_m->gear & (0xFFU)));
    _d[5] |= (uint8_t) ((_m->target_gear_level & (0xFFU)));
    _d[6] |= (uint8_t) ((_m->hand_brake & (0x07U)));
    _d[7] |= (uint8_t) ((_m->mode & (0x03U)));

    *_len = (uint8_t) VEHICLE_SIGNAL_STATUS_DLC;
    *_ide = (uint8_t) VEHICLE_SIGNAL_STATUS_IDE;
    return VEHICLE_SIGNAL_STATUS_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_MOTION_INFO_autonomous(MOTION_INFO_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;
    _m->steering_intervention = (uint8_t) ((_d[0] & (0x01U)));
    _m->brake_intervention = (uint8_t) (((_d[0] >> 1U) & (0x01U)));
    _m->acc_pedal_intervention = (uint8_t) (((_d[0] >> 2U) & (0x01U)));
    _m->throttle_ro = (uint8_t) ((_d[3] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->throttle_phys = (sigfloat_t) (AUTONOMOUS_throttle_ro_fromS(_m->throttle_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->brake = (uint8_t) ((_d[4] & (0xFFU)));
    _m->ESP_brake_pressure_ro = (uint16_t) (((_d[6] & (0x03U)) << 8U) | (_d[5] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->ESP_brake_pressure_phys = (sigfloat_t) (AUTONOMOUS_ESP_brake_pressure_ro_fromS(_m->ESP_brake_pressure_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->driver_brake = (uint8_t) ((_d[7] & (0x01U)));

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < MOTION_INFO_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_MOTION_INFO_autonomous(&_m->mon1, MOTION_INFO_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return MOTION_INFO_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_MOTION_INFO_autonomous(MOTION_INFO_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(MOTION_INFO_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

#ifdef AUTONOMOUS_USE_SIGFLOAT
  _m->throttle_ro = (uint8_t) AUTONOMOUS_throttle_ro_toS(_m->throttle_phys);
  _m->ESP_brake_pressure_ro = (uint16_t) AUTONOMOUS_ESP_brake_pressure_ro_toS(_m->ESP_brake_pressure_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->steering_intervention & (0x01U)) | ((_m->brake_intervention & (0x01U)) << 1U) | ((_m->acc_pedal_intervention & (0x01U)) << 2U) );
  cframe->Data[3] |= (uint8_t) ( (_m->throttle_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->brake & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->ESP_brake_pressure_ro & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( ((_m->ESP_brake_pressure_ro >> 8U) & (0x03U)) );
  cframe->Data[7] |= (uint8_t) ( (_m->driver_brake & (0x01U)) );

  cframe->MsgId = (uint32_t) MOTION_INFO_CANID;
  cframe->DLC = (uint8_t) MOTION_INFO_DLC;
  cframe->IDE = (uint8_t) MOTION_INFO_IDE;
  return MOTION_INFO_CANID;
}

#else

uint32_t Pack_MOTION_INFO_autonomous(MOTION_INFO_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(MOTION_INFO_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->throttle_ro = (uint8_t) AUTONOMOUS_throttle_ro_toS(_m->throttle_phys);
    _m->ESP_brake_pressure_ro = (uint16_t) AUTONOMOUS_ESP_brake_pressure_ro_toS(_m->ESP_brake_pressure_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _d[0] |= (uint8_t) ((_m->steering_intervention & (0x01U)) | ((_m->brake_intervention & (0x01U)) << 1U)
            | ((_m->acc_pedal_intervention & (0x01U)) << 2U));
    _d[3] |= (uint8_t) ((_m->throttle_ro & (0xFFU)));
    _d[4] |= (uint8_t) ((_m->brake & (0xFFU)));
    _d[5] |= (uint8_t) ((_m->ESP_brake_pressure_ro & (0xFFU)));
    _d[6] |= (uint8_t) (((_m->ESP_brake_pressure_ro >> 8U) & (0x03U)));
    _d[7] |= (uint8_t) ((_m->driver_brake & (0x01U)));

    *_len = (uint8_t) MOTION_INFO_DLC;
    *_ide = (uint8_t) MOTION_INFO_IDE;
    return MOTION_INFO_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_MOTOR_INFO_autonomous(MOTOR_INFO_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;
    _m->motor_oil_temp_ro = (uint8_t) ((_d[0] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->motor_oil_temp_phys = (int16_t) AUTONOMOUS_motor_oil_temp_ro_fromS(_m->motor_oil_temp_ro);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->motor_rpm_ro = (uint16_t) (((_d[2] & (0xFFU)) << 8U) | (_d[1] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->motor_rpm_phys = (sigfloat_t) (AUTONOMOUS_motor_rpm_ro_fromS(_m->motor_rpm_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->motor_torque_setpoint_filtered_ro = (uint16_t) (((_d[4] & (0x03U)) << 8U) | (_d[3] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->motor_torque_setpoint_filtered_phys = (int16_t) AUTONOMOUS_motor_torque_setpoint_filtered_ro_fromS(_m->motor_torque_setpoint_filtered_ro);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->motor_torque_setpoint_raw_ro = (uint16_t) (((_d[5] & (0x0FU)) << 6U) | ((_d[4] >> 2U) & (0x3FU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->motor_torque_setpoint_raw_phys = (int16_t) AUTONOMOUS_motor_torque_setpoint_raw_ro_fromS(_m->motor_torque_setpoint_raw_ro);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->motor_torque_total_ro = (uint16_t) (((_d[6] & (0x3FU)) << 4U) | ((_d[5] >> 4U) & (0x0FU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->motor_torque_total_phys = (int16_t) AUTONOMOUS_motor_torque_total_ro_fromS(_m->motor_torque_total_ro);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->motor_coolant_temp_ro = (uint8_t) ((_d[7] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->motor_coolant_temp_phys = (sigfloat_t) (AUTONOMOUS_motor_coolant_temp_ro_fromS(_m->motor_coolant_temp_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < MOTOR_INFO_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_MOTOR_INFO_autonomous(&_m->mon1, MOTOR_INFO_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return MOTOR_INFO_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_MOTOR_INFO_autonomous(MOTOR_INFO_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(MOTOR_INFO_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

#ifdef AUTONOMOUS_USE_SIGFLOAT
  _m->motor_oil_temp_ro = (uint8_t) AUTONOMOUS_motor_oil_temp_ro_toS(_m->motor_oil_temp_phys);
  _m->motor_rpm_ro = (uint16_t) AUTONOMOUS_motor_rpm_ro_toS(_m->motor_rpm_phys);
  _m->motor_torque_setpoint_filtered_ro = (uint16_t) AUTONOMOUS_motor_torque_setpoint_filtered_ro_toS(_m->motor_torque_setpoint_filtered_phys);
  _m->motor_torque_setpoint_raw_ro = (uint16_t) AUTONOMOUS_motor_torque_setpoint_raw_ro_toS(_m->motor_torque_setpoint_raw_phys);
  _m->motor_torque_total_ro = (uint16_t) AUTONOMOUS_motor_torque_total_ro_toS(_m->motor_torque_total_phys);
  _m->motor_coolant_temp_ro = (uint8_t) AUTONOMOUS_motor_coolant_temp_ro_toS(_m->motor_coolant_temp_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->motor_oil_temp_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( (_m->motor_rpm_ro & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->motor_rpm_ro >> 8U) & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->motor_torque_setpoint_filtered_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->motor_torque_setpoint_filtered_ro >> 8U) & (0x03U)) | ((_m->motor_torque_setpoint_raw_ro & (0x3FU)) << 2U) );
  cframe->Data[5] |= (uint8_t) ( ((_m->motor_torque_setpoint_raw_ro >> 6U) & (0x0FU)) | ((_m->motor_torque_total_ro & (0x0FU)) << 4U) );
  cframe->Data[6] |= (uint8_t) ( ((_m->motor_torque_total_ro >> 4U) & (0x3FU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->motor_coolant_temp_ro & (0xFFU)) );

  cframe->MsgId = (uint32_t) MOTOR_INFO_CANID;
  cframe->DLC = (uint8_t) MOTOR_INFO_DLC;
  cframe->IDE = (uint8_t) MOTOR_INFO_IDE;
  return MOTOR_INFO_CANID;
}

#else

uint32_t Pack_MOTOR_INFO_autonomous(MOTOR_INFO_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(MOTOR_INFO_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->motor_oil_temp_ro = (uint8_t) AUTONOMOUS_motor_oil_temp_ro_toS(_m->motor_oil_temp_phys);
    _m->motor_rpm_ro = (uint16_t) AUTONOMOUS_motor_rpm_ro_toS(_m->motor_rpm_phys);
    _m->motor_torque_setpoint_filtered_ro = (uint16_t) AUTONOMOUS_motor_torque_setpoint_filtered_ro_toS(_m->motor_torque_setpoint_filtered_phys);
    _m->motor_torque_setpoint_raw_ro = (uint16_t) AUTONOMOUS_motor_torque_setpoint_raw_ro_toS(_m->motor_torque_setpoint_raw_phys);
    _m->motor_torque_total_ro = (uint16_t) AUTONOMOUS_motor_torque_total_ro_toS(_m->motor_torque_total_phys);
    _m->motor_coolant_temp_ro = (uint8_t) AUTONOMOUS_motor_coolant_temp_ro_toS(_m->motor_coolant_temp_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _d[0] |= (uint8_t) ((_m->motor_oil_temp_ro & (0xFFU)));
    _d[1] |= (uint8_t) ((_m->motor_rpm_ro & (0xFFU)));
    _d[2] |= (uint8_t) (((_m->motor_rpm_ro >> 8U) & (0xFFU)));
    _d[3] |= (uint8_t) ((_m->motor_torque_setpoint_filtered_ro & (0xFFU)));
    _d[4] |= (uint8_t) (((_m->motor_torque_setpoint_filtered_ro >> 8U) & (0x03U)) | ((_m->motor_torque_setpoint_raw_ro & (0x3FU)) << 2U));
    _d[5] |= (uint8_t) (((_m->motor_torque_setpoint_raw_ro >> 6U) & (0x0FU)) | ((_m->motor_torque_total_ro & (0x0FU)) << 4U));
    _d[6] |= (uint8_t) (((_m->motor_torque_total_ro >> 4U) & (0x3FU)));
    _d[7] |= (uint8_t) ((_m->motor_coolant_temp_ro & (0xFFU)));

    *_len = (uint8_t) MOTOR_INFO_DLC;
    *_ide = (uint8_t) MOTOR_INFO_IDE;
    return MOTOR_INFO_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_ERRORS_autonomous(VEHICLE_ERRORS_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;
    _m->is_motor_running = (uint8_t) ((_d[0] & (0x01U)));
    _m->kl_75 = (uint8_t) (((_d[0] >> 1U) & (0x01U)));
    _m->ready_to_drive = (uint8_t) (((_d[0] >> 2U) & (0x01U)));
    _m->timeout = (uint8_t) ((_d[1] & (0x01U)));
    _m->brake_fault = (uint8_t) (((_d[1] >> 1U) & (0x01U)));
    _m->steering_fault = (uint8_t) (((_d[1] >> 2U) & (0x01U)));

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEHICLE_ERRORS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEHICLE_ERRORS_autonomous(&_m->mon1, VEHICLE_ERRORS_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return VEHICLE_ERRORS_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_VEHICLE_ERRORS_autonomous(VEHICLE_ERRORS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(VEHICLE_ERRORS_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->is_motor_running & (0x01U)) | ((_m->kl_75 & (0x01U)) << 1U) | ((_m->ready_to_drive & (0x01U)) << 2U) );
  cframe->Data[1] |= (uint8_t) ( (_m->timeout & (0x01U)) | ((_m->brake_fault & (0x01U)) << 1U) | ((_m->steering_fault & (0x01U)) << 2U) );

  cframe->MsgId = (uint32_t) VEHICLE_ERRORS_CANID;
  cframe->DLC = (uint8_t) VEHICLE_ERRORS_DLC;
  cframe->IDE = (uint8_t) VEHICLE_ERRORS_IDE;
  return VEHICLE_ERRORS_CANID;
}

#else

uint32_t Pack_VEHICLE_ERRORS_autonomous(VEHICLE_ERRORS_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(VEHICLE_ERRORS_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

    _d[0] |= (uint8_t) ((_m->is_motor_running & (0x01U)) | ((_m->kl_75 & (0x01U)) << 1U) | ((_m->ready_to_drive & (0x01U)) << 2U));
    _d[1] |= (uint8_t) ((_m->timeout & (0x01U)) | ((_m->brake_fault & (0x01U)) << 1U) | ((_m->steering_fault & (0x01U)) << 2U));

    *_len = (uint8_t) VEHICLE_ERRORS_DLC;
    *_ide = (uint8_t) VEHICLE_ERRORS_IDE;
    return VEHICLE_ERRORS_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_WHEEL_SPEEDS_autonomous(WHEEL_SPEEDS_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;
    _m->esp_bl_wheel_speed_ro = (uint16_t) (((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->esp_bl_wheel_speed_phys = (sigfloat_t) (AUTONOMOUS_esp_bl_wheel_speed_ro_fromS(_m->esp_bl_wheel_speed_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->esp_br_wheel_speed_ro = (uint16_t) (((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->esp_br_wheel_speed_phys = (sigfloat_t) (AUTONOMOUS_esp_br_wheel_speed_ro_fromS(_m->esp_br_wheel_speed_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->esp_fl_wheel_speed_ro = (uint16_t) (((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->esp_fl_wheel_speed_phys = (sigfloat_t) (AUTONOMOUS_esp_fl_wheel_speed_ro_fromS(_m->esp_fl_wheel_speed_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->esp_fr_wheel_speed_ro = (uint16_t) (((_d[7] & (0xFFU)) << 8U) | (_d[6] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->esp_fr_wheel_speed_phys = (sigfloat_t) (AUTONOMOUS_esp_fr_wheel_speed_ro_fromS(_m->esp_fr_wheel_speed_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < WHEEL_SPEEDS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_WHEEL_SPEEDS_autonomous(&_m->mon1, WHEEL_SPEEDS_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return WHEEL_SPEEDS_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_WHEEL_SPEEDS_autonomous(WHEEL_SPEEDS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(WHEEL_SPEEDS_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

#ifdef AUTONOMOUS_USE_SIGFLOAT
  _m->esp_bl_wheel_speed_ro = (uint16_t) AUTONOMOUS_esp_bl_wheel_speed_ro_toS(_m->esp_bl_wheel_speed_phys);
  _m->esp_br_wheel_speed_ro = (uint16_t) AUTONOMOUS_esp_br_wheel_speed_ro_toS(_m->esp_br_wheel_speed_phys);
  _m->esp_fl_wheel_speed_ro = (uint16_t) AUTONOMOUS_esp_fl_wheel_speed_ro_toS(_m->esp_fl_wheel_speed_phys);
  _m->esp_fr_wheel_speed_ro = (uint16_t) AUTONOMOUS_esp_fr_wheel_speed_ro_toS(_m->esp_fr_wheel_speed_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->esp_bl_wheel_speed_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->esp_bl_wheel_speed_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->esp_br_wheel_speed_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->esp_br_wheel_speed_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->esp_fl_wheel_speed_ro & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->esp_fl_wheel_speed_ro >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->esp_fr_wheel_speed_ro & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->esp_fr_wheel_speed_ro >> 8U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) WHEEL_SPEEDS_CANID;
  cframe->DLC = (uint8_t) WHEEL_SPEEDS_DLC;
  cframe->IDE = (uint8_t) WHEEL_SPEEDS_IDE;
  return WHEEL_SPEEDS_CANID;
}

#else

uint32_t Pack_WHEEL_SPEEDS_autonomous(WHEEL_SPEEDS_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(WHEEL_SPEEDS_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->esp_bl_wheel_speed_ro = (uint16_t) AUTONOMOUS_esp_bl_wheel_speed_ro_toS(_m->esp_bl_wheel_speed_phys);
    _m->esp_br_wheel_speed_ro = (uint16_t) AUTONOMOUS_esp_br_wheel_speed_ro_toS(_m->esp_br_wheel_speed_phys);
    _m->esp_fl_wheel_speed_ro = (uint16_t) AUTONOMOUS_esp_fl_wheel_speed_ro_toS(_m->esp_fl_wheel_speed_phys);
    _m->esp_fr_wheel_speed_ro = (uint16_t) AUTONOMOUS_esp_fr_wheel_speed_ro_toS(_m->esp_fr_wheel_speed_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _d[0] |= (uint8_t) ((_m->esp_bl_wheel_speed_ro & (0xFFU)));
    _d[1] |= (uint8_t) (((_m->esp_bl_wheel_speed_ro >> 8U) & (0xFFU)));
    _d[2] |= (uint8_t) ((_m->esp_br_wheel_speed_ro & (0xFFU)));
    _d[3] |= (uint8_t) (((_m->esp_br_wheel_speed_ro >> 8U) & (0xFFU)));
    _d[4] |= (uint8_t) ((_m->esp_fl_wheel_speed_ro & (0xFFU)));
    _d[5] |= (uint8_t) (((_m->esp_fl_wheel_speed_ro >> 8U) & (0xFFU)));
    _d[6] |= (uint8_t) ((_m->esp_fr_wheel_speed_ro & (0xFFU)));
    _d[7] |= (uint8_t) (((_m->esp_fr_wheel_speed_ro >> 8U) & (0xFFU)));

    *_len = (uint8_t) WHEEL_SPEEDS_DLC;
    *_ide = (uint8_t) WHEEL_SPEEDS_IDE;
    return WHEEL_SPEEDS_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_DYNAMIC_SENSOR_FRAME_autonomous(DYNAMIC_SENSOR_FRAME_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;
    _m->esp_lateral_acceleration_ro = (uint8_t) ((_d[0] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->esp_lateral_acceleration_phys = (sigfloat_t) (AUTONOMOUS_esp_lateral_acceleration_ro_fromS(_m->esp_lateral_acceleration_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->esp_longitudinal_acceleration_ro = (uint16_t) (((_d[2] & (0x03U)) << 8U) | (_d[1] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->esp_longitudinal_acceleration_phys = (sigfloat_t) (AUTONOMOUS_esp_longitudinal_acceleration_ro_fromS(_m->esp_longitudinal_acceleration_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->esp_yaw_rate_ro = (int16_t) __ext_sig__((((_d[4] & (0xFFU)) << 8U) | (_d[3] & (0xFFU))), 16);
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->esp_yaw_rate_phys = (sigfloat_t) (AUTONOMOUS_esp_yaw_rate_ro_fromS(_m->esp_yaw_rate_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->vehicle_mass_ro = (uint8_t) ((_d[5] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->vehicle_mass_phys = (uint16_t) AUTONOMOUS_vehicle_mass_ro_fromS(_m->vehicle_mass_ro);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->pitch_ro = (uint8_t) ((_d[6] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->pitch_phys = (sigfloat_t) (AUTONOMOUS_pitch_ro_fromS(_m->pitch_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DYNAMIC_SENSOR_FRAME_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DYNAMIC_SENSOR_FRAME_autonomous(&_m->mon1, DYNAMIC_SENSOR_FRAME_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return DYNAMIC_SENSOR_FRAME_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_DYNAMIC_SENSOR_FRAME_autonomous(DYNAMIC_SENSOR_FRAME_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(DYNAMIC_SENSOR_FRAME_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

#ifdef AUTONOMOUS_USE_SIGFLOAT
  _m->esp_lateral_acceleration_ro = (uint8_t) AUTONOMOUS_esp_lateral_acceleration_ro_toS(_m->esp_lateral_acceleration_phys);
  _m->esp_longitudinal_acceleration_ro = (uint16_t) AUTONOMOUS_esp_longitudinal_acceleration_ro_toS(_m->esp_longitudinal_acceleration_phys);
  _m->esp_yaw_rate_ro = (int16_t) AUTONOMOUS_esp_yaw_rate_ro_toS(_m->esp_yaw_rate_phys);
  _m->vehicle_mass_ro = (uint8_t) AUTONOMOUS_vehicle_mass_ro_toS(_m->vehicle_mass_phys);
  _m->pitch_ro = (uint8_t) AUTONOMOUS_pitch_ro_toS(_m->pitch_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->esp_lateral_acceleration_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( (_m->esp_longitudinal_acceleration_ro & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->esp_longitudinal_acceleration_ro >> 8U) & (0x03U)) );
  cframe->Data[3] |= (uint8_t) ( (_m->esp_yaw_rate_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->esp_yaw_rate_ro >> 8U) & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->vehicle_mass_ro & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->pitch_ro & (0xFFU)) );

  cframe->MsgId = (uint32_t) DYNAMIC_SENSOR_FRAME_CANID;
  cframe->DLC = (uint8_t) DYNAMIC_SENSOR_FRAME_DLC;
  cframe->IDE = (uint8_t) DYNAMIC_SENSOR_FRAME_IDE;
  return DYNAMIC_SENSOR_FRAME_CANID;
}

#else

uint32_t Pack_DYNAMIC_SENSOR_FRAME_autonomous(DYNAMIC_SENSOR_FRAME_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(DYNAMIC_SENSOR_FRAME_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->esp_lateral_acceleration_ro = (uint8_t) AUTONOMOUS_esp_lateral_acceleration_ro_toS(_m->esp_lateral_acceleration_phys);
    _m->esp_longitudinal_acceleration_ro = (uint16_t) AUTONOMOUS_esp_longitudinal_acceleration_ro_toS(_m->esp_longitudinal_acceleration_phys);
    _m->esp_yaw_rate_ro = (int16_t) AUTONOMOUS_esp_yaw_rate_ro_toS(_m->esp_yaw_rate_phys);
    _m->vehicle_mass_ro = (uint8_t) AUTONOMOUS_vehicle_mass_ro_toS(_m->vehicle_mass_phys);
    _m->pitch_ro = (uint8_t) AUTONOMOUS_pitch_ro_toS(_m->pitch_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _d[0] |= (uint8_t) ((_m->esp_lateral_acceleration_ro & (0xFFU)));
    _d[1] |= (uint8_t) ((_m->esp_longitudinal_acceleration_ro & (0xFFU)));
    _d[2] |= (uint8_t) (((_m->esp_longitudinal_acceleration_ro >> 8U) & (0x03U)));
    _d[3] |= (uint8_t) ((_m->esp_yaw_rate_ro & (0xFFU)));
    _d[4] |= (uint8_t) (((_m->esp_yaw_rate_ro >> 8U) & (0xFFU)));
    _d[5] |= (uint8_t) ((_m->vehicle_mass_ro & (0xFFU)));
    _d[6] |= (uint8_t) ((_m->pitch_ro & (0xFFU)));

    *_len = (uint8_t) DYNAMIC_SENSOR_FRAME_DLC;
    *_ide = (uint8_t) DYNAMIC_SENSOR_FRAME_IDE;
    return DYNAMIC_SENSOR_FRAME_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_CONTROL_MECHANISM_VOLTS_autonomous(CONTROL_MECHANISM_VOLTS_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;
    _m->ecu_kl30_protectd_voltage_ro = (uint8_t) ((_d[0] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->ecu_kl30_protectd_voltage_phys = (sigfloat_t) (AUTONOMOUS_ecu_kl30_protectd_voltage_ro_fromS(_m->ecu_kl30_protectd_voltage_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->ecu_kl30_2_protectd_voltage_ro = (uint8_t) ((_d[1] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->ecu_kl30_2_protectd_voltage_phys = (sigfloat_t) (AUTONOMOUS_ecu_kl30_2_protectd_voltage_ro_fromS(_m->ecu_kl30_2_protectd_voltage_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->ecu_5v8_fb_voltage_ro = (uint8_t) ((_d[2] & (0x3FU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->ecu_5v8_fb_voltage_phys = (sigfloat_t) (AUTONOMOUS_ecu_5v8_fb_voltage_ro_fromS(_m->ecu_5v8_fb_voltage_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->ecu_5v_fb_voltage_ro = (uint8_t) (((_d[3] & (0x0FU)) << 2U) | ((_d[2] >> 6U) & (0x03U)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->ecu_5v_fb_voltage_phys = (sigfloat_t) (AUTONOMOUS_ecu_5v_fb_voltage_ro_fromS(_m->ecu_5v_fb_voltage_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->ecu_5v_supply_0_voltage_ro = (uint8_t) (((_d[4] & (0x03U)) << 4U) | ((_d[3] >> 4U) & (0x0FU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->ecu_5v_supply_0_voltage_phys = (sigfloat_t) (AUTONOMOUS_ecu_5v_supply_0_voltage_ro_fromS(_m->ecu_5v_supply_0_voltage_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->ecu_5v_supply_1_voltage_ro = (uint8_t) (((_d[4] >> 2U) & (0x3FU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->ecu_5v_supply_1_voltage_phys = (sigfloat_t) (AUTONOMOUS_ecu_5v_supply_1_voltage_ro_fromS(_m->ecu_5v_supply_1_voltage_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->ecu_5v_supply_2_voltage_ro = (uint8_t) ((_d[5] & (0x3FU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->ecu_5v_supply_2_voltage_phys = (sigfloat_t) (AUTONOMOUS_ecu_5v_supply_2_voltage_ro_fromS(_m->ecu_5v_supply_2_voltage_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->ecu_5v_supply_3_voltage_ro = (uint8_t) (((_d[6] & (0x0FU)) << 2U) | ((_d[5] >> 6U) & (0x03U)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->ecu_5v_supply_3_voltage_phys = (sigfloat_t) (AUTONOMOUS_ecu_5v_supply_3_voltage_ro_fromS(_m->ecu_5v_supply_3_voltage_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->ecu_5v_supply_4_voltage_ro = (uint8_t) (((_d[7] & (0x03U)) << 4U) | ((_d[6] >> 4U) & (0x0FU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->ecu_5v_supply_4_voltage_phys = (sigfloat_t) (AUTONOMOUS_ecu_5v_supply_4_voltage_ro_fromS(_m->ecu_5v_supply_4_voltage_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->reserved = (uint8_t) (((_d[7] >> 2U) & (0x3FU)));

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CONTROL_MECHANISM_VOLTS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CONTROL_MECHANISM_VOLTS_autonomous(&_m->mon1, CONTROL_MECHANISM_VOLTS_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return CONTROL_MECHANISM_VOLTS_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_CONTROL_MECHANISM_VOLTS_autonomous(CONTROL_MECHANISM_VOLTS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(CONTROL_MECHANISM_VOLTS_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

#ifdef AUTONOMOUS_USE_SIGFLOAT
  _m->ecu_kl30_protectd_voltage_ro = (uint8_t) AUTONOMOUS_ecu_kl30_protectd_voltage_ro_toS(_m->ecu_kl30_protectd_voltage_phys);
  _m->ecu_kl30_2_protectd_voltage_ro = (uint8_t) AUTONOMOUS_ecu_kl30_2_protectd_voltage_ro_toS(_m->ecu_kl30_2_protectd_voltage_phys);
  _m->ecu_5v8_fb_voltage_ro = (uint8_t) AUTONOMOUS_ecu_5v8_fb_voltage_ro_toS(_m->ecu_5v8_fb_voltage_phys);
  _m->ecu_5v_fb_voltage_ro = (uint8_t) AUTONOMOUS_ecu_5v_fb_voltage_ro_toS(_m->ecu_5v_fb_voltage_phys);
  _m->ecu_5v_supply_0_voltage_ro = (uint8_t) AUTONOMOUS_ecu_5v_supply_0_voltage_ro_toS(_m->ecu_5v_supply_0_voltage_phys);
  _m->ecu_5v_supply_1_voltage_ro = (uint8_t) AUTONOMOUS_ecu_5v_supply_1_voltage_ro_toS(_m->ecu_5v_supply_1_voltage_phys);
  _m->ecu_5v_supply_2_voltage_ro = (uint8_t) AUTONOMOUS_ecu_5v_supply_2_voltage_ro_toS(_m->ecu_5v_supply_2_voltage_phys);
  _m->ecu_5v_supply_3_voltage_ro = (uint8_t) AUTONOMOUS_ecu_5v_supply_3_voltage_ro_toS(_m->ecu_5v_supply_3_voltage_phys);
  _m->ecu_5v_supply_4_voltage_ro = (uint8_t) AUTONOMOUS_ecu_5v_supply_4_voltage_ro_toS(_m->ecu_5v_supply_4_voltage_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->ecu_kl30_protectd_voltage_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( (_m->ecu_kl30_2_protectd_voltage_ro & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->ecu_5v8_fb_voltage_ro & (0x3FU)) | ((_m->ecu_5v_fb_voltage_ro & (0x03U)) << 6U) );
  cframe->Data[3] |= (uint8_t) ( ((_m->ecu_5v_fb_voltage_ro >> 2U) & (0x0FU)) | ((_m->ecu_5v_supply_0_voltage_ro & (0x0FU)) << 4U) );
  cframe->Data[4] |= (uint8_t) ( ((_m->ecu_5v_supply_0_voltage_ro >> 4U) & (0x03U)) | ((_m->ecu_5v_supply_1_voltage_ro & (0x3FU)) << 2U) );
  cframe->Data[5] |= (uint8_t) ( (_m->ecu_5v_supply_2_voltage_ro & (0x3FU)) | ((_m->ecu_5v_supply_3_voltage_ro & (0x03U)) << 6U) );
  cframe->Data[6] |= (uint8_t) ( ((_m->ecu_5v_supply_3_voltage_ro >> 2U) & (0x0FU)) | ((_m->ecu_5v_supply_4_voltage_ro & (0x0FU)) << 4U) );
  cframe->Data[7] |= (uint8_t) ( ((_m->ecu_5v_supply_4_voltage_ro >> 4U) & (0x03U)) | ((_m->reserved & (0x3FU)) << 2U) );

  cframe->MsgId = (uint32_t) CONTROL_MECHANISM_VOLTS_CANID;
  cframe->DLC = (uint8_t) CONTROL_MECHANISM_VOLTS_DLC;
  cframe->IDE = (uint8_t) CONTROL_MECHANISM_VOLTS_IDE;
  return CONTROL_MECHANISM_VOLTS_CANID;
}

#else

uint32_t Pack_CONTROL_MECHANISM_VOLTS_autonomous(CONTROL_MECHANISM_VOLTS_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(CONTROL_MECHANISM_VOLTS_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->ecu_kl30_protectd_voltage_ro = (uint8_t) AUTONOMOUS_ecu_kl30_protectd_voltage_ro_toS(_m->ecu_kl30_protectd_voltage_phys);
    _m->ecu_kl30_2_protectd_voltage_ro = (uint8_t) AUTONOMOUS_ecu_kl30_2_protectd_voltage_ro_toS(_m->ecu_kl30_2_protectd_voltage_phys);
    _m->ecu_5v8_fb_voltage_ro = (uint8_t) AUTONOMOUS_ecu_5v8_fb_voltage_ro_toS(_m->ecu_5v8_fb_voltage_phys);
    _m->ecu_5v_fb_voltage_ro = (uint8_t) AUTONOMOUS_ecu_5v_fb_voltage_ro_toS(_m->ecu_5v_fb_voltage_phys);
    _m->ecu_5v_supply_0_voltage_ro = (uint8_t) AUTONOMOUS_ecu_5v_supply_0_voltage_ro_toS(_m->ecu_5v_supply_0_voltage_phys);
    _m->ecu_5v_supply_1_voltage_ro = (uint8_t) AUTONOMOUS_ecu_5v_supply_1_voltage_ro_toS(_m->ecu_5v_supply_1_voltage_phys);
    _m->ecu_5v_supply_2_voltage_ro = (uint8_t) AUTONOMOUS_ecu_5v_supply_2_voltage_ro_toS(_m->ecu_5v_supply_2_voltage_phys);
    _m->ecu_5v_supply_3_voltage_ro = (uint8_t) AUTONOMOUS_ecu_5v_supply_3_voltage_ro_toS(_m->ecu_5v_supply_3_voltage_phys);
    _m->ecu_5v_supply_4_voltage_ro = (uint8_t) AUTONOMOUS_ecu_5v_supply_4_voltage_ro_toS(_m->ecu_5v_supply_4_voltage_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _d[0] |= (uint8_t) ((_m->ecu_kl30_protectd_voltage_ro & (0xFFU)));
    _d[1] |= (uint8_t) ((_m->ecu_kl30_2_protectd_voltage_ro & (0xFFU)));
    _d[2] |= (uint8_t) ((_m->ecu_5v8_fb_voltage_ro & (0x3FU)) | ((_m->ecu_5v_fb_voltage_ro & (0x03U)) << 6U));
    _d[3] |= (uint8_t) (((_m->ecu_5v_fb_voltage_ro >> 2U) & (0x0FU)) | ((_m->ecu_5v_supply_0_voltage_ro & (0x0FU)) << 4U));
    _d[4] |= (uint8_t) (((_m->ecu_5v_supply_0_voltage_ro >> 4U) & (0x03U)) | ((_m->ecu_5v_supply_1_voltage_ro & (0x3FU)) << 2U));
    _d[5] |= (uint8_t) ((_m->ecu_5v_supply_2_voltage_ro & (0x3FU)) | ((_m->ecu_5v_supply_3_voltage_ro & (0x03U)) << 6U));
    _d[6] |= (uint8_t) (((_m->ecu_5v_supply_3_voltage_ro >> 2U) & (0x0FU)) | ((_m->ecu_5v_supply_4_voltage_ro & (0x0FU)) << 4U));
    _d[7] |= (uint8_t) (((_m->ecu_5v_supply_4_voltage_ro >> 4U) & (0x03U)) | ((_m->reserved & (0x3FU)) << 2U));

    *_len = (uint8_t) CONTROL_MECHANISM_VOLTS_DLC;
    *_ide = (uint8_t) CONTROL_MECHANISM_VOLTS_IDE;
    return CONTROL_MECHANISM_VOLTS_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_CONTROL_MECHANISM_TEMPS_autonomous(CONTROL_MECHANISM_TEMPS_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;
    _m->pcb_temp_0 = (int8_t) __ext_sig__(((_d[0] & (0xFFU))), 8);
    _m->pcb_temp_1 = (int8_t) __ext_sig__(((_d[1] & (0xFFU))), 8);
    _m->reserved = (uint64_t) (((uint64_t) (_d[7] & (0xFFU)) << 40U) | ((uint64_t) (_d[6] & (0xFFU)) << 32U) | ((_d[5] & (0xFFU)) << 24U)
            | ((_d[4] & (0xFFU)) << 16U) | ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)));

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CONTROL_MECHANISM_TEMPS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CONTROL_MECHANISM_TEMPS_autonomous(&_m->mon1, CONTROL_MECHANISM_TEMPS_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return CONTROL_MECHANISM_TEMPS_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_CONTROL_MECHANISM_TEMPS_autonomous(CONTROL_MECHANISM_TEMPS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(CONTROL_MECHANISM_TEMPS_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->pcb_temp_0 & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( (_m->pcb_temp_1 & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->reserved & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->reserved >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->reserved >> 16U) & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->reserved >> 24U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( ((_m->reserved >> 32U) & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->reserved >> 40U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) CONTROL_MECHANISM_TEMPS_CANID;
  cframe->DLC = (uint8_t) CONTROL_MECHANISM_TEMPS_DLC;
  cframe->IDE = (uint8_t) CONTROL_MECHANISM_TEMPS_IDE;
  return CONTROL_MECHANISM_TEMPS_CANID;
}

#else

uint32_t Pack_CONTROL_MECHANISM_TEMPS_autonomous(CONTROL_MECHANISM_TEMPS_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(CONTROL_MECHANISM_TEMPS_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

    _d[0] |= (uint8_t) ((_m->pcb_temp_0 & (0xFFU)));
    _d[1] |= (uint8_t) ((_m->pcb_temp_1 & (0xFFU)));
    _d[2] |= (uint8_t) ((_m->reserved & (0xFFU)));
    _d[3] |= (uint8_t) (((_m->reserved >> 8U) & (0xFFU)));
    _d[4] |= (uint8_t) (((_m->reserved >> 16U) & (0xFFU)));
    _d[5] |= (uint8_t) (((_m->reserved >> 24U) & (0xFFU)));
    _d[6] |= (uint8_t) (((_m->reserved >> 32U) & (0xFFU)));
    _d[7] |= (uint8_t) (((_m->reserved >> 40U) & (0xFFU)));

    *_len = (uint8_t) CONTROL_MECHANISM_TEMPS_DLC;
    *_ide = (uint8_t) CONTROL_MECHANISM_TEMPS_IDE;
    return CONTROL_MECHANISM_TEMPS_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_THROTTLE_MODULE_STATUS_autonomous(THROTTLE_MODULE_STATUS_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;
    _m->status = (uint8_t) ((_d[0] & (0x01U)));
    _m->reserved = (uint8_t) (((_d[0] >> 1U) & (0x7FU)));
    _m->target_throttle = (uint8_t) ((_d[1] & (0xFFU)));
    _m->current_throttle = (uint8_t) ((_d[2] & (0xFFU)));
    _m->dac_voltage_1_ro = (uint8_t) ((_d[3] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->dac_voltage_1_phys = (sigfloat_t) (AUTONOMOUS_dac_voltage_1_ro_fromS(_m->dac_voltage_1_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->dac_voltage_2_ro = (uint8_t) ((_d[4] & (0xFFU)));
#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->dac_voltage_2_phys = (sigfloat_t) (AUTONOMOUS_dac_voltage_2_ro_fromS(_m->dac_voltage_2_ro));
#endif // AUTONOMOUS_USE_SIGFLOAT

    _m->fb_current = (uint8_t) ((_d[5] & (0xFFU)));

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < THROTTLE_MODULE_STATUS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_THROTTLE_MODULE_STATUS_autonomous(&_m->mon1, THROTTLE_MODULE_STATUS_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return THROTTLE_MODULE_STATUS_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_THROTTLE_MODULE_STATUS_autonomous(THROTTLE_MODULE_STATUS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(THROTTLE_MODULE_STATUS_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

#ifdef AUTONOMOUS_USE_SIGFLOAT
  _m->dac_voltage_1_ro = (uint8_t) AUTONOMOUS_dac_voltage_1_ro_toS(_m->dac_voltage_1_phys);
  _m->dac_voltage_2_ro = (uint8_t) AUTONOMOUS_dac_voltage_2_ro_toS(_m->dac_voltage_2_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->status & (0x01U)) | ((_m->reserved & (0x7FU)) << 1U) );
  cframe->Data[1] |= (uint8_t) ( (_m->target_throttle & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->current_throttle & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->dac_voltage_1_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->dac_voltage_2_ro & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->fb_current & (0xFFU)) );

  cframe->MsgId = (uint32_t) THROTTLE_MODULE_STATUS_CANID;
  cframe->DLC = (uint8_t) THROTTLE_MODULE_STATUS_DLC;
  cframe->IDE = (uint8_t) THROTTLE_MODULE_STATUS_IDE;
  return THROTTLE_MODULE_STATUS_CANID;
}

#else

uint32_t Pack_THROTTLE_MODULE_STATUS_autonomous(THROTTLE_MODULE_STATUS_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(THROTTLE_MODULE_STATUS_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

#ifdef AUTONOMOUS_USE_SIGFLOAT
    _m->dac_voltage_1_ro = (uint8_t) AUTONOMOUS_dac_voltage_1_ro_toS(_m->dac_voltage_1_phys);
    _m->dac_voltage_2_ro = (uint8_t) AUTONOMOUS_dac_voltage_2_ro_toS(_m->dac_voltage_2_phys);
#endif // AUTONOMOUS_USE_SIGFLOAT

    _d[0] |= (uint8_t) ((_m->status & (0x01U)) | ((_m->reserved & (0x7FU)) << 1U));
    _d[1] |= (uint8_t) ((_m->target_throttle & (0xFFU)));
    _d[2] |= (uint8_t) ((_m->current_throttle & (0xFFU)));
    _d[3] |= (uint8_t) ((_m->dac_voltage_1_ro & (0xFFU)));
    _d[4] |= (uint8_t) ((_m->dac_voltage_2_ro & (0xFFU)));
    _d[5] |= (uint8_t) ((_m->fb_current & (0xFFU)));

    *_len = (uint8_t) THROTTLE_MODULE_STATUS_DLC;
    *_ide = (uint8_t) THROTTLE_MODULE_STATUS_IDE;
    return THROTTLE_MODULE_STATUS_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_LONGITUDINAL_COMMANDS_autonomous(LONGITUDINAL_COMMANDS_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;

    typedef union  {
        float value;
        uint8_t bytes[sizeof(sigfloat_t)];
    }FloatConverter;

    FloatConverter converter;
    for ( size_t i = 0 ; i < sizeof(sigfloat_t) ; i++ ) {
        converter.bytes[i] = _d[i];
    }
    _m->set_velocity = converter.value;

    for ( size_t i = 0 ; i < sizeof(sigfloat_t) ; i++ ) {
        converter.bytes[i] = _d[i + 4];
    }
    _m->set_limit_velocity = converter.value;

//    _m->set_velocity =
//            (int32_t) __ext_sig__((((_d[3] & (0xFFU)) << 24U) | ((_d[2] & (0xFFU)) << 16U) | ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU))), 32);
//    _m->set_limit_velocity = (int32_t) __ext_sig__((((_d[7] & (0xFFU)) << 24U) | ((_d[6] & (0xFFU)) << 16U) | ((_d[5] & (0xFFU)) << 8U)
//            | (_d[4] & (0xFFU))), 32);

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < LONGITUDINAL_COMMANDS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_LONGITUDINAL_COMMANDS_autonomous(&_m->mon1, LONGITUDINAL_COMMANDS_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return LONGITUDINAL_COMMANDS_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_LONGITUDINAL_COMMANDS_autonomous(LONGITUDINAL_COMMANDS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(LONGITUDINAL_COMMANDS_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->set_velocity & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->set_velocity >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->set_velocity >> 16U) & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->set_velocity >> 24U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->set_limit_velocity & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->set_limit_velocity >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( ((_m->set_limit_velocity >> 16U) & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->set_limit_velocity >> 24U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) LONGITUDINAL_COMMANDS_CANID;
  cframe->DLC = (uint8_t) LONGITUDINAL_COMMANDS_DLC;
  cframe->IDE = (uint8_t) LONGITUDINAL_COMMANDS_IDE;
  return LONGITUDINAL_COMMANDS_CANID;
}

#else

uint32_t Pack_LONGITUDINAL_COMMANDS_autonomous(LONGITUDINAL_COMMANDS_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(LONGITUDINAL_COMMANDS_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

    typedef union  {
        float value;
        uint8_t bytes[sizeof(sigfloat_t)];
    }FloatConverter;

    FloatConverter converter;


    converter.value = _m->set_velocity;
    for ( size_t i = 0 ; i < sizeof(sigfloat_t) ; i++ ) {
        _d[i] = converter.bytes[i];
    }

    converter.value = _m->set_limit_velocity;
    for ( size_t i = 0 ; i < sizeof(sigfloat_t) ; i++ ) {
        _d[i + 4] = converter.bytes[i];
    }

//    _d[0] |= (uint8_t) ((_m->set_velocity & (0xFFU)));
//    _d[1] |= (uint8_t) (((_m->set_velocity >> 8U) & (0xFFU)));
//    _d[2] |= (uint8_t) (((_m->set_velocity >> 16U) & (0xFFU)));
//    _d[3] |= (uint8_t) (((_m->set_velocity >> 24U) & (0xFFU)));
//    _d[4] |= (uint8_t) ((_m->set_limit_velocity & (0xFFU)));
//    _d[5] |= (uint8_t) (((_m->set_limit_velocity >> 8U) & (0xFFU)));
//    _d[6] |= (uint8_t) (((_m->set_limit_velocity >> 16U) & (0xFFU)));
//    _d[7] |= (uint8_t) (((_m->set_limit_velocity >> 24U) & (0xFFU)));

    *_len = (uint8_t) LONGITUDINAL_COMMANDS_DLC;
    *_ide = (uint8_t) LONGITUDINAL_COMMANDS_IDE;
    return LONGITUDINAL_COMMANDS_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_COMMANDS_autonomous(VEHICLE_COMMANDS_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;
    _m->set_autonomous = (uint8_t) ((_d[0] & (0x01U)));
    _m->blinker = (uint8_t) (((_d[1] & (0x01U)) << 7U) | ((_d[0] >> 1U) & (0x7FU)));
    _m->headlgiht = (uint8_t) ((_d[1] & (0xFFU)));
    _m->gear = (uint8_t) ((_d[2] & (0xFFU)));
    _m->hand_brake = (uint8_t) ((_d[3] & (0xFFU)));
    _m->emergency_request = (uint8_t) ((_d[4] & (0xFFU)));
    _m->reserved = (uint32_t) (((_d[7] & (0xFFU)) << 16U) | ((_d[6] & (0xFFU)) << 8U) | (_d[5] & (0xFFU)));

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEHICLE_COMMANDS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEHICLE_COMMANDS_autonomous(&_m->mon1, VEHICLE_COMMANDS_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return VEHICLE_COMMANDS_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_VEHICLE_COMMANDS_autonomous(VEHICLE_COMMANDS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(VEHICLE_COMMANDS_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->set_autonomous & (0x01U)) | ((_m->blinker & (0x7FU)) << 1U) );
  cframe->Data[1] |= (uint8_t) ( ((_m->blinker >> 7U) & (0x01U)) | (_m->headlgiht & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->gear & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->hand_brake & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->emergency_request & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->reserved & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( ((_m->reserved >> 8U) & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->reserved >> 16U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEHICLE_COMMANDS_CANID;
  cframe->DLC = (uint8_t) VEHICLE_COMMANDS_DLC;
  cframe->IDE = (uint8_t) VEHICLE_COMMANDS_IDE;
  return VEHICLE_COMMANDS_CANID;
}

#else

uint32_t Pack_VEHICLE_COMMANDS_autonomous(VEHICLE_COMMANDS_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(VEHICLE_COMMANDS_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

    _d[0] |= (uint8_t) ((_m->set_autonomous & (0x01U)) | ((_m->blinker & (0x7FU)) << 1U));
    _d[1] |= (uint8_t) (((_m->blinker >> 7U) & (0x01U)) | (_m->headlgiht & (0xFFU)));
    _d[2] |= (uint8_t) ((_m->gear & (0xFFU)));
    _d[3] |= (uint8_t) ((_m->hand_brake & (0xFFU)));
    _d[4] |= (uint8_t) ((_m->emergency_request & (0xFFU)));
    _d[5] |= (uint8_t) ((_m->reserved & (0xFFU)));
    _d[6] |= (uint8_t) (((_m->reserved >> 8U) & (0xFFU)));
    _d[7] |= (uint8_t) (((_m->reserved >> 16U) & (0xFFU)));

    *_len = (uint8_t) VEHICLE_COMMANDS_DLC;
    *_ide = (uint8_t) VEHICLE_COMMANDS_IDE;
    return VEHICLE_COMMANDS_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

uint32_t Unpack_FRONT_WHEEL_COMMANDS_autonomous(FRONT_WHEEL_COMMANDS_t *_m, const uint8_t *_d, uint8_t dlc_) {
    (void) dlc_;

    typedef union  {
        float value;
        uint8_t bytes[sizeof(sigfloat_t)];
    }FloatConverter;

    FloatConverter converter;
    for ( size_t i = 0 ; i < sizeof(sigfloat_t) ; i++ ) {
        converter.bytes[i] = _d[i];
    }
    _m->set_front_wheel_tire_angle = converter.value;

    for ( size_t i = 0 ; i < sizeof(sigfloat_t) ; i++ ) {
        converter.bytes[i] = _d[i + 4];
    }
    _m->set_front_wheel_angle_rate = converter.value;

//    _m->set_front_wheel_tire_angle = (int32_t) __ext_sig__((((_d[3] & (0xFFU)) << 24U) | ((_d[2] & (0xFFU)) << 16U) | ((_d[1] & (0xFFU)) << 8U)
//            | (_d[0] & (0xFFU))), 32);
//    _m->set_front_wheel_angle_rate = (int32_t) __ext_sig__((((_d[7] & (0xFFU)) << 24U) | ((_d[6] & (0xFFU)) << 16U) | ((_d[5] & (0xFFU)) << 8U)
//            | (_d[4] & (0xFFU))), 32);

#ifdef AUTONOMOUS_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < FRONT_WHEEL_COMMANDS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_FRONT_WHEEL_COMMANDS_autonomous(&_m->mon1, FRONT_WHEEL_COMMANDS_CANID);
#endif // AUTONOMOUS_USE_DIAG_MONITORS

    return FRONT_WHEEL_COMMANDS_CANID;
}

#ifdef AUTONOMOUS_USE_CANSTRUCT

uint32_t Pack_FRONT_WHEEL_COMMANDS_autonomous(FRONT_WHEEL_COMMANDS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < AUTONOMOUS_VALIDATE_DLC(FRONT_WHEEL_COMMANDS_DLC); cframe->Data[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->set_front_wheel_tire_angle & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->set_front_wheel_tire_angle >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->set_front_wheel_tire_angle >> 16U) & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->set_front_wheel_tire_angle >> 24U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->set_front_wheel_angle_rate & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->set_front_wheel_angle_rate >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( ((_m->set_front_wheel_angle_rate >> 16U) & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->set_front_wheel_angle_rate >> 24U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) FRONT_WHEEL_COMMANDS_CANID;
  cframe->DLC = (uint8_t) FRONT_WHEEL_COMMANDS_DLC;
  cframe->IDE = (uint8_t) FRONT_WHEEL_COMMANDS_IDE;
  return FRONT_WHEEL_COMMANDS_CANID;
}

#else

uint32_t Pack_FRONT_WHEEL_COMMANDS_autonomous(FRONT_WHEEL_COMMANDS_t *_m, uint8_t *_d, uint8_t *_len, uint8_t *_ide) {
    uint8_t i;
    for ( i = 0u ; i < AUTONOMOUS_VALIDATE_DLC(FRONT_WHEEL_COMMANDS_DLC) ; _d[i++] = AUTONOMOUS_INITIAL_BYTE_VALUE )
        ;

    typedef union  {
        float value;
        uint8_t bytes[sizeof(sigfloat_t)];
    }FloatConverter;

    FloatConverter converter;


    converter.value = _m->set_front_wheel_tire_angle;
    for ( size_t i = 0 ; i < sizeof(sigfloat_t) ; i++ ) {
        _d[i] = converter.bytes[i];
    }

    converter.value = _m->set_front_wheel_angle_rate;
    for ( size_t i = 0 ; i < sizeof(sigfloat_t) ; i++ ) {
        _d[i + 4] = converter.bytes[i];
    }

//    _d[0] |= (uint8_t) ((_m->set_front_wheel_tire_angle & (0xFFU)));
//    _d[1] |= (uint8_t) (((_m->set_front_wheel_tire_angle >> 8U) & (0xFFU)));
//    _d[2] |= (uint8_t) (((_m->set_front_wheel_tire_angle >> 16U) & (0xFFU)));
//    _d[3] |= (uint8_t) (((_m->set_front_wheel_tire_angle >> 24U) & (0xFFU)));
//    _d[4] |= (uint8_t) ((_m->set_front_wheel_angle_rate & (0xFFU)));
//    _d[5] |= (uint8_t) (((_m->set_front_wheel_angle_rate >> 8U) & (0xFFU)));
//    _d[6] |= (uint8_t) (((_m->set_front_wheel_angle_rate >> 16U) & (0xFFU)));
//    _d[7] |= (uint8_t) (((_m->set_front_wheel_angle_rate >> 24U) & (0xFFU)));

    *_len = (uint8_t) FRONT_WHEEL_COMMANDS_DLC;
    *_ide = (uint8_t) FRONT_WHEEL_COMMANDS_IDE;
    return FRONT_WHEEL_COMMANDS_CANID;
}

#endif // AUTONOMOUS_USE_CANSTRUCT

