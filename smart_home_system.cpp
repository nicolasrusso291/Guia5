#include "mbed.h"
#include "arm_book_lib.h"

#include "smart_home_system.h"

#include "act6.h"
#include "code.h"
#include "eventLog.h"
#include "keypad.h"
#include "pcSerial.h"
#include "peripherals.h"
#include "timeDate.h"
#include "userInterface.h"

extern DigitalOut strobeLight;
extern DigitalOut incorrectCodeLed;
extern DigitalOut systemBlockedLed;

extern pcSerialComMode_t pcSerialComMode;

void userInterfaceUpdate()
{
    userInterfaceMatrixKeypadUpdate();
    incorrectCodeIndicatorUpdate();
    systemBlockedIndicatorUpdate();
}

void newPcSerialComCommandUpdate( char receivedChar )
{
    if( receivedChar != '\0' ) {
        switch (receivedChar) {
            
            case '1': 
                ledInit();
                strobeLight = ON;
                ThisThread::sleep_for(500ms); 
                break;
            case '2': 
                ledInit();
                systemBlockedLed = ON; 
                ThisThread::sleep_for(500ms);
                break;
            case '3': 
                ledInit();
                incorrectCodeLed = ON; 
                ThisThread::sleep_for(500ms);
                break;
            default: 
                ledInit();
                matrixKeypadUpdate(); 
                break;
        }    
    } 
}

void newPcSerialComUpdate()
{
    char receivedChar = pcSerialComCharRead();
    if( receivedChar != '\0' ) {
        switch ( pcSerialComMode ) {
            case PC_SERIAL_COMMANDS:
                newPcSerialComCommandUpdate( receivedChar );
            break;
            default:
                pcSerialComMode = PC_SERIAL_COMMANDS;
            break;
        }
    }    
}


void pcSerialComUpdate()
{
    char receivedChar = pcSerialComCharRead();
    if( receivedChar != '\0' ) {
        switch ( pcSerialComMode ) {
            case PC_SERIAL_COMMANDS:
                pcSerialComCommandUpdate( receivedChar );
            break;

            case PC_SERIAL_GET_CODE:
                pcSerialComGetCodeUpdate( receivedChar );
            break;

            case PC_SERIAL_SAVE_NEW_CODE:
                pcSerialComSaveNewCodeUpdate( receivedChar );
            break;
            default:
                pcSerialComMode = PC_SERIAL_COMMANDS;
            break;
        }
    }    
}

void fireAlarmDeactivationUpdate()
{
    if ( sirenStateRead() ) {
        if ( codeMatchFrom(CODE_KEYPAD) ||
             codeMatchFrom(CODE_PC_SERIAL) ) {
            fireAlarmDeactivate();
        }
    }
}

void fireAlarmUpdate()
{
    fireAlarmActivationUpdate();
    fireAlarmDeactivationUpdate();
    sirenUpdate( fireAlarmStrobeTime() );
    strobeLightUpdate( fireAlarmStrobeTime() );
}

void smartHomeSystemInit()
{
    userInterfaceInit();
    //fireAlarmInit();
    pcSerialComInit();
}

void smartHomeSystemUpdate()
{
    //fireAlarmUpdate();    
    //userInterfaceUpdate();
    newUserInterfaceMatrixKeypadUpdate();    
    newPcSerialComUpdate();
    //eventLogUpdate();
    delay(SYSTEM_TIME_INCREMENT_MS);
}