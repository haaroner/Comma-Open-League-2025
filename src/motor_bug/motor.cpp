#include "motor_test.h"
#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3
#define CHANNEL4 4

#define tim1 81
#define tim2 82
#define tim3 83
#define tim4 84
#define tim5 85
#define tim8 88
#define tim9 89
#define tim10 810
#define tim11 811
#define tim12 812
#define tim13 813
#define tim14 814

//Motor::Motor(GPIO_TypeDef* GPIOx,
//											uint32_t pinNumber,
//											uint16_t pinSourceGPIO,
//											uint8_t AFGPIO, 
//						 GPIO_TypeDef* GPIOx2,
//											uint32_t pinNumber2,
//											uint16_t pinSourceGPIO2,
//											uint8_t AFGPIO2):
//																					_p1(GPIOx,
//																					pinNumber,
//																					GPIO_Mode_AF,
//																					GPIO_Speed_100MHz,
//																					GPIO_OType_PP, 
//																					GPIO_PuPd_NOPULL,
//																					pinSourceGPIO,
//																					AFGPIO),
//																				_p2(GPIOx2,
//																					pinNumber2,
//																					GPIO_Mode_AF,
//																					GPIO_Speed_100MHz,
//																					GPIO_OType_PP, 
//																					GPIO_PuPd_NOPULL,
//																					pinSourceGPIO2,
//																					AFGPIO2)
//{
//	
//	_p1.pinInit();	
//	_p2.pinInit();
//	
//}

Motor_test::Motor_test(char pin_gpio1, uint8_t pin_num1, uint16_t _tim1, uint8_t channel1, 
							char pin_gpio2, uint8_t pin_num2, uint16_t _tim2, uint8_t channel2): _p1(pin_gpio1, pin_num1, _tim1), 
								_p2(pin_gpio2, pin_num2, _tim2)
{
	_p1.pinInit();
	_p2.pinInit();
	if(_tim1 == tim1) {_TIMx1 = TIM1; _RCC_TIMx1 = RCC_APB2ENR_TIM1EN;}
	else if(_tim1 == tim2) {_TIMx1 = TIM2; _RCC_TIMx1 = RCC_APB1ENR_TIM2EN;}
	else if(_tim1 == tim3) {_TIMx1 = TIM3; _RCC_TIMx1 = RCC_APB1ENR_TIM3EN;}
	else if(_tim1 == tim4) {_TIMx1 = TIM4; _RCC_TIMx1 = RCC_APB1ENR_TIM4EN;}
	else if(_tim1 == tim5) {_TIMx1 = TIM5; _RCC_TIMx1 = RCC_APB1ENR_TIM5EN;}
	//else if(_tim1 == tim6) {_TIMx1 = TIM6; _RCC_TIMx1 = RCC_APB1ENR_TIM6EN;}
	//else if(_tim1 == tim7) {_TIMx1 = TIM7; _RCC_TIMx1 = RCC_APB1ENR_TIM7EN;}
	else if(_tim1 == tim8) {_TIMx1 = TIM8; _RCC_TIMx1 = RCC_APB2ENR_TIM8EN;}
	else if(_tim1 == tim9) {_TIMx1 = TIM9; _RCC_TIMx1 = RCC_APB2ENR_TIM9EN;}
	else if(_tim1 == tim10) {_TIMx1 = TIM10; _RCC_TIMx1 = RCC_APB2ENR_TIM10EN;}
	else if(_tim1 == tim11) {_TIMx1 = TIM11; _RCC_TIMx1 = RCC_APB2ENR_TIM11EN;}
	else if(_tim1 == tim12) {_TIMx1 = TIM12; _RCC_TIMx1 = RCC_APB1ENR_TIM12EN;}
	else if(_tim1 == tim13) {_TIMx1 = TIM13; _RCC_TIMx1 = RCC_APB1ENR_TIM13EN;}
	else if(_tim1 == tim14) {_TIMx1 = TIM14; _RCC_TIMx1 = RCC_APB1ENR_TIM14EN;}
	
	if(_tim2 == tim1) {_TIMx2 = TIM1; _RCC_TIMx2 = RCC_APB2ENR_TIM1EN;}
	else if(_tim2 == tim2) {_TIMx2 = TIM2; _RCC_TIMx2 = RCC_APB1ENR_TIM2EN;}
	else if(_tim2 == tim3) {_TIMx2 = TIM3; _RCC_TIMx2 = RCC_APB1ENR_TIM3EN;}
	else if(_tim2 == tim4) {_TIMx2 = TIM4; _RCC_TIMx2 = RCC_APB1ENR_TIM4EN;}
	else if(_tim2 == tim5) {_TIMx2 = TIM5; _RCC_TIMx2 = RCC_APB1ENR_TIM5EN;}
	//else if(_tim2 == tim6) {_TIMx2 = TIM6; _RCC_TIMx2 = RCC_APB1ENR_TIM6EN;}
	//else if(_tim2 == tim7) {_TIMx2 = TIM7; _RCC_TIMx2 = RCC_APB1ENR_TIM7EN;}
	else if(_tim2 == tim8) {_TIMx2 = TIM8; _RCC_TIMx2 = RCC_APB2ENR_TIM8EN;}
	else if(_tim2 == tim9) {_TIMx2 = TIM9; _RCC_TIMx2 = RCC_APB2ENR_TIM9EN;}
	else if(_tim2 == tim10) {_TIMx2 = TIM10; _RCC_TIMx2 = RCC_APB2ENR_TIM10EN;}
	else if(_tim2 == tim11) {_TIMx2 = TIM11; _RCC_TIMx2 = RCC_APB2ENR_TIM11EN;}
	else if(_tim2 == tim12) {_TIMx2 = TIM12; _RCC_TIMx2 = RCC_APB1ENR_TIM12EN;}
	else if(_tim2 == tim13) {_TIMx2 = TIM13; _RCC_TIMx2 = RCC_APB1ENR_TIM13EN;}
	else if(_tim2 == tim14) {_TIMx2 = TIM14; _RCC_TIMx2 = RCC_APB1ENR_TIM14EN;}
	
	_p1.pwmInit(_RCC_TIMx1, 2, 4096, 0, channel1, _TIMx1);	
	_p2.pwmInit(_RCC_TIMx2, 2, 4096, 0, channel2, _TIMx2);
}

//void Motor::motorPWMInit(uint32_t RCC_TIMx1,
//													uint8_t channel1,
//													TIM_TypeDef* TIMx1,
//													uint32_t RCC_TIMx2,
//													uint8_t channel2,
//													TIM_TypeDef* TIMx2)
//{
//	
//	_p1.pwmInit(RCC_TIMx1, 2, 4096, 0, channel1, TIMx1);	
//	_p2.pwmInit(RCC_TIMx2, 2, 4096, 0, channel2, TIMx2);
//	
//}

void Motor_test::motorMove(int32_t pupower)
{
	if(pupower <= -1)
	{
		pupower = -4096 - pupower;
		if(pupower < -4095)
		{
			pupower = -4095;
		}
		_p1.pwm(pupower * -1);
		_p2.pwm(4095);
	}
	else
	{
		pupower = 4096 - pupower;
		if(pupower > 4095)
		{
			pupower = 4095;
		}
		_p1.pwm(4095);
		_p2.pwm(pupower);
	}
}

void Motor_test::blockMotor(int32_t pupower)
{
	_p1.pwm(pupower);
	_p2.pwm(pupower);
}
