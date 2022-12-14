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
 * Updates LED State
 ****/
void LED::setLEDState(unsigned char state)
{
  digitalWrite(_ledPin, state);
  LED::ledUpdate();
  // Serial.printf("<SYSTEM_LED> Setting State: %d\n", state);
}

/****
 * Returns the instaneous state of LED
 ****/
byte LED::getLEDState()
{
  LED::ledUpdate();
  Serial.printf("<SYSTEM_LED> Returning State: %d\n", _ledState);
  return _ledState;
}

/****
 * Method to update LED state
 ****/
void LED::ledUpdate() {
  _ledState = digitalRead(_ledPin);
}

/****
 * Changes state of the LED
 ****/
void LED::toggleLED() {
  LED::setLEDState(!(_ledState));
}

/****
 * Changes the state of the LED to OFF
 ****/
void LED::ledOFF()
{
  LED::setLEDState(DIO_OFF);
  Serial.println("<SYSTEM_LED> LED turned OFF");
}

/****
 * Changes the state of the LED to ON
 ****/
void LED::ledON()
{
  LED::setLEDState(DIO_ON);
  Serial.println("<SYSTEM_LED> LED turned ON");
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
