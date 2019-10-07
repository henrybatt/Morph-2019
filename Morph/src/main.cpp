#include <Arduino.h>
#include <Define.h>
#include <Common.h>
#include <PID.h>
#include <Timer.h>
// #include <bno055.h>
// #include <bno055_driver.h>
#include <MotorController.h>
#include <TSSP.h>
#include <LightSensorArray.h>
#include <Camera.h>
#include <Bluetooth.h>
// #include<i2c_t3.h>

#include <IMU.h>


#include <Vector.h>
#include <Mode.h>
#include <MoveData.h>
#include <LineData.h>
#include <BallData.h>
#include <BluetoothData.h>

#include <Position.h>


// PID's for correction and movement around field
PID headingPID(HEADING_KP, HEADING_KI, HEADING_KD, HEADING_MAX_CORRECTION);
PID attackGoalTrackPID(ATTACK_GOAL_TRACK_KP, ATTACK_GOAL_TRACK_KI, ATTACK_GOAL_TRACK_KD, ATTACK_GOAL_TRACK_MAX_CORRECTION);
PID defendGoalTrackPID(DEFEND_GOAL_TRACK_KP, DEFEND_GOAL_TRACK_KI, DEFEND_GOAL_TRACK_KD, DEFEND_GOAL_TRACK_MAX_CORRECTION);

PID xPID(X_MOVEMENT_KP, X_MOVEMENT_KI, X_MOVEMENT_KD, X_MOVEMENT_MAX);
PID yPID(Y_MOVEMENT_KP, Y_MOVEMENT_KI, Y_MOVEMENT_KD, Y_MOVEMENT_MAX);


// Timer Classes for different robot states 
Timer attackLEDTimer(800000);
Timer defenceLEDTimer(400000);
Timer undecidedLEDTimer(200000);

Timer BTSendTimer = Timer(BT_UPDATE_TIME);

bool ledOn = false; // State of LED
float heading; // IMU heading

// Pointer Setup
// struct bno055_t bno055 = {0};
MotorController Motor;
TSSP Tssps;
LightSensorArray LightArray;
Camera Cam;
Position position;
Bluetooth bluetooth;
Vector currentAcceleration;

IMU Compass;

// Structs of robot data

// Global
BallData ballInfo;
LineData lineInfo;
MoveData moveInfo;

BluetoothData bluetoothData;


// Robot Mode
Mode playMode = Mode::undecided;
Mode defaultMode;

// IMU Compass;

/* --- Centre to goal, idleDist away --- */
void centre(goalData goal, int idleDist);
/* --- Determine angle and speed to orbit around ball --- */
void calculateOrbit();
/* --- Calculate attacking movement --- */
void calculateAttackMovement();
/* --- Calculate direction to move to intercept ball --- */
void calculateDefenseMovement();
/* --- Correction state, either goal or compass --- */
void calculateCorrection();
/* --- Calulates movement of robot based on state and outAvoidance --- */
void calculateMovement();
/*  -- Send bluetooth data and decide playMode -- */
void updateMode();
/* --- Flash LED based off Timer & playMode --- */
void playModeLED();
/* --- Initalise the BNO --- */
void bnoInit();
/* --- Setup Libraries and Variables --- */
void setup();
/* --- Read libraries and calculate values --- */
void loop();


void centre(goalData goal, int idleDist, bool isAttack){
    double goalAngle = doubleMod(goal.angle + heading, 360);
    double xmoveInfo = -xPID.update(goal.distance * sin(degreesToRadians(goalAngle)), 0);
    double ymoveInfo = -yPID.update(goal.distance * cos(degreesToRadians(goalAngle)), idleDist);
    moveInfo.angle = isAttack ? doubleMod(radiansToDegrees(atan2(xmoveInfo, ymoveInfo)) - heading, 360)
                                : doubleMod(radiansToDegrees(atan2(xmoveInfo, ymoveInfo)) - heading + 180, 360);
    moveInfo.speed = sqrt(pow(xmoveInfo,2) + pow(ymoveInfo,2));
}


