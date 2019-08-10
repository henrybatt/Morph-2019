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

#include <LineData.h>
#include <Coord.h>


PID headingPID(HEADING_KP, HEADING_KI, HEADING_KD, HEADING_MAX_CORRECTION);
PID goalTrackPID(GOAL_TRACK_KP, GOAL_TRACK_KI, GOAL_TRACK_KD, GOAL_TRACK_MAX_CORRECTION);
PID coordPID(TO_COORD_KP, TO_COORD_KI, TO_COORD_KD, TO_COORD_MAX_SPEED);

PID xPID(X_MOVEMENT_KP, X_MOVEMENT_KI, X_MOVEMENT_KD, X_MOVEMENT_MAX);
PID yPID(Y_MOVEMENT_KP, Y_MOVEMENT_KI, Y_MOVEMENT_KD, Y_MOVEMENT_MAX);

Timer attackLEDTimer(800000);
Timer defenceLEDTimer(400000);


bool ledOn = false;

IMU Compass;
MotorController Motor;
Tssp Tssps;
LightSensorArray LightArray;
Camera Cam;

DirSpeed movement;
LineData lineInfo(-1, 0, true);

Coord robotCoords;
Coord goalCoords = Coord(0, -FIELD_CM_WITH_GOAL); //Position of defending goal in cartesian

void calculatePosition(){
    // --- Calculate Robot Position --- //
    int angle = Cam.closestDistance() == Cam.yellow.cm ? Cam.yellow.angle : Cam.blue.angle;
    angle = mod(angle + Compass.heading, 360);
    double distance = Cam.closestDistance();

    // Decide if in attacking or defending side of field to determine what quadrant group were in. (Positive or negative y)
    double quadrant = ((ATTACK_GOAL_YELLOW && (Cam.closestDistance() == Cam.yellow.cm)) || (!ATTACK_GOAL_YELLOW && !(Cam.closestDistance() == Cam.yellow.cm)) ? 1 : -1);

    // Serial.print(Cam.yellow.angle);
    // Serial.print(" , ");
    // Serial.print(Cam.yellow.distance);
    // Serial.print(" , ");
    // Serial.println(Cam.yellow.cm);

    // Robot Position calculation. Polar > Cartesian
    robotCoords.x = constrain(distance * -sin(degreesToRadians(angle)), -(FIELD_WIDTH_CM / 2), (FIELD_WIDTH_CM / 2));
    robotCoords.y = FIELD_CM_WITH_GOAL * quadrant + distance * -cos(degreesToRadians(angle));
}

bool moveByDiff(Coord diff){
    if (diff.getMagnitude() < COORD_THRESHOLD_DISTANCE){
        //At coords, stop
        movement.direction = -1;
        movement.speed = 0;
        return true;
    } else {
        // Calculate direction towards coords
        movement.direction = mod(diff.getAngle() - Compass.heading, 360);
        movement.speed = abs(coordPID.update(diff.getMagnitude(), 0));
        return false;
    }
}

bool moveToCoord(Coord coords){
    // --- Find difference between desired and robots' coords and move into position --- //
    if (Cam.yellow.exist || Cam.blue.exist){
        // Movement can be calculated, move by the point difference between coords
        return moveByDiff(coords.subtract(robotCoords));
    } else {
        //Cannot calculate position, stop
        movement.direction = -1;
        movement.speed = 0;
        return false;
    }
}

bool isAttack(){
    return true;
}

