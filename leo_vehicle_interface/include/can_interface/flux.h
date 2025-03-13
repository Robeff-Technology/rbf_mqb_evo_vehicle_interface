// Generator version : v3.1
// DBC filename      : flux_pds.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// DBC file version
#define VER_FLUX_MAJ (0U)
#define VER_FLUX_MIN (0U)

// include current dbc-driver compilation config
#include "flux-config.h"

#ifdef FLUX_USE_DIAG_MONITORS
// This file must define:
// base monitor struct
#include "canmonitorutil.h"

#endif // FLUX_USE_DIAG_MONITORS


// DLC maximum value which is used as the limit for frame's data buffer size.
// Client can set its own value (not sure why) in driver-config
// or can test it on some limit specified by application
// e.g.: static_assert(TESTDB_MAX_DLC_VALUE <= APPLICATION_FRAME_DATA_SIZE, "Max DLC value in the driver is too big")
#ifndef FLUX_MAX_DLC_VALUE
// The value which was found out by generator (real max value)
#define FLUX_MAX_DLC_VALUE 8U
#endif

// The limit is used for setting frame's data bytes
#define FLUX_VALIDATE_DLC(msgDlc) (((msgDlc) <= (FLUX_MAX_DLC_VALUE)) ? (msgDlc) : (FLUX_MAX_DLC_VALUE))

// Initial byte value to be filles in data bytes of the frame before pack signals
// User can define its own custom value in driver-config file
#ifndef FLUX_INITIAL_BYTE_VALUE
#define FLUX_INITIAL_BYTE_VALUE 0U
#endif


// def @CHANNEL_STATUS_MSG CAN Message (288  0x120)
#define CHANNEL_STATUS_MSG_IDE (0U)
#define CHANNEL_STATUS_MSG_DLC (8U)
#define CHANNEL_STATUS_MSG_CANID (0x120U)

typedef struct
{
#ifdef FLUX_USE_BITS_SIGNAL

  // -
  uint8_t ch1_stat : 4;                      //      Bits= 4 Unit:'-'

  // -
  uint8_t ch2_stat : 4;                      //      Bits= 4 Unit:'-'

  // -
  uint8_t ch3_stat : 4;                      //      Bits= 4 Unit:'-'

  // -
  uint8_t ch4_stat : 4;                      //      Bits= 4 Unit:'-'

  // -
  uint8_t ch5_stat : 4;                      //      Bits= 4 Unit:'-'

  // -
  uint8_t ch6_stat : 4;                      //      Bits= 4 Unit:'-'

  // -
  uint8_t ch7_stat : 4;                      //      Bits= 4 Unit:'-'

  // -
  uint8_t ch8_stat : 4;                      //      Bits= 4 Unit:'-'

  // -
  uint8_t ch9_stat : 4;                      //      Bits= 4 Unit:'-'

  // -
  uint8_t ch10_stat : 4;                     //      Bits= 4 Unit:'-'

  // -
  uint8_t ch11_stat : 4;                     //      Bits= 4 Unit:'-'

  // -
  uint8_t ch12_stat : 4;                     //      Bits= 4 Unit:'-'

#else

  // -
  uint8_t ch1_stat;                          //      Bits= 4 Unit:'-'

  // -
  uint8_t ch2_stat;                          //      Bits= 4 Unit:'-'

  // -
  uint8_t ch3_stat;                          //      Bits= 4 Unit:'-'

  // -
  uint8_t ch4_stat;                          //      Bits= 4 Unit:'-'

  // -
  uint8_t ch5_stat;                          //      Bits= 4 Unit:'-'

  // -
  uint8_t ch6_stat;                          //      Bits= 4 Unit:'-'

  // -
  uint8_t ch7_stat;                          //      Bits= 4 Unit:'-'

  // -
  uint8_t ch8_stat;                          //      Bits= 4 Unit:'-'

  // -
  uint8_t ch9_stat;                          //      Bits= 4 Unit:'-'

  // -
  uint8_t ch10_stat;                         //      Bits= 4 Unit:'-'

  // -
  uint8_t ch11_stat;                         //      Bits= 4 Unit:'-'

  // -
  uint8_t ch12_stat;                         //      Bits= 4 Unit:'-'

#endif // FLUX_USE_BITS_SIGNAL

#ifdef FLUX_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // FLUX_USE_DIAG_MONITORS

} CHANNEL_STATUS_MSG_t;

