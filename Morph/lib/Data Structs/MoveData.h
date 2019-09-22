#ifndef MOVEDATA
#define MOVEDATA

#include <Arduino.h>
#include <Common.h>
#include <Debug.h>
#include <Define.h>

struct MoveData{
    double angle;
    double speed;
    double correction;

    MoveData() {}
    MoveData(double a, double s) : angle(a), speed(s) {}
    MoveData(double a, double s, double c) : angle(a), speed(s), correction(c) {}

};

#endif