#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <Debug.h>
#include <Common.h>

struct camData
{
    int x, y;
    bool exist;
    int angle, distance;
    double cm;
};

struct goalData{
    int angle, distance;
    bool exist;
    double cm;
};

class Camera
{
public:
    camData yellow;
    camData blue;

    goalData attack;
    goalData defend;

    void init();
    void read();
    void calc();
    void update();

    void updateAttack(int angle, int distance, bool exist, double cm);
    void updateDefend(int angle, int distance, bool exist, double cm);

    void goalTrack();

    double centimeterDistance(double pixelDistance);
    double closestDistance();


    bool faceGoal;

private:
    int currentin;
    int camBuffer[CAM_BUFFER_NUM];
};
#endif