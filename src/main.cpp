 /* 
  Arkham Labs - ESP32
  Project DhumDhum
  
  Detect footsteps of you upstairs neighbors using 
  an inexpensive Shock Sensor - HW 513
  Signal pin connected to ESP32 - GPIO 32

  Date: Oct 10, 2022
*/



#include <Arduino.h>
// #include <WiFi.h>
// #include <PubSubClient.h>


#define ONBOARD_LED 2

// IO states
#define shockTriggered 0
#define shockIdle 1

#define DIO_ENABLED DIO_ON
#define DIO_DISABLED DIO_OFF
#define DIO_ON 1
#define DIO_OFF 0

// Scan rate
#define shockDebounce 5

// Sensor Pins 
#define knockSensorPin  32
#define shockSensorPin  33


class LED {
private:
  bool _ledEnabled = DIO_DISABLED;
  uint8_t _ledPin;
  unsigned char _ledState;
public:
  LED(uint8_t pin);
  void ledON();
  void ledOFF();
  void setLEDState(unsigned char state);
  int getLEDState();
  void ledFlash(int cycle, int debounce);
  ~LED();
};

LED::LED(uint8_t pin) {
  _ledPin = pin;
  pinMode(pin, OUTPUT);
  LED::ledOFF();
  _ledEnabled = DIO_ENABLED;
  Serial.printf("<SYSTEM_MAIN> LED OBJ init using PIN: %d\n", pin);
}

void LED::setLEDState(unsigned char state) {
  _ledState = state;
  Serial.println("<SYSTEM_LED> Setting State");
}

int LED::getLEDState() {
  Serial.println("<SYSTEM_LED> Returning State");
  return _ledState;
}

void LED::ledOFF() {
  digitalWrite(_ledPin, DIO_OFF);
  LED::setLEDState(DIO_OFF);
  Serial.println("<SYSTEM_LED> LED turned OFF");
}

void LED::ledON() {
  digitalWrite(_ledPin, DIO_ON);
  LED::setLEDState(DIO_ON);
  Serial.println("<SYSTEM_LED> LED turned ON");
}

void LED::ledFlash(int cycle, int debouce = 150) {
  Serial.println("<SYSTEM_LED> LED mode: FLASH enabled");
  LED::ledOFF();
  for(int i = 0; i < cycle; i++) {
    LED::ledON();
    delay(debouce);
    LED::ledOFF();
  }
}

LED::~LED() {
  Serial.println("<SYSTEM_MAIN> LED object deleted!!");
}




class shockSensor {
  private:
  int _shockPin;
  unsigned char _shockState = 1;     // ShockSensor is NC

  public:
  shockSensor(uint8_t pin1);
  void showShock(uint8_t mode);
  void readState();
  int getState();
};


shockSensor::shockSensor(uint8_t pin1) {

}

void shockSensor::showShock(uint8_t mode) {

}

void shockSensor::readState() {

}

int shockSensor::getState() {

}



shockSensor s1(shockSensorPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("<SYS> We are in SETUP!!");
  Serial.println('\n' + "** Fuck Neighbors, White Trash! **" + '\n');
}

void loop() {
  Serial.println("<SYS> We are in LOOP!");
  int sState = s1.getState();
  if(sState == shockTriggered) {
    s1.showShock(shockDebounce);
    sState = s1.getState();
  }
  
}