#pragma once
#include <project_config.h>
#include <motor_test.h>
#include "math.h"

class test_motors
{
	public:
		test_motors(Motor_test &m3, 
           Motor_test &m4);
	void moveMotor(int32_t power);
	void stopRobot();
	void moveRobot(int _maxPower,
										 int _maxPower_angle,
										 int _angle,
										 int _inc);
                     
	private:
		Motor_test _m3;
    Motor_test _m4;
		signed int opowers;
		uint16_t _maxPowerMove;
		double ang;
};
