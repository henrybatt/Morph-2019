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

#endif