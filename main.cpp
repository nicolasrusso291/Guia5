//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
//#include "keypad.h"
#include "smart_home_system.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    smartHomeSystemInit();
    while (true) {
        smartHomeSystemUpdate();
    }
}

//=====[Implementations of public functions]===================================

