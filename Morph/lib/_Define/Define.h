#ifndef DEFINE_H
#define DEFINE_H

#include <Arduino.h>

#define ROBOT 1
#define ATTACK_GOAL_YELLOW true //true = Yellow, false = Blue
#define GOAL_TRACK true

// --- Camera --- //

#define cameraSerial Serial4
#define CAM_BUFFER_NUM 7
#define CAM_START_NUM 255
#define CAM_IMAGE_WIDTH 240
#define CAM_NO_DATA 250

// --- Light Sensors --- //
#define LS_NUM 32
#define LS_CALIBRATE_COUNT 10
#define LS_DEFAULT_THRESHOLD 200
#define LS_BUFFER 200
#define LS_INTERVAL_ANGLE 11.25
#define LS_RADIUS 54
#define LS_AVOID_SIZE 1

#define LS_NUM 32
#define LS_NUM_MULTIPLIER 11.25

#define LS_CALIBRATION_COUNT 50
#define LS_CALIBRATION_BUFFER 60
#define LS_ES_DEFAULT 100
#define NO_LINE_ANGLE 400
#define NO_LINE_SIZE 3
#define LINE_CORNER_ANGLE_THRESHOLD 30
#define LINE_ANGLE_BUFFER -10
#define LINE_ANGLE_BUFFER_CORNER -10
#define LINE_SMALL_SIZE 0.2
#define LINE_BIG_SIZE 0.5

#define MOTOR_NUM 4
#define ORBIT_FAST_SPEED 200
#define ORBIT_SLOW_SPEED 100
#define LINE_SPEED_FAST 200
#define LINE_SPEED_SLOW 100


// #define LS_NUM 36
// #define LS_NUM_MULTIPLIER 10 // = 360 / LS_NUM

// // Number of times to read light sensors for calibration
// #define LS_CALIBRATION_COUNT 50

// // Amount to add onto calibration value
// #define LS_CALIBRATION_BUFFER 60

// // Default value for cluster end-start array
// #define LS_ES_DEFAULT 100

// // Angle and size values if no line is seen
// #define NO_LINE_ANGLE 400
// #define NO_LINE_SIZE 3

// // If an angle mod 90 is within value and 90 - value, then it is considered a corner
// #define LINE_CORNER_ANGLE_THRESHOLD 30

// // If an angle is within value of the line angle, it is outside the line. A value for corner and not corner
// #define LINE_ANGLE_BUFFER -10
// #define LINE_ANGLE_BUFFER_CORNER -10

// // < small size, robot will ignore line. < big size, > small size, robot will sit on the line.
// // > big size and the robot will go back in
// #define LINE_SMALL_SIZE 0.2
// #define LINE_BIG_SIZE 0.5

// // Speeds for slow and fast line avoidance (depending on line size from big size to 2)
// #define LINE_SPEED 20
// #define OVER_LINE_SPEED 60

// // Enable / disable line avoidance
// #define AVOID_LINE true

// --- IR Sensors --- //
#define TSSP_NUM 18
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



#endif