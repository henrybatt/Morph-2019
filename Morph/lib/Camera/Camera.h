#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <Debug.h>
#include <Common.h>

struct camData{
    int x,y;
    bool exist;
    int angle, length;
};

class Camera{
    public:
        camData yellow;
        camData blue;

        void init();
        void read();
        void calc(int heading);

        bool attackVisible();
        bool defendVisible();
        bool goalVisible();

        int attackAngle , defendAngle;

    private:
        int currentin;
        int camBuffer[CAM_BUFFER_NUM];


};
#endif