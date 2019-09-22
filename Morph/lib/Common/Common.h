#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#include <math.h>

#include <Define.h>
#include <Debug.h>

#define PI 3.1415926535897932384626433832795

#define TO_RADIANS 0.01745329251994329576923690768489
#define TO_DEGREES 57.295779513082320876798154814105
#define MATH_E 2.7182818284590452353602874713527


double toDegrees(double rad);
double toRadians(double deg);

int mod(int x, int m);
double doubleMod(double value, double maxValue);

int findSign(double value);

bool isAngleBetween(int angle, int leftAngle, int rightAngle);
bool isAngleBetween(double angle, double leftAngle, double rightAngle);

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


// --- Structures --- //
struct Vector3D {
  double x;
  double y;
  double z;
};

// --- PID --- //

#define IDLE_HEADING_KP 1
#define IDLE_HEADING_KI 0
#define IDLE_HEADING_KD 0.05
#define IDLE_HEADING_MAX_CORRECTION 255

#define HEADING_KP 2
#define HEADING_KI 0
#define HEADING_KD 0.21
#define HEADING_MAX_CORRECTION 255

#define X_MOVEMENT_KP 5
#define X_MOVEMENT_KI 0
#define X_MOVEMENT_KD 0.3
#define X_MOVEMENT_MAX 240

#define Y_MOVEMENT_KP 10
#define Y_MOVEMENT_KI 0
#define Y_MOVEMENT_KD 0.2
#define Y_MOVEMENT_MAX 230

#define TO_COORD_KP 1.5
#define TO_COORD_KI 0
#define TO_COORD_KD 0
#define TO_COORD_MAX_SPEED 100

#define ATTACK_GOAL_TRACK_KP 2
#define ATTACK_GOAL_TRACK_KI 0
#define ATTACK_GOAL_TRACK_KD 1.9 //0.7
#define ATTACK_GOAL_TRACK_MAX_CORRECTION 150

#define DEFEND_GOAL_TRACK_KP 2
#define DEFEND_GOAL_TRACK_KI 0
#define DEFEND_GOAL_TRACK_KD 1.9
#define DEFEND_GOAL_TRACK_MAX_CORRECTION 150
#endif
