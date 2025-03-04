#include "motors.h"
#include "tools.h"

motors::motors(Motor& m1, 
					 Motor& m2,
					 Motor& m3, 
					 Motor& m4,
           uint16_t prescaler,
           double dL): _m1(m1),
                                _m2(m2), 
                                _m3(m3), 
                                _m4(m4)
{
		_prescaler = prescaler;
    _last_time_of_call = 0;
  _dL = dL;
  
}

//int motors::lead_to_degree_borders(int _num)
//{
//  while(_num < -180 || _num > 180)
//  {
//    if(_num < -180)
//        _num += 360;
//    else if(_num > 180)
//        _num -= 360;
//  }
//  return _num;
//}

void motors::moveMotor(int32_t power)
{
		_m1.motorMove(power);//power);//without
		_m2.motorMove(power);//-power);//green right
		_m3.motorMove(power);//white
		_m4.motorMove(power);//-power);//blue right
}

void motors::stopRobot(uint16_t _power)
{
  //_power = calculate_power(_power);
	_m1.blockMotor(_power);
	_m2.blockMotor(_power);
	_m3.blockMotor(_power);
	_m4.blockMotor(_power);
}

void motors::disableMotors()
{
  _m1.disableMotor();
  _m2.disableMotor();
  _m3.disableMotor();
  _m4.disableMotor();
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
    if(_time - _last_time_of_call > 0)
    {
      _move_vector();
      _last_time_of_call = _time;
    }
  }
  
  _last_time_of_call = _time;
  
  _angle = lead_to_degree_borders(_current_movement[0]);
  _maxPower = _current_movement[1];
  
	if(_inc > _maxPower_angle)
		_inc =  _maxPower_angle;
	else if(_inc < -_maxPower_angle)
		_inc =  -_maxPower_angle;
  
	ang = (_angle + 125) * DEG2RAD;
	opowers = int(_maxPower * -cos(ang));
	opowers -= _inc;
	_m2.motorMove(opowers);
	
	ang = (_angle - 125) * DEG2RAD;
	opowers = int(_maxPower * cos(ang));
	opowers += _inc;
	_m1.motorMove(opowers);

	
	ang = (_angle + 55) * DEG2RAD;
	opowers = int(_maxPower * -cos(ang));
	opowers -= _inc;
	_m3.motorMove(opowers);

	
	ang = (_angle - 55) * DEG2RAD;
	opowers = int(_maxPower * -cos(ang));
	opowers -= _inc;
	_m4.motorMove(opowers);
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
