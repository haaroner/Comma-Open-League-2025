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
   
  private:
    void write_reg(uint8_t reg, uint8_t data);
    uint8_t read_reg(uint8_t reg);
};