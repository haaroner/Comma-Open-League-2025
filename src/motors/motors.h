#pragma once
#include "project_config.h"
#include "motor.h"
#include "tools.h"

class motors 
{
	public:
		motors(Motor& m1, 
					Motor& m2,
					Motor& m3, 
					Motor& m4,
          uint16_t prescaler,
          double dL);
	void moveMotor(int32_t power);
	void stopRobot(uint16_t power);
	void moveRobot(double _maxPower,
										 double _maxPower_angle,
										 double _angle,
										 double _inc,
                     uint32_t _time,
                     uint32_t _instant_start_timer);
  //int lead_to_degree_borders(int _num);
  void disableMotors(); 
  void _move_vector();  
  void change_smoothness(float _smoothness);
	private:
    //int calculate_power(int speed);
		Motor _m1;
		Motor _m2;
		Motor _m3;
		Motor _m4;
    uint16_t _prescaler;
		signed int opowers;
		uint16_t _maxPowerMove;
		double ang;
    double _current_movement[2]; //{angle, speed} - vector
    double _wanted_movement[2]; //{angle, speed} - vector
    uint32_t _last_time_of_call;
    double _dL;
};
