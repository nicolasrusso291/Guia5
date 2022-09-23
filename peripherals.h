#ifndef PERIPHERALS_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define PERIPHERALS_H

// Module: fire_alarm ---------------------------------

#ifndef SYSTEM_TIME_INCREMENT_MS
#define SYSTEM_TIME_INCREMENT_MS        10
#endif
#define TEMPERATURE_C_LIMIT_ALARM       50.0
#define STROBE_TIME_GAS                 1000
#define STROBE_TIME_OVER_TEMP           500
#define STROBE_TIME_GAS_AND_OVER_TEMP   100

// Module: temperature_sensor -------------------------

#define LM35_NUMBER_OF_AVG_SAMPLES    100

// Module: fire_alarm ---------------------------------

void fireAlarmInit();
bool gasDetectorStateRead();
bool overTemperatureDetectorStateRead();
bool gasDetectedRead();
bool overTemperatureDetectedRead();
void fireAlarmActivationUpdate();
void fireAlarmDeactivate();
int fireAlarmStrobeTime();


// Module: gas_sensor ---------------------------------

void gasSensorInit();
void gasSensorUpdate();
bool gasSensorRead();

// Module: siren --------------------------------------

void sirenInit();
bool sirenStateRead();
void sirenStateWrite( bool state );
void sirenUpdate( int strobeTime );

// Module: strobe_light --------------------------------------

void strobeLightInit();
bool strobeLightStateRead();
void strobeLightStateWrite( bool state );
void strobeLightUpdate( int strobeTime );

// Module: temperature_sensor -------------------------

void temperatureSensorInit();
void temperatureSensorUpdate();
float temperatureSensorReadCelsius();
float temperatureSensorReadFahrenheit();
float celsiusToFahrenheit( float tempInCelsiusDegrees );
float analogReadingScaledWithTheLM35Formula( float analogReading );

#endif