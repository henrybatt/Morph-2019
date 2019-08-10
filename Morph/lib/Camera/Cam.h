#pragma once
#include <Arduino.h>
#include <Define.h>
#include <Common.h>

typedef struct goal_t {
    int x, y;
    bool exists;
    int angle, length;
};

class Camera {
public:
    goal_t blue;
    goal_t yellow;
    void read();
    void setup();
    void calc();
private:
    int buf[CAM_DATA_LENGTH];
    int lastCall;
};