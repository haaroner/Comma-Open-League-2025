#pragma once

#include "project_config.h"
#include "usart3.h"
#include "time_service.h"
#include "math.h"
//#include "robot_math.h"

/*
CLASS BLDC to control bldc motor with B-G431-ESC driver (with simplefoc lib)
Available commands:
1)callibrate - starts alignment of all elements
callibration lasts approx. 2.5S

2)enable - may be done once callibration have been done
enables motor movement(stops frewheeling)

3)disable - starts frewheeling
after this command motor may be recallibrated or enabled

4)set_speed - sets speed. Can be done after callibrate() or enable()
 
 
This program doesnt provide motor telemetry due to lack of available USARTs
All motors are connected to one STM32's TX bus
*/

//TODO: make any USARTx usage

class BLDC
{
  public:
    BLDC(uint8_t UART_num, char Motor_index, char STOP_byte, char Callibration_byte, 
      uint16_t max_speed)
    {
      _UART_num = UART_num;
      _Motor_index = Motor_index;
      _STOP_byte = STOP_byte;
      _Callibration_byte = Callibration_byte;
      _max_speed = max_speed;
      _cur_speed = 0;
      _max_step = 100;
    }
    
    //simplefoc sais [speed] is in rad/s, but max real speed is reached
    //on 5000 rad/s => it is 100 rps (in real 8rps)
    void set_speed(int speed) 
    {
      //if(speed > 0 && speed <= 5)
        //send_command(_Motor_index, 0, _STOP_byte);
      //else if(speed > 5 && speed <= 10)
        //send_command(_Motor_index, 11, _STOP_byte);
      //else
      send_command(_Motor_index, speed, _STOP_byte);
    }
    
    void set_speed_percent(float speed)
    {
      //if(speed > 0 && speed <= 5)
        //send_command(_Motor_index, 0, _STOP_byte);
      //else if(speed > 5 && speed <= 10)
        //send_command(_Motor_index, 11, _STOP_byte);
      //else
      if(speed > 100.0) speed = 100.0;
      if(speed < -100.0) speed = -100.0;
      speed *= _max_speed / 100.0;
      if(speed < 0.01 && speed > -0.01) speed = 0;
      //if(speed > 1020) speed = 1020;
      //if(speed < -1020) speed = -1020;
      //if(abs(speed - _cur_speed) < _max_step) _cur_speed = speed;
      //else _cur_speed += _max_step * ((speed - _cur_speed) / abs(speed - _cur_speed));
      send_commandf(_Motor_index, speed, _STOP_byte);
    }
    
    void enable_motor()
    {
      set_speed(0);
      send_command(_Callibration_byte, 2, _STOP_byte);
    }
    
    void disable_motor()
    {
      set_speed(0);
     // send_command(_Callibration_byte, 0, _STOP_byte);
    }
    
    void reset()
    {
      usart3::reset_uart();
    }
    
    void callibrate()
    {
      set_speed(0);
      send_command(_Callibration_byte, 1, _STOP_byte);
    }
    
  private:
    void send_command(char ID, int32_t command, char STOP)
    {
      uint8_t _data = 0;
      usart3::write(ID);
      char _sgn = 1;
      bool _has_sent_non_zero = false;
      if(command != 0)
      {
        if(command < 0)
        {
          command = command*-1;
          _sgn = -1;
          usart3::write('-');
        }
        for(int i = 0; i < 3; i++)
        {
          _data = 48 + int(int(command / powf(10, 2 - i)) % 10);
          //if(_data!=48 || i == 2)
            //_has_sent_non_zero = true;
          //if(_has_sent_non_zero)
          usart3::write(_data);
        }
      }
      else
        usart3::write('0');
      
      usart3::write(STOP);
      //usart3::write('D');
      //time_service::delay_ms(100);
    }
    void send_commandf(char ID, float command, char STOP)
    {
      uint16_t _data = 0;
      int _command;
      usart3::write(ID);
      char _sgn = 1;
      bool _has_sent_non_zero = false;
      if(command != 0.0)
      {
        if(command < 0)
        {
          command = command*-1;
          _sgn = -1;
          usart3::write('-');
        }
        command *= 100;
        _command = command;
        for(int i = 0; i < 6; i++)
        {
          _data = 48 + int(int(command / powf(10, 5 - i)) % 10);
          if(_data!=48 || i == 2)
          _has_sent_non_zero = true;
          if(_has_sent_non_zero || i >= 3)
          {
            if(i == 4)
              usart3::write('.');
            usart3::write(_data);
          }
        }
      }
      else
      {
        usart3::write('0');
        usart3::write('.');
        usart3::write('0');
      }
      
      usart3::write(STOP);
      //usart3::write('D');
      //time_service::delay_ms(100);
    }
    uint8_t _UART_num;
    char _Motor_index;
    uint16_t _max_speed;
    char _STOP_byte;
    char _Callibration_byte;
    int32_t _cur_speed;
    int _max_step;
};