#include "mbed.h"
#include "arm_book_lib.h"
#include <string.h>

#include "act6.h"

#include "code.h"
#include "eventLog.h"
#include "keypad.h"
#include "pcSerial.h"
#include "peripherals.h"
#include "smart_home_system.h"
#include "timeDate.h"
#include "userInterface.h"

extern UnbufferedSerial uartUsb;
extern DigitalIn Button1;
extern DigitalIn Button2;
extern DigitalIn Button3;
extern DigitalIn Button4;

extern AnalogIn AD;

extern DigitalOut strobeLight;
extern DigitalOut incorrectCodeLed;
extern DigitalOut systemBlockedLed;

extern pcSerialComMode_t pcSerialComMode;

void newAvailableCommands()
{
    pcSerialComStringWrite( "Available commands:\r\n" );
    pcSerialComStringWrite( "Press '1' to activate LED1\r\n" );
    pcSerialComStringWrite( "Press '2' to activate LED2\r\n" );
    pcSerialComStringWrite( "Press '3' to activate LED3\r\n" );
    pcSerialComStringWrite( "Press '4' to show A/D value\r\n" );
    pcSerialComStringWrite( "Press other key to deactivate LEDs\r\n" );
    pcSerialComStringWrite( "\r\n" );
}

void newPcSerialComInit()
{
    newAvailableCommands();
}

void newUserInterfaceMatrixKeypadUpdate()
{
    char keyReleased = matrixKeypadUpdate();

    if( keyReleased != '\0' ) {
        newPcSerialComCommandUpdate( keyReleased );
        
    }
}

void ledInit(){
    strobeLight = OFF;
    systemBlockedLed = OFF; 
    incorrectCodeLed = OFF;

}

void showAD(){
    char str[50]; 
    sprintf(str, "Potentiometer value: %f\n", AD.read());
    uartUsb.write(str, strlen(str));
}

void showButton(){
    char str[20]; 
    int buttonPressed = 0;
    
    if (Button1.read() == ON){
        buttonPressed = 1;
    } else if (Button2.read() == ON){
        buttonPressed = 2;
    } else if (Button3.read() == ON){
        buttonPressed = 3;
    } else if (Button4.read() == ON){
        buttonPressed = 4;
    }
    if (buttonPressed){
        sprintf(str, "Button %d pressed\n", buttonPressed );
        uartUsb.write(str, strlen(str));
    }
}