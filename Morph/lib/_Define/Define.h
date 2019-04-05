#ifndef DEFINE_H
#define DEFINE_H

#include <Arduino.h>


#define ROBOT 1



// LIGHT SENSORS
#define LS_NUM 16
#define LS_CALIBRATE_COUNT 10
#define LS_DEFAULT_THRESHOLD 200
#define LS_BUFFER 200
#define LS_INTERVAL_ANGLE 22.5


// Testing Light Pins from M&A Black Robot
const int brokenPins[] = {};
const int lightPins[LS_NUM] = {A7, A6, A10, A11, A12, A13, A3, A2, A1, A0, A22, A21, A24, A23, A9,A8};
const int lightThresh[LS_NUM] = {842, 905, 919, 930, 937, 906, 14, 885, 907, 911, 905, 895, 824, 853, 841, 825};

// --- IR Sensors --- //

// Number of periods in a sensor read
#define TSSP_TIMER_PERIOD_NUMBER 4

#define TSSP_NUM 18
#define TSSP_NUM_MULTIPLIER 20 // 360 / TSSP_NUM

// Number of strongest sensors used to calculate angle and strength
#define TSSP_BEST_TSSP_NUMBER 5

// Angle if there is no ball
#define TSSP_NO_BALL 400

// IR Pins
// #define TSSP_PIN_0 0
// #define TSSP_PIN_1 1
// #define TSSP_PIN_2 2
// #define TSSP_PIN_3 3
// #define TSSP_PIN_4 4
// #define TSSP_PIN_5 5
// #define TSSP_PIN_6 6
// #define TSSP_PIN_7 7
// #define TSSP_PIN_8 8
// #define TSSP_PIN_9 9
// #define TSSP_PIN_10 19
// #define TSSP_PIN_11 20
// #define TSSP_PIN_12 21
// #define TSSP_PIN_13 22
// #define TSSP_PIN_14 23
// #define TSSP_PIN_15 24
// #define TSSP_PIN_16 25
// #define TSSP_PIN_17 26

#define TSOP_PIN_0 54
#define TSOP_PIN_1 55
#define TSOP_PIN_2 56
#define TSOP_PIN_3 52
#define TSOP_PIN_4 51
#define TSOP_PIN_5 42
#define TSOP_PIN_6 43
#define TSOP_PIN_7 44
#define TSOP_PIN_8 57
#define TSOP_PIN_9 53
#define TSOP_PIN_10 41
#define TSOP_PIN_11 40

#endif