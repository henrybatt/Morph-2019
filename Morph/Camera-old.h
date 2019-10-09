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

        /* -- Structures of all camera data -- */
        camImage yellow;
        camImage blue;

        goalData attack;
        goalData defend;


        /* -- Setup Camera Serial and read-- */
        void init();

        /* -- Read Camera data and update angles and distances -- */
        void update();

        /* -- If goal's are visible faceGoal -- */
        void goalTrack();

        /* -- Find closest goal in pixels -- */
        double closestDistance();

        /* -- Find closest goal in centimeters -- */
        double closestCentimeter();

        /* -- If attacking goal closest -- */
        bool attackClosest();

        /* -- If a goal is visible -- */
        bool goalVisible();

    private:

        /* -- Read from camera serial to get x & y values of goals -- */
        void read();

        /* -- Calculate angle's + distances towards goals -- */
        void calc();

        /* -- Determines if new data has come over cameraSerial -- */
        bool newData();

        /* -- Populate goal data with values -- */
        void calculateGoal(goalData *goal, camImage image, bool defend);

        /* -- Calculate angle towards image -- */
        int calculateAngle(camImage image);

        /* -- Calculate distance towards image -- */
        int calculateDistance(camImage image);

        /* -- Calculate distance towards goal in centimeters -- */
        int calculateCentimeter(int distance);




        bool newCamData;

        int currentin;
        int camBuffer[CAM_PACKET_SIZE];




};
#endif