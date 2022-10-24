/*
  Arkham Labs
  Project: DhumDhum
  MCU: ESP32/ESP8266 - DevKit

  IOs
  - Shock Sensor: HW-513 #GPIO_32
  - LED: ONBOARD_LED #GPIO_2

  Detect footsteps of your annoying upstairs
  neighbors using an inexpensive Shock Sensor

  Date: Oct 10, 2022
*/

#include <Arduino.h>
#include <TickTwo.h>

#include <rtc_config.h>
#include <led.h>
#include <shockSensor.h>
// #include <WiFi.h>
// #include <PubSubClient.h>

#define ONBOARD_LED 2

// Sensor Pins
// #define knockSensorPin 32
#define shockSensorPin 14

volatile bool shockState;
int shockCount = 0;

void ledCallback();
void shockCallback();

// An instance of shockSensor class and pass the pin
shockSensor s1(shockSensorPin);

// An instance of LED class and pass the pin
LED l1(ONBOARD_LED);

TickTwo timer1(shockCallback, SCAN1);
TickTwo timer2(ledCallback, 150, 6);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  Serial.println("**************<SETUP>*************");
  Serial.println("**********************************");
  Serial.println("** Fuck ************* Neighbors **");
  Serial.println("**********************************");

  s1.shockInit();
  l1.ledInit();

  timer1.start();
  // timer2.start();
}

void loop()
{
  // Serial.println("<LOOP>");

  timer1.update();
  timer2.update();
}

void ledCallback()
{
  l1.toggleLED();
  // timer1.resume();
}

void shockCallback()
{
  s1.readState();
  if (s1.getState())      // If Shock Detected, show using LED
  {
    Serial.printf("<Shock #%d>\n", ++s1.shockCount);
    timer2.start();
  }
}
