#include "Common.h"
// #include "math.h"


double toDegrees(double rad){
  return rad*TO_DEGREES;
}

double toRadians(double deg){
  return deg*TO_RADIANS;
}

int mod(int x, int m){
  int r = x % m;
  return r < 0 ? r + m : r;
}

double doubleMod(double value, double maxValue) {
    return fmod((value + maxValue), maxValue);
}

bool isAngleBetween(int angle, int leftAngle, int rightAngle){
  if(rightAngle < leftAngle){
    return angle < rightAngle || angle > leftAngle;
  }
  else{
    return angle < rightAngle && angle > leftAngle;
  }
}

double angleBetween(double angleCounterClockwise, double angleClockwise){
  return doubleMod(angleClockwise - angleCounterClockwise, 360);
}

double smallestAngleBetween(double angleCounterClockwise, double angleClockwise){
  double ang = angleBetween(angleCounterClockwise, angleClockwise);
  return fmin(ang, 360 - ang);
}

bool angleIsInside(double angleBoundCounterClockwise, double angleBoundClockwise, double angleCheck) {
    if (angleBoundCounterClockwise < angleBoundClockwise) {
        return (angleBoundCounterClockwise < angleCheck && angleCheck < angleBoundClockwise);
    } else {
        return (angleBoundCounterClockwise < angleCheck || angleCheck < angleBoundClockwise);
    }
}

double updateMax(double max, double newVal){
  return max > newVal ? max : newVal;
}

/*int max(int x,int y){
  return x > y ? x : y;
}
*/

int findSign(double value) {
	return value >= 0 ? 1 : -1;
}

double midAngleBetween(double angleCounterClockwise, double angleClockwise){
  return mod(angleCounterClockwise + angleBetween(angleCounterClockwise, angleClockwise) / 2.0, 360);
}

double distanceBetween(double x1, double x2, double y1, double y2){
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int sign(int value){
  return value >= 0 ? 1 : -1;
}

int sign(double value){
  return value >= 0 ? 1 : -1;
}

double degreesToRadians(double degrees){
  return degrees * TO_RADIANS;
}

double radiansToDegrees(double radians){
  return radians * TO_DEGREES;
}

double doubleAbs(double value){
  return value * sign(value);
}
