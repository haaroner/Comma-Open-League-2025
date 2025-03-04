#pragma once

#include "Settings.h"
#include "libs.h"
#include "tools.h"

namespace Robot
{ 
  pin led1('A', 0, write_UP); 
  pin led2('A', 1, write_UP); 
  pin led3('A', 2, write_UP); 
  
  Motor m2('E', 13, tim1, CHANNEL3, 'E', 14, tim1, CHANNEL4);					
  Motor m3('D', 12, tim4, CHANNEL1, 'D', 13, tim4, CHANNEL2);
  Motor m1('D', 14, tim4, CHANNEL3, 'D', 15, tim4, CHANNEL4);
  Motor m4('B', 10, tim2, CHANNEL3, 'B', 11, tim2, CHANNEL4);
  motors motors(m1, m2, m3, m4, 100, 3);//1.5
  
  pin spi2_sck('B', 13, spi2);
  pin spi2_mosi('B', 15, spi2);
  pin spi2_miso('B', 14, spi2);
  pin spi2_ck('B', 12, write_DOWN);
  
  pin usart6_tx('C', 6,  uart6);	
  pin usart6_rx('C', 7,  uart6);   

  pin usart1_tx('B', 6, uart1);
  pin usart1_rx('B', 7, uart1);
    
  pin motors_move('B', 1, read_UP);
  pin gyro_reset('B', 0, read_UP);	
  pin cap_charge('B', 9, write_);
  pin cap_discharge('E', 0, write_);
  pin dribler_control('C', 8, dribler_);
  pin ball_sen('A', 7, adc);
    
  pin tssp_write_4('D', 8, write_DOWN);
  pin tssp_write_3('D', 9, write_DOWN);
  pin tssp_write_2('D', 10, write_DOWN);
  pin tssp_write_1('D', 11, write_DOWN);
  
  pin tssp_left_read('C', 3, read_DOWN);
  pin tssp_right_read('C', 2, read_DOWN);  
  
  pin up('B', 5, read_UP);
  pin down('B', 8, read_UP);
  pin enter('E', 3, read_UP);
  
  pin spi3_mosi('C', 12, spi3);
  pin spi3_sck('C', 10, spi3);
  pin spi3_dc('A', 15, write_DOWN);
  pin spi3_cs('E', 0, write_DOWN);
  pin spi3_rst('C', 11, write_DOWN);
  pin usart2_rx('D', 6, uart2);
  pin usart2_tx('D', 7, uart2);
  
  pin Kecker('E', 9, write_);
  
  pin ball_sen_adc('A', 3, adc);
  
  pin battery_charge('C', 5, adc);
  
  SSD1306 display(3, spi3_dc, spi3_rst, spi3_cs, 1, 1, 1);
    
  camera camera(omni_camera, usart2_tx, usart2_rx);
    
  TSSP ball(digital, tssp_write_4, tssp_write_3, tssp_write_2, 
  tssp_write_1, tssp_left_read, tssp_right_read, 1//,// tssp_left_read_dma, 
  /*tssp_right_read_dma*/);
  mpu9250_spi mpu_sensor(spi2_ck);
  IMU mpu(mpu_sensor);
  
  PID angle_pid(-0.07, -0, 0, 0);
  Queue trajectory;

   
  void init_robot(uint8_t role);
  void callibrate_gyro();
  void control_led(uint8_t _led_num, bool _data);
  void set_blinking(uint8_t _led_num, uint32_t _duration);
  void moveRobot(int16_t _angle, uint8_t _speed);
  void rotateRobot(int16_t _angular_speed);
  void check_buttons();
  bool check_button(uint8_t _button_num);
  void change_side();
  void update();

  int a = 0;
  
  int ball_bluetooth_dist = 0;
  
  volatile uint32_t time, button_timers[3], blinking_timer = 0, blinking_durations,
    init_timer = 0, display_timer = 0, loop_delay = 0, 
    old_time = 0, prediction_timer = 0, keck_timer = 0, point_reached_timer = 0, 
    dribler_speed_change_speed = 0, ball_grab_timer = 0, 
    bluetooth_send_timer = 0, bluetooth_receive_time = 0, timer10ms = 0, 
  timer_1000ms = 0, display_update_time = 0, ball_data = 0, sub_adc_data = 0,
  adc1_sub = 0;
  
  bool test_dribler = 0;
  
  volatile uint32_t otladka1 = 0;
  volatile int otladka2 = 0;
  
  volatile int move_angle = 0, angular_speed = 0, max_angular_speed, gyro = 0,
  robot_x = 0, robot_y = 100, ball_loc_angle = 0, ball_abs_angle = 0, ball_loc_x = 0,
  ball_loc_y = ball_loc_x = 20, forward_angle = 0, backward_angle = 180, ball_angle,
  moving_point[4] = {-1000, -1000, -1000, -1000}, dribler_speed = STOP_DRIBLER_SPEED, 
  gyro_zero_angle = 0, waiting_angle = 0, abs_move_angle = 0;
  
  uint32_t test_timer = 0;
  
  volatile int ball_distance = 20, forward_distance = 100, backward_distance = 100, point_distance = 0, 
    old_b_x = 0, old_b_y = 0, ball_abs_x = 0, ball_abs_y = 0,
    ball_bluetooth_x = 0, ball_bluetooth_y = 0, _dS = 0,_dSSoft = 0, 
    _x1b = 0, _y1b = 0, _defender_predicted_x = 0, 
    _defender_predicted_y = 0, display_data_1 = 0, display_data_2 = 0,
    display_delay_update_time = 30;
  
  double _dxb = 0, _dyb = 0;
  
