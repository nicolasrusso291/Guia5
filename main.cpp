//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "act6.h"
#include "code.h"
#include "eventLog.h"
#include "keypad.h"
#include "pcSerial.h"
#include "peripherals.h"
#include "smart_home_system.h"
#include "timeDate.h"
#include "userInterface.h"


//=====[Main function, the program entry point after power on or reset]========

int main()
{
    smartHomeSystemInit();
    while (true) {
        smartHomeSystemUpdate();
    }
}

//=====[Implementations of public functions]===================================