void calculateOrbit(){
    moveInfo.angle = doubleMod(ballInfo.angle + Tssps.calcAngleAddition(), 360); // Orbit Angle

    int fastSpeed = Cam.attack.face ? ORBIT_FAST_SPEED : ORBIT_FAST_SPEED - 10;
    int slowSpeed = Cam.attack.face ? ORBIT_SLOW_SPEED : ORBIT_SLOW_SPEED + 10;

    //If ball infront of capture zone, surge forwards fast, else move at a modular speed
    if (ballInfo.strength > ATTACK_SURGE_STRENGTH && angleIsInside(360 - ATTACK_CAPTURE_ANGLE, ATTACK_CAPTURE_ANGLE, ballInfo.angle)){
        moveInfo.speed = fastSpeed;
    } else {
        moveInfo.speed = slowSpeed + (double)(fastSpeed - slowSpeed) * (1.0 - abs(Tssps.angleAddition) / (double)90.0);
    }
    
}


void calculateAttackMovement(){
    // Calculate Ball State and Movement

    if (bluetooth.otherData.ballData.isOut){
        // Defender see's ball isOut, move to centre of field
        centre(Cam.defend, ATTACK_IDLE_DISTANCE_DFG, false);
        Cam.attack.face = false;

    } else if (ballInfo.visible()){
        calculateOrbit(); // Calculate Movement towards ball.

    } else { // No ball visible, if goal visible sit in-line
        
        if (ATTACK_CENTERING && Cam.goalVisible()){

            if (Cam.attackClosest()){
                centre(Cam.attack, ATTACK_IDLE_DISTANCE_ATG, true);
                Cam.attack.face = false;
            } else {
                centre(Cam.defend, ATTACK_IDLE_DISTANCE_DFG, false);
                Cam.attack.face = false;
            }

        } else {
            // No ball or goal visible, stop
            moveInfo.angle = -1;
            moveInfo.speed = 0;

        }
    } 
}


void calculateDefenseMovement(){
    if (Cam.defend.visible){
        if (ballInfo.visible()){
            if (angleIsInside(360 - DEFEND_CAPTURE_ANGLE, DEFEND_CAPTURE_ANGLE, ballInfo.angle) && ballInfo.strength > DEFEND_SURGE_STRENGTH && Cam.defend.distance < DEFEND_SURGE_DISTANCE){
                // Ball infront of robot, surge forwards
                calculateOrbit();
                Cam.defend.face = false;
                
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
            centre(Cam.defend, DEFEND_DISTANCE, false);
            // position.moveToCoord(&moveInfo, Vector(0, position.defendGoal.j + DEFEND_DISTANCE_CM));
            Cam.defend.face = false;
       }
    } else {
        if (ballInfo.visible()){
            // No goal, become attacker
            calculateOrbit();
            Cam.defend.face = false; // Stop correcting to goal

        } else {
            // No goal or ball, stop in place
            moveInfo.angle = -1;
            moveInfo.speed = 0;
        }
    }


}


void calculateCorrection(){
    if (Cam.attack.face && playMode == Mode::attack){ // Correct to attack goal
        double goalAngle = doubleMod(Cam.attack.angle + heading, 360);
        moveInfo.correction = round(attackGoalTrackPID.update(doubleMod(doubleMod(heading - goalAngle, 360) + 180, 360) - 180, 0));

    } else if (Cam.defend.face && playMode == Mode::defend){ // Correct to defend goal
        double goalAngle = doubleMod(Cam.defend.angle + heading, 360);
        moveInfo.correction = round(defendGoalTrackPID.update(doubleMod(doubleMod(heading - goalAngle, 360) + 180, 360) - 180, 0));

    } else { // Compass correct
        moveInfo.correction = round(headingPID.update(doubleMod(heading + 180, 360) - 180, 0));
    }
}


void calculateMovement(){ 
    if (playMode == Mode::attack){ // Update movement style based on playMode
        calculateAttackMovement();
    } else {
        calculateDefenseMovement();
    }

    LightArray.calculateOutAvoidance(&moveInfo, heading); // Updates movement with state of line.

    calculateCorrection(); // Update correction value based on goal correction state

}


bool shouldSwitchMode(BluetoothData attacker, BluetoothData defender){
    return (angleIsInside(360 - SWITCH_DEFEND_ANGLE, SWITCH_DEFEND_ANGLE, defender.ballData.angle) && defender.ballData.strength > SWITCH_DEFEND_STRENGTH)
            && ((angleIsInside(360 - SWITCH_ATTACK_ANGLE, SWITCH_ATTACK_ANGLE, attacker.ballData.angle) && attacker.ballData.strength < SWITCH_ATTACK_STRENGTH) 
                || attacker.ballData.strength <  SWITCH_ATTACK_FAR_STRENGTH)
            && (attacker.lineData.onField && defender.lineData.onField);
}


void updateMode(){

    Mode previousMode = playMode;

    ballInfo.isOut = LightArray.isOutsideLine(heading, ballInfo.angle);
    bluetoothData = BluetoothData(ballInfo, lineInfo, playMode, heading, position.robotPosition);
    bluetooth.update(bluetoothData);

    if (bluetooth.isConnected){

        // Connected to  bluetooth, pick playMode
        if (playMode == Mode::undecided){
            // Undecided mode, pick default or opposite
            if (bluetooth.otherData.playMode == Mode::undecided){
                playMode = defaultMode;
            } else {
                playMode = bluetooth.otherData.playMode == Mode::defend ? Mode::attack : Mode::defend;
            }

        } else if (ROBOT){
            // Default playMode decider - Defender
            if (shouldSwitchMode((playMode == Mode::attack ? bluetoothData : bluetooth.otherData), 
                                (playMode == Mode::defend ? bluetoothData : bluetooth.otherData))){
                playMode = playMode == Mode::defend ? Mode::attack : Mode::defend;
            }

        } else {
            // Opposite of default decider
            playMode = bluetooth.otherData.playMode == Mode::defend ? Mode::attack : Mode::defend;

        }

        // If statement for if become defender, move out of way

    } else if (bluetooth.previouslyConnected){
        // Was connected, other robot went offline, switch to defense
        playMode = Mode::defend;

    } else {
        // Never connected, pick default mode
        playMode = defaultMode;
    }
}


void setup(){
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT); //Setup Teensy LED
    digitalWrite(LED_BUILTIN, HIGH);

    // Initalise libraries
    // bnoInit();
    Motor.init();
    Tssps.init();
    LightArray.init();
    Cam.init();
    bluetooth.init();

    Compass.init();

    defaultMode = ROBOT ? Mode::defend : Mode::attack;
     
    // playMode = Mode::attack; // Manual playMode set
    
    digitalWrite(LED_BUILTIN, LOW);
}