  int8_t _test_dribler_mode = 0;
  
  uint8_t move_speed = 0, role = 2 ,point_significanse, dribbler_mode = 0, image_num = 0;
  
  double _alpha = 0;
  unsigned select_arrow_y = 0, menu_level = 0, main_menu_arrow_y = 0;
  
  volatile uint16_t change_speed_time = 10, start_trajectory_length = 0, ball_sen_data = 0;
  
  float cur_dribler_speed = STOP_DRIBLER_SPEED, voltage = 0;
  
  bool _use_dribler = false, trajectory_started = false;
  
  bool use_delays = true, ball_distance_delay_disable = true;
  
  bool fast_stop = 0;
  
  volatile uint16_t robot_position_diff;
  
  volatile bool side = 0, buttons_data[3] = {1, 1, 1}, buttons_old_data[3] = {1, 1, 1}, 
  pressed_buttons[3] = {0, 0, 0}, blinking_leds[3] = {0, 0, 0}, leds_state = 0, motors_state = 0,
  init_image = true, _game_state = 0, is_callibrated = 0, moving_to_point = false,
  is_ball_seen = 0, use_trajectory = 0, trajectory_is_in_progress = 0, 
  trajectory_finished = 0, point_reached = false, side_keck_finished = false,
  waiting = false, wait_rotating = false;
  
  float k_dSSoft = 0.1;
  float dribler_acc = 0;
  
  float ball_sen_data_soft = 0, ball_sen_data_k = 0.5;
  
  struct point robot_position, robot_move, _sub_point, start_trajectory;
  point predicted_point, robot_previous_position;
  struct polar_vector start_trajectory_vector;

  uint8_t max_trajectory_linear_speed, min_trajectory_linear_speed, max_trajectory_angular_speed;
  
  volatile uint8_t bluetooth_data[4];
  
  uint32_t robot_global_speed_timer = 0;
  
  int16_t ball_threshold = 0;
  
  void init_robot(uint8_t _role = 1)
  { 
    time_service::init();
    time_service::startTime();
    
    
    
    Kecker.resetBit();
    
    control_led(0, OFF);
    
    usartik1::usart1Init(9600, 8, 1, 10);//bluetooth
    usart2::usart2Init(230400, 8, 1);//camera
    usart6::usart6Init(115200, 8, 1);//gyro
    
    //adc_voltage.sendMeChannel(15);
    #if USE_DISPLAY
      display.begin();
      display.display();
    #endif
    
    #if USE_DRIBLER
      dribler_control.pwm(200);
      time_service::delay_ms(500);
      dribler_control.pwm(300);
      time_service::delay_ms(500);
      dribler_control.pwm(200);
      time_service::delay_ms(1000);
    #endif
    
    init_timer = time;
    
    if(_role == STANDART_ROBOTS_ROLE_FROM_FLASH)
      role = read_from_FLASH();
    else
      role = _role;
    
    if(role == 1)
    {
      dribler_acc = ATTACKER_DRIBLER_ACCELERATION;
      max_trajectory_linear_speed = ATTACKER_MAX_LINEAR_TRAJECTORY_SPEED;
      min_trajectory_linear_speed = ATTACKER_MIN_LINEAR_TRAJECTORY_SPEED;
      max_trajectory_angular_speed = ATTACKER_MAX_ANGULAR_TRAJECTORY_SPEED;
      
      ball_threshold = ATTACKER_BALL_THRESHOLD;
    }
    else if(role == 2)
    {
      dribler_acc = DEFENDER_DRIBLER_ACCELERATION;
      max_trajectory_linear_speed = DEFENDER_MAX_LINEAR_TRAJECTORY_SPEED;
      min_trajectory_linear_speed = DEFENDER_MIN_LINEAR_TRAJECTORY_SPEED;
      max_trajectory_angular_speed = DEFENDER_MAX_ANGULAR_TRAJECTORY_SPEED;
      
      ball_threshold = DEFENDER_BALL_THRESHOLD;
    }

      
    
    //mpu.init();
    //mpu.update();
  }
  
  uint8_t crc8(uint8_t* data, int len)
  {
      uint8_t crc = 0xFF, i, j;
      for (i = 0; i < len; i++) {
          crc ^= data[i];
          for (j = 0; j < 8; j++) {
              if (crc & 0x80) crc = (char)((crc << 1) ^ 0x31);
              else crc <<= 1;
          }
      }
      return crc;
  }
  
  void send_bluetooth_data(int _num1, int _num2, int _num3)
  {
    if(_num3 < 50)
      usartik1::abcde(255);
    else if(_num3 < 100)
      usartik1::abcde(254);
    else
      usartik1::abcde(253);
    _num1 = constrain(255, 0, int((constrain(200, -200, _num1) / 2) + 100));
    _num2 = constrain(255, 0, int((constrain(200, -200, _num2) / 2) + 100));
   // _num3 = constrain(255, 0, int((constrain(200, -200, _num3) / 2) + 100));
   // uint8_t data[3] = {_num1, _num2, _num3};
    usartik1::abcde(_num1);
    usartik1::abcde(_num2);
    usartik1::abcde((_num1 + _num2) / 2);
   // usartik1::abcde(_num3);
    //usartik1::abcde(crc8(data, 3));
    return;
  }
  
  void use_dribler(bool _data)
  {
    _use_dribler = _data;
  }
  
