#include "eventLog.h"


bool sirenLastState = OFF;
bool gasLastState   = OFF;
bool tempLastState  = OFF;
bool ICLastState    = OFF;
bool SBLastState    = OFF;
int eventsIndex     = 0;
systemEvent_t arrayOfStoredEvents[EVENT_LOG_MAX_STORAGE];

void eventLogUpdate()
{
    bool currentState = sirenStateRead();
    eventLogElementStateUpdate( sirenLastState, currentState, "ALARM" );
    sirenLastState = currentState;

    currentState = gasDetectorStateRead();
    eventLogElementStateUpdate( gasLastState, currentState, "GAS_DET" );
    gasLastState = currentState;

    currentState = overTemperatureDetectorStateRead();
    eventLogElementStateUpdate( tempLastState, currentState, "OVER_TEMP" );
    tempLastState = currentState;

    currentState = incorrectCodeStateRead();
    eventLogElementStateUpdate( ICLastState, currentState, "LED_IC" );
    ICLastState = currentState;

    currentState = systemBlockedStateRead();
    eventLogElementStateUpdate( SBLastState ,currentState, "LED_SB" );
    SBLastState = currentState;
}

int eventLogNumberOfStoredEvents()
{
    return eventsIndex;
}

void eventLogRead( int index, char* str )
{
    str[0] = '\0';
    strcat( str, "Event = " );
    strcat( str, arrayOfStoredEvents[index].typeOfEvent );
    strcat( str, "\r\nDate and Time = " );
    strcat( str, ctime(&arrayOfStoredEvents[index].seconds) );
    strcat( str, "\r\n" );
}

void eventLogWrite( bool currentState, const char* elementName )
{
    char eventAndStateStr[EVENT_LOG_NAME_MAX_LENGTH] = "";

    strcat( eventAndStateStr, elementName );
    if ( currentState ) {
        strcat( eventAndStateStr, "_ON" );
    } else {
        strcat( eventAndStateStr, "_OFF" );
    }

    arrayOfStoredEvents[eventsIndex].seconds = time(NULL);
    strcpy( arrayOfStoredEvents[eventsIndex].typeOfEvent, eventAndStateStr );
    if ( eventsIndex < EVENT_LOG_MAX_STORAGE - 1 ) {
        eventsIndex++;
    } else {
        eventsIndex = 0;
    }

    pcSerialComStringWrite(eventAndStateStr);
    pcSerialComStringWrite("\r\n");

}

void eventLogElementStateUpdate( bool lastState,
                                 bool currentState,
                                 const char* elementName )
{
    if ( lastState != currentState ) {        
        eventLogWrite( currentState, elementName );       
    }
}

void commandShowStoredEvents()
{
    char str[EVENT_STR_LENGTH] = "";
    int i;
    for (i = 0; i < eventLogNumberOfStoredEvents(); i++) {
        eventLogRead( i, str );
        pcSerialComStringWrite( str );   
        pcSerialComStringWrite( "\r\n" );                    
    }
}