void calculateLineAvoidance(){
    bool noLine = (LightArray.getLineAngle() == NO_LINE_ANGLE);
    double angle = noLine ? -1 : doubleMod(LightArray.getLineAngle()+ Compass.heading, 360);
    // double size = LightArray.getLineSize();

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
                if (smallestAngleBetween(lineInfo.angle, angle) <= 100){
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
    // Serial.printf("Light Angle: %f, Line Angle: %f, Line Size: %f, Movement Direction: %f   \n  ",LightArray.getLineAngle(),lineInfo.angle,lineInfo.size,movement.direction); 
}

void calculateOrbit(){
    double value = Tssps.getAngle() > 180 ? Tssps.getAngle() - 360 : Tssps.getAngle();
    double ballAngleDifference = findSign(value) * fmin(90, 0.4 * pow(MATH_E, 0.15 * smallestAngleBetween(Tssps.getAngle(), 0)));
    double strengthFactor = constrain(Tssps.getStrength() / BALL_CLOSE_STRENGTH, 0, 1);
    double distanceMultiplier = constrain((0.02 * strengthFactor * pow(MATH_E, 4.5 * strengthFactor)), 0, 1);
    double angleAddition = ballAngleDifference * distanceMultiplier;
    movement.direction =  Tssps.ballVisible ? mod(Tssps.getAngle() + angleAddition, 360) : -1;
    movement.speed = ORBIT_SLOW_SPEED + (double)(ORBIT_FAST_SPEED - ORBIT_SLOW_SPEED) * (1.0 - (double)abs(angleAddition) / 90.0);
    Serial.printf("Tssp Angle: %i, Movement Direction %f \n",Tssps.getAngle(),movement.direction);
}

void stopLine(){
    if (LightArray.getLineAngle() != NO_LINE_ANGLE){
        Serial.println("STOPPED");
        movement.speed = 0;
        delay(3000);
        calculateOrbit();
    }

}

void attack(){
    #if GOAL_TRACK
        Cam.goalTrack();
    #endif

    if (Tssps.ballVisible){
        // Cam.goalTrack();
        calculateOrbit();
    } else {
        //No ball, move to centre
        movement.speed = 0;
        // moveToCoord(Coord(NO_BALL_COORD_X,NO_BALL_COORD_Y));
    }

}

void defend(){

    if (Cam.defend.exist){
        if (Tssps.ballVisible){
            //Calculate Ball Position ?
            if (angleIsInside(360 - DEFEND_CAPTURE_ANGLE, DEFEND_CAPTURE_ANGLE, Tssps.getAngle()) && Tssps.getStrength() > DEFEND_SURGE_STRENGTH && robotCoords.y < DEFEND_SURGE_Y){
                // Ball near capture zone, orbit behind and surge forwards
                calculateOrbit();
                Serial.println("Surge");

            } else if (!angleIsInside(270, 90, Tssps.getAngle())){
                //Ball is behind robot
                calculateOrbit();
                Serial.print("Behind");

            } else{
                // Defend Goal
                double yMovement = yPID.update(Cam.defend.distance,DEFEND_DISTANCE);
                double xMovement = xPID.update(mod(Tssps.getAngle() + 180, 360) - 180, 0);

                movement.direction = mod(radiansToDegrees(atan2(xMovement, yMovement)), 360);
                movement.speed = sqrt(pow(xMovement,2) + pow(yMovement,2));
                Serial.println("Defend");
            }
        } else {
            // No ball, centre to goal
            moveToCoord(Coord(0, goalCoords.y + DEFEND_DISTANCE));
        }
    } else {
        if (Tssps.ballVisible){
            //No goal, become attacker
            calculateOrbit();
        } else {
            movement.direction = -1;
            movement.speed = 0;
        }
    }
    Cam.faceGoal = false;
}

void calculateMovement(){
    // if (isAttack()){
    //     attack();
    // } else {
    //     defend();
    // }
    calculateOrbit();

    calculateLineAvoidance();
    // stopLine();

    if (Cam.faceGoal){
        double goalAngle = doubleMod(Cam.attack.angle + Compass.heading, 360);
        movement.correction = round(goalTrackPID.update(doubleMod(doubleMod(Compass.heading - goalAngle, 360) + 180, 360) - 180, 0));
        // Serial.printf("Face: %i, Angle: %d, Atttack: %f, Correction: %f \n", Cam.faceGoal, Cam.attack.angle,goalAngle, movement.correction);
    } else {
        movement.correction = round(headingPID.update(doubleMod(Compass.heading + 180, 360) - 180, 0));
    }

    if (!Tssps.ballVisible){
        if(lineInfo.size == 0){
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

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop(){
    Compass.read();

    Tssps.read();

    LightArray.update();

    #if GOAL_TRACK
        Cam.update();
        calculatePosition();
    #endif

    calculateMovement();

    Motor.Move(movement.direction, movement.correction, movement.speed);

    // Serial.println(lineInfo.angle);
// 
    if (attackLEDTimer.timeHasPassed()){
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    }

} 

