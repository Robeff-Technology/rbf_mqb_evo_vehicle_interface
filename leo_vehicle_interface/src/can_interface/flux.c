// Generator version : v3.1
// DBC filename      : flux_pds.dbc
#include "flux.h"


// DBC file version
#if (VER_FLUX_MAJ != (0U)) || (VER_FLUX_MIN != (0U))
#error The FLUX dbc source files have different versions
#endif

#ifdef FLUX_USE_DIAG_MONITORS
// Function prototypes to be called each time CAN frame is unpacked
// FMon function may detect RC, CRC or DLC violation
#include "flux-fmon.h"

#endif // FLUX_USE_DIAG_MONITORS

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

uint32_t Unpack_CHANNEL_STATUS_MSG_flux(CHANNEL_STATUS_MSG_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ch1_stat = (uint8_t) ( (_d[2] & (0x0FU)) );
  _m->ch2_stat = (uint8_t) ( ((_d[2] >> 4U) & (0x0FU)) );
  _m->ch3_stat = (uint8_t) ( (_d[3] & (0x0FU)) );
  _m->ch4_stat = (uint8_t) ( ((_d[3] >> 4U) & (0x0FU)) );
  _m->ch5_stat = (uint8_t) ( (_d[4] & (0x0FU)) );
  _m->ch6_stat = (uint8_t) ( ((_d[4] >> 4U) & (0x0FU)) );
  _m->ch7_stat = (uint8_t) ( (_d[5] & (0x0FU)) );
  _m->ch8_stat = (uint8_t) ( ((_d[5] >> 4U) & (0x0FU)) );
  _m->ch9_stat = (uint8_t) ( (_d[6] & (0x0FU)) );
  _m->ch10_stat = (uint8_t) ( ((_d[6] >> 4U) & (0x0FU)) );
  _m->ch11_stat = (uint8_t) ( (_d[7] & (0x0FU)) );
  _m->ch12_stat = (uint8_t) ( ((_d[7] >> 4U) & (0x0FU)) );

#ifdef FLUX_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CHANNEL_STATUS_MSG_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CHANNEL_STATUS_MSG_flux(&_m->mon1, CHANNEL_STATUS_MSG_CANID);
#endif // FLUX_USE_DIAG_MONITORS

  return CHANNEL_STATUS_MSG_CANID;
}

#ifdef FLUX_USE_CANSTRUCT

uint32_t Pack_CHANNEL_STATUS_MSG_flux(CHANNEL_STATUS_MSG_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(CHANNEL_STATUS_MSG_DLC); cframe->Data[i++] = FLUX_INITIAL_BYTE_VALUE);

  cframe->Data[2] |= (uint8_t) ( (_m->ch1_stat & (0x0FU)) | ((_m->ch2_stat & (0x0FU)) << 4U) );
  cframe->Data[3] |= (uint8_t) ( (_m->ch3_stat & (0x0FU)) | ((_m->ch4_stat & (0x0FU)) << 4U) );
  cframe->Data[4] |= (uint8_t) ( (_m->ch5_stat & (0x0FU)) | ((_m->ch6_stat & (0x0FU)) << 4U) );
  cframe->Data[5] |= (uint8_t) ( (_m->ch7_stat & (0x0FU)) | ((_m->ch8_stat & (0x0FU)) << 4U) );
  cframe->Data[6] |= (uint8_t) ( (_m->ch9_stat & (0x0FU)) | ((_m->ch10_stat & (0x0FU)) << 4U) );
  cframe->Data[7] |= (uint8_t) ( (_m->ch11_stat & (0x0FU)) | ((_m->ch12_stat & (0x0FU)) << 4U) );

  cframe->MsgId = (uint32_t) CHANNEL_STATUS_MSG_CANID;
  cframe->DLC = (uint8_t) CHANNEL_STATUS_MSG_DLC;
  cframe->IDE = (uint8_t) CHANNEL_STATUS_MSG_IDE;
  return CHANNEL_STATUS_MSG_CANID;
}

#else

