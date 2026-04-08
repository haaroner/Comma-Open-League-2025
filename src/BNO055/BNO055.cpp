#include "BNO055.h"
#include "time_service.h"

BNO::BNO()
{
  yaw_timer = 0;
}

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
int16_t BNO::read_reg(uint8_t reg)
{
  while(usart6::available()>0)
    usart6::read();
  usart6::write(0xAA); //start byte
  usart6::write(0x01); //read flag
  usart6::write(reg);
  usart6::write(0x01);
  uint8_t _response = 0;
  uint32_t _duration = time_service::getCurTime();
  
  while(usart6::available() < 2)
  {
  if(time_service::getCurTime() - _duration > 3)
      return 0;
  }
  _response = usart6::read();
  
  if(_response != 0xBB) return -1;
  uint8_t _length = usart6::read();
  if(_length != 1) return -1;
  uint8_t _data = usart6::read();
  if(true)
    return _data;
  else 
    return -1;
}

void BNO::init()
{
  /*reading chip id to check connection*/
  _chip_id = BNO::read_reg(0x00);
  if(_chip_id != 0xA0)
  {
    while(_chip_id != 0xA0)
    {
      _chip_id = BNO::read_reg(0x00);
    }
  }
  
  //BNO::write_reg(0x3D, 0x00); //go to cfgr mode
  //setup
  BNO::write_reg(0x3D, 0X08); //go to IMU mode (gyro+accel+fusion)
}

int16_t BNO::get_yaw()
{
  if(time_service::getCurTime() - yaw_timer > 100)
  {
    MSB = BNO::read_reg(0x1B);
  //else if(time_service::getCurTime() - yaw_timer < 20)
    LSB = BNO::read_reg(0x1A);
  //else
    yaw_timer = time_service::getCurTime();
  }
  
  if(MSB != -1 && LSB != -1 && (((MSB<<8) | LSB)/16 <= 360))
    _result = ((MSB<<8) | LSB)/16;
  return _result;
}

uint8_t BNO::get_calib_status()
{
  int _data = BNO::read_reg(0x35);
  if(_data != -1)
    _calib_status = _data;
  return _calib_status;
}