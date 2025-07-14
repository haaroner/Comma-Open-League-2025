#include "project_config.h"
#include "pin_setup.h"
#include "time_service.h"
#include "robot_math.h"

enum dribler_speed
{
  stop_dribler_speed = 300,
  standart_dribler_speed = 350,
  minimal_dribler_speed = 315,
  keck_dribler_speed = 235,
  min_keck_speed = 265
  
};

int _cur_speed = 300, change_speed_const = 1;
uint32_t _cur_time = 0;

int change_dribler_speed(int _speed)
{
  if(my_abs(_speed - _cur_speed) < change_speed_const )
    _cur_speed = _speed;
  else
  {
    if(_cur_time != time_service::getCurTime())
    {
      _cur_speed = _cur_speed + my_sgn(_speed - _cur_speed) * change_speed_const;
      _cur_time = time_service::getCurTime();
    }
  }
  if(_cur_speed > 300) _cur_speed = 300;
  else if(_cur_speed < 200) _cur_speed = 200;
  return _cur_speed;
}
