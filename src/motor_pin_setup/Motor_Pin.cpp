#include "Motor_Pin.h"

#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3
#define CHANNEL4 4

Motor_Pin::Motor_Pin(GPIO_TypeDef* GPIOx,
											uint32_t pinNumber,
											uint16_t pinSourceGPIO,
											uint8_t AFGPIO)
{
	_GPIOx = GPIOx;
	_pinNumber = pinNumber;
	_modeGPIO = GPIO_Mode_AF;
	_speedGPIO = GPIO_Speed_100MHz;
	_typeGPIO = GPIO_OType_PP;
	_pupdGpio = GPIO_PuPd_NOPULL;	
	_pinSourceGPIO = pinSourceGPIO;
	_AFGPIO = AFGPIO;
}

void Motor_Pin::pinInit()
{
	if(_GPIOx ==GPIOA) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 
	else if(_GPIOx ==GPIOB) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	else if(_GPIOx ==GPIOC) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	else if(_GPIOx ==GPIOD) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	else if(_GPIOx ==GPIOE) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	else if(_GPIOx ==GPIOF) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	else if(_GPIOx ==GPIOG) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	else if(_GPIOx ==GPIOH) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	else if(_GPIOx ==GPIOI) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
	
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

void Motor_Pin::setBit()
{
GPIO_SetBits(_GPIOx, _pinNumber);
}

void Motor_Pin::resetBit()
{
GPIO_ResetBits(_GPIOx, _pinNumber);
}

GPIO_TypeDef* Motor_Pin::getGPIOx()
{
	return _GPIOx;
}
	
uint16_t Motor_Pin::getPinNumber()
{
	return _pinNumber;
}

void Motor_Pin::pwmInit(uint32_t RCC_TIMx, uint8_t channel, TIM_TypeDef* TIMx)
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
	time.TIM_Prescaler = 1; 
	time.TIM_CounterMode = TIM_CounterMode_Up;
	time.TIM_Period = 4096;
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
	ch.TIM_OCMode = TIM_OCMode_PWM1;
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



void Motor_Pin::pwm(uint32_t pulse)
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