  void check_buttons()
  {
    buttons_data[0] = up.read();
    buttons_data[1] = GPIOB -> IDR & GPIO_Pin_8; // Idk why standart class reading isnt working on this pin
    buttons_data[2] = enter.read();
    
    
    for(int i = 0; i < 3; i++)
    {
      if(buttons_data[i] == 0 && buttons_old_data[i] == 1)//is pressed
        button_timers[i] = time;
      if(time - button_timers[i] > BUTTON_MIN_PRESSING_TIME_MS && buttons_data[i] == 1 && buttons_old_data[i] == 0)
      {
        pressed_buttons[i] = 1;
        button_timers[i] = time;
      }
    }
    buttons_old_data[0] = buttons_data[0];
    buttons_old_data[1] = buttons_data[1];
    buttons_old_data[2] = buttons_data[2];
  }
  
  bool check_button(uint8_t _button_num)
  {
    a = pressed_buttons[_button_num - 1];
    pressed_buttons[_button_num - 1] = 0;
    return a;
  }
    
  void change_side()
  {
    side = my_abs(side - 1);
  }

  void set_dribler_speed(uint16_t _speed, bool _fast_stop = true)
  {
    if(role == 1)
      _speed = constrain(MAX_ATTACKER_DRIBLER_SPEED, 0, _speed);
    else
      _speed = constrain(MAX_DEFENDER_DRIBLER_SPEED, 0, _speed);
    dribler_speed = STOP_DRIBLER_SPEED + _speed;
    fast_stop = _fast_stop;
//    _speed = constrain(MAX_DRIBLER_SPEED, 0, _speed);
//    if(time_service::getCurTime() - dribler_speed_change_speed > change_speed_time || (_speed == 0 && fast_stop))
//    {
//      if(my_abs(_speed - dribler_speed) <= 1.4 || (_speed == 0 && fast_stop)) cur_dribler_speed = _speed;
//      else
//      {
//        cur_dribler_speed += 1.4 * my_sgn(_speed - cur_dribler_speed);
//      }
//      dribler_speed = STOP_DRIBLER_SPEED + constrain(MAX_DRIBLER_SPEED, 0, int(cur_dribler_speed));
//      dribler_speed_change_speed = time_service::getCurTime();
//    }
//    dribler_speed = STOP_DRIBLER_SPEED + constrain(MAX_DRIBLER_SPEED, 0, int(_speed));
  }
  
  void change_game_state()
  {
    if(is_callibrated)
      _game_state = my_abs(_game_state - 1);
    if(_game_state == 0) set_dribler_speed(0);
  }

  void motors_on_off(bool _state)
  {
    motors_state = _state; 
  }
  
  
  
//  void set_dribler_speed(int16_t _speed)
//  {
//    if(is_in_the_borders(100, 0, _speed)) dribler_speed = 200 + _speed;
//    else _speed = 200;
//  }
  
  void keck(uint8_t _duration = 10)
  {
    if(_duration > 20) _duration = 20;
    if(time_service::getCurTime() - keck_timer > 700)
    {
      //ENTER_CRITICAL_SECTION();
      Kecker.setBit();
      time_service::delay_ms(_duration);
      Kecker.resetBit();
      keck_timer = time_service::getCurTime();
      //EXIT_CRITICAL_SECTION();
    }
  }
  
  inline void display_draw_string(const char* data, unsigned x = 0, unsigned y = 0)
  {
    drawString(display, data, x, y);
  }
  
  template <typename N>
    
  inline void display_draw_number(N data,unsigned num_of_digits_after_dot = 3, unsigned x = 0, unsigned y = 0)
  {
    printTml(display, data, num_of_digits_after_dot, x, y);
  }
  
  template <typename N>
  
  void display_data(const char* str_data, unsigned _str_len, N num_data,  unsigned num_of_digits_after_dot = 3, unsigned x = 0, unsigned y = 0)
  {
    drawString(display, str_data, x, y);
    printTml(display, num_data, num_of_digits_after_dot, x + _str_len, y);
  }  
  
  inline void display_clear()
  {
    display.clear();
  }
  
  inline void display_update(bool auto_clear = true)
  {
    if(_game_state == 0) display_delay_update_time = 30;
    else display_delay_update_time = 30;
    if(time_service::getCurTime() - init_timer > 1000 && (time_service::getCurTime() - display_timer) > display_delay_update_time) 
    {
      if(init_image) display.clear();//to clear before first .display()
      display.display();
      if(auto_clear) display.clear();// to clear buffer for following .display()
      display_timer = time_service::getCurTime();
      init_image = false;
    }
  }
  
  
  void display_data(int num1, int num2 = 0)
  {
    display_data_1 = num1;
    display_data_2 = num2;
  }
  
  
  void control_led(uint8_t _led_num, bool _data)
  {    
    switch(_led_num)
    {
      case 0: led1.write(_data); led2.write(_data); led3.write(_data); break;
      case 1: led1.write(_data); break;
      case 2: led2.write(_data); break;
      case 3: led3.write(_data); break;
    }
  }
  
  
  void set_blinking(uint8_t _led_num, uint32_t blinking_duration)
  {
   for(int i = 0; i < 3; i++)
      blinking_leds[i] = OFF;
    if(blinking_duration > 0)
    {
      switch(_led_num)
      {
        case 0: blinking_leds[0] = ON; blinking_leds[1] = ON; blinking_leds[2] = ON; break;
        case 1: blinking_leds[0] = ON; break;
        case 2: blinking_leds[1] = ON; break;
        case 3: blinking_leds[2] = ON; break;
      }
    }
    else
    {
      control_led(_led_num, OFF);
    }
    blinking_durations = blinking_duration;
  }
  
  
  void Ilya()
  {
    if(time_service::getCurTime() - keck_timer > 700)
    {
      //ENTER_CRITICAL_SECTION();
      Kecker.setBit();
      time_service::delay_ms(50);
      Kecker.resetBit();
      keck_timer = time_service::getCurTime();
      //EXIT_CRITICAL_SECTION();
    }
  }
  
