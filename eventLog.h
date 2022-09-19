#ifndef EVENTLOG_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define EVENTLOG_H

#include <string.h>
#include "mbed.h"
#include "arm_book_lib.h"
#include "timeDate.h"
#include "peripherals.h"
#include "pcSerial.h"
#include "code.h"

#ifndef EVENT_LOG_MAX_STORAGE
#define EVENT_LOG_MAX_STORAGE       100
#endif
#ifndef EVENT_HEAD_STR_LENGTH
#define EVENT_HEAD_STR_LENGTH         8
#endif
#ifndef EVENT_LOG_NAME_MAX_LENGTH
#define EVENT_LOG_NAME_MAX_LENGTH    13
#endif
#ifndef DATE_AND_TIME_STR_LENGTH
#define DATE_AND_TIME_STR_LENGTH     18
#endif
#ifndef CTIME_STR_LENGTH
#define CTIME_STR_LENGTH             25
#endif
#ifndef NEW_LINE_STR_LENGTH
#define NEW_LINE_STR_LENGTH           3
#endif
#ifndef EVENT_STR_LENGTH
#define EVENT_STR_LENGTH              EVENT_HEAD_STR_LENGTH + \
                                      EVENT_LOG_NAME_MAX_LENGTH + \
                                      DATE_AND_TIME_STR_LENGTH  + \
                                      CTIME_STR_LENGTH + \
                                      NEW_LINE_STR_LENGTH
#endif

// Module: event_log ----------------------------------

typedef struct systemEvent {
    time_t seconds;
    char typeOfEvent[EVENT_LOG_NAME_MAX_LENGTH];
} systemEvent_t;

// Module: event_log ----------------------------------

void commandShowStoredEvents();
void eventLogUpdate();
int eventLogNumberOfStoredEvents();
void eventLogRead( int index, char* str );
void eventLogWrite( bool currentState, const char* elementName );
void eventLogElementStateUpdate( bool lastState,
                                 bool currentState,
                                 const char* elementName );

#endif