#include "smart_home_system.h"

void userInterfaceUpdate()
{
    userInterfaceMatrixKeypadUpdate();
    incorrectCodeIndicatorUpdate();
    systemBlockedIndicatorUpdate();
}

void newPcSerialComCommandUpdate()
{
    char receivedChar = pcSerialComCharRead();
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
    //pcSerialComUpdate();
    //eventLogUpdate();
    delay(SYSTEM_TIME_INCREMENT_MS);
}