// def @CURRENTS_1_MSG CAN Message (292  0x124)
#define CURRENTS_1_MSG_IDE (0U)
#define CURRENTS_1_MSG_DLC (8U)
#define CURRENTS_1_MSG_CANID (0x124U)
// signal: @ch1_current_ro
#define FLUX_ch1_current_ro_CovFactor (0.01)
#define FLUX_ch1_current_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch1_current_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch2_current_ro
#define FLUX_ch2_current_ro_CovFactor (0.01)
#define FLUX_ch2_current_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch2_current_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch3_current_ro
#define FLUX_ch3_current_ro_CovFactor (0.01)
#define FLUX_ch3_current_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch3_current_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch4_current_ro
#define FLUX_ch4_current_ro_CovFactor (0.01)
#define FLUX_ch4_current_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch4_current_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )

typedef struct
{
#ifdef FLUX_USE_BITS_SIGNAL

  // channel1 current
  uint16_t ch1_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch1_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel2 current
  uint16_t ch2_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch2_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel3 current
  uint16_t ch3_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch3_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel4 current
  uint16_t ch4_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch4_current_phys;
#endif // FLUX_USE_SIGFLOAT

#else

  // channel1 current
  uint16_t ch1_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch1_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel2 current
  uint16_t ch2_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch2_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel3 current
  uint16_t ch3_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch3_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel4 current
  uint16_t ch4_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch4_current_phys;
#endif // FLUX_USE_SIGFLOAT

#endif // FLUX_USE_BITS_SIGNAL

#ifdef FLUX_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // FLUX_USE_DIAG_MONITORS

} CURRENTS_1_MSG_t;

// def @CURRENTS_2_MSG CAN Message (296  0x128)
#define CURRENTS_2_MSG_IDE (0U)
#define CURRENTS_2_MSG_DLC (8U)
#define CURRENTS_2_MSG_CANID (0x128U)
// signal: @ch5_current_ro
#define FLUX_ch5_current_ro_CovFactor (0.01)
#define FLUX_ch5_current_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch5_current_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch6_current_ro
#define FLUX_ch6_current_ro_CovFactor (0.01)
#define FLUX_ch6_current_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch6_current_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch7_current_ro
#define FLUX_ch7_current_ro_CovFactor (0.01)
#define FLUX_ch7_current_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch7_current_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch8_current_ro
#define FLUX_ch8_current_ro_CovFactor (0.01)
#define FLUX_ch8_current_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch8_current_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )

typedef struct
{
#ifdef FLUX_USE_BITS_SIGNAL

  // channel5 current
  uint16_t ch5_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch5_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel6 current
  uint16_t ch6_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch6_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel7 current
  uint16_t ch7_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch7_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel8 current
  uint16_t ch8_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch8_current_phys;
#endif // FLUX_USE_SIGFLOAT

#else

  // channel5 current
  uint16_t ch5_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch5_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel6 current
  uint16_t ch6_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch6_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel7 current
  uint16_t ch7_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch7_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel8 current
  uint16_t ch8_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch8_current_phys;
#endif // FLUX_USE_SIGFLOAT

#endif // FLUX_USE_BITS_SIGNAL

#ifdef FLUX_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // FLUX_USE_DIAG_MONITORS

} CURRENTS_2_MSG_t;

// def @CURRENTS_3_MSG CAN Message (300  0x12c)
#define CURRENTS_3_MSG_IDE (0U)
#define CURRENTS_3_MSG_DLC (8U)
#define CURRENTS_3_MSG_CANID (0x12cU)
// signal: @ch9_current_ro
#define FLUX_ch9_current_ro_CovFactor (0.01)
#define FLUX_ch9_current_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch9_current_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch10_current_ro
#define FLUX_ch10_current_ro_CovFactor (0.01)
#define FLUX_ch10_current_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch10_current_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch11_current_ro
#define FLUX_ch11_current_ro_CovFactor (0.01)
#define FLUX_ch11_current_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch11_current_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch12_current_ro
#define FLUX_ch12_current_ro_CovFactor (0.01)
#define FLUX_ch12_current_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch12_current_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )

typedef struct
{
#ifdef FLUX_USE_BITS_SIGNAL

  // channel9 current
  uint16_t ch9_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch9_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel10 current
  uint16_t ch10_current_ro;                  //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch10_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel11 current
  uint16_t ch11_current_ro;                  //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch11_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel12 current
  uint16_t ch12_current_ro;                  //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch12_current_phys;
#endif // FLUX_USE_SIGFLOAT

#else

  // channel9 current
  uint16_t ch9_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch9_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel10 current
  uint16_t ch10_current_ro;                  //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch10_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel11 current
  uint16_t ch11_current_ro;                  //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch11_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel12 current
  uint16_t ch12_current_ro;                  //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch12_current_phys;
#endif // FLUX_USE_SIGFLOAT

#endif // FLUX_USE_BITS_SIGNAL

#ifdef FLUX_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // FLUX_USE_DIAG_MONITORS

} CURRENTS_3_MSG_t;

