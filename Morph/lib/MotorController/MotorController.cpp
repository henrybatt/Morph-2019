#include <MotorController.h>

MotorController::MotorController(){
}

void MotorController::speed(int speed){
    motorA.set(speed);
    motorB.set(speed);
    motorC.set(speed);
    motorD.set(speed);
}

void MotorController::moveDirection(double angle, double rotate, double speed) {
    if(speed != 0) {
        double ratio[MOTOR_NUM] = {
            cos(DEGREES_TO_RADIANS*(MOTOR_ANGLE_0 + 90 - angle)),
            cos(DEGREES_TO_RADIANS*(MOTOR_ANGLE_1 + 90 - angle)),
            cos(DEGREES_TO_RADIANS*(MOTOR_ANGLE_2 + 90 - angle))
        };
        double highestRatio = updateMax(updateMax(abs(ratio[0]), abs(ratio[1])), ratio[2]);
        double ratioMulti = speed / highestRatio;
        double tempValue[MOTOR_NUM] = {
            ((ratio[0] * ratioMulti) + rotate) * MOTOR_0_SCALE,
            ((ratio[1] * ratioMulti) + rotate) * MOTOR_1_SCALE,
            ((ratio[2] * ratioMulti) + rotate) * MOTOR_2_SCALE
        };
        double max = updateMax(updateMax(abs(tempValue[0]), abs(tempValue[1])), tempValue[2]);
        for(int i = 0; i < MOTOR_NUM; i++) {
            tempValue[i] *= speed;
            tempValue[i] /= max;
        }
        for(int i = 0; i < MOTOR_NUM; i++) {
            values[i] = tempValue[i];
        }
    } else {
        for(int i = 0; i < MOTOR_NUM; i++) {
            values[i] = rotate;
        }
    }
    for (int i = 0; i < MOTOR_NUM; i++) {
        motor[i].move(-values[i]);
    }
    currentAngle = angle;
    currentRotate = rotate;
    currentSpeed = speed;
}
}