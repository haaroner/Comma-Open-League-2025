#pragma once
#include <project_config.h>
#include <pin_setup.h>
#include "soft_i2c.h"
class IRlocator
{
	public:
		IRlocator(soft_i2c &irI2C, uint32_t addres);
		int16_t getData(uint8_t data);
	private:
		soft_i2c m_irI2C;
		uint32_t m_addres;
};