// def @CONSUMPTION_1_MSG CAN Message (301  0x12d)
#define CONSUMPTION_1_MSG_IDE (0U)
#define CONSUMPTION_1_MSG_DLC (8U)
#define CONSUMPTION_1_MSG_CANID (0x12dU)
// signal: @ch1_cons_ro
#define FLUX_ch1_cons_ro_CovFactor (0.01)
#define FLUX_ch1_cons_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch1_cons_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch2_cons_ro
#define FLUX_ch2_cons_ro_CovFactor (0.01)
#define FLUX_ch2_cons_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch2_cons_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch3_cons_ro
#define FLUX_ch3_cons_ro_CovFactor (0.01)
#define FLUX_ch3_cons_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch3_cons_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch4_cons_ro
#define FLUX_ch4_cons_ro_CovFactor (0.01)
#define FLUX_ch4_cons_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch4_cons_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )

typedef struct
{
#ifdef FLUX_USE_BITS_SIGNAL

  // channel1 consumption
  uint16_t ch1_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch1_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel2 consumption
  uint16_t ch2_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch2_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel3 consumption
  uint16_t ch3_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch3_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel4 consumption
  uint16_t ch4_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch4_cons_phys;
#endif // FLUX_USE_SIGFLOAT

#else

  // channel1 consumption
  uint16_t ch1_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch1_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel2 consumption
  uint16_t ch2_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch2_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel3 consumption
  uint16_t ch3_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch3_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // channel4 consumption
  uint16_t ch4_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch4_cons_phys;
#endif // FLUX_USE_SIGFLOAT

#endif // FLUX_USE_BITS_SIGNAL

#ifdef FLUX_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // FLUX_USE_DIAG_MONITORS

} CONSUMPTION_1_MSG_t;

// def @CONSUMPTION_2_MSG CAN Message (302  0x12e)
#define CONSUMPTION_2_MSG_IDE (0U)
#define CONSUMPTION_2_MSG_DLC (8U)
#define CONSUMPTION_2_MSG_CANID (0x12eU)
// signal: @ch5_cons_ro
#define FLUX_ch5_cons_ro_CovFactor (0.01)
#define FLUX_ch5_cons_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch5_cons_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch6_cons_ro
#define FLUX_ch6_cons_ro_CovFactor (0.01)
#define FLUX_ch6_cons_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch6_cons_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch7_cons_ro
#define FLUX_ch7_cons_ro_CovFactor (0.01)
#define FLUX_ch7_cons_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch7_cons_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch8_cons_ro
#define FLUX_ch8_cons_ro_CovFactor (0.01)
#define FLUX_ch8_cons_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch8_cons_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )

typedef struct
{
#ifdef FLUX_USE_BITS_SIGNAL

  // -
  uint16_t ch5_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch5_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t ch6_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch6_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t ch7_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch7_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t ch8_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch8_cons_phys;
#endif // FLUX_USE_SIGFLOAT

#else

  // -
  uint16_t ch5_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch5_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t ch6_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch6_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t ch7_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch7_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t ch8_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch8_cons_phys;
#endif // FLUX_USE_SIGFLOAT

#endif // FLUX_USE_BITS_SIGNAL

#ifdef FLUX_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // FLUX_USE_DIAG_MONITORS

} CONSUMPTION_2_MSG_t;

// def @CONSUMPTION_3_MSG CAN Message (303  0x12f)
#define CONSUMPTION_3_MSG_IDE (0U)
#define CONSUMPTION_3_MSG_DLC (8U)
#define CONSUMPTION_3_MSG_CANID (0x12fU)
// signal: @ch9_cons_ro
#define FLUX_ch9_cons_ro_CovFactor (0.01)
#define FLUX_ch9_cons_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch9_cons_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch10_cons_ro
#define FLUX_ch10_cons_ro_CovFactor (0.01)
#define FLUX_ch10_cons_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch10_cons_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch11_cons_ro
#define FLUX_ch11_cons_ro_CovFactor (0.01)
#define FLUX_ch11_cons_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch11_cons_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @ch12_cons_ro
#define FLUX_ch12_cons_ro_CovFactor (0.01)
#define FLUX_ch12_cons_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_ch12_cons_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )

