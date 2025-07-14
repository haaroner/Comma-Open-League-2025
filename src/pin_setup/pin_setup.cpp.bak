#include "pin_setup.h"

#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3
#define CHANNEL4 4

pin::pin(char pin_gpio, uint8_t pin_num, uint16_t function)
{
  _function = function;
  _is_tim_configured = false;
	if(pin_gpio == 'A') _GPIOx = GPIOA;
	else if(pin_gpio == 'B') _GPIOx = GPIOB;
	else if(pin_gpio == 'C') _GPIOx = GPIOC;
	else if(pin_gpio == 'D') _GPIOx = GPIOD;
	else if(pin_gpio == 'E') _GPIOx = GPIOE;
	else if(pin_gpio == 'F') _GPIOx = GPIOF;
	else if(pin_gpio == 'G') _GPIOx = GPIOG;
	else if(pin_gpio == 'H') _GPIOx = GPIOH;
	else if(pin_gpio == 'I') _GPIOx = GPIOI;
	
	if(pin_num == 0) { _pinNumber = GPIO_Pin_0; _pinSourceGPIO = GPIO_PinSource0;}
	else if(pin_num == 1)  {_pinNumber = GPIO_Pin_1; _pinSourceGPIO = GPIO_PinSource1;}
	else if(pin_num == 2)  {_pinNumber = GPIO_Pin_2; _pinSourceGPIO = GPIO_PinSource2;}
	else if(pin_num == 3)  {_pinNumber = GPIO_Pin_3; _pinSourceGPIO = GPIO_PinSource3;}
	else if(pin_num == 4)  {_pinNumber = GPIO_Pin_4; _pinSourceGPIO = GPIO_PinSource4;}
	else if(pin_num == 5)  {_pinNumber = GPIO_Pin_5; _pinSourceGPIO = GPIO_PinSource5;}
	else if(pin_num == 6)  {_pinNumber = GPIO_Pin_6; _pinSourceGPIO = GPIO_PinSource6;}
	else if(pin_num == 7)  {_pinNumber = GPIO_Pin_7; _pinSourceGPIO = GPIO_PinSource7;}
	else if(pin_num == 8)  {_pinNumber = GPIO_Pin_8; _pinSourceGPIO = GPIO_PinSource8;}
	else if(pin_num == 9)  {_pinNumber = GPIO_Pin_9; _pinSourceGPIO = GPIO_PinSource9;}
	else if(pin_num == 10)  {_pinNumber = GPIO_Pin_10; _pinSourceGPIO = GPIO_PinSource10;}
	else if(pin_num == 11)  {_pinNumber = GPIO_Pin_11; _pinSourceGPIO = GPIO_PinSource11;}
	else if(pin_num == 12)  {_pinNumber = GPIO_Pin_12; _pinSourceGPIO = GPIO_PinSource12;}
	else if(pin_num == 13)  {_pinNumber = GPIO_Pin_13; _pinSourceGPIO = GPIO_PinSource13;}
	else if(pin_num == 14)  {_pinNumber = GPIO_Pin_14; _pinSourceGPIO = GPIO_PinSource14;}
	else if(pin_num == 15)  {_pinNumber = GPIO_Pin_15; _pinSourceGPIO = GPIO_PinSource15;}
	
	if(function == uart1 || function == uart2 || function == uart3 || function == uart6)//uarts(1, 2, 3, 6)
	{
		_modeGPIO = GPIO_Mode_AF;
		_speedGPIO = GPIO_Speed_100MHz;
		_typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_DOWN;
		if(function == uart1) _AFGPIO = GPIO_AF_USART1;
		if(function == uart2) _AFGPIO = GPIO_AF_USART2;
		if(function == uart3) _AFGPIO = GPIO_AF_USART3;
		if(function == uart6) _AFGPIO = GPIO_AF_USART6;
	}
	else if(function == i2c) //i2c
	{
		_modeGPIO = GPIO_Mode_OUT;
		_speedGPIO = GPIO_Speed_100MHz;
		_typeGPIO = GPIO_OType_OD;
		_pupdGpio = GPIO_PuPd_UP;
		_AFGPIO = GPIO_AF_I2C3;
	}
	else if(function == read_UP)//read with pupd_UP
	{
		_modeGPIO = GPIO_Mode_IN;
		_speedGPIO = GPIO_Speed_100MHz;
		_typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_UP;
		_AFGPIO = GPIO_AF_I2C3;
	}
	else if(function == read_)//write
	{
		_modeGPIO = GPIO_Mode_OUT;
		_speedGPIO = GPIO_Speed_100MHz;
		_typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_NOPULL;
		_AFGPIO = GPIO_AF_I2C3;
	}
  else if(function == write_UP)//write_UP
	{
		_modeGPIO = GPIO_Mode_OUT;
		_speedGPIO = GPIO_Speed_100MHz;
		_typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_UP;
		_AFGPIO = GPIO_AF_I2C3;
	}
  else if(function == read_DOWN) //read_DOWN
  {
		_modeGPIO = GPIO_Mode_IN;
		_speedGPIO = GPIO_Speed_50MHz;
		_typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_DOWN;
		_AFGPIO = GPIO_AF_I2C3; 
  }
	else if(function == tim1 || function == tim2 || function == tim3 || function == tim4 || function == tim5 || 
		function == tim6 || function == tim7 || function == tim8 || function == tim9 || function == tim10 || function == tim11 ||
	function == tim12 || function == tim13 || function == tim14)
	{
		_modeGPIO = GPIO_Mode_AF;
		_speedGPIO = GPIO_Speed_100MHz;
		_typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_NOPULL;
		if(function == tim1) _AFGPIO = GPIO_AF_TIM1;
		else if(function == tim2) _AFGPIO = GPIO_AF_TIM2;
		else if(function == tim3) _AFGPIO = GPIO_AF_TIM3;
		else if(function == tim4) _AFGPIO = GPIO_AF_TIM4;
		else if(function == tim5) _AFGPIO = GPIO_AF_TIM5;
		else if(function == tim8) _AFGPIO = GPIO_AF_TIM8;
		else if(function == tim9) _AFGPIO = GPIO_AF_TIM9;
		else if(function == tim10) _AFGPIO = GPIO_AF_TIM10;
		else if(function == tim11) _AFGPIO = GPIO_AF_TIM11;
		else if(function == tim12) _AFGPIO = GPIO_AF_TIM12;
		else if(function == tim13) _AFGPIO = GPIO_AF_TIM13;
		else if(function == tim14) _AFGPIO = GPIO_AF_TIM14;
		_is_tim_configured = true;
	}
  else if(function == spi1) //spi1
	{
		_modeGPIO = GPIO_Mode_AF;
		_speedGPIO = GPIO_Speed_100MHz;
		_typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_NOPULL;
		_AFGPIO = GPIO_AF_SPI1;
	}
  else if(function == spi2) //spi2
	{
		_modeGPIO = GPIO_Mode_AF;
		_speedGPIO = GPIO_Speed_100MHz;
		_typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_NOPULL;
		_AFGPIO = GPIO_AF_SPI2;
	}
  else if(function == spi3) //spi3
	{
		_modeGPIO = GPIO_Mode_AF;
		_speedGPIO = GPIO_Speed_100MHz;
		_typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_NOPULL;
		_AFGPIO = GPIO_AF_SPI3;
	}
  else if(function == adc) // adc
  {
    _modeGPIO = GPIO_Mode_AN;
    _speedGPIO = GPIO_Speed_100MHz;
    _typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_NOPULL;
		_AFGPIO = GPIO_AF_TIM3;
  }
	else if(function == write_)
	{
		_modeGPIO = GPIO_Mode_OUT;
		_speedGPIO = GPIO_Speed_100MHz;
		_typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_NOPULL;
		_AFGPIO = GPIO_AF_I2C3;
	}
  else if(function == write_DOWN)
	{
		_modeGPIO = GPIO_Mode_OUT;
		_speedGPIO = GPIO_Speed_50MHz;
		_typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_DOWN;
		_AFGPIO = GPIO_AF_I2C3;
	}
  else if(function == read_)
	{
		_modeGPIO = GPIO_Mode_IN;
		_speedGPIO = GPIO_Speed_100MHz;
		_typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_NOPULL;
		_AFGPIO = GPIO_AF_I2C3;
	}
  else if(function == dribler_)
  {
    _modeGPIO = GPIO_Mode_AF;
		_speedGPIO = GPIO_Speed_100MHz;
		_typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_NOPULL;
    _AFGPIO = GPIO_AF_TIM3;
    pin::pinInit();
    pin::pwmInit(RCC_APB1ENR_TIM3EN, 840, 4000, 0, 1, TIM3, 1);
  }
  else if(function == dribler_new)
  {
    _modeGPIO = GPIO_Mode_AF;
		_speedGPIO = GPIO_Speed_100MHz;
		_typeGPIO = GPIO_OType_PP;
		_pupdGpio = GPIO_PuPd_NOPULL;
    _AFGPIO = GPIO_AF_TIM2;
    pin::pinInit();
    pin::pwmInit(RCC_APB1ENR_TIM2EN, 839, 4000, 0, 2, TIM2, 1);
  }
  if(function != dribler_) pin::pinInit();
}

