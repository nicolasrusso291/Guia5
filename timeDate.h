#ifndef TIMEDATE_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TIMEDATE_H

#include "mbed.h"
#include "arm_book_lib.h"

// Module: date_and_time ------------------------------

char* dateAndTimeRead();
void dateAndTimeWrite( int year, int month, int day, 
                       int hour, int minute, int second );

#endif