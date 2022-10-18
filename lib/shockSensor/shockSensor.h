#ifndef shockSensor_h
#define shockSensor_h

#include <Arduino.h>
#include <rtc_config.h>

class shockSensor
{
private:
  unsigned char _shockEnabled = DIO_DISABLED;
  uint8_t _shockPin;
  volatile byte _shockState = DIO_OFF; // ShockSensor is NC
  int shockCount = 0;

public:
  shockSensor(uint8_t pin);
  void shockInit();
  void readState();
  int getState();
  bool shockMonitor();
  void showShock(uint8_t mode);
};

#endif