  void moveRobot(int16_t _angle, uint8_t _speed)
  {
    move_angle = lead_to_degree_borders(_angle);
    if(_speed > 100) _speed = 0;
      move_speed = _speed;
  }
  
  void moveRobotAbs(int16_t _angle, uint16_t _speed)
  {
    abs_move_angle = _angle;
    move_angle = lead_to_degree_borders(_angle - gyro);
    if(_speed > 100) _speed = 100;
    move_speed = _speed;
  }
  
  void moveRobotAbs(polar_vector _vector)
  {
    abs_move_angle = _vector.angle;
    move_angle = lead_to_degree_borders(abs_move_angle - gyro);
    move_speed = _vector.length;
    if(move_speed > 100) move_speed = 100;
  }
  
  void constrainRobotSpeed(uint8_t _max_speed, uint8_t _min_speed)
  {
    _max_speed = constrain(100, 0, _max_speed);
    _min_speed = constrain(100, 0, _min_speed);
    move_speed = constrain(_max_speed, _min_speed, move_speed);
  }
  
  void setRobotSpeed(uint16_t _speed)
  {
    if(_speed > 100) _speed = 100;
    move_speed = _speed;
  }
  
  int getAngleToPoint(int _x, int _y)
  {
    return get_angle_to_point(robot_x, robot_y, _x, _y).angle;
  }
  
  int getAngleToPoint(point _point)
  {
    return get_angle_to_point(robot_x, robot_y, _point.x, _point.y).angle;
  }
  
  int getDistanceToPoint(int _x, int _y)
  {
    return get_angle_to_point(robot_x, robot_y, _x, _y).length;
  }
  
  int getDistanceToPoint(point _point)
  {
    return get_angle_to_point(robot_x, robot_y, _point.x, _point.y).length;
  }
  
  polar_vector get_data_of_point(point _data)
  {
    return get_angle_to_point(robot_x, robot_y, _data.x, _data.y);
  }
  
  bool is_in_square(int _min_x, int _min_y, int _max_x, int _max_y)
  {
    return (is_in_borders(_max_x, _min_x, robot_position.x) &&
           is_in_borders(_max_y, _min_y, robot_position.y));
  }
  
  uint16_t get_trajectory_length()
  {
    return trajectory.calculate_distance(robot_position);
  }
  
  void add_stop_to_route(int _x, int _y, int _angle = 255, uint8_t _significance = 2) //:)
  {
    point _point;
    _point.x = _x;
    _point.y = _y;
    _point.angle = _angle;
    trajectory.push(_point, _significance);
  }
  
  void add_stop_to_route(point _point, int _angle = 0, uint8_t _significance = 2) //:)
  {
    trajectory.push(_point, _significance);
  }
  
  uint8_t enable_trajectory(bool _state)
  {
    use_trajectory = _state;
    if(!_state)
    {
      trajectory_started = false; 
      trajectory.clear();
    }
    if(_state)
    {
      start_trajectory_length = get_trajectory_length();
      trajectory_started = true;
      trajectory_finished = false;
    }
    update();
  }
  
  void setAngle(int16_t x0_angle, int16_t _max_angular_speed, float _kp = 0)
  {
    if (_kp != 0) angle_pid.set_ratio(_kp, 0, 0, 0);
    angular_speed = angle_pid.calculate_radially(x0_angle, gyro);
    if(angular_speed > _max_angular_speed)
      angular_speed = _max_angular_speed;
    else if(angular_speed < -_max_angular_speed)
      angular_speed = -_max_angular_speed;
    max_angular_speed = _max_angular_speed;
  }
  
  void moveToAngle(int16_t x0_angle, int16_t _max_angular_speed, uint32_t timeout)
  {
    uint32_t _start_time = time_service::getCurTime(), x0_angle_tim = 0;
    waiting = true;
    wait_rotating = true;
    while(_start_time + timeout > time_service::getCurTime())
    {
      setAngle(x0_angle, _max_angular_speed);
      update();
      time_service::delay_ms(1);
      if(my_abs(gyro - x0_angle) < 5)
      {
        if(x0_angle_tim == 0)
          x0_angle_tim = time_service::getCurTime();
        if(time_service::getCurTime() - x0_angle_tim > 500)
          break;
      }
      else
      {
        x0_angle_tim = 0;
      }
    }
    waiting = false;
    wait_rotating = false;
  }
  
