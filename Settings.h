#pragma once

#include "tools.h"
////////////////////////////////////
#define OTLADKA false
#define USE_MOTORS true
#define USE_DISPLAY true
#define USE_DRIBLER true
#define USE_FRONT_CAMERA false
  //////////////////////////////////

#define STOP_DRIBLER_SPEED 249
#define MAX_ATTACKER_DRIBLER_SPEED 40
#define MAX_DEFENDER_DRIBLER_SPEED 130

#define ATTACKER_DRIBLER_ACCELERATION 0.4
#define DEFENDER_DRIBLER_ACCELERATION 1.5




/////////////////////////////////////////////////////////
#define ATTACKER_SHORT_TRAJECTORY_CHANCE 4 //0...10

#define ATTACKER_BALL_THRESHOLD 2
#define DEFENDER_BALL_THRESHOLD 8 //set both to zero and test it


//trajectory settings
//all speeds are in %, you can change in anyway you want
//in Tomsk linear speeds were almost 2 times higher
#define ATTACKER_MAX_LINEAR_TRAJECTORY_SPEED 27//30
#define ATTACKER_MIN_LINEAR_TRAJECTORY_SPEED 15//15
#define ATTACKER_MAX_ANGULAR_TRAJECTORY_SPEED 6//7
/////////////////////////////////////////////////////////////////////



//for defender no need to change it cause we dont have dribler
#define DEFENDER_MAX_LINEAR_TRAJECTORY_SPEED 23
#define DEFENDER_MIN_LINEAR_TRAJECTORY_SPEED 15
#define DEFENDER_MAX_ANGULAR_TRAJECTORY_SPEED 5
#define DEFENDER_STANDART_ANGULAR_KP -0.2

//just dreams
#define CHALLENGE false
#define CHALLENGE_NUM 1 

#define POWER_SUPPLY 16
#define STANDART_POWER 13
#define POWER_K 1

// ATTACKER's out of bounds
//distance in cm(primerno)
///////////////////////////////////////////////////
#define ROBOT_MAX_X 70
#define ROBOT_MIN_X -70
#define ROBOT_MAX_RIGHT_Y 220
#define ROBOT_MAX_LEFT_Y 200
/////////////////////////////////////////////////

#define DEFENDER_MIN_ANGLE_ERR 10

#define ROBOT_MAX_X_DIFF 0
#define ROBOT_MIN_X_DIFF 0

#define ROBOT_MAX_Y 210
#define ROBOT_MIN_Y 10

#define CENTRAL_GATE_OUT 55
#define SIDE_GATE_OUT 58

#define CHANGE_SPEED_VECTOR_CONST 2

#define USE_BLUETOOTH 0

#define KP_GYRO_MOVING 1.0
#define KD_GYRO_MOVING 10.0
#define KI_GYRO_MOVING 0.01

#define KP_GYRO_STOPPED 1.0
#define KD_GYRO_STOPPED 10.0
#define KI_GYRO_STOPPED 0.01

#define ATTACKER_BALL_DETECTION_LIGHTNESS 2650/////////
#define DEFENDER_BALL_DETECTION_LIGHTNESS 2900

#define BUTTON_MIN_PRESSING_TIME_MS 65

#define BALL_K1
#define BALL_K2
#define BALL_K3
#define BALL_K4

#define KICK_OFF_DURATION 1000

#define STANDART_ROBOTS_ROLE_FROM_FLASH 255

#define FAST_POINT_MOVEMENT_SPEED 255
#define SLOW_POINT_MOVEMENT_SPEED -255