typedef struct
{
#ifdef FLUX_USE_BITS_SIGNAL

  // -
  uint16_t ch9_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch9_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t ch10_cons_ro;                     //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch10_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t ch11_cons_ro;                     //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch11_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t ch12_cons_ro;                     //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch12_cons_phys;
#endif // FLUX_USE_SIGFLOAT

#else

  // -
  uint16_t ch9_cons_ro;                      //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch9_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t ch10_cons_ro;                     //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch10_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t ch11_cons_ro;                     //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch11_cons_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t ch12_cons_ro;                     //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t ch12_cons_phys;
#endif // FLUX_USE_SIGFLOAT

#endif // FLUX_USE_BITS_SIGNAL

#ifdef FLUX_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // FLUX_USE_DIAG_MONITORS

} CONSUMPTION_3_MSG_t;

// def @BUS_STATUS_MSG CAN Message (316  0x13c)
#define BUS_STATUS_MSG_IDE (0U)
#define BUS_STATUS_MSG_DLC (8U)
#define BUS_STATUS_MSG_CANID (0x13cU)
// signal: @bus_voltage_ro
#define FLUX_bus_voltage_ro_CovFactor (0.01)
#define FLUX_bus_voltage_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_bus_voltage_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @bus_current_ro
#define FLUX_bus_current_ro_CovFactor (0.01)
#define FLUX_bus_current_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_bus_current_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @bus_power_ro
#define FLUX_bus_power_ro_CovFactor (0.01)
#define FLUX_bus_power_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_bus_power_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @bus_consumption_ro
#define FLUX_bus_consumption_ro_CovFactor (0.01)
#define FLUX_bus_consumption_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define FLUX_bus_consumption_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )

typedef struct
{
#ifdef FLUX_USE_BITS_SIGNAL

  // -
  uint16_t bus_voltage_ro;                   //      Bits=16 Factor= 0.01            Unit:'V'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t bus_voltage_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t bus_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t bus_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t bus_power_ro;                     //      Bits=16 Factor= 0.01            Unit:'W'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t bus_power_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t bus_consumption_ro;               //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t bus_consumption_phys;
#endif // FLUX_USE_SIGFLOAT

#else

  // -
  uint16_t bus_voltage_ro;                   //      Bits=16 Factor= 0.01            Unit:'V'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t bus_voltage_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t bus_current_ro;                   //      Bits=16 Factor= 0.01            Unit:'A'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t bus_current_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t bus_power_ro;                     //      Bits=16 Factor= 0.01            Unit:'W'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t bus_power_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t bus_consumption_ro;               //      Bits=16 Factor= 0.01            Unit:'Ah'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t bus_consumption_phys;
#endif // FLUX_USE_SIGFLOAT

#endif // FLUX_USE_BITS_SIGNAL

#ifdef FLUX_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // FLUX_USE_DIAG_MONITORS

} BUS_STATUS_MSG_t;

// def @TEMPERATURES_MSG CAN Message (317  0x13d)
#define TEMPERATURES_MSG_IDE (0U)
#define TEMPERATURES_MSG_DLC (8U)
#define TEMPERATURES_MSG_CANID (0x13dU)
// signal: @controller_temp_ro
#define FLUX_controller_temp_ro_CovFactor (0.1)
#define FLUX_controller_temp_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.1)) )
#define FLUX_controller_temp_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )
// signal: @box_temp_1_ro
#define FLUX_box_temp_1_ro_CovFactor (0.1)
#define FLUX_box_temp_1_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.1)) )
#define FLUX_box_temp_1_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )
// signal: @box_temp_2_ro
#define FLUX_box_temp_2_ro_CovFactor (0.1)
#define FLUX_box_temp_2_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.1)) )
#define FLUX_box_temp_2_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )
// signal: @box_temp_3_ro
#define FLUX_box_temp_3_ro_CovFactor (0.1)
#define FLUX_box_temp_3_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.1)) )
#define FLUX_box_temp_3_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )
// signal: @box_temp_4_ro
#define FLUX_box_temp_4_ro_CovFactor (0.1)
#define FLUX_box_temp_4_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.1)) )
#define FLUX_box_temp_4_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )

