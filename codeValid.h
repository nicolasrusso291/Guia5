#ifndef CODEVALID_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define CODEVALID_H

#include "userInterface.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "pcSerial.h"

typedef enum{
    CODE_KEYPAD,
    CODE_PC_SERIAL,
} codeOrigin_t;

bool codeMatchFrom( codeOrigin_t codeOrigin );
void codeDeactivate();

#endif