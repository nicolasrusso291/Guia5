#ifndef KEYPAD_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define KEYPAD_H

void matrixKeypadInit( int updateTime_ms );
char matrixKeypadUpdate();
char matrixKeypadScan();
void matrixKeypadReset();

#endif

