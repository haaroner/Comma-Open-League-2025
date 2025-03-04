#pragma once
#include "project_config.h"


class Motor_Pin
{
	public:
		Motor_Pin(GPIO_TypeDef* GPIOx,
		uint32_t pinNumber,
		uint16_t pinSourceGPIO,
		uint8_t AFGPIO);
	void pinInit();
	void pwmInit(uint32_t RCC_TIMx,uint8_t channel, TIM_TypeDef* TIMx);
	void pwm(uint32_t pulse);
	void setBit();
	void resetBit();
	GPIO_TypeDef* getGPIOx();
	uint16_t getPinNumber();
	private:
		GPIO_TypeDef* _GPIOx;
		uint32_t _pinNumber;
		GPIOMode_TypeDef _modeGPIO;
		GPIOSpeed_TypeDef _speedGPIO;
		GPIOOType_TypeDef _typeGPIO;
		GPIOPuPd_TypeDef _pupdGpio;
	uint16_t _pinSourceGPIO;
	uint8_t _AFGPIO;
	TIM_TypeDef* _TIMx;
	uint8_t _channel;
		
};
