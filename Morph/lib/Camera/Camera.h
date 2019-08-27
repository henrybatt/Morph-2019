#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <Debug.h>
#include <Common.h>

struct camData{
    int x, y;
    bool exist;
    int angle, distance;
    double cm;
};

struct goalData{
    int angle, distance;
    bool exist, face;
    double cm;
};

class Camera{
    public:
        camData yellow;
        camData blue;

        goalData attack;
        goalData defend;

        void init();
        void update();

        void goalTrack();

        double closestDistance();

        double closestDistanceCentimeter();

    private:
        void read();
        void calc();

        bool newData();

        void updateAttack(int angle, int distance, bool exist, double cm);
        void updateDefend(int angle, int distance, bool exist, double cm);

        double centimeterDistance(int distance);

        bool newCamData;

        int currentin;
        int camBuffer[CAM_BUFFER_NUM];
};
#endif