void pin::pinInit()
{
	if(_GPIOx == GPIOA) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 
	else if(_GPIOx == GPIOB) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	else if(_GPIOx == GPIOC) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	else if(_GPIOx == GPIOD) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	else if(_GPIOx == GPIOE) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	else if(_GPIOx == GPIOF) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	else if(_GPIOx == GPIOG) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	else if(_GPIOx == GPIOH) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	else if(_GPIOx == GPIOI) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
	
	GPIO_InitTypeDef Pin;
	Pin.GPIO_Pin = _pinNumber;
	Pin.GPIO_Mode = _modeGPIO;
	Pin.GPIO_Speed = _speedGPIO;
	Pin.GPIO_OType = _typeGPIO;
	Pin.GPIO_PuPd = _pupdGpio;
	GPIO_Init(_GPIOx, &Pin);
	
	if(_modeGPIO == GPIO_Mode_AF)
	{
		GPIO_PinAFConfig(_GPIOx,_pinSourceGPIO, _AFGPIO);
	}		
}

void pin::setBit()
{
  GPIO_SetBits(_GPIOx, _pinNumber);
}

void pin::resetBit()
{
  GPIO_ResetBits(_GPIOx, _pinNumber);
}

void pin::write(bool _data)
{
  if(_data)
    GPIO_SetBits(_GPIOx, _pinNumber);
  else
    GPIO_ResetBits(_GPIOx, _pinNumber);
}

