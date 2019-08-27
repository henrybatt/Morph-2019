#include <Arduino.h>
#include <Define.h>
#include <Common.h>
#include <PID.h>
#include <Timer.h>
#include <IMU.h>
#include <MotorController.h>
#include <TSSP.h>
#include <LightArrayVector.h>
#include <LightSensorArray.h>
#include <Camera.h>
#include <Coord.h>

// PID's for correction and movement around field
PID headingPID(HEADING_KP, HEADING_KI, HEADING_KD, HEADING_MAX_CORRECTION);
PID attackGoalTrackPID(ATTACK_GOAL_TRACK_KP, ATTACK_GOAL_TRACK_KI, ATTACK_GOAL_TRACK_KD, ATTACK_GOAL_TRACK_MAX_CORRECTION);
PID defendGoalTrackPID(DEFEND_GOAL_TRACK_KP, DEFEND_GOAL_TRACK_KI, DEFEND_GOAL_TRACK_KD, DEFEND_GOAL_TRACK_MAX_CORRECTION);


PID coordPID(TO_COORD_KP, TO_COORD_KI, TO_COORD_KD, TO_COORD_MAX_SPEED);

PID xPID(X_MOVEMENT_KP, X_MOVEMENT_KI, X_MOVEMENT_KD, X_MOVEMENT_MAX);
PID yPID(Y_MOVEMENT_KP, Y_MOVEMENT_KI, Y_MOVEMENT_KD, Y_MOVEMENT_MAX);


// Timer Classes for different robot states 
Timer attackLEDTimer(800000);
Timer defenceLEDTimer(400000);

bool ledOn = false;

IMU Compass;
MotorController Motor;
TSSP Tssps;
LightArrayVector LightVector;
LightSensorArray LightArray;
Camera Cam;

// Structs of robot data
BallData ballInfo;
LineData lineInfo;
MoveData moveInfo;

// Robot Mode
Mode playMode = Mode::undecided;
Mode defaultMode;


void centre(int idleDist){
    // --- Centre to goal, idleDist away --- //

    if (Cam.defend.exist){
        double goalAngle = doubleMod(Cam.defend.angle + Compass.heading, 360);
        double xmoveInfo = -xPID.update(Cam.defend.distance * sin(degreesToRadians(goalAngle)), 0);
        double ymoveInfo = -yPID.update(Cam.defend.distance * cos(degreesToRadians(goalAngle)), idleDist);
        moveInfo.angle = doubleMod(radiansToDegrees(atan2(xmoveInfo, ymoveInfo)) - Compass.heading + 180, 360);
        moveInfo.speed = sqrt(pow(xmoveInfo,2) + pow(ymoveInfo,2));
    }
}


void calculateOrbit(){
    // --- Determine angle and speed to orbit around ball --- //
    moveInfo.angle = doubleMod(ballInfo.angle + Tssps.calcAngleAddition(), 360); // Orbit Angle

    //If ball infront of capture zone, surge forwards fast, else move at a modular speed
     if (ballInfo.strength > ATTACK_SURGE_STRENGTH && angleIsInside(360 - ATTACK_CAPTURE_ANGLE, ATTACK_CAPTURE_ANGLE, ballInfo.angle)){ 
        moveInfo.speed = ORBIT_FAST_SPEED;
    } else {
        moveInfo.speed = ORBIT_SLOW_SPEED + (double)(ORBIT_FAST_SPEED - ORBIT_SLOW_SPEED) * (1.0 - abs(Tssps.angleAddition) / (double)90.0);
    }
    
}


void calculateAttackMovement(){
    // --- Calculate attacking movement --- //

    // Calculate Ball State and Movement
    if (ballInfo.exist){
        calculateOrbit(); // Calculate Movement towards ball.

    } else { // No ball visible, if defending goal visible sit in-line
        if (Cam.defend.exist){
            // No ball visible, move to idle spot.
            centre(ATTACK_IDLE_DISTANCE);
        } else {
            // No ball or goal visible, stop
            moveInfo.angle = -1;
            moveInfo.speed = 0;

        }
    }

    
}


