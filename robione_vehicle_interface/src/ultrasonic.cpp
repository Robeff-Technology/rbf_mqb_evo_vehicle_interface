#include "robione_vehicle_interface/ultrasonic.h"

#include <cstring>

UltrasonicParser::UltrasonicParser()
 : state_(WAIT_HEADER), header_(0), data_h_(0), data_l_(0), sum_(0), last_distance_(0)
{
}

void UltrasonicParser::set_callback(Callback cb)
{
  callback_ = std::move(cb);
}

void UltrasonicParser::reset()
{
  state_ = WAIT_HEADER;
  header_ = data_h_ = data_l_ = sum_ = 0;
}

bool UltrasonicParser::input_byte(uint8_t b)
{
  switch (state_) {
    case WAIT_HEADER:
      if (b == 0xFF) {
        header_ = b;
        state_ = READ_DATA_H;
      }
      break;

    case READ_DATA_H:
      data_h_ = b;
      state_ = READ_DATA_L;
      break;

    case READ_DATA_L:
      data_l_ = b;
      state_ = READ_SUM;
      break;

    case READ_SUM:
      sum_ = b;
      {
        uint8_t calc = static_cast<uint8_t>((static_cast<int>(header_) + static_cast<int>(data_h_) + static_cast<int>(data_l_)) & 0x00FF);
        if (calc == sum_) {
          last_distance_ = static_cast<uint16_t>((static_cast<uint16_t>(data_h_) << 8) | data_l_);
          if (callback_) callback_(last_distance_);
          // Successful parse; prepare for next frame
          state_ = WAIT_HEADER;
          return true;
        } else {
          // checksum mismatch: try to resync. If this byte is 0xFF treat as header for next frame
          if (b == 0xFF) {
            header_ = b;
            state_ = READ_DATA_H;
          } else {
            state_ = WAIT_HEADER;
          }
        }
      }
      break;
  }

  return false;
}

int UltrasonicParser::process_bytes(const uint8_t * data, int length)
{
  int parsed = 0;
  for (int i = 0; i < length; ++i) {
    if (input_byte(data[i])) ++parsed;
  }
  return parsed;
}
