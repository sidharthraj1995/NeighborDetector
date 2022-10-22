/**==============================================
 * *                   LED Library
 * Simple library to interact with Light Emitting
 * Diode for ease of use
 *   
 *
 *=============================================**/


#ifndef LED_h
#define LED_h

#include <Arduino.h>
#include <rtc_config.h>

class LED
{
private:
    unsigned char _ledEnabled;
    
    uint8_t _ledPin;
    volatile byte _ledState;
    int flashCount = 0;

public:
    LED(uint8_t pin);
    void ledInit();
    void setLEDState(byte state);
    byte getLEDState();
    void toggleLED();
    void ledON();
    void ledOFF();
    void ledFlash(int cycle = 3, int debounce = 250);
    ~LED();
};

#endif