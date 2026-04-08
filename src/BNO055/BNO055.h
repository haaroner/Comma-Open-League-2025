#include "project_config.h"
#include "usart6.h"
#include "time_service.h"

class BNO
{
  public:
  BNO();
  void init();
  void update();
  int16_t get_yaw();
  uint8_t get_calib_status();
   
  private:
    int32_t MSB, LSB;
    int _calib_status;
    int _result;
    void write_reg(uint8_t reg, uint8_t data);
    int16_t read_reg(uint8_t reg);
    uint32_t yaw_timer;
};