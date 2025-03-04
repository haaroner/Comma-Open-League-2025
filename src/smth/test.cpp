#include "test.h"

test_motors::test_motors(Motor_test &m3, Motor_test &m4): _m3(m3), _m4(m4)
                                      
{
		
}
void test_motors::moveMotor(int32_t power)
{
		_m3.motorMove(-power);//without
	//	_m2.motorMove(-power);//green right
		//_m3.motorMove(-power);//white
		//_m4.motorMove(power);//blue right
}

void test_motors::stopRobot()
{
	_m3.blockMotor(250);
	//_m2.blockMotor(250);
	//_m3.blockMotor(250);
	//_m4.blockMotor(250);
}

void test_motors::moveRobot(int _maxPower,
										 int _maxPower_angle,
										 int _angle,
										 int _inc)
{
	if(_inc > _maxPower_angle)
		_inc =  _maxPower_angle;
	else if(_inc < -_maxPower_angle)
		_inc =  -_maxPower_angle;
	_angle += 180;
	ang = (double(_angle) + 135)/57.3;
	opowers = _maxPower * cos(ang);
	opowers += _inc;
	_m3.motorMove(opowers);
	
	ang = (double(_angle) - 135)/57.3;
	opowers = _maxPower * -cos(ang);
	opowers += _inc;
	_m4.motorMove(-opowers);

//	ang = (double(_angle) + 135)/57.3;
//	opowers = _maxPower * -cos(ang);
//	opowers += _inc;
//	_m1.motorMove(opowers);
//	
//	ang = (double(_angle) - 135)/57.3;
//	opowers = _maxPower * cos(ang);
//	opowers += _inc;
//	_m2.motorMove(-opowers);

//	
//	ang = (double(_angle) + 45)/57.3;
//	opowers = _maxPower * -cos(ang);
//	opowers -= _inc;
//	_m3.motorMove(-opowers);

//	
//	ang = (double(_angle) - 45)/57.3;
//	opowers = _maxPower * cos(ang);
//	opowers -= _inc;
//	_m4.motorMove(opowers);
}

// you are clown
