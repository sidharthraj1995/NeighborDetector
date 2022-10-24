#include "shockSensor.h"

/****
 * Shock Class Constructor
 ****/
shockSensor::shockSensor(uint8_t pin)
{
  _shockPin = pin;
  _shockEnabled = DIO_DISABLED;
}

/****
 * Init Shock Sensor class
 * Enabled Shock Sensor system
 ****/
void shockSensor::shockInit()
{
  pinMode(_shockPin, INPUT);
  _shockState = DIO_ENABLED;
  Serial.printf("<SYSTEM_SHOCK> Init successful using PIN: %d\n", _shockPin);
}

/****
 * Simple method to read Shock sensor state
 ****/
void shockSensor::readState()
{
  _shockState = digitalRead(_shockPin);
  // Serial.println("<SHOCK> Shock Sensor READ!!");
}

/****
 * Simple method to return shock sensor state
 ****/
byte shockSensor::getState()
{
  if (_shockState == shockTriggered)
    return DIO_ON;

  return DIO_OFF;
}

bool shockSensor::shockMonitor()
{
  volatile byte shock = shockSensor::getState();
  if (shock == shockTriggered)
  {
    return DIO_ON;
  }

  return DIO_OFF;
}

/****
 * !!PENDING!! Internal call to "show" shock
 * still not sure if there is a need for this within shocksensor class
 ****/
void shockSensor::showShock(uint8_t mode)
{
  //to
}