void calculateDefenseMovement(){
    // --- Calculate direction to move to intercept ball --- //

    if (Cam.defend.exist){
        if (ballInfo.exist){
            if (angleIsInside(360 - DEFEND_CAPTURE_ANGLE, DEFEND_CAPTURE_ANGLE, ballInfo.angle) && ballInfo.strength > DEFEND_SURGE_STRENGTH && Cam.defend.distance < DEFEND_SURGE_DISTANCE){
                // Ball infront of robot, surge forwards
                calculateOrbit();
                Cam.defend.face = false; // Stop correcting to goal

            } else if (!angleIsInside(270, 90, ballInfo.angle)){
                // Ball behind robot
                calculateOrbit();

            } else {
                // Defend Goal
                double xmoveInfo = -xPID.update(mod(ballInfo.angle + 180, 360) - 180, 0);
                double ymoveInfo = yPID.update(Cam.defend.distance, DEFEND_DISTANCE);
                moveInfo.angle = mod(radiansToDegrees(atan2(xmoveInfo, ymoveInfo)), 360);
                moveInfo.speed = sqrt(pow(xmoveInfo, 2) + pow(ymoveInfo, 2));
            }

        } else {
            // No ball, centre to goal
            centre(DEFEND_DISTANCE);
        }   

    } else {
        if (ballInfo.exist){
            // No goal, become attacker
            calculateOrbit();
            Cam.defend.face = false; // Stop correcting to goal

        } else {
            // No goal or ball, stop in place
            moveInfo.angle = -1;
            moveInfo.speed = 0;
            Cam.defend.face = false; // Stop correcting to goal
        }
    }

}


void calculateCorrection(){
    //Correction state. Either Goal or Compass

    if (Cam.attack.face && playMode == Mode::attack){ // Correct to attack goal
        double goalAngle = doubleMod(Cam.attack.angle + Compass.heading, 360);
            moveInfo.correction = round(attackGoalTrackPID.update(doubleMod(doubleMod(Compass.heading - goalAngle, 360) + 180, 360) - 180, 0));

    } else if (Cam.defend.face && playMode == Mode::defend){ // Correct to defend goal
            double goalAngle = doubleMod(Cam.defend.angle + Compass.heading, 360);
        moveInfo.correction = round(defendGoalTrackPID.update(doubleMod(doubleMod(Compass.heading - goalAngle, 360) + 180, 360) - 180, 0));

    } else { // Compass correct
        moveInfo.correction = round(headingPID.update(doubleMod(Compass.heading + 180, 360) - 180, 0));
    }
}


void calculateMovement(){ 
    // --- Calulates movement of robot based on state and outAvoidance --- //

    if (playMode == Mode::attack){ // Update movement style based on playMode
        calculateAttackMovement();
    } else {
        calculateDefenseMovement();
    }

    moveInfo = LightArray.calculateOutAvoidance(Compass.heading, moveInfo); // Updates movement with state of line.

    calculateCorrection(); // Update correction value based on goal correction state


}


// Mode caclulateMode(){

// }


void setup(){
    // --- Setup Libraries and Variables --- //

    pinMode(LED_BUILTIN, OUTPUT); //Setup Teensy LED
    digitalWrite(LED_BUILTIN, HIGH);
    
    // Initalise libraries
    Compass.init();
    Motor.init();
    Tssps.init();
    LightVector.init();
    LightArray.init();
    Cam.init();

    defaultMode = ROBOT ? Mode::attack : Mode::defend;

}


void loop(){
    // --- Read libraries and calculate values --- //

    // Read from libraries to find data
    Compass.read();
    Tssps.read();
    LightArray.update(Compass.heading);

    #if GOAL_TRACK // If using camera, update, else don't bother 
        Cam.update(); // Read Cam data
        Cam.goalTrack(); // Update goalTrack States
    #endif

    ballInfo = Tssps.getBallData();
    lineInfo = LightArray.getLineData();

    playMode = Mode::undecided; // Manual playMode set

    // calculatePosition(); // Calculates robot's postion on field in cartesian corrdinates
    calculateMovement(); //Calculate movement values 

    Motor.Move(moveInfo.angle, moveInfo.correction, moveInfo.speed); // Move towards target

    // Flash LED based off Timer & playMode
    if (playMode == Mode::attack && attackLEDTimer.timeHasPassed()){
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    } else if (playMode == Mode::defend && defenceLEDTimer.timeHasPassed()){
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    }

} 

