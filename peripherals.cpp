#include "peripherals.h"

DigitalIn Button1(D7);
DigitalIn Button2(D6);
DigitalIn Button3(D5);
DigitalIn Button4(D4);

// Module: A/D

AnalogIn AD(A0);

// Module: fire_alarm ---------------------------------

DigitalIn alarmTestButton(BUTTON1); 

// Module: gas_sensor ---------------------------------

DigitalIn mq2(PE_12);

// Module: siren --------------------------------------

DigitalOut sirenPin(PE_10);

// Module: strobe_light -------------------------------

DigitalOut strobeLight(LED1);

// Module: temperature_sensor -------------------------

AnalogIn lm35(A1);

// Module: fire_alarm ---------------------------------

bool gasDetected                  = OFF;
bool overTemperatureDetected      = OFF;
bool gasDetectorState             = OFF;
bool overTemperatureDetectorState = OFF;

// Module: siren --------------------------------------

bool sirenState = OFF;
int accumulatedTimeAlarm = 0;

// Module: strobe_light --------------------------------

bool strobeLightState = OFF;

// Module: temperature_sensor -------------------------

float lm35TemperatureC = 0.0;
float lm35ReadingsArray[LM35_NUMBER_OF_AVG_SAMPLES];
int lm35SampleIndex     = 0;

// Module: fire_alarm ---------------------------------

void fireAlarmInit()
{
    temperatureSensorInit();
    gasSensorInit();
    sirenInit();
    strobeLightInit();    

    alarmTestButton.mode(PullDown); 
}

bool gasDetectorStateRead()
{
    return gasDetectorState;
}

bool overTemperatureDetectorStateRead()
{
    return overTemperatureDetectorState;
}

bool gasDetectedRead()
{
    return gasDetected;
}

bool overTemperatureDetectedRead()
{
    return overTemperatureDetected;
}

void fireAlarmActivationUpdate()
{
    temperatureSensorUpdate();
    gasSensorUpdate();

    overTemperatureDetectorState = temperatureSensorReadCelsius() > 
                            TEMPERATURE_C_LIMIT_ALARM;

    if ( overTemperatureDetectorState ) {
        overTemperatureDetected = ON;
        sirenStateWrite(ON);
        strobeLightStateWrite(ON);
    }

    gasDetectorState = !gasSensorRead();

    if ( gasDetectorState ) {
        gasDetected = ON;
        sirenStateWrite(ON);
        strobeLightStateWrite(ON);
    }
    
    if ( alarmTestButton ) {
        overTemperatureDetected = ON;
        gasDetected = ON;
        sirenStateWrite(ON);
        strobeLightStateWrite(ON);
    }

}


void fireAlarmDeactivate()
{
    sirenStateWrite(OFF);
    strobeLightStateWrite(OFF);
    overTemperatureDetected = OFF;
    gasDetected      = OFF;    
}

int fireAlarmStrobeTime()
{
    if( gasDetectedRead() && overTemperatureDetectedRead() ) {
        return STROBE_TIME_GAS_AND_OVER_TEMP;
    } else if ( gasDetectedRead() ) {
        return STROBE_TIME_GAS;
    } else if ( overTemperatureDetectedRead() ) {
        return STROBE_TIME_OVER_TEMP;
    } else {
        return 0;
    }
}

// Module: gas_sensor ---------------------------------

void gasSensorInit()
{
}

void gasSensorUpdate()
{
}

bool gasSensorRead()
{
    return mq2;
}



// Module: siren --------------------------------------

void sirenInit()
{
    sirenPin = ON;
}

bool sirenStateRead()
{
    return sirenState;
}

void sirenStateWrite( bool state )
{
    sirenState = state;
}

void sirenUpdate( int strobeTime )
{
    static int accumulatedTimeAlarm = 0;
    accumulatedTimeAlarm = accumulatedTimeAlarm + SYSTEM_TIME_INCREMENT_MS;
    
    if( sirenState ) {
        if( accumulatedTimeAlarm >= strobeTime ) {
                accumulatedTimeAlarm = 0;
                sirenPin= !sirenPin;
        }
    } else {
        sirenPin = ON;
    }
}



// Module: strobe_light -------------------------

void strobeLightInit()
{
    strobeLight = OFF;
}

bool strobeLightStateRead()
{
    return strobeLightState;
}

void strobeLightStateWrite( bool state )
{
    strobeLightState = state;
}

void strobeLightUpdate( int strobeTime )
{
    static int accumulatedTimeAlarm = 0;
    accumulatedTimeAlarm = accumulatedTimeAlarm + SYSTEM_TIME_INCREMENT_MS;
    
    if( strobeLightState ) {
        if( accumulatedTimeAlarm >= strobeTime ) {
            accumulatedTimeAlarm = 0;
            strobeLight= !strobeLight;
        }
    } else {
        strobeLight = OFF;
    }
}

// Module: temperature_sensor -------------------------

void temperatureSensorInit()
{
    int i;
    
    for( i=0; i<LM35_NUMBER_OF_AVG_SAMPLES ; i++ ) {
        lm35ReadingsArray[i] = 0;
    }
}

void temperatureSensorUpdate()
{
    static int lm35SampleIndex = 0;
    float lm35ReadingsSum = 0.0;
    float lm35ReadingsAverage = 0.0;

    int i = 0;

    lm35ReadingsArray[lm35SampleIndex] = lm35.read();
       lm35SampleIndex++;
    if ( lm35SampleIndex >= LM35_NUMBER_OF_AVG_SAMPLES) {
        lm35SampleIndex = 0;
    }
    
   lm35ReadingsSum = 0.0;
    for (i = 0; i < LM35_NUMBER_OF_AVG_SAMPLES; i++) {
        lm35ReadingsSum = lm35ReadingsSum + lm35ReadingsArray[i];
    }
    lm35ReadingsAverage = lm35ReadingsSum / LM35_NUMBER_OF_AVG_SAMPLES;
       lm35TemperatureC = analogReadingScaledWithTheLM35Formula ( lm35ReadingsAverage );    
}


float temperatureSensorReadCelsius()
{
    return lm35TemperatureC;
}

float temperatureSensorReadFahrenheit()
{
    return celsiusToFahrenheit( lm35TemperatureC );
}

float celsiusToFahrenheit( float tempInCelsiusDegrees )
{
    return ( tempInCelsiusDegrees * 9.0 / 5.0 + 32.0 );
}

float analogReadingScaledWithTheLM35Formula( float analogReading )
{
    return ( analogReading * 3.3 / 0.01 );
}