  bool moveToPoint(point _point, int16_t _speed, int16_t _angle = 255, int16_t _max_speed = max_trajectory_linear_speed, int16_t _min_speed = min_trajectory_linear_speed)
  {
    int d_1_Speed, d_2_speed;
    int accel_1_Length, accel_2_Length, whole_path, start_point_distance; //1.1 - tg of line
    moving_point[0] = _point.x;
    moving_point[1] = _point.y;
    moving_point[2] = 0; //choosing angle will be added in the future
    moving_point[3] = _speed;
    move_angle = get_angle_to_point(robot_position, _point).angle;
    point_distance = get_angle_to_point(robot_position, _point).length;
    otladka2 = point_distance;
    start_point_distance = get_angle_to_point(robot_position, start_trajectory).length;
    _max_speed = _max_speed - constrain(20, 0, my_abs(angular_speed) * 2);
    // -1 - speed from reg
    // 0 - turn to point
    // 1 - standart speed
    if(_speed == 0 || point_distance < 10)
    {
      move_speed = 0;
      moveRobotAbs(move_angle,constrain(_max_speed, 0, move_speed));
    }
    else if(_speed == -1)
    {
      if(use_trajectory)
      {
        if(_point.angle != - 255)
        {
          setAngle(_point.angle, 3);
        }
        
        if(point_distance > start_point_distance / 2)
        {
          move_speed = constrain(_max_speed, _min_speed, my_abs(start_point_distance - point_distance) * 1.5);
        }
        else
        {
          move_speed = constrain(_max_speed, _min_speed, (point_distance) * 1.5);
        }
      }
      else
        move_speed = constrain(_max_speed, _min_speed, point_distance * 1.5);
      moveRobotAbs(move_angle,constrain(_max_speed, _min_speed, move_speed));
    }
    else
    {
      move_speed = _speed;
      moveRobotAbs(move_angle, constrain(_max_speed, _min_speed, move_speed));
    }
    
    if(_point.angle != -255)
      setAngle(_point.angle, max_trajectory_angular_speed, -0.29);
    
    if((point_distance > 8 && _point.significanse == 2) ||
       (point_distance > 12  && _point.significanse == 1) ||
       (point_distance > 25 && _point.significanse == 0)) 
      point_reached_timer = time_service::getCurTime();
    
    point_reached = time_service::getCurTime() - point_reached_timer > 150;
    
    otladka1 = int(point_reached_timer / 1000);
    
    return time_service::getCurTime() - point_reached_timer > 150;
  }
  
  bool moveToPoint(int _x, int _y, int16_t _speed,  int16_t _x0_angle = -255)
  {
    use_trajectory = false;
    uint8_t _max_speed = 70;
    uint8_t _min_speed = 10;
    _sub_point.x = _x;
    _sub_point.y = _y;
    moving_point[2] = 0; //choosing angle will be added in the future
    moving_point[3] = _speed;
    move_angle = get_angle_to_point(robot_position, _sub_point).angle;
    point_distance = get_angle_to_point(robot_position, _sub_point).length;
    // -1 - speed from reg
    // 0 - turn to point
    // 1 - standart speed
    if(_speed == 0 || point_distance < 5) move_speed = 0;
    else if(_speed == -1) move_speed = constrain(_max_speed, _min_speed, point_distance * 2);
    else move_speed = _speed;
    
    if(_x0_angle != - 255)
      setAngle(_x0_angle, 5);
    moveRobotAbs(move_angle, move_speed);
    
    if(point_distance > 5) point_reached_timer = time_service::getCurTime();
    
    return time_service::getCurTime() - point_reached_timer > 200;
  }
  
  void rotateRobot(int16_t _angular_speed, int16_t _max_angular_speed)
  {
    angular_speed = _angular_speed;
    max_angular_speed = _max_angular_speed;
  }
  
//  bool predict()
//  {
//   _alpha = atan2(_dxb, _dyb);
//   
//   if(_dSSoft > 70 && _dyb > 20)
//   {
//     _y1b = ball_abs_y - 37;
//     _x1b = tan(_alpha) * _y1b;
//     if(my_abs(_x1b + camera.get_old_b_x()) < 45)
//     {
//      _defender_predicted_x = _x1b * 1.4 + camera.get_old_b_x();
//      _defender_predicted_y = 35;
//      prediction_timer = time_service::getCurTime();
//      predicted_point.x = _defender_predicted_x;
//      predicted_point.y = _defender_predicted_y;
//      return true;
//     }
//     else
//     {
//       if(time - prediction_timer < 2000)
//       {
//         _defender_predicted_x = _x1b * 1.4 + camera.get_old_b_x();
//         _defender_predicted_y = 35;
//         predicted_point.x = _defender_predicted_x;
//         predicted_point.y = _defender_predicted_y;
//         return true;
//       }
//     }
//   }
//   else
//   {
//     if(time - prediction_timer < 2000)
//     {
//       _y1b = ball_abs_y - 35;
//       _x1b = tan(_alpha) * _y1b;
//       if(my_abs(_x1b + camera.get_old_b_x()) < 45)
//       {
//        _defender_predicted_x = _x1b * 1.3 + camera.get_old_b_x();
//        _defender_predicted_y = 35;
//        predicted_point.x = _defender_predicted_x;
//        predicted_point.y = _defender_predicted_y;
//        return true;
//       }
//     }
//   }
//   return false;
//  }
  bool predict(uint8_t min_speed = 50)
  {
    _alpha = atan2(_dxb, _dyb);
     
    if(_dSSoft > 0/* && _dyb > 20*/)
    {
      if(my_abs(_alpha) < 90)
      {
        _y1b = ball_abs_y - 35;
        _x1b = tan(_alpha) * _y1b;
      }
      if(my_abs(_x1b + camera.get_old_b_x()) < 45)
      {
         _defender_predicted_x = _x1b * 1.4 + camera.get_old_b_x();
         _defender_predicted_y = 35;
         prediction_timer = time_service::getCurTime();
         predicted_point.x = _defender_predicted_x;
         predicted_point.y = _defender_predicted_y;
         return true;
      }
    }
  }
  
  bool is_ball_seen_T(uint16_t _T)
  {
    return camera.is_ball_seen(_T);
  }
  
