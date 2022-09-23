#ifndef CODE_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define CODE_H

#define CODE_NUMBER_OF_KEYS   4

typedef enum{
    CODE_KEYPAD,
    CODE_PC_SERIAL,
} codeOrigin_t;

void codeWrite( char* newCodeSequence );
bool codeMatch( char* codeToCompare );

bool codeMatchFrom( codeOrigin_t codeOrigin );
void codeDeactivate();


#endif