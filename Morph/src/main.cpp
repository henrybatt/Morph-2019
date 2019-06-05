#include <Arduino.h>
#include <Common.h>
#include <PID.h>
#include <Timer.h>
#include <IMU.h>
#include <MotorController.h>
#include <Camera.h>
#include <tssp.h>
#include <LightSensorController.h>

PID idleHeadingPID(IDLE_HEADING_KP, IDLE_HEADING_KI, IDLE_HEADING_KD, IDLE_HEADING_MAX_CORRECTION);
PID headingPID(HEADING_KP, HEADING_KI, HEADING_KD, HEADING_MAX_CORRECTION);
Timer LEDTimer(500);

bool ledOn = false;

IMU Compass;
MotorController Motor;
Camera Camera;
Tssp Tssps;
LightSensorController LightSensors;
DirSpeed finalMovement;

void calculateOrbit() {
  double value = Tssps.getAngle() > 180 ? Tssps.getAngle() - 360 : Tssps.getAngle();
  double ballAngleDifference = findSign(value) * fmin(90, 0.4 * pow(MATH_E, 0.15 * smallestAngleBetween(Tssps.getAngle(), 0)));
  double strengthFactor = constrain(Tssps.getStrength() / BALL_CLOSE_STRENGTH, 0, 1);
  double distanceMultiplier = constrain((0.02 * strengthFactor * pow(MATH_E, 4.5 * strengthFactor)), 0, 1);
  double angleAddition = ballAngleDifference * distanceMultiplier;
  finalMovement.direction = Tssps.ballVisible ? doubleMod(Tssps.getAngle() + angleAddition, 360) : -1;
  finalMovement.speed = ORBIT_SLOW_SPEED + (double)(ORBIT_FAST_SPEED - ORBIT_SLOW_SPEED) * (1.0 - (double)abs(angleAddition) / 90.0); 
}

void calculateMovement() {
  double correction;
  calculateOrbit();
  if(Tssps.ballVisible) {
    correction = Compass.heading > 180 ? -headingPID.update(Compass.heading - 360, 0) : -headingPID.update(Compass.heading, 0);
  } else {
    correction = Compass.heading > 180 ? -idleHeadingPID.update(Compass.heading - 360, 0) : -idleHeadingPID.update(Compass.heading, 0);
    finalMovement.speed = 0;
  }
  Motor.Move(finalMovement.direction, correction, finalMovement.speed);
}

void setup() {
  Compass.init();
  Motor.Setup();
  Camera.init();
  Tssps.init();
  LightSensors.init();

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(13, LOW);
}

void loop() {
  Compass.read();

  Camera.read();

  Tssps.read();

  LightSensors.read();

  calculateMovement();

  if(LEDTimer.timeHasPassed()) {
    digitalWrite(13, ledOn);
    ledOn = !ledOn;
  }

}
  

