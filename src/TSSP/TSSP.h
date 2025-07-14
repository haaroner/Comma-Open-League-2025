#include "project_config.h"
#include "pin_setup.h"
#include "time_service.h"
#include "dma.h"
#include "tools.h"

enum mode
{
  digital,
  analog
};

class TSSP
{
  public:
    TSSP(uint16_t reading_mode,pin &write_1, pin &write_2, pin &write_3, pin &write_4,pin &read_1, 
         pin &read_2, uint8_t role/*, Dma &left_dma, Dma &right_dma*/);
    void get_data();
    int16_t get_angle();
    uint16_t get_distance();
    bool is_see();
  private:
    void get_digital_data(), get_analog_data();
    void set_addres(uint8_t _data);
    uint16_t get_angle_from_index(uint16_t _num);
    uint16_t _mode;
    pin _write_1, _write_2, _write_3, _write_4;
    pin _read_1, _read_2;
    //Dma _left_dma, _right_dma;
    uint8_t _channels[16][4];
    bool _data[32];
    uint16_t _adc_data[32];
    double _x, _y;
    bool _result[32];
    uint16_t _adc_result[32];
    int16_t _result_angle;
    uint16_t _result_distance;
    uint16_t _test;
    uint16_t _min_analog_level;
    uint8_t _role;
    uint32_t _tim;
    bool _is_see, _angle_en;
};
