#include "robot_math.h"
#include "tools.h"

class Action
{
  public:
    Action()
    {
      _data = 0;
    }
    void activate()
    {
      _data = 1;
    }
    bool read()
    {
      _sub = _data;
      _data = 0;
      return _sub;
    }
  private:
    bool _data, _sub;
};
