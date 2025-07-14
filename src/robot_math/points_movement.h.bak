#pragma once

#include "project_config.h"
#include "robot_math.h"

class point_trajectory
{
  public:
    point_trajectory(int (&points)[10][2], uint8_t num_of_points, uint8_t min_dL):_points(points)
    {
      
      _num_of_points = num_of_points;
      _cur_point = 0;
      _min_dL = min_dL;
    }
    void start_trajectory(int start_point, int _robot_x, int _robot_y)
    {
      _cur_point = 0;
      _trajectory_distance = get_distance_to_point(_robot_x, _robot_y,_points[_cur_point][0], _points[_cur_point][1]);
    }
    void calculate_trajectory(int _robot_x, int _robot_y)
    {
      if(_trajectory_distance < _min_dL)
      {
        if(_cur_point == _num_of_points - 1) _cur_point = -1;
        else _cur_point++;
      }
      
      _trajectory_angle = get_angle_to_point(_robot_x, _robot_y,_points[_cur_point][0], _points[_cur_point][1]);
      _trajectory_distance = get_distance_to_point(_robot_x, _robot_y,_points[_cur_point][0], _points[_cur_point][1]);
      
    }
    int16_t get_angle();
    uint16_t get_distance();
  private:
    int (&_points)[10][2];
    int16_t _trajectory_angle;
    uint16_t _trajectory_distance;
    uint8_t _num_of_points;
    int8_t _cur_point;
    uint8_t _min_dL;
};