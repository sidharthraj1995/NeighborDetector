/* 
  Arkham Labs - ESP32
  Project: DhumDhum Detector
  
  Date: Oct 10, 2022
*/

#include <Arduino.h>


#define ONBOARD_LED 2


// Sensor Pins 
#define knockSensorPin  32
#define shockSensorPin  33

// Sensor states
bool knockState = 0;
bool shockState = 0;

// Output state
bool ledState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Define pin type 
  pinMode(knockSensorPin, INPUT);
  pinMode(shockSensorPin, INPUT);

  pinMode(ONBOARD_LED, OUTPUT);

  // Initial states
  shockState = digitalRead(shockSensorPin);
  digitalWrite(ONBOARD_LED, LOW);
}

void loop() {
  if(shockState == 0)
  {
    digitalWrite(ONBOARD_LED,LOW);
    for(int i=0; i<5; i++)
    {
        digitalWrite(ONBOARD_LED, HIGH);
        Serial.println("Sen1: Shock Detected!!");
        delay(150);
        digitalWrite(ONBOARD_LED, LOW);
        delay(150);
        if(i == 4)
        {
          shockState = 1; 
        }
      }
    }
    else
    {
      shockState = digitalRead(shockSensorPin);
      digitalWrite(ONBOARD_LED, HIGH);
    }
}