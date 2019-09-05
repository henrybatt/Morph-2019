#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <Debug.h>
#include <Common.h>

struct camImage{
    int x, y;
    bool visible;
};

struct goalData{
    int angle, distance;
    bool visible, face;
};

class Camera{
    public:

        // -- Structures of all camera data --
        camImage yellow;
        camImage blue;

        goalData attack;
        goalData defend;


        // -- Setup Camera Serial and read-- 
        void init();

        // -- Read Camera data and update angles and distances --
        void update();

        // -- If goal's are visible faceGoal --
        void goalTrack();

        // -- Find closest goal in pixels --
        double closestDistance();

    private:

        // -- Read from camera serial to get x & y values of goals --
        void read();

        // -- Calculate angle's + distances towards goals --
        void calc();

        // -- Determines if new data has come over cameraSerial --
        bool newData();

        // -- Populate goal data with values -- 
        void calculateGoal(goalData *goal, camImage image);

        // -- Calculate angle towards image --
        int calculateAngle(camImage image);

        // -- Calculate distance towards image --
        int calculateDistance(camImage image);

        // -- If attacking goal closest --
        bool attackClosest();


        bool newCamData;

        int currentin;
        int camBuffer[CAM_BUFFER_NUM];




};
#endif