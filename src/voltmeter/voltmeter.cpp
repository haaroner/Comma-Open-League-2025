#include "voltmeter.h"

voltmeter::voltmeter(Dma &dma_meter):_dma_meter(dma_meter)
{
  _kv = 0.004267720571744; /*4.385 * 0.000807*/;
  _data = 13.05;
  _old_data = 13.05;
  k1 = 0.9;
  k2 = 0.1;
};

float voltmeter::get_voltage(float _data)
{
  _data *= _kv;
 // _data = _old_data * k1 + _data * k2;
  //_old_data = _data;
 return _data;
}