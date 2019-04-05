#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>

#define PI 3.1415926535897932384626433832795

#define TO_RADIANS 0.01745329251994329576923690768489
#define TO_DEGREES 57.29577951308232087679815481410517

double toDegrees(double rad);
double toRadians(double deg);

int mod(int n, int modulo);
double doubleMod(double value, double maxValue);

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

#endif
