#ifndef PCSERIAL_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define PCSERIAL_H

typedef enum {
    PC_SERIAL_COMMANDS,
    PC_SERIAL_GET_CODE,
    PC_SERIAL_SAVE_NEW_CODE,
} pcSerialComMode_t;

void pcSerialComInit();
char pcSerialComCharRead();
void pcSerialComStringWrite( const char* str );
void pcSerialComStringRead( char* str, int strLength );
void availableCommands();
void commandShowCurrentAlarmState();
void commandShowCurrentGasDetectorState();
void commandShowCurrentOverTemperatureDetectorState();
void commandShowCurrentTemperatureInCelsius();
void commandShowCurrentTemperatureInFahrenheit();
void commandSetDateAndTime();
void commandShowDateAndTime();

void pcSerialComCommandUpdate( char receivedChar );
bool pcSerialComCodeCompleteRead();
void pcSerialComCodeCompleteWrite( bool state );
void pcSerialComGetCodeUpdate( char receivedChar );
void pcSerialComSaveNewCodeUpdate( char receivedChar );
void commandEnterCodeSequence();
void commandEnterNewCode();

#endif