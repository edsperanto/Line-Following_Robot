// File:  main.cpp
// Run: sudo ./main

#include <iostream>
#include <csignal>  //Handles the keyboard Interrupt
#include <unistd.h>
#include "QTRXSensor.h"
#include "Motor.h"

// Global flag used to exit from the main loop
bool RUNNING = true;
const unsigned int SLEEP_TIME = 500000;   // 0.5 second

// Callback handler if CTRL-C signal is detected
void my_handler(int s) {
    std::cout << "Detected CTRL-C signal no. " << s << std::endl;
    RUNNING = false;
    delay(500);
    std::cout << "Program ended ...\n";
}

int main() {

    std::signal(SIGINT, my_handler); // Handle Ctrl-C
    QTRXSensor sensor = QTRXSensor();
    Motor motor = Motor();
    sensor.emittersOn();
    sensor.calibrateSensors();

    while(RUNNING) {
        sensor.readSensors();
        sensor.printSensorValues();
        std::cout << sensor.lineValue() << std::endl;
        motor.run();
    }

    sensor.emittersOff();
    motor.stop();
    
}
