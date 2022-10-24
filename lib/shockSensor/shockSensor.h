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

public:
  shockSensor(uint8_t pin);
  int shockCount = 0;
  void shockInit();
  void readState();
  byte getState();
  void setState();
  bool shockMonitor();            // redundant?
  void showShock(uint8_t mode);   // get rid of it

  // Add callabck func for read
};

#endif