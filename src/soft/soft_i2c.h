#pragma once
#include "project_config.h"
#include "pin_setup.h"

class soft_i2c 
{
	public:
		soft_i2c(pin &sclPin, 
				pin &sdaPin);
	void softI2cInit();
	void sclHigh();
	void sclLow();
	void sdaHigh();
	void sdaLow();
	bool generateStart();
	bool generateStop();
	void delay();
	bool sdaRead();
	bool sclRead();
	void writeBit(bool bit);
	bool send(uint8_t package);
	bool readAch();
	uint8_t read();
	void sendAch();
	void sendNach();
		
	private:
		pin _sclPin; 
		pin _sdaPin;
		
};
