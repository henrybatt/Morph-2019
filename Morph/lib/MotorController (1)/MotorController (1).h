#ifndef MOTORCONTROLLER1_H
#define MOTORCONTROLLER1_H

#include <Motor.h>
#include <Common.h>

class MotorController
{
    public:
        MotorController();
        void moveDirection(double angle, double rotate, double speed);
        void speed(int speed);
    private:
        /* PWM , DIR, BRK, REV */
        double MOTOR_NUM = {0};

        Motor motorA = Motor(PWM_0, INONE_0, INTWO_0, 0);
        Motor motorB = Motor(PWM_1, INONE_1, INTWO_1, 0);
        Motor motorC = Motor(PWM_2, INONE_2, INTWO_2, 0);
        Motor motorD = Motor(PWM_3, INONE_3, INTWO_3, 0);
};

#endif