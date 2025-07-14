#pragma once

#include "robot_math.h"
#include "Settings.h"
#include "tools.h"
#include "time_service.h"

class PID
{
  public:
    PID(float _kp = 1, float _ki = 0, float _kd = 0, int _max_i = 0)
    {
      kp = _kp;
      ki = _ki;
      kd = _kd;
      p = 0;
      i = 0;
      d = 0;
      max_i = _max_i;
      time = 0;
    }
    
    void set_ratio(float _kp, float _ki, float _kd, int _max_i)
    {
      kp = _kp;
      ki = _ki;
      kd = _kd;
      max_i = _max_i;
    }
    
    void nullification()
    {
      p = 0;
      i = 0;
      d = 0;
    }
    
    int calculate_radially(int x0, int _data)
    {
      if(time_service::getCurTime() - time > 0)
      {
        e = lead_to_degree_borders(x0 - _data);
        p = e * kp;
        d = (e - e_old) * kd;
        i += e * ki;
        
        if(i > max_i) i = max_i;
        else if(i < -max_i) i = -max_i;
        
        u = p;
        e_old = e;
        time = time_service::getCurTime();
      }
      return -u;  
    }
    
    int calculate_lineary(int x0, int _data)
    {
      if(time_service::getCurTime() - time >= 10)
      {
        e = x0 - _data;
        p = e * kp;
        d = (e - e_old) * kd;
        i += e * ki;
        
        if(i > max_i) i = max_i;
        else if(i < -max_i) i = -max_i;
        
        u = p + i+ d;
        e_old = e;
        time = time_service::getCurTime();
      }
      return u;
      
      
    }
    
  private:
    float kp, ki, kd;
    float e, e_old, time, u, max_i;
    float p, i, d;
};