  void wait(uint32_t _duration,bool en_rotation = false, int16_t _angle = 255, uint8_t rotation_speed = 10, int16_t _keck_angle = 255)
  {
      uint32_t _start_time = time_service::getCurTime();
      waiting = true;
      wait_rotating = en_rotation;
      waiting_angle = _angle;
      int16_t _delta = gyro - _keck_angle;
      while(_start_time + _duration > time_service::getCurTime())
      {
        if(en_rotation && my_abs(_angle) <= 180) setAngle(_angle, rotation_speed);
        if(en_rotation && _keck_angle == 255 && my_abs(gyro - _angle) < 7) break;
        if((my_abs(gyro - _keck_angle) < 5 || (_delta >= 0 && gyro - _keck_angle < 0))
          && _keck_angle != 255)
        {
          set_dribler_speed(0);
          wait(7);
          keck();
        }
        
        if(!use_delays || ball_distance_delay_disable)
        {
          if(!use_delays)
          {
            waiting = false;
            return;
          }
            
          if(ball_distance_delay_disable)
          {
            //if(is_ball_seen_T(200) && (ball_distance > 17 || my_abs(ball_loc_angle) > 17))
            //if(ADC2->DR > BALL_DETECTION_LIGHTNESS)
            //{  
             // waiting = false;
             // return;
            //}
          }
        }
        
        update();
        time_service::delay_ms(1);
      }
      waiting = false;
  }
  
  void callibrate_gyro()
  {
    motors.moveRobot(0, 0, 0, 0, 0, 0);
    control_led(2, ON);
    wait(500);
    //mpu.calibrate(1000);
    //mpu.setZeroAngle();
    while(usart6::available() == 0);
    gyro_zero_angle = lead_to_degree_borders((usart6::read() * 2));
    control_led(2, OFF);
   // motors_on_off(OFF);
    is_callibrated = true;
  }
  
  void side_keck(int16_t _start_angle = 255, int16_t _stop_angle = 255, uint8_t _speed = 30, int16_t _keck_angle = 0, uint8_t _kick_power = 6, uint8_t turn_speed = 8)
  {
      uint32_t _timeout = 1500;
      uint32_t _start_tim = time;
      bool _keck_done = false;
      if(_start_angle != 255)
      {
        while(my_abs(lead_to_degree_borders(gyro - _start_angle)) > 7 && time - _start_tim < _timeout)
        {
          setAngle(_start_angle, turn_speed);
          update();
          
//          if(!use_delays || ball_distance_delay_disable)
//          {
//            if(!use_delays)
//            {
//              _keck_done = true;
//              return;
//            }
//              
//            if(ball_distance_delay_disable)
//            {
//              if(is_ball_seen_T(200) && (ball_distance > 17 || my_abs(ball_loc_angle) > 17))
//              {  
//                _keck_done = true;
//                return;
//              }
//            }
//          }
        }
      }
      wait(100);
      _start_tim = time;
      int16_t _delta = lead_to_degree_borders(gyro - _keck_angle);
      if(_stop_angle != 255)
      {
        while(my_abs(gyro - _stop_angle) > 2 && time - _start_tim < _timeout)
        {
          if((my_abs(gyro - _keck_angle) < 3 || 
            ((_delta >= 0 && lead_to_degree_borders(gyro - _keck_angle) < 0) ||
            (_delta <= 0 && lead_to_degree_borders(gyro - _keck_angle) > 0)))
            && _keck_angle != 255 && !_keck_done)
          {
            set_dribler_speed(0);
            wait(10);
            keck(_kick_power);
            _keck_done = true;
          }
          
//          if(!use_delays || ball_distance_delay_disable)
//          {
//            if(!use_delays) 
//            {
//              _keck_done = true;
//              return;
//            }
//            if(ball_distance_delay_disable)
//            {
//              if(is_ball_seen_T(200) && (ball_distance > 17 || my_abs(ball_loc_angle) > 17))
//              {
//                _keck_done = true;
//                return;
//              }
//            }
//          }
          Robot::wait(1, true, _stop_angle, _speed, _keck_angle);
        }
      }
  }
  
  
  void direct_keck(uint8_t _power = 20, uint8_t stop_duration = 20)
  {
    _power = constrain(20, 0, _power);
    set_dribler_speed(0);
    wait(stop_duration);
    keck(_power); 
    wait(100);
  }
  
  bool is_ball_captured(uint32_t wait_duration = 1000)
  {
    return (time - ball_grab_timer) > wait_duration;
  }
  
  void enable_delay()
  {
    use_delays = true;
  }
  
  void disable_delay()
  {
    use_delays = false;
  }
  
  void ball_distance_disable_delay(bool _data)
  {
    ball_distance_delay_disable = _data;
  }
  
