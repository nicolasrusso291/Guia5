#ifndef CODE_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define CODE_H

#include "mbed.h"
#include "arm_book_lib.h"

#ifndef CODE_NUMBER_OF_KEYS
#define CODE_NUMBER_OF_KEYS   4
#endif

void codeWrite( char* newCodeSequence );
bool codeMatch( char* codeToCompare );

#endif