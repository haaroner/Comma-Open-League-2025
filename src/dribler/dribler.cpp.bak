#include "project_config.h"
#include "dribler.h"

dribler::dribler(pin &control_pin, uint8_t tim_num, bool initialization): _control_pin(control_pin)
{
  _init_pulse = 150;
  _cur_speed = 0;
  _max_speed = 80;//may be 90
  _min_speed = -80;
  _cur_time = 0;
  _control_pin.pwmInit(RCC_APB1ENR_TIM3EN, 159, 2000, 0, 3, TIM3, 1);
  _control_pin.pwm(150);
  if(initialization)
    time_service::delay_ms(3000);
}
void dribler::set_speed(int16_t speed, uint16_t d_speed)
{
  if(time_service::getCurTime() != _cur_time)
  {
    if(speed <= _max_speed && speed >= _min_speed)
    {
      _control_pin.pwm(convert_to_pulse(speed));
      if(abs(double(speed - _cur_speed)) > d_speed)
        _cur_speed += d_speed * (abs(double(speed)) / speed);
      else
        _cur_speed = speed;
      
      _control_pin.pwm(convert_to_pulse(_cur_speed));
    }
    _cur_time = time_service::getCurTime();
  }
}

uint16_t dribler::convert_to_pulse(int16_t data)
{
  if(data <= _max_speed + 150 && data >= _min_speed + 150)//
    return data + 150;
  else return 0;
}
