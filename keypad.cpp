#include "keypad.h"

// Module: matrix_keypad ------------------------------

DigitalOut keypadRowPins[MATRIX_KEYPAD_NUMBER_OF_ROWS] = {PB_3, PB_5, PC_7, PA_15};
DigitalIn keypadColPins[MATRIX_KEYPAD_NUMBER_OF_COLS]  = {PB_12, PB_13, PB_15, PC_6};

// Module: matrix_keypad ------------------------------

matrixKeypadState_t matrixKeypadState;
int timeIncrement_ms = 0;
int accumulatedDebounceMatrixKeypadTime = 0;
char matrixKeypadLastKeyPressed = '\0';

// Module: matrix_keypad ------------------------------

void matrixKeypadInit( int updateTime_ms )
{
    timeIncrement_ms = updateTime_ms;
    matrixKeypadState = MATRIX_KEYPAD_SCANNING;
    int pinIndex = 0;
    for( pinIndex=0; pinIndex<MATRIX_KEYPAD_NUMBER_OF_COLS; pinIndex++ ) {
        (keypadColPins[pinIndex]).mode(PullUp);
    }
}
char matrixKeypadScan()
{
    int row = 0;
    int col = 0;
    int i = 0; 

    char matrixKeypadIndexToCharArray[] = {
        '1', '2', '3', 'A',
        '4', '5', '6', 'B',
        '7', '8', '9', 'C',
        '*', '0', '#', 'D',
    };

    for( row=0; row<MATRIX_KEYPAD_NUMBER_OF_ROWS; row++ ) {

        for( i=0; i<MATRIX_KEYPAD_NUMBER_OF_ROWS; i++ ) {
            keypadRowPins[i] = ON;
        }

        keypadRowPins[row] = OFF;

        for( col=0; col<MATRIX_KEYPAD_NUMBER_OF_COLS; col++ ) {
            if( keypadColPins[col] == OFF ) {
                return matrixKeypadIndexToCharArray[
                    row*MATRIX_KEYPAD_NUMBER_OF_ROWS + col];
            }
        }
    }
    return '\0';
}

void matrixKeypadReset()
{
    matrixKeypadState = MATRIX_KEYPAD_SCANNING;
}

char matrixKeypadUpdate(){
    char keyDetected = '\0';
    char keyReleased = '\0';

    switch( matrixKeypadState ) {

    case MATRIX_KEYPAD_SCANNING:
        keyDetected = matrixKeypadScan();
        if( keyDetected != '\0' ) {
            matrixKeypadLastKeyPressed = keyDetected;
            accumulatedDebounceMatrixKeypadTime = 0;
            matrixKeypadState = MATRIX_KEYPAD_DEBOUNCE;
            char str[5] = "";
            sprintf ( str, "%c\n",
                    matrixKeypadLastKeyPressed);
            //pcSerialComStringWrite(str);
            //showAD();
            //showButton();
        }
        break;

    case MATRIX_KEYPAD_DEBOUNCE:
        if( accumulatedDebounceMatrixKeypadTime >=
            DEBOUNCE_KEY_TIME_MS ) {
            keyDetected = matrixKeypadScan();
            if( keyDetected == matrixKeypadLastKeyPressed ) {
                matrixKeypadState = MATRIX_KEYPAD_KEY_HOLD_PRESSED;
            } else {
                matrixKeypadState = MATRIX_KEYPAD_SCANNING;
            }
        }
        accumulatedDebounceMatrixKeypadTime =
            accumulatedDebounceMatrixKeypadTime + timeIncrement_ms;
        break;

    case MATRIX_KEYPAD_KEY_HOLD_PRESSED:
        keyDetected = matrixKeypadScan();
        if( keyDetected != matrixKeypadLastKeyPressed ) {
            if( keyDetected == '\0' ) {
                keyReleased = matrixKeypadLastKeyPressed;
            }
            matrixKeypadState = MATRIX_KEYPAD_SCANNING;
        }
        break;

    default:
        matrixKeypadReset();
        break;
    }
    return keyReleased;
}

