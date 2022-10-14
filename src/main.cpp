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

// Scan rate
#define shockDebounce 5

// Sensor Pins 
#define knockSensorPin  32
#define shockSensorPin  33

// Sensor states
bool knockSt = 0;
bool shockSt = 0;



// *************** 
// Wifi credentials
// Update network credentials below
// ***************
// const char* SS_D = "E.L.S.A BCKUP";
// const char* PWD = "funnypear2902";



// *************** 
// MQTT credentials
// Update MQTT credentials below
// ***************
// const char *mqttServer = "MQTT_BROKER_IP";
// #define mqtt_port 12595
// #define MQTT_USER "eapcfltj"
// #define MQTT_PASSWORD "3EjMIy89qzVn"



// *************** 
// MQTT
// Add topics below
// ***************

// WiFiClient wifiClient;

// PubSubClient mqttClient(wifiClient); 


class shockSensor {
  private:
  int _shockPin = 999;
  int _ledPin = 990;
  unsigned char _shockState = 1;     // ShockSensor is NC
  unsigned char _ledState = 1;

  public:
  shockSensor(int pin1, int pin2 = ONBOARD_LED);
  void showShock(int debounce);
  void readState();
  int getState();
  void ledON();
  void ledOFF();
};

shockSensor::shockSensor(int pin1, int pin2) {
  pinMode(pin1, INPUT);
  _shockState = 1;        // No shock detected
  _shockPin = pin1;

  pinMode(pin2, OUTPUT);
  digitalWrite(pin2, LOW);
  _ledPin = pin2;
}

void shockSensor::ledOFF() {
  if (!(_ledPin == 99))
  {
    digitalWrite(_ledPin, LOW);
  }
}

void shockSensor::ledON() {
  if (!(_ledPin == 99))
  {
    digitalWrite(_ledPin, HIGH);
  }
}

void shockSensor::showShock(int debounce) {
  if( !(_ledState == 1) )
  {
    shockSensor::ledOFF();
    for(int i=1; i<=debounce; i++)
    {
        shockSensor::ledON();
        Serial.println("Sen1: Shock Detected!!");
        delay(150);
        shockSensor::ledOFF();
        delay(150);
        if(i == debounce)
        {
          _ledState = 1; 
        }
    }
  }
}

void shockSensor::readState() {
  if (!(_ledState == 0)) {
    _shockState = digitalRead(_shockPin);
    delay(150);
  }
  _ledState = 0;
}

int shockSensor::getState() {
  if (!(_shockPin == 99))
  {
    shockSensor::readState();
    return _shockState;
  }
  return 1;
}

shockSensor s1(shockSensorPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int sState = s1.getState();
  if(sState == 0) {
    s1.showShock(shockDebounce);
  }
  
}