#ifndef CONTROL_h
#define CONTROL_h

#include <Arduino.h>

// Scan Rates
#define SCAN1 2     // Scans at 2
#define SCAN2 5     // Scans at 5
#define SCAN3 10    // Scans at 10


// Control States
#define DIO_ON 1    // True
#define DIO_OFF 0   // False

// Control IO states
#define DIO_ENABLED DIO_ON
#define DIO_DISABLED DIO_OFF

#define shockTriggered DIO_OFF
#define shockIdle DIO_ON

// Scan rate
#define shockDebounce 5


#endif