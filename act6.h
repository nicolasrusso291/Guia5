#ifndef ACT6_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define ACT6_H


#include "mbed.h"
#include "keypad.h"
#include "pcSerial.h"
#include "userInterface.h"
#include "peripherals.h"

void newUserInterfaceMatrixKeypadUpdate();

// Mostrar A/D, teclado matricial y pulsador

void ledInit();
void showAD();
void showTM();
void showButton();

#endif