#ifndef CONTROL_h
#define CONTROL_h

#include <Arduino.h>

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


#endif