typedef struct
{
#ifdef FLUX_USE_BITS_SIGNAL

  // -
  uint16_t controller_temp_ro;               //      Bits=12 Factor= 0.1             Unit:'-'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t controller_temp_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t box_temp_1_ro;                    //      Bits=12 Factor= 0.1             Unit:'-'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t box_temp_1_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t box_temp_2_ro;                    //      Bits=12 Factor= 0.1             Unit:'-'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t box_temp_2_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t box_temp_3_ro;                    //      Bits=12 Factor= 0.1             Unit:'-'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t box_temp_3_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t box_temp_4_ro;                    //      Bits=12 Factor= 0.1             Unit:'-'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t box_temp_4_phys;
#endif // FLUX_USE_SIGFLOAT

#else

  // -
  uint16_t controller_temp_ro;               //      Bits=12 Factor= 0.1             Unit:'-'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t controller_temp_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t box_temp_1_ro;                    //      Bits=12 Factor= 0.1             Unit:'-'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t box_temp_1_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t box_temp_2_ro;                    //      Bits=12 Factor= 0.1             Unit:'-'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t box_temp_2_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t box_temp_3_ro;                    //      Bits=12 Factor= 0.1             Unit:'-'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t box_temp_3_phys;
#endif // FLUX_USE_SIGFLOAT

  // -
  uint16_t box_temp_4_ro;                    //      Bits=12 Factor= 0.1             Unit:'-'

#ifdef FLUX_USE_SIGFLOAT
  sigfloat_t box_temp_4_phys;
#endif // FLUX_USE_SIGFLOAT

#endif // FLUX_USE_BITS_SIGNAL

#ifdef FLUX_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // FLUX_USE_DIAG_MONITORS

} TEMPERATURES_MSG_t;

// Function signatures

uint32_t Unpack_CHANNEL_STATUS_MSG_flux(CHANNEL_STATUS_MSG_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef FLUX_USE_CANSTRUCT
uint32_t Pack_CHANNEL_STATUS_MSG_flux(CHANNEL_STATUS_MSG_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_CHANNEL_STATUS_MSG_flux(CHANNEL_STATUS_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_CURRENTS_1_MSG_flux(CURRENTS_1_MSG_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef FLUX_USE_CANSTRUCT
uint32_t Pack_CURRENTS_1_MSG_flux(CURRENTS_1_MSG_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_CURRENTS_1_MSG_flux(CURRENTS_1_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_CURRENTS_2_MSG_flux(CURRENTS_2_MSG_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef FLUX_USE_CANSTRUCT
uint32_t Pack_CURRENTS_2_MSG_flux(CURRENTS_2_MSG_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_CURRENTS_2_MSG_flux(CURRENTS_2_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_CURRENTS_3_MSG_flux(CURRENTS_3_MSG_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef FLUX_USE_CANSTRUCT
uint32_t Pack_CURRENTS_3_MSG_flux(CURRENTS_3_MSG_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_CURRENTS_3_MSG_flux(CURRENTS_3_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_CONSUMPTION_1_MSG_flux(CONSUMPTION_1_MSG_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef FLUX_USE_CANSTRUCT
uint32_t Pack_CONSUMPTION_1_MSG_flux(CONSUMPTION_1_MSG_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_CONSUMPTION_1_MSG_flux(CONSUMPTION_1_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_CONSUMPTION_2_MSG_flux(CONSUMPTION_2_MSG_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef FLUX_USE_CANSTRUCT
uint32_t Pack_CONSUMPTION_2_MSG_flux(CONSUMPTION_2_MSG_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_CONSUMPTION_2_MSG_flux(CONSUMPTION_2_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_CONSUMPTION_3_MSG_flux(CONSUMPTION_3_MSG_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef FLUX_USE_CANSTRUCT
uint32_t Pack_CONSUMPTION_3_MSG_flux(CONSUMPTION_3_MSG_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_CONSUMPTION_3_MSG_flux(CONSUMPTION_3_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_BUS_STATUS_MSG_flux(BUS_STATUS_MSG_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef FLUX_USE_CANSTRUCT
uint32_t Pack_BUS_STATUS_MSG_flux(BUS_STATUS_MSG_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_BUS_STATUS_MSG_flux(BUS_STATUS_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // FLUX_USE_CANSTRUCT

uint32_t Unpack_TEMPERATURES_MSG_flux(TEMPERATURES_MSG_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef FLUX_USE_CANSTRUCT
uint32_t Pack_TEMPERATURES_MSG_flux(TEMPERATURES_MSG_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_TEMPERATURES_MSG_flux(TEMPERATURES_MSG_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // FLUX_USE_CANSTRUCT

#ifdef __cplusplus
}
#endif
