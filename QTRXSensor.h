// File:  QTRXSensor.h

#include <iostream>
#include <wiringPi.h>
#include <unistd.h>

const int NUM_SENSORS= 5;

class QTRXSensor {

    public:

        // constants
        
        // variables
        unsigned int values[NUM_SENSORS];
        static const int LED_ON_PIN = 10;

        // functions
        QTRXSensor();
        ~QTRXSensor();
        void emittersOn();
        void emittersOff();
        void readSensors();
        void calibrateSensors();
        void printSensorValues();
        int lineValue();

    private:

        // constants
        const unsigned int CHARGE_TIME = 500;   // us
        const unsigned int READING_TIMEOUT = 2000;    // us
        const unsigned int SLEEP_TIME = 500000;   // us
        const int SENSOR[NUM_SENSORS] = { 20, 21, 22, 23, 24 };
        const int SENSOR_WEIGHTS[NUM_SENSORS] = { 0, 25, 50, 75, 100 };

        // variables
        int calibratedMax[NUM_SENSORS] = { 1000, 1000, 1000, 1000, 1000 };
        int calibratedMin[NUM_SENSORS] = { 1000, 1000, 1000, 1000, 1000 };
        int lastValue = 0;
    
};

