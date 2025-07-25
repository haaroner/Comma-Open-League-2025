#pragma once
#include "project_config.h"
#include "motor.h"
#include "tools.h"
#include "BLDC_Motor.h"

class motors 
{
	public:
		motors(BLDC& m1, 
					BLDC& m2,
					BLDC& m3, 
					BLDC& m4,
          float dL);
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
  void enableMotors();
  void _move_vector();  
  void calibrate();
  void change_smoothness(float _smoothness);
  void change_robot(uint8_t _num);
	private:
    //int calculate_power(int speed);
		BLDC _m1;
		BLDC _m2;
		BLDC _m3;
		BLDC _m4;
  bool _motors_calibrated;
    float Sm1, Sm2, Sm3, Sm4;
    uint16_t _prescaler;
		signed int opowers;
		uint16_t _maxPowerMove;
		double ang, _cur_inc, _inc_max_step;
    double _current_movement[2]; //{angle, speed} - vector
    double _wanted_movement[2]; //{angle, speed} - vector
    uint32_t _last_time_of_call;
    float _dL;
    uint8_t _robot;
};
