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
  
  point back_kick(20, 160, 125, 1 );
  
  point speed_1(8, 15);
  point speed_2(25, 60);
  point speed_3(45, 70);
  
  point a_min(16, 25);
  point a_max(16, 45);
  
  point a_cur(16, 0);
  
  point b_min(35, 60);
  point b_max(35, 65);
  
  point b_cur(30, 0);
  
  point defender_speed_1(5, 5);
  point defender_speed_2(10, 40);
  point defender_speed_3(30, 70);
 
  
  /* Defender points*/
  point defender_left_end(-40, 15);//-45 15
  point defender_left_change_sector(-37, 35);//-30  30
  
  point defender_right_end(38, 15);
  point defender_right_change_sector(35, 35);
  
  point defender_middle_cross_point;
  
  point defender_no_ball_right_point(32, 30);
  point defender_no_ball_left_point(-32, 30);
  point defender_no_ball_middle_point(0, 50);
}