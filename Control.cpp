// File:  Motor.cpp

#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include <csignal>
#include "Motor.h"

Motor::Motor() {

    std::cout << "Initializing motors" << std::endl;

    // set up pins
    wiringPiSetupGpio();

    // digital output pins
    pinMode(ENABLE, OUTPUT);
    pinMode(M1_DIR, OUTPUT);
    pinMode(M2_DIR, OUTPUT);

    // pwm output pins
    pinMode(M1_PWM, PWM_OUTPUT);
    pinMode(M2_PWM, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(MAX_SPEED);
    pwmSetClock(PWM_CLOCK_SPEED);

    // setup direction
    digitalWrite(M1_DIR, LOW);
    digitalWrite(M2_DIR, LOW);

}

Motor::~Motor() {
    std::cout << "Shutting down motors..." << std::endl;
    stop();
}

void Motor::run() {
    pwmWrite(M1_PWM, pwmDuty(10));
    pwmWrite(M2_PWM, pwmDuty(10));
    digitalWrite(ENABLE, HIGH);
}

void Motor::stop() {
    digitalWrite(ENABLE, LOW);
    pwmWrite(M1_PWM, pwmDuty(0));
    pwmWrite(M2_PWM, pwmDuty(0));
}

int Motor::pwmDuty(int duty) {
    return int(MAX_SPEED*(duty/100.0));
}
