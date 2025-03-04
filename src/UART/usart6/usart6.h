#pragma once
#include "project_config.h"

namespace usart6
{
	void usart6Init(uint32_t speed, uint8_t word_length, float stop_bits);
	void write(uint8_t _byte);
	uint16_t read();
	uint16_t available();
	extern volatile uint8_t tx[16];
	extern volatile uint8_t rx[16];
	extern volatile uint16_t _rxCnt;
	extern volatile uint16_t _txCnt;
	extern volatile bool flag;
	extern volatile uint16_t _readCnt;
	extern volatile uint16_t _sendCnt;
}
