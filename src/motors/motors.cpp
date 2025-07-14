#include "motors.h"
#include "tools.h"

motors::motors(BLDC& m1, 
					 BLDC& m2,
					 BLDC& m3, 
					 BLDC& m4,
           float dL): _m1(m1),
                                _m2(m2), 
                                _m3(m3), 
                                _m4(m4)
{
    _last_time_of_call = 0;
  _dL = dL;
  _motors_calibrated = false;
  _inc_max_step = 0.05;
  _cur_inc = 0;
  _robot = 1;
}

void motors::disableMotors()
{
  if(_motors_calibrated)
  _m1.disable_motor();
}

void motors::enableMotors()
{
  if(_motors_calibrated)
  _m1.enable_motor();
}

void motors::calibrate()
{
  _m1.callibrate();
  _motors_calibrated = true;
}

void motors::moveRobot(double _maxPower,
										 double _maxPower_angle,
										 double _angle,
										 double _inc,
                     uint32_t _time,
                     uint32_t _instant_start_timer)
{
  //_maxPower = calculate_power(_maxPower);
  //_maxPower_angle = calculate_power(_maxPower_angle);
  //_inc = calculate_power(_inc);
  
  _wanted_movement[0] = lead_to_degree_borders(_angle);
  _wanted_movement[1] = _maxPower;
  
  if(_last_time_of_call == 0 || _time - _instant_start_timer < 500)
  {
    _current_movement[0] = lead_to_degree_borders(_angle);
    _current_movement[1] = _maxPower;
  }
  else
  {
    if(_time - _last_time_of_call > 9)
    {
      _last_time_of_call = _time;
    }
  }
 // if(_time - _last_time_of_call >= 10)
  //{
  _move_vector();
  _angle = lead_to_degree_borders(_current_movement[0]);
  _maxPower = _current_movement[1];
	if(_inc > _maxPower_angle)
		_inc =  _maxPower_angle;
	else if(_inc < -_maxPower_angle)
		_inc =  -_maxPower_angle;
  
 // if(fabs(_inc - _cur_inc) < _inc_max_step) _cur_inc = _inc;
 // else _cur_inc += _inc_max_step * ((_inc - _cur_inc) / fabs(_inc - _cur_inc));
  _cur_inc = _inc;
  
  if(_robot == 1)
  {
    Sm1 = (_maxPower*cosf((_angle + 30) * DEG2RAD));//60 30
    Sm2 = (_maxPower*cosf((_angle + 140) * DEG2RAD));//130  140
    Sm3 = (_maxPower*cosf((_angle - 140) * DEG2RAD));//-130
    Sm4 = (_maxPower*cosf((_angle - 30) * DEG2RAD));//-60
    
    float e = (Sm1 + Sm2 + Sm3 + Sm4) / 4;
    e = 0;
    Sm1 += e;
    Sm2 -= e;
    Sm3 += e;
    Sm4 -= e;

    Sm1 +=_inc;
    Sm2 -=_inc;
    Sm3 +=_inc;
    Sm4 -=_inc;
    //if(_motors_calibrated)
    //{
      _m1.set_speed_percent(-Sm1);
      _m2.set_speed_percent(-Sm2);
      _m3.set_speed_percent(Sm3);
      _m4.set_speed_percent(-Sm4);
    //}
  }
  else
  {
    Sm1 = (_maxPower*cosf((_angle + 30) * DEG2RAD));//60 30
    Sm2 = (_maxPower*cosf((_angle + 140) * DEG2RAD));//130  140
    Sm3 = (_maxPower*cosf((_angle - 140) * DEG2RAD));//-130
    Sm4 = (_maxPower*cosf((_angle - 30) * DEG2RAD));//-60
    
    float e = (Sm1 + Sm2 + Sm3 + Sm4) / 4;
    e = 0;
    Sm1 += e;
    Sm2 -= e;
    Sm3 += e;
    Sm4 -= e;

    Sm1 +=_inc;
    Sm2 -=_inc;
    Sm3 +=_inc;
    Sm4 -=_inc;
    //if(_motors_calibrated)
    //{
      _m1.set_speed_percent(-Sm1);
      _m2.set_speed_percent(-Sm2);
      _m3.set_speed_percent(Sm3);
      _m4.set_speed_percent(Sm4);
    //}
  }
  _last_time_of_call = _time;
  //}
}

void motors::moveMotor(int32_t power)
{
  if(_motors_calibrated)
  {
    _m1.set_speed(power);
    _m2.set_speed(power);
    _m3.set_speed(power);
    _m4.set_speed(power);
  }
}

void motors::change_robot(uint8_t _num)
{
  _robot = _num;
}

void motors::change_smoothness(float _smoothness)
{
  _dL = _smoothness;
}

void motors::_move_vector()
{
  double _x1, _x2, _x3, _x4;
  double _y1, _y2, _y3, _y4;
  double _L;
  double _alpha;
  
  _x1 = sin( _current_movement[0] / 57.3) * _current_movement[1];
  _x2 = sin( _wanted_movement[0] / 57.3) * _wanted_movement[1];
  
  _y1 = cos( _current_movement[0] / 57.3) * _current_movement[1];
  _y2 = cos( _wanted_movement[0] / 57.3) * _wanted_movement[1];
  
  _x3 = _x2 - _x1; // gets projection difference between 2 vectors on Ox
  _y3 = _y2 - _y1; // /=/
  
  _alpha = atan2(_x3, _y3);
  _L = sqrt(double(_x3 * _x3 + _y3 * _y3));
  
  if(_L > _dL)
  {
    _x4 = _dL * sin(_alpha);
    _y4 = _dL * cos(_alpha);
    
    _x1 += _x4;
    _y1 += _y4;
    _current_movement[0] = atan2(_x1, _y1) * 57.3;
    _current_movement[1] = sqrt(_x1 * _x1 + _y1 * _y1);
  }
  else
  {
    _current_movement[0] = _wanted_movement[0];
    _current_movement[1] = _wanted_movement[1];
  }
}


//// you are clown
