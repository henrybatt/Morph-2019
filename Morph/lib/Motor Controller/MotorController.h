#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>
#include <Motors.h>
#include <Common.h>
#include <MoveData.h>

class MotorController{
public:
  double vector1, vector2, off;
  Motor motorFrontLeft;
  Motor motorFrontRight;
  Motor motorBackLeft;
  Motor motorBackRight;
  void init();
  void Move(MoveData moveInfo);
  void Turn(int speed);
  void Brake();
  int weights [4] = {0, 0, 0, 0};

};


#endif
