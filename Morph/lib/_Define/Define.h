#ifndef DEFINE_H
#define DEFINE_H

#include <Arduino.h>

#define ROBOT 0  //1 or 0, 1 = A
#define ATTACK_GOAL_YELLOW true //true = Yellow, false = Blue
#define GOAL_TRACK true

// --- Movement Speed --- //
#define ORBIT_FAST_SPEED 145 // Vertical movement of orbit
#define ORBIT_SLOW_SPEED 130 // Horizontal movement

#define ACCELERATION false
#define MAX_ACCELERATION 0.5

#define LINE_OVER_SPEED 200 // Speed when all the way off line
#define LINE_SPEED 125 //75 // Modular speed to cross over line (2 times min, half max)
#define LINE_SPEED_CLOSE 75 // Speed when movement towards ball is close to line

#define LINE_SIZE_MEDIUM 0.1
#define LINE_SPEED_FAST 255


// --- Camera --- //
#define cameraSerial Serial4
#define CAM_BAUD 115200
#define CAM_PACKET_SIZE 7
#define CAM_START_BYTE 255
#define CAM_IMAGE_WIDTH 120
#define CAM_IMAGE_HEIGHT 120
#define CAM_CENTRE_X 60
#define CAM_CENTRE_Y 60
#define CAM_NO_DATA 250


// --- Light Sensors --- //
#define LS_NUM 32
#define LS_NUM_MULTIPLIER 11.25 // L360 / LS_NUM

#define LS_CALIBRATION_COUNT 50
#define LS_CALIBRATION_BUFFER 300
#define NO_LINE_ANGLE -1
#define NO_LINE_SIZE -1
#define LINE_CORNER_ANGLE_THRESHOLD 30 // If angle mod 90 greater than value and less than 90 - value, must be on corner
#define LINE_BUFFER -10 // If orbit angle within line angle and buffer, must want to move outside line
#define LINE_BUFFER_CORNER -10 // ^
#define LINE_SIZE_BIG 0.4 // If line size bigger than move back into field
#define LINE_SIZE_SMALL 0.1 // If line size bigger than this but smaller than bigger, sit on line if want to orbit out


// --- Ball Data --- //
#define BALL_CAPTURE_ANGLE 30
#define BALL_CAPTURE_STRENGTH 150


// --- IR Sensors --- //
#define TSSP_NUM 18
#define TSSP_NUM_MULTIPLIER 20 //360 / LS_NUM
#define TSSP_NO_BALL -1
#define TSSP_READ_NUM 255
#define BALL_CLOSE_STRENGTH 145
#define BALL_FAR_STRENGTH 50
#define ANGLE_DIFF_MULTIPLIER 0.15
#define TSSP_PERIOD 4


// --- Movement --- //
#define MOVEMENT_ANGLE_OFFSET 0
#define MOVEMENT_ROTATION_OFFSET 0
#define TOTAL_BRAKE_TIME 100


// --- IMU Sensor --- //
#define IMU_CALIBRATION_COUNT 50
#define IMU_CALIBRATION_TIME 40

#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C

#define GYRO_FULL_SCALE_250_DPS 0x00
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define ACC_FULL_SCALE_2_G 0x00
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18


// --- Motor -- //
#define MOTOR_NUM 4
#define MOTOR_ANGLE_0 45
#define MOTOR_ANGLE_1 135
#define MOTOR_ANGLE_2 225
#define MOTOR_ANGLE_3 315


// -- Bluetooth -- //
#define BT_BAUD 9600 //38400 //115200
#define BTSerial Serial5
#define BT_START_BYTE 255
#define BT_PACKET_SIZE 15
#define BT_DISCONNECT_TIME 1000000
#define BT_UPDATE_TIME 100000



// --- Field Information --- //
#define FIELD_WIDTH_CM 182
#define FIELD_LENGTH_CM 243
#define GOAL_OFFSET_CM 30
#define DEFENDING_BOX_WIDTH_CM 30
#define FIELD_LENGTH_WITH_GOAL (FIELD_LENGTH_CM / 2 - GOAL_OFFSET_CM)


// --- Coords --- //
#define COORD_THRESHOLD_DISTANCE 2

//Coords to move when no ball visible
#define NO_BALL_COORD_X 0
#define NO_BALL_COORD_Y 0

//Coords to move when other robot sees ball is out of field
#define BALL_OUT_COORD_X 0
#define BALL_OUT_COORD_Y -30


// --- Switching --- //

// Ball must be within front of the defender and close
#define SWITCH_DEFEND_ANGLE 20
#define SWITCH_DEFEND_STRENGTH 165

// AND in front of attacker and semi far away
#define SWITCH_ATTACK_ANGLE 90
#define SWITCH_ATTACK_STRENGTH 140

// OR far from attacker
#define SWITCH_ATTACK_FAR_STRENGTH 110

#define DEFEND_SURGE_DISTANCE_1 48
#define DEFEND_SURGE_DISTANCE_0 53



#if ROBOT // Fun ifs, why
    #define DEFEND_DISTANCE 24
    #define DEFEND_SURGE_DISTANCE 26

    #define ATTACK_IDLE_DISTANCE_DFG 40 // Distance from defending goal to sit at when no ball
    #define ATTACK_IDLE_DISTANCE_ATG 100 // Distance from attacking goal to sit at when no ball

#else 
    #define DEFEND_DISTANCE 46
    #define DEFEND_SURGE_DISTANCE 53

    #define ATTACK_IDLE_DISTANCE_DFG 53 // Distance from defending goal to sit at when no ball
    #define ATTACK_IDLE_DISTANCE_ATG 80 // Distance from attacking goal to sit at when no ball
#endif




// --- Defender --- //
// #define DEFEND_DISTANCE 74//65//60
#define DEFEND_DISTANCE_CM 25 //Distance from goal in CM to sit at

#define DEFEND_SURGE_STRENGTH 160 // Strength of ball to surge

#define DEFEND_CAPTURE_ANGLE 15 // Angle range of ball to surge

// #define DEFEND_SURGE_DISTANCE 94//82//82  //70 // Distance from goal to surge till
#define DEFEND_SURGE_Y -30

// --- Attacker --- //
#define ATTACK_CENTERING false 
// #define ATTACK_IDLE_DISTANCE_DFG 82 // Distance from defending goal to sit at when no ball
// #define ATTACK_IDLE_DISTANCE_ATG 100 // Distance from attacking goal to sit at when no ball

#define ATTACK_SURGE_STRENGTH 180 // Strength of ball to surge 

#define ATTACK_CAPTURE_ANGLE 10 // Angle range of ball to surge



#endif