#include <MotorController.h>
#include <Common.h>

MotorController::MotorController(){
}

MotorController::Speed(int speed){
    motorA.set(speed);
    motorB.set(speed);
    motorC.set(speed);
    motorD.set(speed);
}

MotorController::move(){
    
}