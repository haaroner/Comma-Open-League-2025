#include "project_config.h"
#include "robot_math.h"
#include "Points.h"
#define ec 2.7182

double _data, angK, distK;

double convert_dist(double max_dist, double dist)
{
  _data = (dist - max_dist) / max_dist + 1;
  
  if(_data > 1)
    _data = 1;
  else if(_data < 0)
    _data = 0;
  
  return _data;
}

int16_t exponential_detour(double ball_angle, double distance, double k1_angle, double k2_angle, double k1_dist, double k2_dist)
{
  angK = k1_angle * pow(ec, double(k2_angle * abs(ball_angle)));
  
  if(angK > 90)
    angK = 90;
  
  distance = convert_dist(7, distance);
  
  distK = k1_dist * pow(ec, double(k2_dist * distance));
  
  if(distK > 1)
    distK = 1;
  
  if(ball_angle > 0)
    _data = angK * distK;
  else
    _data = -angK * distK;
  
  return _data;
}

float new_velocity(int _ball_dist)
{
  float _result_speed;
  if(_ball_dist < Points::speed_1.x)
    return Points::speed_1.y;
  else if(_ball_dist < Points::speed_2.x)
    return get_y_from_line(get_line_from_points(Points::speed_1, Points::speed_2), _ball_dist);
  else if(_ball_dist < Points::speed_3.x)
    return get_y_from_line(get_line_from_points(Points::speed_2, Points::speed_3), _ball_dist);
  else
    return Points::speed_3.y;
}

float new_defender_velocity(int _dist)
{
  float _result_speed;
  if(_dist < Points::defender_speed_1.x)
    return Points::defender_speed_1.y;
  else if(_dist < Points::defender_speed_2.x)
    return get_y_from_line(get_line_from_points(Points::defender_speed_1, Points::defender_speed_2), _dist);
  else if(_dist < Points::defender_speed_3.x)
    return get_y_from_line(get_line_from_points(Points::defender_speed_2, Points::defender_speed_3), _dist);
  else
    return Points::defender_speed_3.y;
}
