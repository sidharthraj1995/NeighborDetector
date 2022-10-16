/* 
  Arkham Labs
  Project: DhumDhum
  MCU: ESP32 - DevKit
  
  IOs
  - Shock Sensor: HW-513 #GPIO32
  - LED: ONBOARD_LED #GPIO2
  
  Detect footsteps of your annoying upstairs
  neighbors using an inexpensive Shock Sensor
  
  Date: Oct 10, 2022
*/



#include <Arduino.h>
// #include <WiFi.h>
// #include <PubSubClient.h>


#define ONBOARD_LED 2

// Shock sensor Trigger state
#define shockTriggered 0

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
  int _shockPin;
  int _ledPin;
  unsigned char _shockState = 1;     // ShockSensor is NC
  unsigned char _ledState = 0;

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
  Serial.printf("<INIT> Shock Sensor successfully registered on PIN: %d\n", pin1);

  pinMode(pin2, OUTPUT);
  shockSensor::ledOFF();
  _ledPin = pin2;
  Serial.printf("<INIT> Shock LED successfully registered on PIN: %d\n", pin2);
}

void shockSensor::ledOFF() {
  if (!(_ledPin == 99))
  {
    digitalWrite(_ledPin, LOW);
    _ledState = 0;
    Serial.println("<LED> LED_OFF!");
  }
}

void shockSensor::ledON() {
  if (!(_ledPin == 99))
  {
    digitalWrite(_ledPin, HIGH);
    _ledState = 1;
    Serial.println("<LED> LED_ON!");
  }
}

void shockSensor::showShock(int debounce) {
  if( !(_shockState == shockTriggered) )
  {
    shockSensor::ledOFF();
    for(int i=1; i<=debounce; i++)
    {
        shockSensor::ledON();
        Serial.println("<SHOW> Shock Detected!!");
        delay(150);
        shockSensor::ledOFF();
        delay(150);
        if(i == debounce)
        {
          _shockState = 1; 
        }
    }
  }
}

void shockSensor::readState() {
  Serial.println("<READ> Asked to READ state!");
  _shockState = digitalRead(_shockPin);
  delay(150);
  Serial.println("<READ> NEW state captured");
  _ledState = 0;
}

int shockSensor::getState() {
  Serial.println("<GET> Asked to GET state!");
  if (!(_shockPin == 99))
  {
    shockSensor::readState();
    Serial.println("<GET> RETURN Shock sensor latest state!");
    return _shockState;
  }
  return 1;
}



shockSensor s1(shockSensorPin, ONBOARD_LED);

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