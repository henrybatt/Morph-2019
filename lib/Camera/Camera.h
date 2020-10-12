#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <Debug.h>
#include <Common.h>

#include <GoalData.h>


class Camera{
    public:

        /* -- Structures of goal data -- */
        GoalData attack;
        GoalData defend;

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

        /* -- Determines if new data has come over cameraSerial -- */
        bool newData();

    private:

        /* -- Read from camera serial to get x & y values of goals -- */
        void read();

        /* -- Calculate distance towards goal in centimeters -- */
        int calculateCentimeter(int distance);

        bool newCamData;

        int currentin;

};
#endif