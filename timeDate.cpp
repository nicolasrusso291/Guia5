#include "mbed.h"
#include "arm_book_lib.h"

#include "timeDate.h"

#include "act6.h"
#include "code.h"
#include "eventLog.h"
#include "keypad.h"
#include "pcSerial.h"
#include "peripherals.h"
#include "userInterface.h"


// Module: date_and_time ------------------------------

char* dateAndTimeRead()
{
    time_t epochSeconds;
    epochSeconds = time(NULL);
    return ctime(&epochSeconds);    
}

void dateAndTimeWrite( int year, int month, int day, 
                       int hour, int minute, int second )
{
    struct tm rtcTime;

    rtcTime.tm_year = year - 1900;
    rtcTime.tm_mon  = month - 1;
    rtcTime.tm_mday = day;
    rtcTime.tm_hour = hour;
    rtcTime.tm_min  = minute;
    rtcTime.tm_sec  = second;

    rtcTime.tm_isdst = -1;

    set_time( mktime( &rtcTime ) );
}