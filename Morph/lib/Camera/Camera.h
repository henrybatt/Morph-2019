#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>

#include <Define.h>
#include <Pins.h>
#include <Debug.h>

#include <Common.h>

#include <IMU.h>

typedef struct goalData{
    int x,y;
    bool exist;
    int angle, length;
};



class Camera{
    public:
        goalData yellow;
        goalData blue;

        void init();
        void read();
        void calc();

        void goalTracking();

        bool attackVisible();
        bool defendVisible();
        bool goalVisible();

    private:
        int currentin;
        int camBuffer[CAM_BUFFER_NUM];


};
#endif