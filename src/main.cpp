/*
  Arkham Labs
  Project: DhumDhum
  MCU: ESP32 - DevKit

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

#define timeSeconds 2


// Sensor Pins
#define knockSensorPin 32
#define shockSensorPin 33

volatile bool shockState;
int shockCount = 0;

// An instance of shockSensor class and pass the pin
shockSensor s1(shockSensorPin);

// An instance of LED class and pass the pin
LED l1(ONBOARD_LED);

void changeState()
{
  digitalWrite(ONBOARD_LED, !(digitalRead(ONBOARD_LED)));
}

void ledCallback() {
  l1.toggleLED();
}

void shockCallback() {
  s1.readState();
}




TickTwo timer1(shockCallback, 1000, 4);
TickTwo timer2(ledCallback, 600, 6);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("<SETUP>");
  Serial.println('\n' + "** Fuck Neighbors, White Trash! **" + '\n');

  s1.shockInit();
  l1.ledInit();

  pinMode(ONBOARD_LED, OUTPUT);

  timer1.start();
  timer2.start();
}

void loop()
{
  Serial.println("<LOOP>");

  timer1.update();
  timer2.update();

  if (s1.getState() == shockTriggered) {
    s1.shockCount++;
    Serial.printf("<Shock #%d>\n", shockCount);
    // timer2.interval(150);
  }
}