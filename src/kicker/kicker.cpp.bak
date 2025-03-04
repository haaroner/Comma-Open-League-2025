#include "kicker.h"

kicker::kicker(pin &charge,
								pin &discharge):
								_charge(charge),
								_discharge(discharge)
{
	ready = false;
	state = 0;
	_tim = 0;
	_time = 0;
}

void kicker::check(uint32_t _actual_time)
{
	_time = _actual_time;
	if(state == 0)
	{
		_discharge.resetBit();
		if(_time - _tim < 500)
			_charge.setBit();
		else
		{
			ready = true;
			_charge.resetBit();
		}
	}
	else if(state == 1)
	{
		_charge.resetBit();
		if(_time - _tim < 20)
		{
			_discharge.setBit();
		}
		else
		{
			state = 0;
			_tim = _time;
		}
		ready = false;
	}
  else if(state == 2)
  {
    _discharge.setBit();
  }
}

void kicker::keck()
{
	if(ready == true)
	{
		state = 1;
		_tim = _time;
	}
}
void kicker::discharge()
{
  _charge.resetBit();
  if(state != 2)
    time_service::delay_ms(100);
  state = 2;
}