uint32_t Pack_CHANNEL_STATUS_MSG_flux(CHANNEL_STATUS_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(CHANNEL_STATUS_MSG_DLC); _d[i++] = FLUX_INITIAL_BYTE_VALUE);

  _d[2] |= (uint8_t) ( (_m->ch1_stat & (0x0FU)) | ((_m->ch2_stat & (0x0FU)) << 4U) );
  _d[3] |= (uint8_t) ( (_m->ch3_stat & (0x0FU)) | ((_m->ch4_stat & (0x0FU)) << 4U) );
  _d[4] |= (uint8_t) ( (_m->ch5_stat & (0x0FU)) | ((_m->ch6_stat & (0x0FU)) << 4U) );
  _d[5] |= (uint8_t) ( (_m->ch7_stat & (0x0FU)) | ((_m->ch8_stat & (0x0FU)) << 4U) );
  _d[6] |= (uint8_t) ( (_m->ch9_stat & (0x0FU)) | ((_m->ch10_stat & (0x0FU)) << 4U) );
  _d[7] |= (uint8_t) ( (_m->ch11_stat & (0x0FU)) | ((_m->ch12_stat & (0x0FU)) << 4U) );

  *_len = (uint8_t) CHANNEL_STATUS_MSG_DLC;
  *_ide = (uint8_t) CHANNEL_STATUS_MSG_IDE;
  return CHANNEL_STATUS_MSG_CANID;
}

#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_CURRENTS_1_MSG_flux(CURRENTS_1_MSG_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ch1_current_ro = (uint16_t) ( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch1_current_phys = (sigfloat_t)(FLUX_ch1_current_ro_fromS(_m->ch1_current_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch2_current_ro = (uint16_t) ( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch2_current_phys = (sigfloat_t)(FLUX_ch2_current_ro_fromS(_m->ch2_current_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch3_current_ro = (uint16_t) ( ((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch3_current_phys = (sigfloat_t)(FLUX_ch3_current_ro_fromS(_m->ch3_current_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch4_current_ro = (uint16_t) ( ((_d[7] & (0xFFU)) << 8U) | (_d[6] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch4_current_phys = (sigfloat_t)(FLUX_ch4_current_ro_fromS(_m->ch4_current_ro));
#endif // FLUX_USE_SIGFLOAT

#ifdef FLUX_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CURRENTS_1_MSG_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CURRENTS_1_MSG_flux(&_m->mon1, CURRENTS_1_MSG_CANID);
#endif // FLUX_USE_DIAG_MONITORS

  return CURRENTS_1_MSG_CANID;
}

#ifdef FLUX_USE_CANSTRUCT