void loop(){
    // Read from libraries to find data

    // bno055_convert_float_euler_h_deg(&heading);

    Compass.read();
    heading = Compass.heading;

    Tssps.read();
    LightArray.update(heading);

    #if GOAL_TRACK // If using camera, update, else don't bother 
        Cam.update(); // Read Cam data
        Cam.goalTrack(); // Update goalTrack States
        // position.calcRobotPosition(Cam, heading);
    #endif

    if (BTSendTimer.timeHasPassed()){
        updateMode();
    }

    calculateMovement(); //Calculate movement values 

    Motor.Move(moveInfo); // Move towards target

    playModeLED();

} 

/*
void bnoInit(){
    delay(100);
    Wire.begin();
    // setup BNO055 driver
    bno055.bus_read = bno055_read;
    bno055.bus_write = bno055_write;
    bno055.delay_msec = bno055_delay_ms;
    bno055.dev_addr = BNO055_I2C_ADDR2;

    s8 result = bno055_init(&bno055);
    result += bno055_set_power_mode(BNO055_POWER_MODE_NORMAL);
    // see page 22 of the datasheet, Section 3.3.1
    // we don't use NDOF or NDOF_FMC_OFF because it has a habit of snapping to magnetic north which is undesierable
    // instead we use IMUPLUS (acc + gyro fusion) if there is magnetic interference, otherwise M4G (basically relative mag)
    result += bno055_set_operation_mode(BNO055_OPERATION_MODE_IMUPLUS);
    if (result == 0){
        Serial.println("BNO055 initialised");
    } else {
        Serial.printf("BNO055 init error: %d\n", result);
    }
    
}
*/

void playModeLED(){
    if (playMode == Mode::attack && attackLEDTimer.timeHasPassed()){
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    } else if (playMode == Mode::defend && defenceLEDTimer.timeHasPassed()){
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    } else if (playMode == Mode::undecided && undecidedLEDTimer.timeHasPassed()){
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    }
}
