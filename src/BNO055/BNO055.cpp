#include "BNO055.h"

BNO::BNO()
{}

void BNO::write_reg(uint8_t reg, uint8_t data) 
{
  usart6::write(0xAA); //start byte
  usart6::write(0x00); //write flag
  usart6::write(reg);  //reg addr
  usart6::write(0x01);
  usart6::write(data);
  time_service::delay_ms(1);
}
volatile uint8_t _chip_id = 0;
uint8_t BNO::read_reg(uint8_t reg)
{
  while(usart6::available()>0)
    usart6::read();
  usart6::write(0xAA); //start byte
  usart6::write(0x01); //read flag
  usart6::write(reg);
  usart6::write(0x01);
  uint8_t _response = 0;
  uint32_t _duration = time_service::getCurTime();
  
  while(_response!=0xBB)
  {
    if(usart6::available()>0)
      _response = usart6::read();
    if(time_service::getCurTime() - _duration > 200)
      return 255;
  }
  
  while(usart6::available() < 2);
  usart6::read();
  return usart6::read();
}

void BNO::init()
{
  /*reading chip id to check connection*/
  _chip_id = BNO::read_reg(0x00);
  if(_chip_id != 0xA0)
  {
    while(true);
  }
  
  BNO::write_reg(0x3D, 0x00); //go to cfgr mode
  //setup
  BNO::write_reg(0x3D, 0X08); //go to IMU mode (gyro+accel+fusion)
}

int16_t BNO::get_yaw()
{
  int _result;
  _result = ((BNO::read_reg(0x1B)<<8) | BNO::read_reg(0x1A))/16;
  return _result;
}