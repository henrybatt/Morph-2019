#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

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
        Motor motorB = Motor(PWM_1, DIR_1, BRK_1, 0);
        Motor motorC = Motor(PWM_2, DIR_2, BRK_2, 0);
        Motor motorD = Motor(PWM_3, DIR_3, BRK_3, 0);
};

#endif