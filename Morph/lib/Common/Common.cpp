#include "Common.h"
#include "math.h"


double toDegrees(double rad){
  return rad*TO_DEGREES;
}

double toRadians(double deg){
  return deg*TO_RADIANS;
}

int mod(int n, int modulo){
  int r = n % modulo;
  return r < 0 ? r + modulo : r;
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

double midAngleBetween(double angleCounterClockwise, double angleClockwise){
  return mod(angleCounterClockwise + angleBetween(angleCounterClockwise, angleClockwise) / 2.0, 360);
}

double updateMax(double max, double newVal){
  return max > newVal ? max : newVal;
}

/*int max(int x,int y){
  return x > y ? x : y;
}
*/
