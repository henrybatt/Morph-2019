#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <Debug.h>

class Camera{
public:
    void init();
    void read();

private:
    int currentin;
    int camBuffer[CAM_BUFFER_NUM];

    int yangle;
    int ydist;
    int bangle;
    int bdist;
};
#endif