uint8_t pin::read()
{
  return getGPIOx() -> IDR & getPinNumber();
}

GPIO_TypeDef* pin::getGPIOx()
{
	return _GPIOx;
}

uint8_t pin::abvgd()
{
  return getGPIOx() -> IDR;
}
	
uint16_t pin::getPinNumber()
{
	return _pinNumber;
}

void pin::pwmInit(uint32_t RCC_TIMx,uint16_t _prescaler, uint32_t _period, uint32_t  _start_pulse, uint8_t channel, TIM_TypeDef* TIMx, bool pwm_en)
{
	_TIMx = TIMx;
	_channel = channel;
	if(_TIMx == TIM1) RCC_APB2PeriphClockCmd(RCC_TIMx, ENABLE);
	else if(_TIMx == TIM2) RCC_APB1PeriphClockCmd(RCC_TIMx, ENABLE);
	else if(_TIMx == TIM3) RCC_APB1PeriphClockCmd(RCC_TIMx, ENABLE);
	else if(_TIMx == TIM4) RCC_APB1PeriphClockCmd(RCC_TIMx, ENABLE);
	else if(_TIMx == TIM5) RCC_APB1PeriphClockCmd(RCC_TIMx, ENABLE);
	else if(_TIMx == TIM6) RCC_APB1PeriphClockCmd(RCC_TIMx, ENABLE);
	else if(_TIMx == TIM7) RCC_APB1PeriphClockCmd(RCC_TIMx, ENABLE);
	else if(_TIMx == TIM8) RCC_APB2PeriphClockCmd(RCC_TIMx, ENABLE);
	else if(_TIMx == TIM9) RCC_APB2PeriphClockCmd(RCC_TIMx, ENABLE);
	else if(_TIMx == TIM10) RCC_APB2PeriphClockCmd(RCC_TIMx, ENABLE);
	else if(_TIMx == TIM11) RCC_APB2PeriphClockCmd(RCC_TIMx, ENABLE);
	else if(_TIMx == TIM12) RCC_APB1PeriphClockCmd(RCC_TIMx, ENABLE);
	else if(_TIMx == TIM13) RCC_APB1PeriphClockCmd(RCC_TIMx, ENABLE);
	else if(_TIMx == TIM14) RCC_APB1PeriphClockCmd(RCC_TIMx, ENABLE);
	
	TIM_TimeBaseInitTypeDef time;
  time.TIM_Prescaler = _prescaler;
	time.TIM_CounterMode = TIM_CounterMode_Up;
	time.TIM_Period = _period;
	time.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(_TIMx, &time);
	TIM_Cmd(_TIMx,ENABLE);
	
	if (_TIMx == TIM1)
	{
		TIM_BDTRInitTypeDef ch1;
		ch1.TIM_OSSRState = TIM_OSSRState_Disable;
		ch1.TIM_OSSIState = TIM_OSSIState_Disable;
		ch1.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
		ch1.TIM_DeadTime = 0;
		ch1.TIM_Break = TIM_Break_Disable;
		ch1.TIM_BreakPolarity = TIM_BreakPolarity_High;
		ch1.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
		TIM_BDTRConfig(TIM1, &ch1);
	}
	
	TIM_OCInitTypeDef ch;
  if(pwm_en == 1) ch.TIM_OCMode = TIM_OCMode_PWM1;
  else ch.TIM_OCMode = TIM_OCMode_Timing;
	ch.TIM_OutputState = TIM_OutputState_Enable;
	if(_TIMx != TIM1)ch.TIM_OutputNState = TIM_OutputNState_Disable;
	else ch.TIM_OutputNState = TIM_OutputNState_Enable;
	ch.TIM_Pulse = 0;
	ch.TIM_OCPolarity = TIM_OCPolarity_High;
	ch.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	if(_TIMx != TIM1)ch.TIM_OCIdleState = TIM_OCIdleState_Set;
		else ch.TIM_OCIdleState = TIM_OCIdleState_Reset;
	if(_TIMx != TIM1)ch.TIM_OCNIdleState = TIM_OCNIdleState_Set;
		else ch.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	
	if(_channel == CHANNEL1)
	{
		TIM_OC1Init(_TIMx, &ch);
	}
	else if(_channel == CHANNEL2)
	{
		TIM_OC2Init(_TIMx, & ch);
	
	}
	else if(_channel == CHANNEL3)
	{
		TIM_OC3Init(_TIMx, & ch);
	
	}
	else if(_channel == CHANNEL4)
	{
		TIM_OC4Init(_TIMx, & ch);
	
	}
	TIM_Cmd(_TIMx,ENABLE);
	if(_TIMx == TIM1) TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void pin::pwm(uint32_t pulse)
{
if(_channel == CHANNEL1)
	{
		TIM_SetCompare1(_TIMx,pulse);
	}
	else if(_channel == CHANNEL2)
	{
		TIM_SetCompare2(_TIMx,pulse);
	
	}
	else if(_channel == CHANNEL3)
	{
		TIM_SetCompare3(_TIMx,pulse);
	
	}
	else if(_channel == CHANNEL4)
	{
		TIM_SetCompare4(_TIMx,pulse);
	}
}

TIM_TypeDef* pin::getTimerx()
{
  if(_is_tim_configured)
    return _TIMx;
  else 
    return NULL; 
}

uint8_t pin::getChannel()
{
  if(_is_tim_configured)
    return _channel;
  else
    return NULL;
}
