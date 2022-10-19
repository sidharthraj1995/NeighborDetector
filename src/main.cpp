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

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;


void changeState()
{
  digitalWrite(ONBOARD_LED, !(digitalRead(ONBOARD_LED)));
}

// An instance of LED class and pass the pin
// LED l1(ONBOARD_LED);

// An instance of shockSensor class and pass the pin
shockSensor s1(shockSensorPin);


TickTwo timer1(s1.readState, 1000, 4);
TickTwo timer2(changeState, 500, 3);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("<SETUP>");
  Serial.println('\n' + "** Fuck Neighbors, White Trash! **" + '\n');
  s1.shockInit();

  pinMode(ONBOARD_LED, OUTPUT);
  // l1.ledInit();

  timer1.start();
  timer2.start();
}

void loop()
{
  Serial.println("<LOOP>");

  timer1.update();
  timer2.update();

  if (!(s1.shockMonitor())) {
    s1.shockCount++;
    Serial.printf("<Shock #%d>\n", shockCount);
    // timer2.interval(150);
  }
}