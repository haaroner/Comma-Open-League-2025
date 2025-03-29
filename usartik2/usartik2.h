#pragma once
#include "project_config.h"

namespace usartik2
{
  void usartik2Init(uint32_t speed, uint8_t word_length, float stop_bits, uint16_t buff_size = 25);
  void write_uart2(uint8_t _byte);
  void abcde(uint8_t _data);
  uint16_t read();
  uint16_t available();
  extern volatile uint8_t tx[25];
  extern volatile uint8_t rx[25];
  extern volatile uint16_t _rxCnt;
  extern volatile uint16_t _txCnt;
  extern volatile bool flag;
  extern volatile uint16_t _readCnt;
  extern volatile uint16_t _sendCnt;
  extern volatile uint16_t _buffer_size;
}
