#pragma once
#include "project_config.h"
#include "tools.h"
namespace Points
{
  /* Common points*/
  point backward_gate(1, 1);
  point forward_gate(0, 220);
  
  point gate_left_point(-50, 0);
  point gate_right_point(50, 0);
  
  
  /*Attacker points*/
  point long_ricochet_right(58, 60, 40, 2);
  point long_ricochet_left(-58, 60, -40, 2);
  
  point back_kick(25, 178, 117, 1);
  
  point speed_1(8, 15);
  point speed_2(25, 60);
  point speed_3(45, 70);
  
  point defender_speed_1(5, 5);
  point defender_speed_2(10, 40);
  point defender_speed_3(30, 70);
 
  
  /* Defender points*/
  point defender_left_end(-45, 20);//-45 15
  point defender_left_change_sector(-30, 44);//-30  30
  
  point defender_right_end(45, 20);
  point defender_right_change_sector(30, 44);
  
  point defender_middle_cross_point;
  
  point defender_no_ball_right_point(27, 35);
  point defender_no_ball_left_point(-27, 35);
}