#include "LED.h"

LED::LED(uint8_t pin)
{
  _ledPin = pin;
}

/****
 * Init LED class, register the pin and set the mode
 * It also Enables LED system
 * SET the LED to OFF
 ****/
void LED::ledInit()
{
  pinMode(_ledPin, OUTPUT);
  LED::ledOFF();
  _ledEnabled = DIO_ENABLED;
  Serial.printf("<SYSTEM_MAIN> LED OBJ init using PIN: %d\n", _ledPin);
}

/****
 * Used to set the logical state of the LED
 ****/
void LED::setLEDState(unsigned char state)
{
  _ledState = state;
  Serial.println("<SYSTEM_LED> Setting State");
}

/****
 * Returns the instaneous state of LED
 ****/
int LED::getLEDState()
{
  Serial.println("<SYSTEM_LED> Returning State");
  return _ledState;
}

/****
 * Changes the state of the LED to OFF
 ****/
void LED::ledOFF()
{
  digitalWrite(_ledPin, DIO_OFF);
  LED::setLEDState(DIO_OFF);
  Serial.println("<SYSTEM_LED> LED turned OFF");
}

/****
 * Changes the state of the LED to ON
 ****/
void LED::ledON()
{
  digitalWrite(_ledPin, DIO_ON);
  LED::setLEDState(DIO_ON);
  Serial.println("<SYSTEM_LED> LED turned ON");
}

/****
 * Changes the state of the LED to passed state
 ****/
void LED::ledToggle()
{
  digitalWrite(_ledPin, _ledState);
  Serial.printf("<SYSTEM_LED> LED turned to state %d\n", _ledState);
  LED::setLEDState(!_ledState);
}

/****
 * !!PENDING!!
 * A method to internally flash the LED
 ****/
void LED::ledFlash(int cycle , int debouce)
{
  LED::ledOFF();
  for (int i = 0; i < cycle; i++)
  {
    LED::ledON();
    delay(debouce);
    LED::ledOFF();
    delay(debouce);
  }
  flashCount++;
  Serial.printf("<SYSTEM_LED> <%d> LED mode: FLASH, CYCLE: %d, DEBOUNCE: %d\n", flashCount, cycle, debouce);
}

/****
 * LED deconstructor
 ****/
LED::~LED()
{
  Serial.println("<SYSTEM_MAIN> LED object deleted!!");
}
