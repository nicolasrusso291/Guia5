#ifndef SMARTHOME_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define SMARTHOME_H

#include "mbed.h"
#include "arm_book_lib.h"
#include "codeValid.h"
#include "eventLog.h"
#include "peripherals.h"
#include "act6.h"

#ifndef SYSTEM_TIME_INCREMENT_MS
#define SYSTEM_TIME_INCREMENT_MS   10
#endif

void userInterfaceUpdate();
void newPcSerialComCommandUpdate();
void pcSerialComUpdate();
void fireAlarmDeactivationUpdate();
void fireAlarmUpdate();
void smartHomeSystemInit();
void smartHomeSystemUpdate();

#endif
