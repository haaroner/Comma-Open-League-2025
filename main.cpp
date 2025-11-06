#include "Robot.h"
#include "Settings.h"
#include "BNO055.h"
//#include <iostream>
//#include <vector>
//std::vector<int> data(1, 2);
uint8_t attacker_state, attacker_old_state = 1, attacker_state1_tim = 0;
uint8_t defender_state = 1, defender_old_state = 0;
uint8_t defender_defence_sector, defender_move_sector;
point defender_move_point, defender_defence_point, 
defender_new_left_change_sector, defender_new_right_change_sector,
attacker_start_2_state_point;
int16_t attacker_2_state_side;
int defender_move_speed = 0, defender_move_point_dist;
int additional_defender_y = 0;
uint32_t timer_100ms = 0;
int test_1 = 0;
int max_out_v = 10;
uint32_t attacker_2_to_1_tim = 0;

uint8_t _daleko = 0;

uint32_t defender_1_to_2_tim = 0, defender_2_to_1_tim,
         defender_1_to_3_tim = 0, defender_3_to_1_tim = 0, test_timer_1 = 0,
         _attacker_5_sub_tim = 0, attacker_3_to_1_tim = 0, attacker_4_to_1_tim = 0, attacker_5_to_1_tim = 0;
int attacker_2_state_trajectory_type = undefined_trajectory;
circle defender_gate_circle(0, -5, 40);
uint32_t _attacker_4_tim = 0, _attacker_4_sub_tim = 0;
uint8_t attacker_use_detour = 0;
uint32_t attacker_start_detour_timer = 0, attacker_stop_detour_timer = 0;
uint32_t _goida = 0;
point defender_middle_cross_point, defender_detour_left_point, defender_detour_right_point,
defender_detour_point, ball_abs_position;

#define TEST_DRIBLER false 
#define TEST_MOTORS false
#define TEST_BLUETOOTH false
 
uint8_t role = 0, gaming_state = 0;  
uint8_t _abc = 0;
line defender_left_line, defender_middle_line, defender_right_line,
  defender_ball_gate_line;
