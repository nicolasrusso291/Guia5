#ifndef SMARTHOME_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define SMARTHOME_H

#ifndef SYSTEM_TIME_INCREMENT_MS
#define SYSTEM_TIME_INCREMENT_MS   10
#endif

void userInterfaceUpdate();
void newPcSerialComCommandUpdate(char receivedChar);
void newPcSerialComUpdate();
void pcSerialComUpdate();
void fireAlarmDeactivationUpdate();
void fireAlarmUpdate();
void smartHomeSystemInit();
void smartHomeSystemUpdate();

#endif
