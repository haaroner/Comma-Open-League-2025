#include "libs.h"
#include "robot_math.h"

class Timer
{
  public:
    Timer()
    {
      _start_time = 0;
    }
    void save_time()
    {
      _start_time = time_service::getCurTime();
    }
    bool is_duration_reached(uint32_t _duration)
    {
      return time_service::getCurTime() - _start_time >= _duration;
    }
    uint32_t get_time()
    {
      return time_service::getCurTime() - _start_time;
    }
  private:
    uint32_t _start_time;
};