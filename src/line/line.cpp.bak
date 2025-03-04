#include "line.h"

line::line(pin bit_1, pin bit_2, pin bit_3, pin bit_4, Dma data_1, Dma data_2):
                                                                   _bit_1(bit_1),
                                                                   _bit_2(bit_2),
                                                                   _bit_3(bit_3),
                                                                   _bit_4(bit_4),
                                                                   _data_1(data_1),
                                                                   _data_2(data_2)
{
  _angle_const = 11.25;
  _standart_light = 2000;
  _distance = 0;
  _counter = 0;
}

void line::set_address(uint8_t _address)
{
  uint16_t channels[16][4] = {
                                {0,0,0,0},
                                {0,0,0,1},
                                {0,0,1,0},
                                {0,0,1,1},
                                {0,1,0,0},
                                {0,1,0,1},
                                {0,1,1,0},
                                {0,1,1,1},
                                {1,0,0,0},
                                {1,0,0,1},
                                {1,0,1,0},
                                {1,0,1,1},
                                {1,1,0,0},
                                {1,1,0,1},
                                {1,1,1,0},
                                {1,1,1,1}
                              };
  
  _bit_1.write(channels[_address][0]);
  _bit_2.write(channels[_address][1]);
  _bit_3.write(channels[_address][2]);
  _bit_4.write(channels[_address][3]);
}

void line::read_sensors()
{
  for(int i = 0; i < 16; i++)
  {
    set_address(i);
    _data[15 - i] = floor(double(_data_1.dataReturn(0) / _standart_light));
    _data[31 - i] = floor(double(_data_2.dataReturn(0) / _standart_light));
  }
}


int16_t line::get_data()
{
  for(int i = 0; i < 32; i++)
  {
    if(_data[i] == 1)
    {
      if(_data[i] <= 15)
        _distance += i * _angle_const + 11.25;
      else
        _distance += (i - 15) * _angle_const * -1;
      _counter++;
    }
  }
  _average_angle = _distance / _counter;
}