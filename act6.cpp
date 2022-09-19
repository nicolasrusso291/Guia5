#include "act6.h"

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