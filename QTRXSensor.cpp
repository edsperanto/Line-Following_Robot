// File:  QTRXSensor.cpp

#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include <csignal>
#include "QTRXSensor.h"

QTRXSensor::QTRXSensor() {
    std::cout << "Initializing" << std::endl;
    wiringPiSetupGpio();
    pinMode(LED_ON_PIN, OUTPUT);
}

QTRXSensor::~QTRXSensor() {
    for(int pin = 0; pin < NUM_SENSORS; pin++) {
        pinMode(SENSOR[pin], OUTPUT);
        digitalWrite(SENSOR[pin], LOW);
    }
    emittersOff();
}

void QTRXSensor::emittersOn() {
    digitalWrite(LED_ON_PIN, HIGH);
    delayMicroseconds(20);
}

void QTRXSensor::emittersOff() {
    digitalWrite(LED_ON_PIN, LOW);
    delayMicroseconds(20);
}

void QTRXSensor::readSensors() {

    // reset values
    for(int i = 0; i < NUM_SENSORS; i++) {
        values[i] = READING_TIMEOUT;
    }

    // charge capacitors
    for(int pin = 0; pin < NUM_SENSORS; pin++) {
        pinMode(SENSOR[pin], OUTPUT);
        pullUpDnControl(SENSOR[pin], PUD_OFF);
        digitalWrite(SENSOR[pin], HIGH);
    }
    delayMicroseconds(CHARGE_TIME);

    // read values
    for(int pin = 0; pin < NUM_SENSORS; pin++) {
        pinMode(SENSOR[pin], INPUT);
    }
    unsigned int startTime = micros();
    while(micros() - startTime < READING_TIMEOUT) {
        unsigned int time = micros() - startTime;
        for(int pin = 0; pin < NUM_SENSORS; pin++) {
            if(digitalRead(SENSOR[pin]) == 0 && time < values[pin]) {
                values[pin] = micros() - startTime;
                break;
            }
        }
    }

}

void QTRXSensor::calibrateSensors() {

    const int NUM_READS = 10;
    const double READ_DELAY = 100000;  // 0.1 seconds

    std::cout << "Calibrating Sensors" << std::endl;
    for(int i = 0; i < NUM_READS; i++) {
        readSensors();
        for(int sensor = 0; sensor < NUM_SENSORS; sensor++) {
            if(values[sensor] < calibratedMin[sensor])
                calibratedMin[sensor] = values[sensor];
            if(values[sensor] > calibratedMax[sensor])
                calibratedMax[sensor] = values[sensor];
        }
        usleep(SLEEP_TIME);
    }

    std::cout << "Calibrated Min: ";
    for(int i = NUM_SENSORS-1; i >= 0; i--) {
        std::cout << calibratedMin[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Calibrated Max: ";
    for(int i = NUM_SENSORS-1; i >= 0; i--) {
        std::cout << calibratedMax[i] << " ";
    }
    std::cout << std::endl;

}

void QTRXSensor::printSensorValues() {
    std::cout << values[4] << " ";
    std::cout << values[3] << " ";
    std::cout << values[2] << " ";
    std::cout << values[1] << " ";
    std::cout << values[0] << " ";
    std::cout << std::endl;
}

int QTRXSensor::lineValue() {
    int distFromMin, range;
    lastValue = 0;
    readSensors();
    for(int i = 0; i < NUM_SENSORS; i++) {
        distFromMin = values[i] - calibratedMin[i];
        range = calibratedMax[i] - calibratedMin[i];
        lastValue += (int)((float)distFromMin/(float)range*SENSOR_WEIGHTS[i]);
    }
    return lastValue;
}
