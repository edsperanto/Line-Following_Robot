// File:  Motor.h

#include <iostream>
#include <wiringPi.h>
#include <unistd.h>

class Motor {

    public:

        // constants
        // variables

        // functions
        Motor();
        ~Motor();
        void run();
        void stop();

    private:

        // constants
        const int ENABLE = 26;
        const int M1_PWM = 18;
        const int M1_DIR = 12;
        const int M2_PWM = 13;
        const int M2_DIR = 19;
        const int MAX_SPEED = 1000;
        const int PWM_CLOCK_SPEED = 19;

        // variables

        // functions
        int pwmDuty(int duty);
    
};

