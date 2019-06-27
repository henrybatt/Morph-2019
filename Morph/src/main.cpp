#include <Arduino.h>
#include <Common.h>
#include <PID.h>
#include <Timer.h>
#include <IMU.h>
#include <MotorController.h>
#include <Camera.h>
#include <Tssp.h>
#include <LightSensorArray.h>


PID idleHeadingPID(IDLE_HEADING_KP, IDLE_HEADING_KI, IDLE_HEADING_KD, IDLE_HEADING_MAX_CORRECTION);
PID headingPID(HEADING_KP, HEADING_KI, HEADING_KD, HEADING_MAX_CORRECTION);

// PID goalTrackPID(GOAL_TRACK_KP, GOAL_TRACK_KI, GOAL_TRACK_KD, GOAL_TRACK_MAX_CORRECTION);

Timer attackLEDTimer(800000);
Timer defenceLEDTimer(400000);

bool ledOn = false;

IMU Compass;
MotorController Motor;
Camera Cam;
Tssp Tssps;
LightSensorArray LightArray;
DirSpeed movement;
LineInfo lineInfo(-1, 0, true);

void calculateLineAvoidance(){
    bool noLine = (LightArray.getLineAngle() == NO_LINE_ANGLE);
    double angle = noLine ? -1 : doubleMod(LightArray.getLineAngle()+ Compass.heading, 360);
    if (lineInfo.onField){
        if (!noLine){
            // Touching Line
            lineInfo.angle = angle;
            lineInfo.size = 1;
            lineInfo.onField = false;
        }
    } else {
        // On line
        if (lineInfo.size == 3){
            if (!noLine){
                // Over line but touching
                lineInfo.angle = doubleMod(angle + 180, 360);
                lineInfo.size = 2;
            }
        }else{
            if (noLine){
                //No line but was on
                if (lineInfo.size <= 1){
                    //Was inside line
                    lineInfo.onField = true;
                    lineInfo.angle = -1;
                    lineInfo.size = 0;
                } else {
                    //Was outside line
                    lineInfo.size = 3;
                }
            } else {
                //On line still
                if (smallestAngleBetween(lineInfo.angle, angle) <= 90){
                    lineInfo.angle = angle;
                    lineInfo.size = 1;
                } else {
                    lineInfo.angle = doubleMod(angle + 180, 360);
                    lineInfo.size = 2;
                }
            }
        }
    }
    if (!noLine){
        movement.direction = doubleMod(lineInfo.angle + 180 - Compass.heading, 360);
        if (lineInfo.size == 2){
            movement.speed = abs(movement.direction - lineInfo.angle) < 60 ? LINE_SPEED_SLOW : LINE_SPEED_FAST;
        } else if (lineInfo.size == 1 && smallestAngleBetween(lineInfo.angle, movement.direction) < 60){
            movement.speed = 0;
        }
    } else {
        if (lineInfo.size == 3){
            movement.direction = doubleMod(lineInfo.angle + 180 - Compass.heading, 360);
            movement.speed = abs(movement.direction - lineInfo.angle) < 60 ? LINE_SPEED_SLOW : LINE_SPEED_FAST;
        }
    }
}

void calculateOrbit(){
    double value = Tssps.getAngle() > 180 ? Tssps.getAngle() - 360 : Tssps.getAngle();
    double ballAngleDifference = findSign(value) * fmin(90, 0.4 * pow(MATH_E, 0.15 * smallestAngleBetween(Tssps.getAngle(), 0)));
    double strengthFactor = constrain(Tssps.getStrength() / BALL_CLOSE_STRENGTH, 0, 1);
    double distanceMultiplier = constrain((0.02 * strengthFactor * pow(MATH_E, 4.5 * strengthFactor)), 0, 1);
    double angleAddition = ballAngleDifference * distanceMultiplier;
    movement.direction =  Tssps.ballVisible ? mod(Tssps.getAngle() + angleAddition, 360) : -1;
    movement.speed = ORBIT_SLOW_SPEED + (double)(ORBIT_FAST_SPEED - ORBIT_SLOW_SPEED) * (1.0 - (double)abs(angleAddition) / 90.0);
}

void calculateMovement(){

    // if (Cam.attack.facingGoal) {
    //     movement.correction = round(goalTrackPID.update(doubleMod(doubleMod(Compass.heading - Cam.attack.angle, 360) + 180, 360), 0));
    // } else {
    //     movement.correction = round(headingPID.update(doubleMod(Compass.heading + 180, 360)- 180, 0));
    // }

    calculateOrbit();

    calculateLineAvoidance();

    movement.correction = round(idleHeadingPID.update(doubleMod(Compass.heading + 180, 360) - 180, 0));

    if (!Tssps.ballVisible){
        if (lineInfo.angle == -1){
            movement.speed = 0;
        }
    }

    Motor.Move(movement.direction, movement.correction, movement.speed);
    // Motor.Move(0, movement.correction, 0);
}

void setup(){

    Compass.init();
    Motor.init();
    Cam.init();
    Tssps.init();
    LightArray.init();

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    digitalWrite(13, LOW);
}


void loop(){
    Compass.read();

    Cam.read();
    Cam.calc();

    Tssps.read();

    LightArray.read();

    calculateMovement();

    if (attackLEDTimer.timeHasPassed()){
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    }

} 