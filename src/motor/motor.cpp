#include "motor.h"

#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3
#define CHANNEL4 4

Motor::Motor(char pin_gpio1, uint8_t pin_num1, uint16_t _tim1, uint8_t channel1, 
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
	else if(_tim1 == tim7) {_TIMx1 = TIM7; _RCC_TIMx1 = RCC_APB1ENR_TIM7EN;}
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
	else if(_tim2 == tim7) {_TIMx2 = TIM7; _RCC_TIMx2 = RCC_APB1ENR_TIM7EN;}
	else if(_tim2 == tim8) {_TIMx2 = TIM8; _RCC_TIMx2 = RCC_APB2ENR_TIM8EN;}
	else if(_tim2 == tim9) {_TIMx2 = TIM9; _RCC_TIMx2 = RCC_APB2ENR_TIM9EN;}
	else if(_tim2 == tim10) {_TIMx2 = TIM10; _RCC_TIMx2 = RCC_APB2ENR_TIM10EN;}
	else if(_tim2 == tim11) {_TIMx2 = TIM11; _RCC_TIMx2 = RCC_APB2ENR_TIM11EN;}
	else if(_tim2 == tim12) {_TIMx2 = TIM12; _RCC_TIMx2 = RCC_APB1ENR_TIM12EN;}
	else if(_tim2 == tim13) {_TIMx2 = TIM13; _RCC_TIMx2 = RCC_APB1ENR_TIM13EN;}
	else if(_tim2 == tim14) {_TIMx2 = TIM14; _RCC_TIMx2 = RCC_APB1ENR_TIM14EN;}
	
	_p1.pwmInit(_RCC_TIMx1, 1, 4000, 0, channel1, _TIMx1, 1);	
	_p2.pwmInit(_RCC_TIMx2, 1, 4000, 0, channel2, _TIMx2, 1);
}

void Motor::motorMove(double pupower)
{
  //if(abs(double(pupower)) < 13)
  //{
    //if(pupower > 0)
      //pupower = 1/((13 - pupower) * 0.0002442);
    //else
      //pupower = -1 / ((13 - abs(double(pupower))) * 0.0002442);
  //}
  //else
  //{
    //pupower = 4095 * (abs(double(pupower)) / pupower);
  //}
  if(pupower < 0) power_sgn = -1;
  else power_sgn = 1;
  pupower = int(pow(int((pupower/30.03) / 0.0000183902 * power_sgn), 0.6851) * power_sgn);//0.6851    68803946594376
	if(pupower <= -1)
	{
		pupower = -4000 - pupower;
		if(pupower < -4000)
		{
			pupower = -4000;
		}
		_p1.pwm(pupower * -1);
		_p2.pwm(4000);
	}
	else
	{
		pupower = 4000 - pupower;
		if(pupower > 4000)
		{
			pupower = 4000;
		}
		_p1.pwm(4000);
		_p2.pwm(pupower);
	}
}

void Motor::disableMotor()
{
  _p1.pwm(0);
  _p2.pwm(0);
}

void Motor::blockMotor(int32_t pupower)
{
	_p1.pwm(pupower);
	_p2.pwm(pupower);
}
