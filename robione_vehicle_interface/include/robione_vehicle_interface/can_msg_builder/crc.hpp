#pragma once

#include <stddef.h>
#include <stdint.h>

#define CRC8_AUTOSAR_POLY (0x2FU)
#define CRC8_AUTOSAR_INIT (0xFFU)
#define CRC8_AUTOSAR_XOROUT (0xFFU)

/**
 * CRC-8/AUTOSAR
 *  - poly:   0x2F
 *  - init:   0xFF
 *  - xorout: 0xFF
 *  - refin/refout: false/false
 *
 * Use: crc = crc8_autosar(data, 7); // data[0..6], write to data[7]
 */
static inline uint8_t crc8_autosar(const uint8_t * data, size_t len)
{
  uint8_t crc = CRC8_AUTOSAR_INIT;

  for (size_t i = 0; i < len; i++) {
    crc ^= data[i];
    for (uint8_t bit = 0; bit < 8; bit++) {
      if (crc & 0x80U) {
        crc = (uint8_t)((crc << 1U) ^ CRC8_AUTOSAR_POLY);
      } else {
        crc = (uint8_t)(crc << 1U);
      }
    }
  }

  return (uint8_t)(crc ^ CRC8_AUTOSAR_XOROUT);
}
