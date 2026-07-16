#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <stdexcept>

class SerialPortException : public std::runtime_error
{
public:
  SerialPortException(const std::string & message);
};

class SerialPort
{
public:
  SerialPort();
  SerialPort(const char * port_name);
  ~SerialPort();

  void open();
  void configure(unsigned int baud_rate, int data_bits = 8, char parity = 'N', int stop_bits = 1);
  void write(const char * data, int length);
  int read(char * buffer, int buffer_size);
  // Read exactly `length` bytes into `buffer`, waiting up to `timeout_ms` milliseconds.
  // If `timeout_ms` < 0, wait indefinitely until bytes are received.
  // Returns number of bytes actually read (may be < length on timeout) or throws on error.
  int read_exact(char * buffer, int length, int timeout_ms = -1);
  void close();
  void set_port_name(const char * port_name);

private:
  const char * port_name_;
  int fd_;
  bool is_open_();
  bool is_configured_;
  unsigned int baud_rate_;
  int data_bits_;
  char parity_;
  int stop_bits_;
  int buffer_size_;
  char * buffer_;
};

#endif  // SERIAL_PORT_H
