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
    char str[20]; 
    sprintf(str, "%f\n", AD.read());
    uartUsb.write(str, strlen(str));
}

void showButton(){
    char str[20]; 
    sprintf(str, "Boton1: %d\n", Button1.read());
    uartUsb.write(str, strlen(str));
    sprintf(str, "Boton2: %d\n", Button2.read());
    uartUsb.write(str, strlen(str));
    sprintf(str, "Boton3: %d\n", Button3.read());
    uartUsb.write(str, strlen(str));
    sprintf(str, "Boton4: %d\n", Button4.read());
    uartUsb.write(str, strlen(str));
}