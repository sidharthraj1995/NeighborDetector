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

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;


// --------- START of CLASS ------------------------------------


// --------- END of CLASS ------------------------------------

volatile bool shockState;
int shockCount = 0;

void changeState()
{
  digitalWrite(ONBOARD_LED, !(digitalRead(ONBOARD_LED)));
}

// An instance of LED class and pass the pin
// LED l1(ONBOARD_LED);

// An instance of shockSensor class and pass the pin
shockSensor s1(shockSensorPin);


void sMonitor()
{
  if (!(s1.shockMonitor()))
  {
    // timer2.start();
  }
}

TickTwo timer1(sMonitor, 1000, 2);
TickTwo timer2(changeState, 250, 3);

// Checks if motion was detected, sets LED HIGH and starts a timer
// void IRAM_ATTR detectsShock() {
//   Serial.println("Shock DETECTED!!!");
//   l1.ledON();
//   startTimer = true;
//   lastTrigger = millis();
// }

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
  // attachInterrupt(digitalPinToInterrupt(shockSensorPin), detectsShock, RISING);
}

void loop()
{
  Serial.println("<LOOP>");

  // now = millis();
  // // Turn off the LED after the number of seconds defined in the timeSeconds variable
  // if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
  //   Serial.println("Shock stopped...");
  //   l1.ledOFF();
  //   startTimer = false;
  // }

  timer1.update();
  timer2.update();
}