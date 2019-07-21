#include <Arduino.h>
#include <Define.h>
#include <Common.h>
#include <PID.h>
#include <Timer.h>
#include <IMU.h>
#include <MotorController.h>
#include <Tssp.h>
#include <LightSensorArray.h>
#include <Camera.h>


PID idleHeadingPID(IDLE_HEADING_KP, IDLE_HEADING_KI, IDLE_HEADING_KD, IDLE_HEADING_MAX_CORRECTION);
PID headingPID(HEADING_KP, HEADING_KI, HEADING_KD, HEADING_MAX_CORRECTION);

PID goalTrackPID(GOAL_TRACK_KP, GOAL_TRACK_KI, GOAL_TRACK_KD, GOAL_TRACK_MAX_CORRECTION);

Timer attackLEDTimer(800000);
Timer defenceLEDTimer(400000);

bool ledOn = false;

IMU Compass;
MotorController Motor;
Tssp Tssps;
LightSensorArray LightArray;
Camera Cam;

DirSpeed movement;
LineInfo lineInfo(-1, 0, true);


void calculateLineAvoidance(){
    bool noLine = (LightArray.getLineAngle() == NO_LINE_ANGLE);
    double angle = noLine ? -1 : doubleMod(LightArray.getLineAngle()+ Compass.heading, 360);
    double size = LightArray.getLineSize();

    if (lineInfo.onField){
        if (!noLine){
            // Touching Line
            lineInfo.angle = angle;
            lineInfo.size = 1;
            // lineInfo.size = size;
            lineInfo.onField = false;
        }
    } else {
        // On line
        if (lineInfo.size == 3){
            if (!noLine){
                // Over line but touching
                lineInfo.angle = doubleMod(angle + 180, 360);
                lineInfo.size = 2;
                // lineInfo.size = 2 - size;
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
                    // lineInfo.size = size;

                } else {
                    lineInfo.angle = doubleMod(angle + 180, 360);
                    lineInfo.size = 2;
                    // lineInfo.size = 2 - size;
                }
            }

        }
    }
    if (!noLine){
        movement.direction = doubleMod(lineInfo.angle + 180 - Compass.heading, 360);
        if (lineInfo.size == 2){
            movement.speed = abs(movement.direction - lineInfo.angle) < 60 ? LINE_SPEED_SLOW : LINE_SPEED_FAST;
        } else if (lineInfo.size == 1 && abs(movement.direction - lineInfo.angle) < 60){
            movement.speed = 0;
        }
    } else {
        if (lineInfo.size == 3){
            movement.direction = doubleMod(lineInfo.angle + 180 - Compass.heading, 360);
            movement.speed = abs(movement.direction - lineInfo.angle) < 60 ? LINE_SPEED_SLOW : LINE_SPEED_FAST;
        }
    }   
    // Serial.printf("Line Angle: %f, Line Size: %f, Movement Direction: %f   \n  ", lineInfo.angle,lineInfo.size,movement.direction); 
}

void calculateOrbit(){
    double value = Tssps.getAngle() > 180 ? Tssps.getAngle() - 360 : Tssps.getAngle();
    double ballAngleDifference = findSign(value) * fmin(90, 0.4 * pow(MATH_E, 0.15 * smallestAngleBetween(Tssps.getAngle(), 0)));
    double strengthFactor = constrain(Tssps.getStrength() / BALL_CLOSE_STRENGTH, 0, 1);
    double distanceMultiplier = constrain((0.02 * strengthFactor * pow(MATH_E, 4.5 * strengthFactor)), 0, 1);
    double angleAddition = ballAngleDifference * distanceMultiplier;
    movement.direction =  Tssps.ballVisible ? mod(Tssps.getAngle() + angleAddition, 360) : -1;
    movement.speed = ORBIT_SLOW_SPEED + (double)(ORBIT_FAST_SPEED - ORBIT_SLOW_SPEED) * (1.0 - (double)abs(angleAddition) / 90.0);
    // Serial.printf("Tssp Angle: %i, Movement Direction %f \n",Tssps.getAngle(),movement.direction);
}

void stopLine(){
    bool noLine = (LightArray.getLineAngle() == NO_LINE_ANGLE);
    if (!noLine){
        movement.speed = 0;
    }
}

bool isAttack(){
    return true;
}

void attack(){
    Cam.goalTrack();
    calculateOrbit();
}

void defend(){
    calculateOrbit();
}

void calculateMovement(){
    if (isAttack()){
        attack();
    } else {
        defend();
    }

    calculateLineAvoidance();
    // stopLine();

    if (Cam.facingGoal){
        movement.correction = round(goalTrackPID.update(doubleMod(doubleMod(Compass.heading - Cam.attackAngle, 360) + 180, 360), 0));
    } else {
        movement.correction = round(headingPID.update(doubleMod(Compass.heading + 180, 360) - 180, 0));
    }

    if (!Tssps.ballVisible){
        if (lineInfo.angle == -1){
            movement.speed = 0;
        }
    }

}

void setup(){
    Compass.init();
    Motor.init();
    Tssps.init();
    LightArray.init();
    Cam.init();

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    digitalWrite(13, LOW);
}

void loop(){
    Compass.read();

    Tssps.read();

    LightArray.read();

    #if GOAL_TRACK
        Cam.calc(Compass.heading);
    #endif
    
    calculateMovement();

    Motor.Move(movement.direction, movement.correction, movement.speed);

    if (attackLEDTimer.timeHasPassed()){
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    }

} 
