#include "code.h"

char codeSequence[CODE_NUMBER_OF_KEYS] = { '1', '8', '0', '5' };

void codeWrite( char* newCodeSequence )
{
    int i;
    for (i = 0; i < CODE_NUMBER_OF_KEYS; i++) {
        codeSequence[i] = newCodeSequence[i];
    }
}

bool codeMatch( char* codeToCompare )
{
    int i;
    for (i = 0; i < CODE_NUMBER_OF_KEYS; i++) {
        if ( codeSequence[i] != codeToCompare[i] ) {
            return false;
        }
    }
    return true;
}
