#ifndef USERINTERFACE_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define USERINTERFACE_H

// Module: user_interface -----------------------------

bool userInterfaceCodeCompleteRead();
void userInterfaceCodeCompleteWrite( bool state );
bool incorrectCodeStateRead();
void incorrectCodeStateWrite( bool state );
void incorrectCodeIndicatorUpdate();
bool systemBlockedStateRead();
void systemBlockedStateWrite( bool state );
void systemBlockedIndicatorUpdate();
void userInterfaceMatrixKeypadUpdate();
void userInterfaceInit();

#endif