uint32_t Pack_CURRENTS_1_MSG_flux(CURRENTS_1_MSG_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(CURRENTS_1_MSG_DLC); cframe->Data[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->ch1_current_ro = (uint16_t) FLUX_ch1_current_ro_toS(_m->ch1_current_phys);
  _m->ch2_current_ro = (uint16_t) FLUX_ch2_current_ro_toS(_m->ch2_current_phys);
  _m->ch3_current_ro = (uint16_t) FLUX_ch3_current_ro_toS(_m->ch3_current_phys);
  _m->ch4_current_ro = (uint16_t) FLUX_ch4_current_ro_toS(_m->ch4_current_phys);
#endif // FLUX_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->ch1_current_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->ch1_current_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->ch2_current_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->ch2_current_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->ch3_current_ro & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->ch3_current_ro >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->ch4_current_ro & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->ch4_current_ro >> 8U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) CURRENTS_1_MSG_CANID;
  cframe->DLC = (uint8_t) CURRENTS_1_MSG_DLC;
  cframe->IDE = (uint8_t) CURRENTS_1_MSG_IDE;
  return CURRENTS_1_MSG_CANID;
}

#else

uint32_t Pack_CURRENTS_1_MSG_flux(CURRENTS_1_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(CURRENTS_1_MSG_DLC); _d[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->ch1_current_ro = (uint16_t) FLUX_ch1_current_ro_toS(_m->ch1_current_phys);
  _m->ch2_current_ro = (uint16_t) FLUX_ch2_current_ro_toS(_m->ch2_current_phys);
  _m->ch3_current_ro = (uint16_t) FLUX_ch3_current_ro_toS(_m->ch3_current_phys);
  _m->ch4_current_ro = (uint16_t) FLUX_ch4_current_ro_toS(_m->ch4_current_phys);
#endif // FLUX_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->ch1_current_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->ch1_current_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->ch2_current_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->ch2_current_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->ch3_current_ro & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->ch3_current_ro >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->ch4_current_ro & (0xFFU)) );
  _d[7] |= (uint8_t) ( ((_m->ch4_current_ro >> 8U) & (0xFFU)) );

  *_len = (uint8_t) CURRENTS_1_MSG_DLC;
  *_ide = (uint8_t) CURRENTS_1_MSG_IDE;
  return CURRENTS_1_MSG_CANID;
}

#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_CURRENTS_2_MSG_flux(CURRENTS_2_MSG_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ch5_current_ro = (uint16_t) ( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch5_current_phys = (sigfloat_t)(FLUX_ch5_current_ro_fromS(_m->ch5_current_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch6_current_ro = (uint16_t) ( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch6_current_phys = (sigfloat_t)(FLUX_ch6_current_ro_fromS(_m->ch6_current_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch7_current_ro = (uint16_t) ( ((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch7_current_phys = (sigfloat_t)(FLUX_ch7_current_ro_fromS(_m->ch7_current_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch8_current_ro = (uint16_t) ( ((_d[7] & (0xFFU)) << 8U) | (_d[6] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch8_current_phys = (sigfloat_t)(FLUX_ch8_current_ro_fromS(_m->ch8_current_ro));
#endif // FLUX_USE_SIGFLOAT

#ifdef FLUX_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CURRENTS_2_MSG_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CURRENTS_2_MSG_flux(&_m->mon1, CURRENTS_2_MSG_CANID);
#endif // FLUX_USE_DIAG_MONITORS

  return CURRENTS_2_MSG_CANID;
}

#ifdef FLUX_USE_CANSTRUCT

uint32_t Pack_CURRENTS_2_MSG_flux(CURRENTS_2_MSG_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(CURRENTS_2_MSG_DLC); cframe->Data[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->ch5_current_ro = (uint16_t) FLUX_ch5_current_ro_toS(_m->ch5_current_phys);
  _m->ch6_current_ro = (uint16_t) FLUX_ch6_current_ro_toS(_m->ch6_current_phys);
  _m->ch7_current_ro = (uint16_t) FLUX_ch7_current_ro_toS(_m->ch7_current_phys);
  _m->ch8_current_ro = (uint16_t) FLUX_ch8_current_ro_toS(_m->ch8_current_phys);
#endif // FLUX_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->ch5_current_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->ch5_current_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->ch6_current_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->ch6_current_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->ch7_current_ro & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->ch7_current_ro >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->ch8_current_ro & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->ch8_current_ro >> 8U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) CURRENTS_2_MSG_CANID;
  cframe->DLC = (uint8_t) CURRENTS_2_MSG_DLC;
  cframe->IDE = (uint8_t) CURRENTS_2_MSG_IDE;
  return CURRENTS_2_MSG_CANID;
}

#else

uint32_t Pack_CURRENTS_2_MSG_flux(CURRENTS_2_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(CURRENTS_2_MSG_DLC); _d[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->ch5_current_ro = (uint16_t) FLUX_ch5_current_ro_toS(_m->ch5_current_phys);
  _m->ch6_current_ro = (uint16_t) FLUX_ch6_current_ro_toS(_m->ch6_current_phys);
  _m->ch7_current_ro = (uint16_t) FLUX_ch7_current_ro_toS(_m->ch7_current_phys);
  _m->ch8_current_ro = (uint16_t) FLUX_ch8_current_ro_toS(_m->ch8_current_phys);
#endif // FLUX_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->ch5_current_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->ch5_current_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->ch6_current_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->ch6_current_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->ch7_current_ro & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->ch7_current_ro >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->ch8_current_ro & (0xFFU)) );
  _d[7] |= (uint8_t) ( ((_m->ch8_current_ro >> 8U) & (0xFFU)) );

  *_len = (uint8_t) CURRENTS_2_MSG_DLC;
  *_ide = (uint8_t) CURRENTS_2_MSG_IDE;
  return CURRENTS_2_MSG_CANID;
}

#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_CURRENTS_3_MSG_flux(CURRENTS_3_MSG_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ch9_current_ro = (uint16_t) ( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch9_current_phys = (sigfloat_t)(FLUX_ch9_current_ro_fromS(_m->ch9_current_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch10_current_ro = (uint16_t) ( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch10_current_phys = (sigfloat_t)(FLUX_ch10_current_ro_fromS(_m->ch10_current_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch11_current_ro = (uint16_t) ( ((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch11_current_phys = (sigfloat_t)(FLUX_ch11_current_ro_fromS(_m->ch11_current_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch12_current_ro = (uint16_t) ( ((_d[7] & (0xFFU)) << 8U) | (_d[6] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch12_current_phys = (sigfloat_t)(FLUX_ch12_current_ro_fromS(_m->ch12_current_ro));
#endif // FLUX_USE_SIGFLOAT

#ifdef FLUX_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CURRENTS_3_MSG_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CURRENTS_3_MSG_flux(&_m->mon1, CURRENTS_3_MSG_CANID);
#endif // FLUX_USE_DIAG_MONITORS

  return CURRENTS_3_MSG_CANID;
}

#ifdef FLUX_USE_CANSTRUCT

uint32_t Pack_CURRENTS_3_MSG_flux(CURRENTS_3_MSG_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(CURRENTS_3_MSG_DLC); cframe->Data[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->ch9_current_ro = (uint16_t) FLUX_ch9_current_ro_toS(_m->ch9_current_phys);
  _m->ch10_current_ro = (uint16_t) FLUX_ch10_current_ro_toS(_m->ch10_current_phys);
  _m->ch11_current_ro = (uint16_t) FLUX_ch11_current_ro_toS(_m->ch11_current_phys);
  _m->ch12_current_ro = (uint16_t) FLUX_ch12_current_ro_toS(_m->ch12_current_phys);
#endif // FLUX_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->ch9_current_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->ch9_current_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->ch10_current_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->ch10_current_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->ch11_current_ro & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->ch11_current_ro >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->ch12_current_ro & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->ch12_current_ro >> 8U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) CURRENTS_3_MSG_CANID;
  cframe->DLC = (uint8_t) CURRENTS_3_MSG_DLC;
  cframe->IDE = (uint8_t) CURRENTS_3_MSG_IDE;
  return CURRENTS_3_MSG_CANID;
}

#else

uint32_t Pack_CURRENTS_3_MSG_flux(CURRENTS_3_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(CURRENTS_3_MSG_DLC); _d[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->ch9_current_ro = (uint16_t) FLUX_ch9_current_ro_toS(_m->ch9_current_phys);
  _m->ch10_current_ro = (uint16_t) FLUX_ch10_current_ro_toS(_m->ch10_current_phys);
  _m->ch11_current_ro = (uint16_t) FLUX_ch11_current_ro_toS(_m->ch11_current_phys);
  _m->ch12_current_ro = (uint16_t) FLUX_ch12_current_ro_toS(_m->ch12_current_phys);
#endif // FLUX_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->ch9_current_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->ch9_current_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->ch10_current_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->ch10_current_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->ch11_current_ro & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->ch11_current_ro >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->ch12_current_ro & (0xFFU)) );
  _d[7] |= (uint8_t) ( ((_m->ch12_current_ro >> 8U) & (0xFFU)) );

  *_len = (uint8_t) CURRENTS_3_MSG_DLC;
  *_ide = (uint8_t) CURRENTS_3_MSG_IDE;
  return CURRENTS_3_MSG_CANID;
}

#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_CONSUMPTION_1_MSG_flux(CONSUMPTION_1_MSG_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ch1_cons_ro = (uint16_t) ( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch1_cons_phys = (sigfloat_t)(FLUX_ch1_cons_ro_fromS(_m->ch1_cons_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch2_cons_ro = (uint16_t) ( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch2_cons_phys = (sigfloat_t)(FLUX_ch2_cons_ro_fromS(_m->ch2_cons_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch3_cons_ro = (uint16_t) ( ((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch3_cons_phys = (sigfloat_t)(FLUX_ch3_cons_ro_fromS(_m->ch3_cons_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch4_cons_ro = (uint16_t) ( ((_d[7] & (0xFFU)) << 8U) | (_d[6] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch4_cons_phys = (sigfloat_t)(FLUX_ch4_cons_ro_fromS(_m->ch4_cons_ro));
#endif // FLUX_USE_SIGFLOAT

#ifdef FLUX_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CONSUMPTION_1_MSG_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CONSUMPTION_1_MSG_flux(&_m->mon1, CONSUMPTION_1_MSG_CANID);
#endif // FLUX_USE_DIAG_MONITORS

  return CONSUMPTION_1_MSG_CANID;
}

#ifdef FLUX_USE_CANSTRUCT

uint32_t Pack_CONSUMPTION_1_MSG_flux(CONSUMPTION_1_MSG_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(CONSUMPTION_1_MSG_DLC); cframe->Data[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->ch1_cons_ro = (uint16_t) FLUX_ch1_cons_ro_toS(_m->ch1_cons_phys);
  _m->ch2_cons_ro = (uint16_t) FLUX_ch2_cons_ro_toS(_m->ch2_cons_phys);
  _m->ch3_cons_ro = (uint16_t) FLUX_ch3_cons_ro_toS(_m->ch3_cons_phys);
  _m->ch4_cons_ro = (uint16_t) FLUX_ch4_cons_ro_toS(_m->ch4_cons_phys);
#endif // FLUX_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->ch1_cons_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->ch1_cons_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->ch2_cons_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->ch2_cons_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->ch3_cons_ro & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->ch3_cons_ro >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->ch4_cons_ro & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->ch4_cons_ro >> 8U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) CONSUMPTION_1_MSG_CANID;
  cframe->DLC = (uint8_t) CONSUMPTION_1_MSG_DLC;
  cframe->IDE = (uint8_t) CONSUMPTION_1_MSG_IDE;
  return CONSUMPTION_1_MSG_CANID;
}

#else

uint32_t Pack_CONSUMPTION_1_MSG_flux(CONSUMPTION_1_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(CONSUMPTION_1_MSG_DLC); _d[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->ch1_cons_ro = (uint16_t) FLUX_ch1_cons_ro_toS(_m->ch1_cons_phys);
  _m->ch2_cons_ro = (uint16_t) FLUX_ch2_cons_ro_toS(_m->ch2_cons_phys);
  _m->ch3_cons_ro = (uint16_t) FLUX_ch3_cons_ro_toS(_m->ch3_cons_phys);
  _m->ch4_cons_ro = (uint16_t) FLUX_ch4_cons_ro_toS(_m->ch4_cons_phys);
#endif // FLUX_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->ch1_cons_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->ch1_cons_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->ch2_cons_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->ch2_cons_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->ch3_cons_ro & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->ch3_cons_ro >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->ch4_cons_ro & (0xFFU)) );
  _d[7] |= (uint8_t) ( ((_m->ch4_cons_ro >> 8U) & (0xFFU)) );

  *_len = (uint8_t) CONSUMPTION_1_MSG_DLC;
  *_ide = (uint8_t) CONSUMPTION_1_MSG_IDE;
  return CONSUMPTION_1_MSG_CANID;
}

#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_CONSUMPTION_2_MSG_flux(CONSUMPTION_2_MSG_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ch5_cons_ro = (uint16_t) ( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch5_cons_phys = (sigfloat_t)(FLUX_ch5_cons_ro_fromS(_m->ch5_cons_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch6_cons_ro = (uint16_t) ( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch6_cons_phys = (sigfloat_t)(FLUX_ch6_cons_ro_fromS(_m->ch6_cons_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch7_cons_ro = (uint16_t) ( ((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch7_cons_phys = (sigfloat_t)(FLUX_ch7_cons_ro_fromS(_m->ch7_cons_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch8_cons_ro = (uint16_t) ( ((_d[7] & (0xFFU)) << 8U) | (_d[6] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch8_cons_phys = (sigfloat_t)(FLUX_ch8_cons_ro_fromS(_m->ch8_cons_ro));
#endif // FLUX_USE_SIGFLOAT

#ifdef FLUX_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CONSUMPTION_2_MSG_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CONSUMPTION_2_MSG_flux(&_m->mon1, CONSUMPTION_2_MSG_CANID);
#endif // FLUX_USE_DIAG_MONITORS

  return CONSUMPTION_2_MSG_CANID;
}

#ifdef FLUX_USE_CANSTRUCT

uint32_t Pack_CONSUMPTION_2_MSG_flux(CONSUMPTION_2_MSG_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(CONSUMPTION_2_MSG_DLC); cframe->Data[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->ch5_cons_ro = (uint16_t) FLUX_ch5_cons_ro_toS(_m->ch5_cons_phys);
  _m->ch6_cons_ro = (uint16_t) FLUX_ch6_cons_ro_toS(_m->ch6_cons_phys);
  _m->ch7_cons_ro = (uint16_t) FLUX_ch7_cons_ro_toS(_m->ch7_cons_phys);
  _m->ch8_cons_ro = (uint16_t) FLUX_ch8_cons_ro_toS(_m->ch8_cons_phys);
#endif // FLUX_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->ch5_cons_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->ch5_cons_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->ch6_cons_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->ch6_cons_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->ch7_cons_ro & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->ch7_cons_ro >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->ch8_cons_ro & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->ch8_cons_ro >> 8U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) CONSUMPTION_2_MSG_CANID;
  cframe->DLC = (uint8_t) CONSUMPTION_2_MSG_DLC;
  cframe->IDE = (uint8_t) CONSUMPTION_2_MSG_IDE;
  return CONSUMPTION_2_MSG_CANID;
}

#else

uint32_t Pack_CONSUMPTION_2_MSG_flux(CONSUMPTION_2_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(CONSUMPTION_2_MSG_DLC); _d[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->ch5_cons_ro = (uint16_t) FLUX_ch5_cons_ro_toS(_m->ch5_cons_phys);
  _m->ch6_cons_ro = (uint16_t) FLUX_ch6_cons_ro_toS(_m->ch6_cons_phys);
  _m->ch7_cons_ro = (uint16_t) FLUX_ch7_cons_ro_toS(_m->ch7_cons_phys);
  _m->ch8_cons_ro = (uint16_t) FLUX_ch8_cons_ro_toS(_m->ch8_cons_phys);
#endif // FLUX_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->ch5_cons_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->ch5_cons_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->ch6_cons_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->ch6_cons_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->ch7_cons_ro & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->ch7_cons_ro >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->ch8_cons_ro & (0xFFU)) );
  _d[7] |= (uint8_t) ( ((_m->ch8_cons_ro >> 8U) & (0xFFU)) );

  *_len = (uint8_t) CONSUMPTION_2_MSG_DLC;
  *_ide = (uint8_t) CONSUMPTION_2_MSG_IDE;
  return CONSUMPTION_2_MSG_CANID;
}

#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_CONSUMPTION_3_MSG_flux(CONSUMPTION_3_MSG_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ch9_cons_ro = (uint16_t) ( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch9_cons_phys = (sigfloat_t)(FLUX_ch9_cons_ro_fromS(_m->ch9_cons_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch10_cons_ro = (uint16_t) ( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch10_cons_phys = (sigfloat_t)(FLUX_ch10_cons_ro_fromS(_m->ch10_cons_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch11_cons_ro = (uint16_t) ( ((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch11_cons_phys = (sigfloat_t)(FLUX_ch11_cons_ro_fromS(_m->ch11_cons_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->ch12_cons_ro = (uint16_t) ( ((_d[7] & (0xFFU)) << 8U) | (_d[6] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->ch12_cons_phys = (sigfloat_t)(FLUX_ch12_cons_ro_fromS(_m->ch12_cons_ro));
#endif // FLUX_USE_SIGFLOAT

#ifdef FLUX_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CONSUMPTION_3_MSG_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CONSUMPTION_3_MSG_flux(&_m->mon1, CONSUMPTION_3_MSG_CANID);
#endif // FLUX_USE_DIAG_MONITORS

  return CONSUMPTION_3_MSG_CANID;
}

#ifdef FLUX_USE_CANSTRUCT

uint32_t Pack_CONSUMPTION_3_MSG_flux(CONSUMPTION_3_MSG_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(CONSUMPTION_3_MSG_DLC); cframe->Data[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->ch9_cons_ro = (uint16_t) FLUX_ch9_cons_ro_toS(_m->ch9_cons_phys);
  _m->ch10_cons_ro = (uint16_t) FLUX_ch10_cons_ro_toS(_m->ch10_cons_phys);
  _m->ch11_cons_ro = (uint16_t) FLUX_ch11_cons_ro_toS(_m->ch11_cons_phys);
  _m->ch12_cons_ro = (uint16_t) FLUX_ch12_cons_ro_toS(_m->ch12_cons_phys);
#endif // FLUX_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->ch9_cons_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->ch9_cons_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->ch10_cons_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->ch10_cons_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->ch11_cons_ro & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->ch11_cons_ro >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->ch12_cons_ro & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->ch12_cons_ro >> 8U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) CONSUMPTION_3_MSG_CANID;
  cframe->DLC = (uint8_t) CONSUMPTION_3_MSG_DLC;
  cframe->IDE = (uint8_t) CONSUMPTION_3_MSG_IDE;
  return CONSUMPTION_3_MSG_CANID;
}

#else

uint32_t Pack_CONSUMPTION_3_MSG_flux(CONSUMPTION_3_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(CONSUMPTION_3_MSG_DLC); _d[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->ch9_cons_ro = (uint16_t) FLUX_ch9_cons_ro_toS(_m->ch9_cons_phys);
  _m->ch10_cons_ro = (uint16_t) FLUX_ch10_cons_ro_toS(_m->ch10_cons_phys);
  _m->ch11_cons_ro = (uint16_t) FLUX_ch11_cons_ro_toS(_m->ch11_cons_phys);
  _m->ch12_cons_ro = (uint16_t) FLUX_ch12_cons_ro_toS(_m->ch12_cons_phys);
#endif // FLUX_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->ch9_cons_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->ch9_cons_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->ch10_cons_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->ch10_cons_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->ch11_cons_ro & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->ch11_cons_ro >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->ch12_cons_ro & (0xFFU)) );
  _d[7] |= (uint8_t) ( ((_m->ch12_cons_ro >> 8U) & (0xFFU)) );

  *_len = (uint8_t) CONSUMPTION_3_MSG_DLC;
  *_ide = (uint8_t) CONSUMPTION_3_MSG_IDE;
  return CONSUMPTION_3_MSG_CANID;
}

#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_BUS_STATUS_MSG_flux(BUS_STATUS_MSG_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->bus_voltage_ro = (uint16_t) ( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->bus_voltage_phys = (sigfloat_t)(FLUX_bus_voltage_ro_fromS(_m->bus_voltage_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->bus_current_ro = (uint16_t) ( ((_d[3] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->bus_current_phys = (sigfloat_t)(FLUX_bus_current_ro_fromS(_m->bus_current_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->bus_power_ro = (uint16_t) ( ((_d[5] & (0xFFU)) << 8U) | (_d[4] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->bus_power_phys = (sigfloat_t)(FLUX_bus_power_ro_fromS(_m->bus_power_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->bus_consumption_ro = (uint16_t) ( ((_d[7] & (0xFFU)) << 8U) | (_d[6] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->bus_consumption_phys = (sigfloat_t)(FLUX_bus_consumption_ro_fromS(_m->bus_consumption_ro));
#endif // FLUX_USE_SIGFLOAT

#ifdef FLUX_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BUS_STATUS_MSG_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BUS_STATUS_MSG_flux(&_m->mon1, BUS_STATUS_MSG_CANID);
#endif // FLUX_USE_DIAG_MONITORS

  return BUS_STATUS_MSG_CANID;
}

#ifdef FLUX_USE_CANSTRUCT

uint32_t Pack_BUS_STATUS_MSG_flux(BUS_STATUS_MSG_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(BUS_STATUS_MSG_DLC); cframe->Data[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->bus_voltage_ro = (uint16_t) FLUX_bus_voltage_ro_toS(_m->bus_voltage_phys);
  _m->bus_current_ro = (uint16_t) FLUX_bus_current_ro_toS(_m->bus_current_phys);
  _m->bus_power_ro = (uint16_t) FLUX_bus_power_ro_toS(_m->bus_power_phys);
  _m->bus_consumption_ro = (uint16_t) FLUX_bus_consumption_ro_toS(_m->bus_consumption_phys);
#endif // FLUX_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->bus_voltage_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->bus_voltage_ro >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->bus_current_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->bus_current_ro >> 8U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->bus_power_ro & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->bus_power_ro >> 8U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->bus_consumption_ro & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->bus_consumption_ro >> 8U) & (0xFFU)) );

  cframe->MsgId = (uint32_t) BUS_STATUS_MSG_CANID;
  cframe->DLC = (uint8_t) BUS_STATUS_MSG_DLC;
  cframe->IDE = (uint8_t) BUS_STATUS_MSG_IDE;
  return BUS_STATUS_MSG_CANID;
}

#else

uint32_t Pack_BUS_STATUS_MSG_flux(BUS_STATUS_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(BUS_STATUS_MSG_DLC); _d[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->bus_voltage_ro = (uint16_t) FLUX_bus_voltage_ro_toS(_m->bus_voltage_phys);
  _m->bus_current_ro = (uint16_t) FLUX_bus_current_ro_toS(_m->bus_current_phys);
  _m->bus_power_ro = (uint16_t) FLUX_bus_power_ro_toS(_m->bus_power_phys);
  _m->bus_consumption_ro = (uint16_t) FLUX_bus_consumption_ro_toS(_m->bus_consumption_phys);
#endif // FLUX_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->bus_voltage_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->bus_voltage_ro >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->bus_current_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->bus_current_ro >> 8U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->bus_power_ro & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->bus_power_ro >> 8U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->bus_consumption_ro & (0xFFU)) );
  _d[7] |= (uint8_t) ( ((_m->bus_consumption_ro >> 8U) & (0xFFU)) );

  *_len = (uint8_t) BUS_STATUS_MSG_DLC;
  *_ide = (uint8_t) BUS_STATUS_MSG_IDE;
  return BUS_STATUS_MSG_CANID;
}

#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_TEMPERATURES_MSG_flux(TEMPERATURES_MSG_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->controller_temp_ro = (uint16_t) ( ((_d[1] & (0x0FU)) << 8U) | (_d[0] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->controller_temp_phys = (sigfloat_t)(FLUX_controller_temp_ro_fromS(_m->controller_temp_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->box_temp_1_ro = (uint16_t) ( ((_d[2] & (0xFFU)) << 4U) | ((_d[1] >> 4U) & (0x0FU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->box_temp_1_phys = (sigfloat_t)(FLUX_box_temp_1_ro_fromS(_m->box_temp_1_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->box_temp_2_ro = (uint16_t) ( ((_d[4] & (0x0FU)) << 8U) | (_d[3] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->box_temp_2_phys = (sigfloat_t)(FLUX_box_temp_2_ro_fromS(_m->box_temp_2_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->box_temp_3_ro = (uint16_t) ( ((_d[5] & (0xFFU)) << 4U) | ((_d[4] >> 4U) & (0x0FU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->box_temp_3_phys = (sigfloat_t)(FLUX_box_temp_3_ro_fromS(_m->box_temp_3_ro));
#endif // FLUX_USE_SIGFLOAT

  _m->box_temp_4_ro = (uint16_t) ( ((_d[7] & (0x0FU)) << 8U) | (_d[6] & (0xFFU)) );
#ifdef FLUX_USE_SIGFLOAT
  _m->box_temp_4_phys = (sigfloat_t)(FLUX_box_temp_4_ro_fromS(_m->box_temp_4_ro));
#endif // FLUX_USE_SIGFLOAT

#ifdef FLUX_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TEMPERATURES_MSG_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TEMPERATURES_MSG_flux(&_m->mon1, TEMPERATURES_MSG_CANID);
#endif // FLUX_USE_DIAG_MONITORS

  return TEMPERATURES_MSG_CANID;
}

#ifdef FLUX_USE_CANSTRUCT

uint32_t Pack_TEMPERATURES_MSG_flux(TEMPERATURES_MSG_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(TEMPERATURES_MSG_DLC); cframe->Data[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->controller_temp_ro = (uint16_t) FLUX_controller_temp_ro_toS(_m->controller_temp_phys);
  _m->box_temp_1_ro = (uint16_t) FLUX_box_temp_1_ro_toS(_m->box_temp_1_phys);
  _m->box_temp_2_ro = (uint16_t) FLUX_box_temp_2_ro_toS(_m->box_temp_2_phys);
  _m->box_temp_3_ro = (uint16_t) FLUX_box_temp_3_ro_toS(_m->box_temp_3_phys);
  _m->box_temp_4_ro = (uint16_t) FLUX_box_temp_4_ro_toS(_m->box_temp_4_phys);
#endif // FLUX_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->controller_temp_ro & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->controller_temp_ro >> 8U) & (0x0FU)) | ((_m->box_temp_1_ro & (0x0FU)) << 4U) );
  cframe->Data[2] |= (uint8_t) ( ((_m->box_temp_1_ro >> 4U) & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->box_temp_2_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->box_temp_2_ro >> 8U) & (0x0FU)) | ((_m->box_temp_3_ro & (0x0FU)) << 4U) );
  cframe->Data[5] |= (uint8_t) ( ((_m->box_temp_3_ro >> 4U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->box_temp_4_ro & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( ((_m->box_temp_4_ro >> 8U) & (0x0FU)) );

  cframe->MsgId = (uint32_t) TEMPERATURES_MSG_CANID;
  cframe->DLC = (uint8_t) TEMPERATURES_MSG_DLC;
  cframe->IDE = (uint8_t) TEMPERATURES_MSG_IDE;
  return TEMPERATURES_MSG_CANID;
}

#else

uint32_t Pack_TEMPERATURES_MSG_flux(TEMPERATURES_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < FLUX_VALIDATE_DLC(TEMPERATURES_MSG_DLC); _d[i++] = FLUX_INITIAL_BYTE_VALUE);

#ifdef FLUX_USE_SIGFLOAT
  _m->controller_temp_ro = (uint16_t) FLUX_controller_temp_ro_toS(_m->controller_temp_phys);
  _m->box_temp_1_ro = (uint16_t) FLUX_box_temp_1_ro_toS(_m->box_temp_1_phys);
  _m->box_temp_2_ro = (uint16_t) FLUX_box_temp_2_ro_toS(_m->box_temp_2_phys);
  _m->box_temp_3_ro = (uint16_t) FLUX_box_temp_3_ro_toS(_m->box_temp_3_phys);
  _m->box_temp_4_ro = (uint16_t) FLUX_box_temp_4_ro_toS(_m->box_temp_4_phys);
#endif // FLUX_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->controller_temp_ro & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->controller_temp_ro >> 8U) & (0x0FU)) | ((_m->box_temp_1_ro & (0x0FU)) << 4U) );
  _d[2] |= (uint8_t) ( ((_m->box_temp_1_ro >> 4U) & (0xFFU)) );
  _d[3] |= (uint8_t) ( (_m->box_temp_2_ro & (0xFFU)) );
  _d[4] |= (uint8_t) ( ((_m->box_temp_2_ro >> 8U) & (0x0FU)) | ((_m->box_temp_3_ro & (0x0FU)) << 4U) );
  _d[5] |= (uint8_t) ( ((_m->box_temp_3_ro >> 4U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->box_temp_4_ro & (0xFFU)) );
  _d[7] |= (uint8_t) ( ((_m->box_temp_4_ro >> 8U) & (0x0FU)) );

  *_len = (uint8_t) TEMPERATURES_MSG_DLC;
  *_ide = (uint8_t) TEMPERATURES_MSG_IDE;
  return TEMPERATURES_MSG_CANID;
}

#endif // FLUX_USE_CANSTRUCT

