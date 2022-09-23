#ifndef TIMEDATE_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TIMEDATE_H

char* dateAndTimeRead();
void dateAndTimeWrite( int year, int month, int day, 
                       int hour, int minute, int second );

#endif