  void draw_menu()
  {
    timer_1000ms = time_service::getCurTime();
    display_clear();
    if(_game_state)
    {
      if(check_button(ENTER_BUTTON))
        change_game_state();
      
      display_data("Gyro & gates", 11, gyro, 1, 0, 0);
      display_draw_number(lead_to_degree_borders(forward_angle - gyro), 1, 13, 0);
      display_data("Robot XY", 9, robot_x, 1, 0, 1);
      display_draw_number(robot_y, 1, 12, 1);
      display_data("def_data", 8, display_data_1, 2, 0, 2);
      display_draw_number(display_data_2, 1, 14, 2);
      
      display.drawLine(64, 40, constrain(128, 0, _x1b + 64), 64);
    }
    else
    {
      if(check_button(UP_BUTTON))
        select_arrow_y = constrain(4, 0, select_arrow_y - 1);
      if(check_button(DOWN_BUTTON))
        select_arrow_y = constrain(4, 0, select_arrow_y + 1);
      if(menu_level == 0)
      {
        if(check_button(ENTER_BUTTON))
        {
          switch(select_arrow_y)
          {
            case 0: callibrate_gyro(); break;
            case 1: change_side(); break;
            case 2: change_game_state(); break;
            case 3: keck(50); break;
            case 4: 
              menu_level = 11;
              main_menu_arrow_y = select_arrow_y;
              select_arrow_y = 0;
            break;
          }
        }
        
        display_data("Gyro & gate", 10, gyro, 1, 0, 0);
        display_draw_number(lead_to_degree_borders(forward_angle - gyro), 1, 13, 0);
        if(side)
          display_draw_string("Side  Yellow", 0, 1);
        else
          display_draw_string("Side  Blue", 0, 1);
        display_draw_string("RUN-------------", 0, 2);
        //display_data("voltage", 7, dma_voltage.dataReturn(0), 1, 0, 3);
        display_draw_string("Keck", 0, 3);
        display_data("voltage", 7, voltage, 1, 7, 3);
        //display_draw_number(voltage, 1, 9, 3);
        display_draw_string("Test data", 0, 4);
        display_draw_number(display_data_1, 1, 9, 4);
        display_draw_number(display_data_2, 1, 14, 4);
      }
      else if(menu_level == 11)
      {
        if(check_button(ENTER_BUTTON)) 
        {
          switch(select_arrow_y)
          {
            case 0: 
              menu_level = 0;
              select_arrow_y = main_menu_arrow_y;
              break;
            case 2: 
              _test_dribler_mode = my_abs(_test_dribler_mode - 1);
              if(_test_dribler_mode == 1)
              {
                if(role == 1)
                  set_dribler_speed(40);
                else
                  set_dribler_speed(130);
              }
              else
                set_dribler_speed(0);
              break;
            case 4:
              if(dribler_speed == 0)
                set_dribler_speed(40, false);
              else
                set_dribler_speed(0, true);
              dribbler_mode = my_abs(dribbler_mode - 1);
              break;
          }
        }
        
        display_draw_string("...", 0, 0);
        display_data("Robot XY", 9, robot_x, 1, 0, 1);
        display_draw_number(robot_y, 1, 12, 1);
        //display_data("Ball abs XY", 11, ball_abs_x, 1, 0, 2);
        //display_draw_number(ball_abs_y, 1, 14, 2);
        display_draw_string("dribler", 0, 2);
        display_data("def_data", 8, display_data_1, 1, 0, 3);
        display_draw_number(display_data_2, 1, 14, 3);
        //display_draw_string("on/off dribbler",0, 4);
        //display_draw_number(dribler_speed, 1, 14, 4);
      }
      display_draw_string("<", 17, select_arrow_y);
    }
    display_update();
    display_update_time = time_service::getCurTime() - timer_1000ms;
//      if(time - timer_1000ms > 1000)
//      {
//        image_num = my_abs(image_num - 1);
//        display.drawImage(image_num);
//        //display.display();
//        timer_1000ms = time;
//      }
  }
  