bool _aboba = false;
uint8_t test_dribler_speed = 0, to_keck = 0, test_stop_dribler_speed = 0;
uint32_t _test_dribler_power = 5, test_stop_time = 5;
uint32_t spas = 0;
int arr[] = {200};
volatile uint16_t test_kick_power = 0, wait_time = 300, kick_dr_speed = 100, wait_stop_time = 50, wait_stop_speed = 30;
volatile int testg_data = 0, sub_data = 0;
uint32_t restrict_timer = 0;
int main()
{
  
  Adc ADC_ball_sen(ADC2, 1, 8, RCC_APB2Periph_ADC2, Robot::ball_sen_adc, 5);
  ADC_ball_sen.sendMeChannel(8);
  
  Dma DMA_ball_sen(RCC_AHB1Periph_DMA2, ADC_ball_sen);
  DMA_ball_sen.dmaInit(DMA2_Stream3, DMA_Channel_1, 1);
  DMA_ball_sen.adcInitInDma(5);
  
  Robot::ball_led_adc.setBit();
  point challenge_point(0, 75); 
  role = 1;
  Robot::init_robot(role);
  usart6::usart6Init(115200, 8, 1);
  time_service::init();
  time_service::startTime();
 // BNO testg;
//  testg.init();
  //time_service::delay_ms(1000);
  //while(true)
 // {
   // sub_data = testg.get_yaw();
    //if(sub_data != 4095)
      //testg_data = sub_data;
   // time_service::delay_ms(150);
  //}
//  
  Robot::kecker_cap_1.resetBit() ;
  Robot::kecker_cap_2.resetBit(); 
  
  Robot::kecker_solenoid_C.resetBit();
  Robot::kecker_solenoid_R.resetBit();
  Robot::kecker_solenoid_L.resetBit();
  Robot::kecker_kick.resetBit();
  Robot::motors_on_off(ON);
  
  
  #if TEST_DRIBLER
  
  while(true)
  {
    Robot::use_dribler(true);
    Robot::set_dribler_speed(constrain(100, 0, test_dribler_speed));
    if(to_keck == 1)
    {//AWESOME KICK PARAMS 90 drib   3ms kick
      //Robot::set_dribler_speed(55, true);
      //Robot::wait(150);
      Robot::set_dribler_speed(kick_dr_speed, true);
      Robot::wait(wait_time);
      Robot::set_dribler_speed(wait_stop_speed, true);
      Robot::wait(wait_stop_time);
      Robot::keck_new(right_solenoid, two_capasitors, test_kick_power);
      Robot::wait(50);
      test_dribler_speed = constrain(70, 0, test_dribler_speed);
      Robot::wait(100);
      to_keck = 0;
    }
    Robot::update();
  }
  #endif
  
  #if TEST_MOTORS
  Robot::wait(5000);
  Robot::use_dribler(true);
  while(true)
  {
    
    Robot::moveRobotAbs(0, 100);
    Robot::set_dribler_speed(40);
    Robot::update();
    Robot::display_data(Robot::cur_dribler_speed);
    Robot::wait(10);
  }
  #endif
  

  while(true)
  {
    gaming_state = Robot::_game_state;
    
    ball_abs_position.x = Robot::ball_abs_x;
    ball_abs_position.y = Robot::ball_abs_y;
    
    if(gaming_state == 0)
    {
      Robot::enable_game_zone_restriction(false);
      Robot::use_dribler(true);
      //Robot::set_dribler_speed(0);
      Robot::enable_trajectory(false);
      
      if(!Robot::is_callibrated)
        Robot::set_blinking(1, 300);
      else
      {
        Robot::control_led(1, Robot::is_ball_seen);
      }
      Robot::control_led(3, my_abs(Robot::gyro) < 5);
      Robot::control_led(2, my_abs(lead_to_degree_borders(Robot::gyro - Robot::forward_angle)) < 10);   
      attacker_state = 1;
      attacker_old_state = 0;
      defender_state = 1;
      defender_old_state = 0;
      Robot::display_data(Robot::forward_piece_angle);
      //Robot::display_data(Robot::is_ball_captured(), my_abs(Robot::_ball_sen_high_data - Robot::_ball_sen_low_data));
    }
    else if(gaming_state == 1)
    {
      if(role == 3)
      {
        if((!Robot::is_ball_captured()))
        {
          Robot::moveRobotAbs(Robot::ball_abs_angle, 15);
          Robot::setAngle(Robot::ball_abs_angle, 20.0, 0.2, -0.1, 0.05);        
          if(my_abs(Robot::ball_loc_angle) > 30)
            Robot::move_speed *= 0.75;
          Robot::set_dribler_speed(90);
        }
        else
        {
          Robot::setAngle(Robot::forward_angle, 5.0, 0.3, -0.1, 0.05);
          if(Robot::getDistanceToPoint(challenge_point) < 30)
            Robot::moveToPoint(challenge_point, 10, 0);
          else
            Robot::moveToPoint(challenge_point, 10, 0);
          
          if(Robot::getDistanceToPoint(challenge_point) < 7)
          {
            Robot::set_dribler_speed(90);
            Robot::moveRobotAbs(0, 20);
            Robot::moveRobotAbs(0, 0);
            if(Robot::time % 10 <= 4)
              Robot::wait(1500, true, Robot::forward_angle+10, 10, Robot::forward_angle);
            else
              Robot::wait(1500, true, Robot::forward_angle-10, 10, Robot::forward_angle);
            Robot::moveRobotAbs(0, 0);
            Robot::rotateRobot(0, 0);
            Robot::wait(200);
            Robot::keck_new(middle_solenoid, two_capasitors, 100);
            Robot::wait(2000);
          }
        }
      }
      if(role == 1)
      {
        Robot::enable_game_zone_restriction(false);
        
        if(attacker_state == 255)
        {
          Robot::moveRobot(90, 5);
          Robot::set_dribler_speed(0);
          Robot::rotateRobot(0, 0);
          Robot::update();
        }
        
        if(attacker_state == 1)
        {
          Robot::changeSmoothness(1);
          if(attacker_old_state != 1)
          {
            attacker_state1_tim = Robot::time;
          }
          if(Robot::ball_distance < 40 || Robot::is_ball_captured())
            Robot::set_dribler_speed(60.0);        
          else      
            Robot::set_dribler_speed(0.0);  

          if(Robot::is_ball_captured() && (Robot::time - attacker_state1_tim) > 500 && Robot::time - spas > 500)
          {
            Robot::moveRobot(0, 5);
            Robot::enable_game_zone_restriction(true);
            if(Robot::forward_distance > 70)
            {              
              Robot::set_dribler_speed(90, false, 5);
              Robot::moveRobotAbs(0, 0);
              Robot::wait(450);
              if(Robot::robot_y > 45 || (my_abs(Robot::robot_x) < 25))
              {
                attacker_state = 2;
                attacker_5_to_1_tim = Robot::time;
              }
              else
              {
                attacker_state = 3;
                //attacker_state = 2;
              }
              attacker_3_to_1_tim = Robot::time;
            }
            else
            {
              attacker_5_to_1_tim = Robot::time;
              if(Robot::robot_y > 190 && my_abs(Robot::robot_x) > 35)
              {
                attacker_state = 5;
                //attacker_state = 2;
              }
              else
              {
                Robot::set_dribler_speed(90);
                Robot::wait(350);
                if(_daleko != 2)
                  _daleko = 0;
                attacker_state = 4;
                //attacker_state = 2;
                _attacker_4_tim = Robot::time;
              }
            }
            attacker_use_detour = 0;
            attacker_start_detour_timer = Robot::time;
            attacker_start_2_state_point.x = Robot::robot_x;
            attacker_start_2_state_point.y = Robot::robot_y;
            
            attacker_2_state_trajectory_type = undefined_trajectory;
            
            if(Robot::robot_y < 170)
            {
              if(Robot::time % 10 <   ATTACKER_SHORT_TRAJECTORY_CHANCE)
                attacker_2_state_side = my_sgn(Robot::robot_x);
              else
                attacker_2_state_side = my_sgn(Robot::robot_x)*-1;
            }
            else
              attacker_2_state_side = my_sgn(Robot::robot_x)*-1;         
          }
         attacker_old_state = 1;
        }
        if(attacker_state == 2)
        {
          _goida = Robot::time;
          _aboba = false;
          Robot::enable_game_zone_restriction(true);
          if(attacker_old_state != 2)
          {
            attacker_use_detour = 0;
            attacker_start_detour_timer = Robot::time;
            attacker_stop_detour_timer = Robot::time;
          }
          if(Robot::is_ball_captured()) attacker_2_to_1_tim = Robot::time;
          
          if(Robot::time - attacker_2_to_1_tim > 500)
          {
            Robot::enable_game_zone_restriction(false);
            Robot::enable_trajectory(false);
            attacker_state = 1;
            attacker_old_state = 2;
          }
          
        }
         if(attacker_state == 3)
         {
          Robot::enable_game_zone_restriction(true);
          if(Robot::is_ball_captured()) attacker_3_to_1_tim = Robot::time;
          
          if(Robot::time - attacker_3_to_1_tim > 500)
          {
            Robot::enable_game_zone_restriction(true);
            Robot::enable_trajectory(false);
            attacker_state = 1;
            attacker_old_state = 3;
          }
          
          }
         if(attacker_state == 4)
         {
           if(Robot::is_ball_captured()) attacker_4_to_1_tim = Robot::time;
          
          if(Robot::time - attacker_4_to_1_tim > 500)
          {
            Robot::enable_game_zone_restriction(false);
            Robot::enable_trajectory(false);
            attacker_state = 1;
            attacker_old_state = 4;
          }
           _attacker_4_sub_tim = Robot::time;
           attacker_old_state = 4;
         }
         
         if(attacker_state == 5)
         {
           //Robot::enable_game_zone_restriction(true);
          if(Robot::is_ball_captured()) attacker_5_to_1_tim = Robot::time;
          
          if(Robot::time - attacker_5_to_1_tim > 500)
          {
            Robot::enable_game_zone_restriction(false);
            Robot::enable_trajectory(false);
            attacker_state = 1;
            attacker_old_state = 5;
          }
           _attacker_5_sub_tim = Robot::time;
         }
        if(attacker_state == 1)
        {  
          Robot::enable_trajectory(false);
          Robot::moveRobotAbs(lead_to_degree_borders(Robot::ball_abs_angle), fixed_velocity(Robot::ball_distance, my_abs(Robot::ball_loc_angle)));

          Robot::setAngle(lead_to_degree_borders(Robot::ball_abs_angle), 30.0, 0.3, -0.1, 0.05);
          
          if(Robot::ball_seen_time > 50)
            restrict_timer = Robot::time;
          
          if(Robot::ball_seen_time > 500)
            Robot::move_speed = constrain(10, 0, Robot::move_speed);
          
          //if(Robot::robot_y > 185)
            //Robot::move_speed = constrain(20, 0, Robot::move_speed);
          
          if(Robot::robot_y < 60 && my_abs(Robot::gyro) > 135)
          {
            Robot::move_speed = constrain(20, 0, Robot::move_speed);
          }
        }
        if(attacker_state == 2)
        {
          
          if(attacker_2_state_trajectory_type == detour_trajectory)
          {
            Robot::enable_trajectory(false);
            Robot::add_stop_to_route(Robot::robot_x, 100, 135 * my_sgn(Robot::robot_x), 0);
            attacker_start_2_state_point.x = Robot::robot_x;
            attacker_start_2_state_point.y = Robot::robot_y;
            attacker_2_state_side = -1 * my_sgn(attacker_start_2_state_point.x);
            attacker_2_state_trajectory_type = undefined_trajectory;
          }
          
          if(attacker_2_state_trajectory_type == undefined_trajectory)
          {
            if(attacker_2_state_side != my_sgn(attacker_start_2_state_point.x))
            {
              Robot::add_stop_to_route(10 * my_sgn(attacker_start_2_state_point.x), 150, -90 * my_sgn(attacker_2_state_side), 0);
              Robot::add_stop_to_route(30 * attacker_2_state_side, 150, 180, 0);             
              attacker_2_state_trajectory_type = long_trajectory;
            }
            else
            {
              Robot::add_stop_to_route(35 * my_sgn(attacker_2_state_side), 
            attacker_start_2_state_point.y, 180 * my_sgn(attacker_2_state_side), 0);
              
              attacker_2_state_trajectory_type = short_trajectory;
            }
            
            Robot::add_stop_to_route(Points::back_kick.x * my_sgn(attacker_2_state_side), Points::back_kick.y, Points::back_kick.angle * my_sgn(attacker_2_state_side), 2);
            Robot::enable_trajectory(true);
          }
          
          if(Robot::robot_position_diff > 6) attacker_start_detour_timer = Robot::time;
          
          if(Robot::time - attacker_start_detour_timer > 2000 && attacker_use_detour == 0) 
          {
            attacker_2_state_trajectory_type = detour_trajectory;
            attacker_stop_detour_timer = Robot::time;
            attacker_use_detour = 1;
          }
          else
            attacker_use_detour = 0;

          if(Robot::get_trajectory_length() < 30)
          {
            Robot::changeSmoothness(2);
            Robot::set_dribler_speed(100, false, 3);
            Robot::enable_game_zone_restriction(false);
          }
          else
          {
            Robot::changeSmoothness(1);
            Robot::set_dribler_speed(100, false, 3);
            Robot::enable_game_zone_restriction(true);
          }
          
          if(Robot::trajectory_finished)
          {
            Robot::changeSmoothness(2);
            Robot::enable_game_zone_restriction(false);
            Robot::enable_trajectory(false);
            Robot::moveRobotAbs(0,0);
            if(Robot::time % 10 <= 2)
            {
              _daleko = 1;
              Robot::set_dribler_speed(100);
              //Robot::wait(50);
              attacker_state = 4;
              _attacker_4_tim = Robot::time;
            }
            else if(Robot::time % 10 <= 0) // 6
            {
              //Robot::set_dribler_speed(45, true, 10);
              //Robot::wait(300);
              Robot::set_dribler_speed(110, false, 10);//160 400
              if(Robot::robot_x > 0)
                Robot::wait(400); 
              else
                Robot::wait(400);
              Robot::set_dribler_speed(0, true);
              Robot::wait(1);
              if(Robot::robot_x > 0)
                Robot::keck_new(right_solenoid, R_capacitor, 4);//6
              else
                Robot::keck_new(left_solenoid, L_capacitor, 3);
              //Robot::moveRobotAbs(-90 * my_sgn(attacker_2_state_side), 70);
              Robot::wait(250);
              attacker_state = 1;
            }
            else
            {
              Robot::wait(1);
              Robot::set_dribler_speed(100, true);
              Robot::wait(50);
              Robot::moveRobotAbs(-100 * my_sgn(attacker_2_state_side), 80);
              Robot::set_dribler_speed(130, true);
              Robot::enable_game_zone_restriction(true);
              Robot::wait(400);
              Robot::moveRobotAbs(0, 0);
              Robot::wait(100);
              Robot::enable_game_zone_restriction(false);
              _daleko = 2;
              attacker_state = 4;
            }
          }
          attacker_old_state = 2;        
        }
        if(attacker_state == 3)
        {
          Robot::set_dribler_speed(100);
          if(attacker_old_state != 3)
          {
            Robot::enable_trajectory(false);
            Robot::add_stop_to_route(40*my_sgn(Robot::robot_x),50,120*my_sgn(Robot::robot_x),1);
            Robot::add_stop_to_route(33*my_sgn(Robot::robot_x),45,145*my_sgn(Robot::robot_x),2);
            Robot::enable_trajectory(true);
          }
          
          if(Robot::trajectory_finished)
          {
            Robot::enable_game_zone_restriction(false);
            Robot::enable_trajectory(false);
            Robot::moveRobotAbs(0,0);
            Robot::set_dribler_speed(120, true);
            Robot::wait(250);
            Robot::wait(700, true, 160*my_sgn(Robot::robot_x), 10); 
            Robot::set_dribler_speed(100, true);
            if(Robot::robot_x >= 0)
              Robot::keck_new(right_solenoid, two_capasitors, 3);
            else
              Robot::keck_new(left_solenoid, two_capasitors, 3);
            attacker_state = 1;
          }
          attacker_old_state = 3;        
        }
        
        if(attacker_state == 4)
        {
          attacker_old_state = 4;
          Robot::set_dribler_speed(100, true);
          Robot::enable_game_zone_restriction(false);
          Robot::enable_trajectory(false);
          Robot::moveRobotAbs(0,0);
          //Robot::wait(50);
          Robot::turn_to_gates(1000, 2);
//          if(_daleko !=0)
//            Robot::wait(1000, true, Robot::forward_angle, 20, Robot::forward_angle);
//          else
//            Robot::wait(1000, true, Robot::forward_angle, 20, Robot::forward_angle);
          _daleko = 0;
          Robot::rotateRobot(0, 0);
          Robot::wait(25);
          Robot::keck_new(middle_solenoid, two_capasitors, 50);
          attacker_state = 1;
          spas = Robot::time;
        }
        
        if(attacker_state == 5)
        {
          Robot::set_dribler_speed(90);
          if(attacker_old_state != 5)
          {
            Robot::enable_game_zone_restriction(false);
            Robot::enable_trajectory(false);
            Robot::add_stop_to_route(40*my_sgn(Robot::robot_x),195,90*my_sgn(Robot::robot_x),1);
            Robot::add_stop_to_route(40*my_sgn(Robot::robot_x),200,90*my_sgn(Robot::robot_x),1);
            Robot::enable_trajectory(true);
          }
          if(Robot::trajectory_finished)
          {
            Robot::set_dribler_speed(100);
            Robot::enable_trajectory(false);
            Robot::moveRobotAbs(0,0);
            Robot::wait(700, true, 100*my_sgn(Robot::robot_x), 10); 
            Robot::set_dribler_speed(100, true);
            Robot::wait(100);
            Robot::wait(1500, true, -95*my_sgn(Robot::robot_x), 15);
            if(Robot::robot_x>0)
            {
            Robot::set_dribler_speed(30, true);
            Robot::wait(10);
            }
            else
            {
              Robot::set_dribler_speed(0, true);
              Robot::wait(20);
            }
            if(Robot::robot_x > 0)
            Robot::keck_new(left_solenoid, two_capasitors, 10);
            else
            Robot::keck_new(right_solenoid, two_capasitors, 20);  
            attacker_old_state = 5;
            Robot::set_dribler_speed(0, true);
            Robot::wait(300);

            attacker_state = 1;
          }
          attacker_old_state = 5;        
        }
        
        Robot::changeSmoothness(2);
        
        /*if(my_abs(Robot::robot_x) > (ATTACKER_MAX_X - 30))
        {
          max_out_v = constrainf(60, 0, 60/30*my_abs(ATTACKER_MAX_X - Robot::robot_x));
          Robot::move_speed = constrain(max_out_v+35, 0, Robot::move_speed);           
        }*/
        if(Robot::robot_x > (ATTACKER_MAX_X - 15))
        {
            polar_vector move_vector, out_vector;
            move_vector.angle = Robot::abs_move_angle;
            move_vector.length = Robot::move_speed;
            out_vector.angle = -90;
          out_vector.length = constrain(35, 0, constrain(35, 0, 35 - my_abs(ATTACKER_MAX_X - Robot::robot_x)));
            Robot::abs_move_angle = sum_of_vectors(move_vector.angle, move_vector.length, 
            out_vector.angle, out_vector.length);
            Robot::move_speed = get_len_from_sum_of_vectors();     
        }
        
        if(Robot::robot_x < (ATTACKER_MIN_X + 15))
        {
            polar_vector move_vector, out_vector;
            move_vector.angle = Robot::abs_move_angle;
            move_vector.length = Robot::move_speed;
            out_vector.angle = 90;
          out_vector.length = constrain(15, 0, constrain(15, 0, 15 - my_abs(ATTACKER_MIN_X - Robot::robot_x)));
            Robot::abs_move_angle = sum_of_vectors(move_vector.angle, move_vector.length, 
            out_vector.angle, out_vector.length);
            Robot::move_speed = get_len_from_sum_of_vectors();     
        }
        
        if(Robot::forward_distance < 45 && my_abs(Robot::robot_x) < 30)
          {
            polar_vector move_vector, out_vector;
            move_vector.angle = Robot::abs_move_angle;
            move_vector.length = Robot::move_speed;
            out_vector.angle = lead_to_degree_borders(180+Robot::forward_angle);
            out_vector.length = constrain(15, 0, 45 - Robot::forward_distance);
            Robot::abs_move_angle = sum_of_vectors(move_vector.angle, move_vector.length, 
            out_vector.angle, out_vector.length);
            Robot::move_speed = get_len_from_sum_of_vectors();     
          }
        
        if(attacker_state != 255)
        {
        
        if(Robot::robot_x > ATTACKER_MAX_X)
        {
          Robot::moveRobotAbs(-90, 15);
          Robot::changeSmoothness(2);          
        }
          
        if(Robot::robot_x < ATTACKER_MIN_X)
        {
          Robot::moveRobotAbs(90, 15);  
          Robot::changeSmoothness(2);
        }          
          
        if(Robot::robot_y > 212) 
        {
          Robot::moveRobotAbs(180, 15);
          Robot::changeSmoothness(2);
        }          
          
        if(Robot::robot_y < 27)
        {
          Robot::moveRobotAbs(0, 15);
          Robot::changeSmoothness(2);
        }          
                  
        if(Robot::robot_y > 195 && Robot::robot_x < 33 && Robot::robot_x > -33)
        {
          Robot::moveRobotAbs(180, 15); 
          Robot::changeSmoothness(2);
        }          
         
        if(Robot::robot_y < 35 && Robot::robot_x < 30 && Robot::robot_x > -30)
        {
          Robot::moveRobotAbs(0, 15);
          Robot::changeSmoothness(2);
        }
      }
      Robot::display_data(attacker_state, Robot::is_ball_captured()); 
      }
      else if(role == 2)
      { 
        Robot::changeSmoothness(1);
        Robot::enable_game_zone_restriction(false);
        if(defender_state == 255)
        {
          Robot::setAngle(0, 20.0, 0.2, -0.1, 0.05);
        }
         if(defender_state == 1)
         {
           if(defender_old_state != 1)
           {
             defender_1_to_2_tim = Robot::time;
           }
           if(/*Robot::_dSSoft > 20 || */
             my_abs(Robot::ball_abs_x) > 30 || Robot::ball_abs_y > 160 || Robot::ball_abs_y < 40 || defender_move_point_dist > 8) defender_1_to_2_tim = Robot::time;
           
           if(Robot::time - defender_1_to_2_tim > 1500 && 
             (Robot::time - defender_2_to_1_tim > 4000))
           {
             defender_state = 2;
             defender_2_to_1_tim = Robot::time;
           }
           
         }      
           
         if(defender_state == 2)
         {
           Robot::enable_game_zone_restriction(true);
           if(my_abs(Robot::ball_abs_angle) > 60 || Robot::ball_seen_time > 750)
           {
              defender_state = 1;
             defender_old_state = 2;
             Robot::set_dribler_speed(0);
           }
           if(Robot::time - defender_2_to_1_tim > 3000)
           {
             defender_state = 1;
             Robot::moveRobotAbs(0, 0);
             Robot::set_dribler_speed(100);
             Robot::wait(10);
             Robot::wait(1000, true, Robot::forward_angle, 7, Robot::forward_angle);
             Robot::set_dribler_speed(0, true);
             Robot::wait(10);
             Robot::keck_new(middle_solenoid, two_capasitors, 50);
             defender_state = 1;
             defender_old_state = 2;
           }
         }
         
         if(defender_state == 3)
         {
           if(Robot::robot_y > 55) defender_3_to_1_tim = Robot::time;
           
           if(Robot::time - defender_3_to_1_tim > 500)
             defender_state = 1;
         }
         
         if(defender_state == 1)
         {
           Robot::enable_game_zone_restriction(false);
           
           Robot::set_dribler_speed(0);
           /*calculate all lines for defender geometry*/
           
           additional_defender_y = constrain(40, 0, Robot::ball_abs_y - (Points::defender_left_change_sector.y + 5));
           
           if(Robot::ball_seen_time > 1000)
            additional_defender_y = 0;
           defender_new_left_change_sector.x = Points::defender_left_change_sector.x;
           defender_new_left_change_sector.y = additional_defender_y + Points::defender_left_change_sector.y;
           
           defender_new_right_change_sector.x = Points::defender_right_change_sector.x;
           defender_new_right_change_sector.y = additional_defender_y + Points::defender_right_change_sector.y;
           
           defender_left_line = get_line_from_points(Points::defender_left_end, defender_new_left_change_sector);
           defender_right_line = get_line_from_points(Points::defender_right_end, defender_new_right_change_sector);
           defender_middle_line = get_line_from_points(defender_new_left_change_sector, defender_new_right_change_sector);
           defender_ball_gate_line = get_line_from_points(ball_abs_position, Points::backward_gate);
           
           /*point to defy which defence sector to use*/
           defender_middle_cross_point = find_lines_crosspoint(defender_ball_gate_line, defender_middle_line);
           
           /*choose defence sector*/
           if(defender_middle_cross_point.x >= Points::defender_right_change_sector.x)
           {
             defender_defence_sector = right_sector;
             defender_defence_point = find_lines_crosspoint(defender_ball_gate_line, defender_right_line);
           }
           else if(defender_middle_cross_point.x <= Points::defender_left_change_sector.x)
           {
             defender_defence_sector = left_sector;
             defender_defence_point = find_lines_crosspoint(defender_ball_gate_line, defender_left_line);
           }
           else
           {
             defender_defence_sector = middle_sector;
             defender_defence_point = find_lines_crosspoint(defender_ball_gate_line, defender_middle_line);
           }
           //defender_defence_point *= 1.2;
           /*get current robot's sector*/
           if(Robot::robot_x >= Points::defender_right_change_sector.x)
             defender_move_sector = right_sector;
           else if(Robot::robot_x <= Points::defender_left_change_sector.x)
             defender_move_sector = left_sector;
           else
             defender_move_sector = middle_sector;
           
           if(Robot::ball_abs_x > 30 && Robot::ball_abs_y <= 25)
           {
             defender_defence_point = Points::defender_right_end;
             defender_defence_sector = right_sector;
           }
           else if(Robot::ball_abs_x < -30 && Robot::ball_abs_y <= 18 )
           {
              defender_defence_point = Points::defender_left_end;
              defender_defence_sector = left_sector;
           }
             
           if(Robot::ball_seen_time > 750)
           {
             if(Robot::ball_abs_x > 35)
             {
                defender_defence_point = Points::defender_no_ball_right_point;
                defender_defence_sector = right_sector;          
             }
             else if(Robot::ball_abs_x < -35)
             {
                defender_defence_sector = left_sector;  
                defender_defence_point = Points::defender_no_ball_left_point;
             }
             else
             {
                defender_defence_sector = middle_sector;  
                defender_defence_point = Points::defender_no_ball_middle_point;
             }
           }
           
           if(defender_move_sector == left_sector)
           {
              if(defender_defence_sector != left_sector)
                defender_move_point = defender_new_left_change_sector;
              else
              {
                defender_move_point = find_lines_crosspoint(defender_ball_gate_line, defender_left_line);
                if(Robot::ball_seen_time > 1000)
                  defender_move_point = defender_defence_point;
              }
           }          
           else if(defender_move_sector == right_sector)
           {
              if(defender_defence_sector != right_sector)
                defender_move_point = defender_new_right_change_sector;
              else
              {
                defender_move_point = find_lines_crosspoint(defender_ball_gate_line, defender_right_line);
                if(Robot::ball_seen_time > 1000)
                  defender_move_point = defender_defence_point;
              }
           }
           else if(defender_move_sector == middle_sector)
           {
              if(defender_defence_sector == right_sector)
                defender_move_point = defender_new_right_change_sector;
              else if(defender_defence_sector == left_sector)
                defender_move_point = defender_new_left_change_sector;
              else
              {
                defender_move_point = defender_middle_cross_point;
                if(Robot::ball_seen_time > 1000)
                  defender_move_point = defender_defence_point;
              }
           }
           if(Robot::ball_seen_time > 750)
           {
             if(Robot::ball_abs_x > 30)
             {
                defender_move_point = Points::defender_no_ball_right_point;
                defender_defence_sector = right_sector;          
             }
             else if(Robot::ball_abs_x < -30)
             {
                defender_defence_sector = left_sector;  
                defender_move_point = Points::defender_no_ball_left_point;
             }
             else
             {
               defender_defence_sector = middle_sector;
               defender_move_point = Points::defender_no_ball_middle_point;
             }
           }
           defender_move_point_dist = Robot::getDistanceToPoint(defender_defence_point);
           defender_move_speed = new_defender_velocity(defender_move_point_dist);
           
           if(Robot::ball_seen_time > 1000)
             defender_move_speed = 30;
           
           if(defender_move_point_dist < 1)
              defender_move_speed = 0;
           if(Robot::robot_y < 30)
           {
             if(Robot::robot_x > 20 && Robot::ball_abs_angle > 30)
               defender_move_speed = constrain(30, 0, defender_move_speed);
             else if(Robot::robot_x < -20 && Robot::ball_abs_angle < -30)
               defender_move_speed = constrain(30, 0, defender_move_speed);
           }
           Robot::moveRobotAbs(Robot::getAngleToPoint(defender_move_point), defender_move_speed);
           Robot::setAngle(0, 20.0, 0.045, -0.001, 0.08);
           
           if(Robot::robot_y < 22)
                 Robot::moveRobotAbs(0, 10);
           
           if(Robot::robot_y > 60)
           {
            Robot::enable_game_zone_restriction(true);
            if(lead_to_degree_borders(Robot::getAngleToPoint(Robot::ball_abs_position) - Robot::getAngleToPoint(Points::gate_left_point)) < 0 &&
               lead_to_degree_borders(Robot::getAngleToPoint(Robot::ball_abs_position) - Robot::getAngleToPoint(Points::gate_right_point)) > 0)
            {
               defender_detour_left_point.x = Robot::ball_abs_x - 25;
               defender_detour_left_point.y = Robot::ball_abs_y;
                
               defender_detour_right_point.x = Robot::ball_abs_x + 25;
               defender_detour_right_point.y = Robot::ball_abs_y; 

               if(defender_detour_left_point.x < -50)
                 defender_detour_point.x = defender_detour_right_point.x;
               else if(defender_detour_right_point.x > 50)
                 defender_detour_point.x = defender_detour_left_point.x;
               else
               {
                 if(Robot::getDistanceToPoint(defender_detour_right_point) < Robot::getDistanceToPoint(defender_detour_left_point))
                     defender_detour_point.x = defender_detour_right_point.x;
                 else
                     defender_detour_point.x = defender_detour_left_point.x;
               }
               defender_detour_point.y = Robot::ball_abs_y;
               Robot::setAngle(0,  20.0, 0.2, -0.1, 0.05);
               Robot::moveToPoint(defender_detour_point, 25, 255, 100, 0);
            }
          }
         }       
         else if(defender_state == 2)
         {
           defender_move_speed = constrain(8, 4, Robot::ball_distance * 0.25);
           if(Robot::ball_loc_angle > 30)
             defender_move_speed *= 0.75;
           Robot::moveRobotAbs(Robot::ball_abs_angle, 10);
           Robot::setAngle(Robot::ball_abs_angle, 7.0, 0.045, -0.001, 0.08);
           Robot::set_dribler_speed(100);
         }
         else if(defender_state == 3)
         {
           defender_detour_point = find_vector_circle_cross_points(defender_gate_circle, 
           Robot::ball_abs_position);
           Robot::moveToPoint(defender_detour_point, 30, 255, 100, 0);
           Robot::setAngle(lead_to_degree_borders(Robot::backward_angle + 180),
           20.0, 0.045, -0.001, 0.08);
         }
         Robot::display_data(defender_ball_gate_line.a * 10, defender_ball_gate_line.c);
      }
      if(Robot::ball_seen_time > 1000)
        additional_defender_y = constrain(10, 0, additional_defender_y);
    }
    defender_old_state = defender_state;
    
    Robot::update();
  }
}