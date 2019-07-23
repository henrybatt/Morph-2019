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

struct goalData{
    int angle, length;
    bool exist;
};

class Camera{
    public:
        camData yellow;
        camData blue;

        goalData attack;
        goalData defend;

        void init();
        void read();
        void calc();
        void update();

        void updateAttack(int angle, int length, bool exist);
        void updateDefend(int angle, int length, bool exist);

        void goalTrack();

        bool faceGoal;

    private:
        int currentin;
        int camBuffer[CAM_BUFFER_NUM];


};
#endif