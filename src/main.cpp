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
// #include <WiFi.h>
// #include <PubSubClient.h>


#define ONBOARD_LED 2

#define timeSeconds 2

// Control States
#define DIO_ON 1
#define DIO_OFF 0

// Control IO states
#define DIO_ENABLED DIO_ON
#define DIO_DISABLED DIO_OFF

#define shockTriggered DIO_OFF
#define shockIdle DIO_ON

// Scan rate
#define shockDebounce 5

// Sensor Pins 
#define knockSensorPin  32
#define shockSensorPin  33


// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;


class LED {
private:
  unsigned char _ledEnabled = DIO_DISABLED;
  uint8_t _ledPin;
  volatile byte _ledState = DIO_OFF;
  int flashCount = 0;
public:
  LED(uint8_t pin);
  void ledON();
  void ledOFF();
  void setLEDState(unsigned char state);
  int getLEDState();
  void ledFlash(int cycle, int debounce);
  ~LED();
};

/****
 * Init LED class, register the pin and set the mode
 * It also Enables LED system 
 * SET the LED to OFF
 ****/
LED::LED(uint8_t pin) {
  _ledPin = pin;
  pinMode(pin, OUTPUT);
  LED::ledOFF();
  _ledEnabled = DIO_ENABLED;
  Serial.printf("<SYSTEM_MAIN> LED OBJ init using PIN: %d\n", pin);
}

/****
 * Used to set the logical state of the LED
 ****/
void LED::setLEDState(unsigned char state) {
  _ledState = state;
  Serial.println("<SYSTEM_LED> Setting State");
}

/****
 * Returns the instaneous state of LED
 ****/
int LED::getLEDState() {
  Serial.println("<SYSTEM_LED> Returning State");
  return _ledState;
}

/****
 * Changes the state of the LED to OFF
 ****/
void LED::ledOFF() {
  digitalWrite(_ledPin, DIO_OFF);
  LED::setLEDState(DIO_OFF);
  Serial.println("<SYSTEM_LED> LED turned OFF");
}

/****
 * Changes the state of the LED to ON
 ****/
void LED::ledON() {
  digitalWrite(_ledPin, DIO_ON);
  LED::setLEDState(DIO_ON);
  Serial.println("<SYSTEM_LED> LED turned ON");
}

/****
 * !!PENDING!!
 * A method to internally flash the LED 
 ****/
void LED::ledFlash(int cycle = 3, int debouce = 500) {
  LED::ledOFF();
  for(int i = 0; i < cycle; i++) {
    LED::ledON();
    delay(debouce);
    LED::ledOFF();
    delay(debouce);
  }
  flashCount++;
  Serial.printf("<SYSTEM_LED> <%d> LED mode: FLASH, CYCLE: %d, DEBOUNCE: %d\n", flashCount, cycle, debouce);
}

/****
 * LED deconstructor
 ****/
LED::~LED() {
  Serial.println("<SYSTEM_MAIN> LED object deleted!!");
}

// --------- END of CLASS ------------------------------------

class shockSensor {
  private:
  unsigned char _shockEnabled = DIO_DISABLED;
  uint8_t _shockPin;
  volatile byte _shockState = DIO_OFF;     // ShockSensor is NC
  int shockCount =0;

  public:
  shockSensor(uint8_t pin);
  void shockInit();
  void readState();
  int getState();
  bool shockMonitor();
  void showShock(uint8_t mode);
};


/****
 * Shock Class Constructor
 ****/
shockSensor::shockSensor(uint8_t pin) {
  _shockPin = pin;
}

/****
 * Init Shock Sensor class
 * Enabled Shock Sensor system
 ****/
void shockSensor::shockInit() {
  pinMode(_shockPin, INPUT_PULLUP);
  _shockState = DIO_ENABLED;
  Serial.printf("<SYSTEM_SHOCK> Init successful using PIN: %d\n", _shockPin);
}

/****
 * Simple method to read Shock sensor state
 ****/
void shockSensor::readState() {
  _shockState = digitalRead(_shockPin);
  Serial.println("<SHOCK> Shock Sensor READ!!");
}

/****
 * Simple method to return shock sensor state
 ****/
int shockSensor::getState() {
  shockSensor::readState();
  if ( _shockState == shockTriggered)
    return DIO_ON;

  return DIO_OFF;
}

bool shockSensor::shockMonitor() {
  volatile byte shock = shockSensor::getState();
  if (shock == shockTriggered) {
    return DIO_ON;
  }

  return DIO_OFF;
}

/****
 * !!PENDING!! Internal call to show shock
 * still not sure if there is a need for this within shocksensor class
 ****/
void shockSensor::showShock(uint8_t mode) {
}

// --------- END of CLASS ------------------------------------

// An instance of LED class and pass the pin
LED l1(ONBOARD_LED);

// An instance of shockSensor class and pass the pin
shockSensor s1(shockSensorPin);
  
volatile bool shockState;


// Checks if motion was detected, sets LED HIGH and starts a timer
// void IRAM_ATTR detectsShock() {
//   Serial.println("Shock DETECTED!!!");
//   l1.ledON();
//   startTimer = true;
//   lastTrigger = millis();
// }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("<SETUP>");
  Serial.println('\n' + "** Fuck Neighbors, White Trash! **" + '\n');
  s1.shockInit();
  // attachInterrupt(digitalPinToInterrupt(shockSensorPin), detectsShock, RISING);
}

void loop() {
  Serial.println("<LOOP>");
  
  // now = millis();
  // // Turn off the LED after the number of seconds defined in the timeSeconds variable
  // if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
  //   Serial.println("Shock stopped...");
  //   l1.ledOFF();
  //   startTimer = false;
  // }
  
  if( !(s1.shockMonitor()) ) {
    l1.ledFlash(3, 250);
  }

  delay(500);
}