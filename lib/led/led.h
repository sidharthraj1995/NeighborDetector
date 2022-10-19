/****
 * Custom LED Library
 ****/
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
    int getLEDState();
    void ledON();
    void ledOFF();
    void ledFlash(int cycle = 3, int debounce = 250);
    ~LED();
};

#endif