#ifndef KEYPAD_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define KEYPAD_H

#include "mbed.h"
#include "arm_book_lib.h"

// Module: matrix_keypad ------------------------------

#ifndef MATRIX_KEYPAD_NUMBER_OF_ROWS
#define MATRIX_KEYPAD_NUMBER_OF_ROWS    4
#endif
#ifndef MATRIX_KEYPAD_NUMBER_OF_COLS
#define MATRIX_KEYPAD_NUMBER_OF_COLS    4
#endif
#ifndef DEBOUNCE_KEY_TIME_MS
#define DEBOUNCE_KEY_TIME_MS           40
#endif

// Module: matrix_keypad ------------------------------

typedef enum {
    MATRIX_KEYPAD_SCANNING,
    MATRIX_KEYPAD_DEBOUNCE,
    MATRIX_KEYPAD_KEY_HOLD_PRESSED
} matrixKeypadState_t;


// Module: matrix_keypad ------------------------------

void matrixKeypadInit( int updateTime_ms );
char matrixKeypadUpdate();
char matrixKeypadScan();
void matrixKeypadReset();

#endif

