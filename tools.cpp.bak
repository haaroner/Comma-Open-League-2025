#include "tools.h"

int lead_to_degree_borders(int _num)
{
  while(_num < -180 || _num > 180)
  {
    if(_num < -180)
        _num += 360;
    else if(_num > 180)
        _num -= 360;
  }
  return _num;
}

int lead_to_borders(int max, int min, int _num)
{
  while(_num < min || _num > max)
  {
    if(_num < min)
        _num += max - min;
    else if(_num > max)
        _num -= max - min;
  }
  return _num;
}

int _my_abs(int _num)
{
  return int(abs(double(_num)));
}

bool is_in_the_angle_borders(int max, int min, int _num)
{
  if(max < min) 
  {
    int _sub = max;
    max = min;
    min = _sub;
  }
  
  int _maxD = _my_abs(lead_to_degree_borders(max - min));
  
  if(_my_abs(lead_to_degree_borders(max - _num)) < _maxD && _my_abs(lead_to_degree_borders(min - _num)) < _maxD)
    return true;
  else
    return false;
}

bool is_in_the_borders(int max, int min, int num)
{
  return ((num < max && num > min) || (num < max && num > min));
}

int constrain(int max, int min, int _num)
{
  if(_num > max) _num = max;
  else if(_num < min) _num = min;
  
  return _num;
}


float constrainf(float max, float min, float _num)
{
  if(_num > max) _num = max;
  else if(_num < min) _num = min;
  
  return _num;
}