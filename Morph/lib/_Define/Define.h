#ifndef DEFINE_H
#define DEFINE_H

#include <Arduino.h>

#define ROBOT 1 //1 or 0, 1 = A
#define ATTACK_GOAL_YELLOW true //true = Yellow, false = Blue
#define GOAL_TRACK false


// --- Camera --- //

#define CAM_SERIAL Serial4
#define CAM_DATA_LENGTH 7
#define CAM_CENTRE_X 79
#define CAM_CENTRE_Y 67
#define CAM_BEGIN_BYTE 0xB

// --- Light Sensors --- //

#define LS_BUFFER 300
#define LS_INTERVAL_ANGLE 11.25
#define LS_RADIUS 54
#define LS_AVOID_SIZE 1

#define LS_NUM 32
#define LS_NUM_MULTIPLIER 11.25 // L360 / LS_NUM

#define LS_CALIBRATION_COUNT 50
#define LS_CALIBRATION_BUFFER 220
#define LS_ES_DEFAULT 100
#define NO_LINE_ANGLE -1
#define NO_LINE_SIZE -1
#define LINE_CORNER_ANGLE_THRESHOLD 30
#define LINE_ANGLE_BUFFER -10
#define LINE_ANGLE_BUFFER_CORNER -10
#define LINE_SMALL_SIZE 0.2
#define LINE_BIG_SIZE 0.5 
#define LINE_SPEED 100
#define OVER_LINE_SPEED 200

#define MOTOR_NUM 4
#define ORBIT_FAST_SPEED 255
#define ORBIT_SLOW_SPEED 255
#define LINE_SPEED_FAST 150
#define LINE_SPEED_SLOW 100


// --- IR Sensors --- //

#define TSSP_NUM 18

// #define TSSP_NUM 18//18
#define TSSP_NO_BALL 400

// --- Movement --- //
#define MOVEMENT_ANGLE_OFFSET 0
#define MOVEMENT_ROTATION_OFFSET 0
#define TOTAL_BRAKE_TIME 100

// --- IMU Sensor --- //
#define IMU_CALIBRATION_COUNT 20
#define IMU_CALIBRATION_TIME 50

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

// Motor
#define MOTOR_ANGLE_0 45
#define MOTOR_ANGLE_1 135
#define MOTOR_ANGLE_2 225
#define MOTOR_ANGLE_3 315

// Field Information
#define FIELD_WIDTH_CM 182
#define FIELD_LENGTH_CM 243
#define GOAL_OFFSET_CM 30
#define DEFENDING_BOX_WIDTH_CM 30
#define FIELD_CM_WITH_GOAL (FIELD_WIDTH_CM / 2 - GOAL_OFFSET_CM)

// --- Coords --- //
#define COORD_THRESHOLD_DISTANCE 2

//Coords to move when no ball visible
#define NO_BALL_COORD_X 0
#define NO_BALL_COORD_Y 0

//Coords to move when other robot sees ball is out of field
#define BALL_OUT_COORD_X 0
#define BALL_OUT_COORD_Y -30


// - Defender - //

#define DEFEND_CAPTURE_ANGLE 20
#define DEFEND_SURGE_STRENGTH 150 //
#define DEFEND_SURGE_DISTANCE 400
#define DEFEND_DISTANCE 30 //Distance from goal in CM to sit at
#define DEFEND_SURGE_Y -30

#endif