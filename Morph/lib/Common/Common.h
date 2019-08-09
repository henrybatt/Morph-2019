#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795

#define TO_RADIANS 0.01745329251994329576923690768489
#define TO_DEGREES 57.295779513082320876798154814105
#define MATH_E 2.7182818284590452353602874713527


double toDegrees(double rad);
double toRadians(double deg);

int mod(int x, int m);
double doubleMod(double value, double maxValue);

int findSign(double value);

bool angleIsInside(double angleBoundCounterClockwise, double angleBoundClockwise, double angleCheck);
double angleBetween(double angleCounterClockwise, double angleClockwise);
double smallestAngleBetween(double angle1, double angle2);
double midAngleBetween(double angleCounterClockwise, double angleClockwise);

double degreesToRadians(double degrees);
double radiansToDegrees(double radians);

int sign(int value);
int sign(double value);

double doubleAbs(double value);

double distanceBetween(double x1, double y1, double x2, double y2);
double updateMax(double max, double newVal);
double angleMap(double angle, double max);

#define ARRAYSHIFTDOWN(a, lower, upper){          \
    if (upper == (sizeof(a)/sizeof(a[0])) - 1){   \
        for (int q = upper - 1; q >= lower; q--){ \
            *(a + q + 1) = *(a + q); }            \
    } else{                                       \
        for (int q = upper; q >= lower; q--){     \
            *(a + q + 1) = *(a + q); }}}

//int max(int x, int y);

struct Vector3D {
  double x;
  double y;
  double z;
};

struct DirSpeed {
    double direction;
    double speed;
    double correction;
};




#define TSSP_MAX_IGNORE 256
#define TSSP_MIN_IGNORE 0
#define TSSP_READ_NUM 255
#define TSSP_INTERVAL_ANGLE 20
#define BALL_CLOSE_STRENGTH 140

#define TSSP_X_0 0 // 0
#define TSSP_X_1 0.34202
#define TSSP_X_2 0.642788
#define TSSP_X_3 0.866025
#define TSSP_X_4 0.984808
#define TSSP_X_5 0.984808
#define TSSP_X_6 0.866025
#define TSSP_X_7 0.642788
#define TSSP_X_8 0.34202
#define TSSP_X_9 0
#define TSSP_X_10 -0.34202
#define TSSP_X_11 -0.642788
#define TSSP_X_12 -0.866025
#define TSSP_X_13 -0.984808
#define TSSP_X_14 -0.984808
#define TSSP_X_15 -0.866025
#define TSSP_X_16 -0.642788
#define TSSP_X_17 -0.34202

#define TSSP_Y_0 1
#define TSSP_Y_1 0.939693
#define TSSP_Y_2 0.766044
#define TSSP_Y_3 0.5
#define TSSP_Y_4 0.173648
#define TSSP_Y_5 -0.173648
#define TSSP_Y_6 -0.5
#define TSSP_Y_7 -0.766044
#define TSSP_Y_8 -0.939693
#define TSSP_Y_9 -1
#define TSSP_Y_10 -0.939693
#define TSSP_Y_11 -0.766044
#define TSSP_Y_12 -0.5
#define TSSP_Y_13 -0.173648
#define TSSP_Y_14 0.173648
#define TSSP_Y_15 0.5
#define TSSP_Y_16 0.766044
#define TSSP_Y_17 0.93963


// --- PID --- //

#define IDLE_HEADING_KP 1
#define IDLE_HEADING_KI 0
#define IDLE_HEADING_KD 0.05
#define IDLE_HEADING_MAX_CORRECTION 255

#define HEADING_KP 2
#define HEADING_KI 0
#define HEADING_KD 0.2
#define HEADING_MAX_CORRECTION 255

#define X_MOVEMENT_KP 5
#define X_MOVEMENT_KI 0
#define X_MOVEMENT_KD 0.3
#define X_MOVEMENT_MAX 100

#define Y_MOVEMENT_KP 10
#define Y_MOVEMENT_KI 0
#define Y_MOVEMENT_KD 0.1
#define Y_MOVEMENT_MAX 100


#define TO_COORD_KP 1.5
#define TO_COORD_KI 0
#define TO_COORD_KD 0
#define TO_COORD_MAX_SPEED 100

#define GOAL_TRACK_KP 2
#define GOAL_TRACK_KI 0
#define GOAL_TRACK_KD 0.2
#define GOAL_TRACK_MAX_CORRECTION 150

#endif
