#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <MotorController.h>

void MotorController::init(){
    motorFrontLeft.Setup(MOTOR_FRONT_LEFT_ENA,MOTOR_FRONT_LEFT_IN1,MOTOR_FRONT_LEFT_IN2,MOTOR_FRONT_LEFT_REVERSED);
    motorBackLeft.Setup(MOTOR_BACK_LEFT_ENA,MOTOR_BACK_LEFT_IN1,MOTOR_BACK_LEFT_IN2,MOTOR_BACK_LEFT_REVERSED);
    motorBackRight.Setup(MOTOR_BACK_RIGHT_ENA,MOTOR_BACK_RIGHT_IN1,MOTOR_BACK_RIGHT_IN2,MOTOR_BACK_RIGHT_REVERSED);
    motorFrontRight.Setup(MOTOR_FRONT_RIGHT_ENA,MOTOR_FRONT_RIGHT_IN1,MOTOR_FRONT_RIGHT_IN2,MOTOR_FRONT_RIGHT_REVERSED);
}

void MotorController::Move(MoveData moveInfo){

     #if ACCELERATION
        Vector optimal = Vector(moveInfo.angle, MAX_ACCELERATION * moveInfo.speed / 255, false);
        Vector output = currentAcceleration + optimal;
        currentAcceleration = output * (1 - MAX_ACCELERATION);
        int angle = output.arg;
        int speed = output.mag * 255;
    #else 
        int angle = moveInfo.angle;
        int speed = moveInfo.speed;
    #endif


  int rotation = moveInfo.correction;

  if(speed!=0){
    double angRad = degreesToRadians(360-angle);

    double weights[4] = {
        cos(degreesToRadians(45+90)-angRad),
        cos(degreesToRadians(135+90)-angRad),
        cos(degreesToRadians(-45+90)-angRad),
        cos(degreesToRadians(-135+90)-angRad)

    };


    double maxVal = fmax(doubleAbs(weights[0]),fmax(doubleAbs(weights[1]),fmax(doubleAbs(weights[2]),doubleAbs(weights[3]))));

    double power = speed/maxVal;

    for(int i = 0; i < 4; i++){
      weights[i] = round(weights[i]*power)+rotation;
    }

    maxVal = fmax(doubleAbs(weights[0]),fmax(doubleAbs(weights[1]),fmax(doubleAbs(weights[2]),doubleAbs(weights[3]))));

    double changeFactor = speed/maxVal;

    for(int i = 0; i < 4; i++){
      weights[i] = round(weights[i]*changeFactor);
    }

      motorFrontRight.Move(weights[1]);
      motorFrontLeft.Move(weights[3]);
      motorBackRight.Move(weights[0]);
      motorBackLeft.Move(weights[2]);

    }
  else{
    rotation = constrain(rotation, -255, 255);
    motorFrontRight.Move(rotation);
    motorFrontLeft.Move(rotation);
    motorBackRight.Move(rotation);
    motorBackLeft.Move(rotation);
  }
}

void MotorController::Turn(int speed){
  motorFrontLeft.Move(speed);
  motorFrontRight.Move(speed);
  motorBackLeft.Move(speed);
  motorBackRight.Move(speed);
}

void MotorController::Brake(){
  motorFrontLeft.Move(0);
  motorFrontRight.Move(0);
  motorBackLeft.Move(0);
  motorBackRight.Move(0);
}
