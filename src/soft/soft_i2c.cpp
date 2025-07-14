#include "soft_i2c.h"

soft_i2c::soft_i2c(pin & sclPin,
				 pin & sdaPin): 
				 _sclPin(sclPin),
				 _sdaPin(sdaPin)
{
	sdaHigh();
	sclHigh();
}

void soft_i2c::sdaHigh()
{
	_sdaPin.setBit();
}

void soft_i2c::sdaLow()
{
	_sdaPin.resetBit();
}

void soft_i2c::sclHigh()
{
	_sclPin.setBit();
}

void soft_i2c::sclLow()
{
	_sclPin.resetBit();
}

void soft_i2c::delay()
{
	volatile uint8_t iter = 25;
	while(iter)
	{
		iter--;
	}		
}

bool soft_i2c::sdaRead()
{
	bool data = (_sdaPin.getGPIOx()->IDR & _sdaPin.getPinNumber());
	return data;
}

bool soft_i2c::sclRead()
{
	bool data = (_sclPin.getGPIOx()->IDR & _sclPin.getPinNumber());
	return data;
}

void soft_i2c::softI2cInit()
{
	_sdaPin.pinInit();
	_sclPin.pinInit();
}

bool soft_i2c::generateStart()
{
	sdaHigh();
	sclHigh();
	delay(); 
	if(!sdaRead())
	{
		return false;
	}
	sdaLow();
	delay();
	if(sdaRead())
	{
		return false;
	}
	sclLow();
	delay();
	if(sclRead())
	{
		return false;
	}
	return true;
}

bool soft_i2c::generateStop()
{
	sclLow();
	delay();
	sdaLow();
	delay();
	sclHigh();
	delay();
	sdaHigh();
	delay();
	return true;
}

void soft_i2c::sendAch()
{
	sclLow();
	delay();
	sdaLow();
	delay();
	sclHigh();
	delay();
	sclLow();
	delay();
}

void soft_i2c::sendNach()
{
	sclLow();
	delay();
	sdaHigh();
	delay();
	sclHigh();
	delay();
	sclLow();
	delay();
}

void soft_i2c::writeBit(bool bit)
{
	sclLow();
	delay();
	if(!bit)
	{
		sdaLow();
	}
	else
	{
		sdaHigh();
	}
	delay();
	sclHigh();
	delay();
}

uint8_t soft_i2c::read()
{
	sdaHigh();
	uint8_t number = 0;
	for(int8_t iter = 7; iter >= 0; iter--)
	{
		number <<= 1;
		sclLow();
		delay();
		sclHigh();
		delay();
		if(sdaRead())
		{
			number |= 0x01;
		}
	}
	sclLow();
	delay();
	return number;
}

bool soft_i2c::send(uint8_t package)
{
	for(uint8_t iter = 0x80; iter > 0x00; iter >>=1)
	{
		if(package & iter)
		{
			writeBit(1);
		}
		else
		{
			writeBit(0);
		}
	}
	sclLow();
	delay();
	return true;
}

bool soft_i2c::readAch()
{
	sclLow();
	delay();
	sclHigh();
	delay();
	if(sdaRead())
	{
		sclLow();
		delay();
		return false;
	}
	sclLow();
	delay();
	return true;
}
