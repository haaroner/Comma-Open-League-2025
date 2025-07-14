#include "project_config.h"

#include "pin_setup.h"
#include "Dma.h"

class line
{
  public:
    line(pin bit_1, pin bit_2, pin bit_3, pin bit_4, Dma data_1, Dma data_2);
    int16_t get_data();
  private:
    pin _bit_1;
    pin _bit_2;
    pin _bit_3;
    pin _bit_4;
    
    Dma _data_1;
    Dma _data_2;
  
    uint16_t _data[32];
    
    float _angle_const;
    int _standart_light;
    int _distance, _counter, _average_angle;
  
    void read_sensors();
    void set_address(uint8_t _address);
};
