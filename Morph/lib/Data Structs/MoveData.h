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
    MoveData(double angle, double speed) : angle(angle), speed(speed) {}
    MoveData(double angle, double speed, double correction) : angle(angle), speed(speed), correction(correction) {}

};

#endif