#pragma once
#include "project_config.h"

enum pin_function
{
  read_,
  read_UP,
  read_DOWN,
  write_,
  write_UP,
  write_DOWN,
  uart1,
  uart2,
  uart3,
  uart6,
  i2c, 
  spi1,
  spi2,
  spi3,
  adc,
  tim1,
  tim2,
  tim3,
  tim4,
  tim5,
  tim6,
  tim7,
  tim8,
  tim9,
  tim10,
  tim11,
  tim12,
  tim13,
  tim14,
  dribler_
};

class pin
{
	public:
//		pin(GPIO_TypeDef* GPIOx,
//		uint32_t pinNumber,
//		GPIOMode_TypeDef modeGPIO,
//		GPIOSpeed_TypeDef speedGPIO,
//		GPIOOType_TypeDef typeGPIO,
//		GPIOPuPd_TypeDef pupdGpio,
//		uint16_t pinSourceGPIO,
//		uint8_t AFGPIO);
	pin(char pin_gpio, uint8_t pin_num, uint16_t function);
	void pinInit();
	void pwmInit(uint32_t RCC_TIMx,uint16_t _prescaler, uint32_t _period, uint32_t _start_pulse, uint8_t channel, TIM_TypeDef* TIMx, bool pwm_en);
	void pwm(uint32_t pulse);
	void setBit();
	void resetBit();
  void write(bool _data);
  uint8_t read();
  uint8_t abvgd();
	GPIO_TypeDef* getGPIOx();
  TIM_TypeDef* getTimerx();
  uint8_t getChannel();
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
  uint8_t _function;
  bool _is_tim_configured;
};