 void update()
 {
    old_time = time;
    time = time_service::getCurTime();
    loop_delay = time - old_time;
    
    //mpu.update();
   if(usart6::available() > 0)
    gyro = lead_to_degree_borders((usart6::read() * 2) - gyro_zero_angle);//lead_to_degree_borders(mpu.getAngle());
    
   // ball.get_data();
    //ball_angle = lead_to_degree_borders(ball.get_angle() + gyro);
    
    camera.getData();
    camera.calculate_pos(gyro, side);
    
    robot_x = camera.get_x();
    robot_y = camera.get_y();
    
    robot_position.x = robot_x;
    robot_position.y = robot_y;
    
    ball_loc_angle = lead_to_degree_borders(ball_threshold + camera.get_ball_angle());
    ball_abs_angle = lead_to_degree_borders(ball_threshold + camera.get_abs_ball_angle());
    ball_distance = camera.get_ball_distance();
    
    ball_loc_x = camera.get_ball_loc_x();
    ball_loc_y = camera.get_ball_loc_y();
    
    ball_abs_x = camera.get_ball_abs_x();
    ball_abs_y = camera.get_ball_abs_y();
    
    old_b_x = camera.get_old_b_x();
    old_b_y = camera.get_old_b_y();
    
    _dxb = camera.get_dbx();
    _dyb = camera.get_dby();
    _dS = camera.get_dS();
    _dSSoft = camera.get_dSSoft();
    
    is_ball_seen = camera.is_ball_seen();
    
    forward_angle = camera.get_forward_angle();
    forward_distance = camera.get_forward_distance();
    backward_angle = camera.get_backward_angle();
    backward_distance = camera.get_backward_distance();
    sub_adc_data = ADC2 -> DR;
    if(sub_adc_data != 0) ball_data = sub_adc_data;
    
    if(role == 1)
    {
      if(ball_data < ATTACKER_BALL_DETECTION_LIGHTNESS) ball_grab_timer = time;
    }
    else
    {
      if(ball_data < DEFENDER_BALL_DETECTION_LIGHTNESS) ball_grab_timer = time;
    }
    
   if(time - bluetooth_send_timer > 5 && _game_state == 1)
    {
      if(is_ball_seen_T(100))
        send_bluetooth_data(ball_abs_x, ball_abs_y, ball_distance);
     bluetooth_send_timer = time;
    }
   
    if(usartik1::available() >= 4)
    {
      for (int i = 0; i < 4; i++)
        bluetooth_data[i] = usartik1::read();
      if(bluetooth_data[0] >= 253 && my_abs(bluetooth_data[3] - (bluetooth_data[1] + bluetooth_data[2]) / 2) < 2)
      {
          bluetooth_receive_time = time;
          ball_bluetooth_x = int(bluetooth_data[1] - 100) * 2;
          ball_bluetooth_y = int(bluetooth_data[2] - 100) * 2;
          ball_bluetooth_dist = bluetooth_data[0];
        
      }
    }
    if(time - timer10ms > 10)
    {
      //ball_sen_data = DMA_ball_sen.dataReturn(0);
      ball_sen_data_soft = ball_sen_data * ball_sen_data_k + ball_sen_data_soft * (1 - ball_sen_data_k);
      timer10ms = time;
    }
    
//    if(camera.get_ball_seen_time() + 100 < bluetooth_receive_time || (ball_distance > 150 && ball_bluetooth_dist > 253 && time - bluetooth_receive_time < 100))
//    {
//      ball_abs_x = ball_bluetooth_x;
//      ball_abs_y = ball_bluetooth_y;
//      ball_loc_x = ball_abs_x - robot_x;
//      ball_loc_y = ball_abs_y - robot_y;
//      ball_abs_angle = getAngleToPoint(ball_abs_x, ball_abs_y);
//      ball_loc_angle = lead_to_degree_borders(ball_abs_angle - gyro);
//      ball_distance = getDistanceToPoint(ball_loc_x, ball_loc_y);
//    }
    
    if(time - robot_global_speed_timer > 500)
    {
      robot_position_diff = get_angle_to_point(robot_position, robot_previous_position).length;
      robot_previous_position = robot_position;
      robot_global_speed_timer = time;
    }
    
    adc1_sub = ADC1 -> DR;
    if(adc1_sub != 0) voltage = adc1_sub * 0.002625 + 5.55;
    #if USE_DISPLAY
      draw_menu();
    #else
      if(check_button(DOWN_BUTTON))
        callibrate_gyro();
      if(check_button(UP_BUTTON) && time - init_timer > 5000)
        change_game_state();
      if(check_button(ENTER_BUTTON))
        change_game_state();
      //control_led(0, ON);
      #endif
    check_buttons();
    
    if(time - blinking_timer > blinking_durations && blinking_durations > 0)
    {
      leds_state = my_abs(leds_state - 1);
      for(int i   = 0; i < 3; i++)
      {
        if(blinking_leds[i])
        {
          control_led(i + 1, leds_state);
        }
      }
      blinking_timer = time;
    }
    
    if(use_trajectory)
    {
      //if first point
      if((!trajectory_is_in_progress || trajectory_started) && trajectory.get_length() > 0)
      {
        robot_move = trajectory.pop();
        moving_point[0] = robot_move.x;
        moving_point[1] = robot_move.y;
        start_trajectory.x = robot_x;
        start_trajectory.y = robot_y;
        start_trajectory_vector.angle = move_angle;
        start_trajectory_vector.length = move_speed;
        point_reached = false;
        trajectory_started = false;
        trajectory_is_in_progress = true;
        point_reached_timer = time_service::getCurTime();
      }
      //if distance less than const
      if(point_reached && trajectory.get_length() > 0)
      {
        robot_move = trajectory.pop();
        moving_point[0] = robot_move.x;
        moving_point[1] = robot_move.y;
        start_trajectory.x = robot_x;
        start_trajectory.y = robot_y;
        start_trajectory_vector.angle = move_angle;
        start_trajectory_vector.length = move_speed;
        point_reached = false;
        point_reached_timer = time_service::getCurTime();
      }
      
      if(point_reached  && trajectory.get_length() <= 0)
      {
        trajectory_finished = true;
        trajectory_is_in_progress = false;
      }
      else
      {
        trajectory_finished = false;
        trajectory_is_in_progress = true;
      }
      moveToPoint(robot_move, -1);     
    }
    else
      trajectory_is_in_progress = false;
    
    if(waiting)
    {
      move_speed = 0;
      if(!wait_rotating)
        angular_speed = 0;
      else
      {
        if(my_abs(gyro - waiting_angle) < 10) angular_speed = 0;
      }
    }
    
    if(time_service::getCurTime() - dribler_speed_change_speed > change_speed_time || (dribler_speed == STOP_DRIBLER_SPEED && fast_stop))
    {
      if(my_abs(cur_dribler_speed - dribler_speed) <= dribler_acc || (dribler_speed == STOP_DRIBLER_SPEED && fast_stop)) cur_dribler_speed = dribler_speed;
      else
      {
        cur_dribler_speed += dribler_acc * my_sgn(dribler_speed - cur_dribler_speed);
      }
      //dribler_speed = STOP_DRIBLER_SPEED + constrain(MAX_DRIBLER_SPEED, 0, int(cur_dribler_speed));
      dribler_speed_change_speed = time_service::getCurTime();
    }
    if(role == 1)
      cur_dribler_speed = constrainf(STOP_DRIBLER_SPEED + MAX_ATTACKER_DRIBLER_SPEED, STOP_DRIBLER_SPEED, cur_dribler_speed);
    else
      cur_dribler_speed = constrainf(STOP_DRIBLER_SPEED + MAX_DEFENDER_DRIBLER_SPEED, STOP_DRIBLER_SPEED, cur_dribler_speed);
    //display_data(cur_dribler_speed);
    
    #if USE_DRIBLER
      if(_use_dribler)
        dribler_control.pwm(cur_dribler_speed);
      else
        dribler_control.pwm(STOP_DRIBLER_SPEED);
    #else
      dribler_control.pwm(0);
    #endif
    
    if(motors_state && !OTLADKA)
    {
      #if USE_MOTORS
      motors.moveRobot(move_speed, 30, move_angle, angular_speed, time, 0);
      #else
      motors.disableMotors();
      #endif
      
//      if(dribler_speed < 300 && dribler_speed >= 200) //unnecessary if will delete it later haha 
//        dribler_control.pwm(dribler_speed);
    }
    else
    {
      motors.disableMotors();
      //#if USE_DRIBLER
        //dribler_control.pwm(STOP_DRIBLER_SPEED);
      //#else
        //dribler_control.pwm(0);
      //#endif
    }  
  }
}