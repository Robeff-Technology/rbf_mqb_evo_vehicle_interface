#ifndef ROBIONE_ULTRASONIC_H
#define ROBIONE_ULTRASONIC_H

#include <cstdint>
#include <functional>
#include <vector>

// Ultrasonic frame parser for 4-byte frames:
// Header(0xFF) DATA_H DATA_L SUM
// SUM == (Header + DATA_H + DATA_L) & 0xFF
// When a valid frame is parsed, the user callback is invoked with the 16-bit distance

class UltrasonicParser
{
public:
  using Callback = std::function<void(uint16_t distance)>;

  UltrasonicParser();

  // Set callback invoked on valid frame
  void set_callback(Callback cb);

  // Reset parser state
  void reset();

  // Feed a single byte into the parser. When a valid frame is assembled,
  // the callback will be invoked. Returns true if a complete frame was parsed.
  bool input_byte(uint8_t b);

  // Feed a buffer of bytes into the parser. Returns number of complete frames parsed.
  int process_bytes(const uint8_t * data, int length);

  // Utility: last parsed distance (valid after callback or a successful parse)
  uint16_t last_distance() const { return last_distance_; }

private:
  enum State { WAIT_HEADER, READ_DATA_H, READ_DATA_L, READ_SUM } state_;

  uint8_t header_;
  uint8_t data_h_;
  uint8_t data_l_;
  uint8_t sum_;
  uint16_t last_distance_;

  Callback callback_;
};

#endif  // ROBIONE_ULTRASONIC_H
