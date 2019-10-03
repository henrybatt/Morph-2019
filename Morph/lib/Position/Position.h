#ifndef POSITION_H
#define POSITION_H

#include <Arduino.h>
#include <Common.h>
#include <Define.h>
#include <Debug.h>
#include <Vector.h>
#include <Camera.h>
#include <MoveData.h>
#include <PID.h>
#include <BallData.h>

class Position{
    public:

        // Position of robot on field
        Vector robotPosition;

        // Position of ball relative to robot
        Vector ballRelPosition;

        // Position of ball on field
        Vector ballPosition;

        // Goal Coordinates
        Vector defendGoal = Vector(0, -(FIELD_LENGTH_CM / 2) + GOAL_OFFSET_CM);
        Vector attackGoal = Vector(0, (FIELD_LENGTH_CM / 2) - GOAL_OFFSET_CM);

        /* -- Calculate robots position in cartesian form -- */
        void calcRobotPosition(Camera Cam, float heading );

        /* -- Calculate ball position relative to robot -- */
        void calcBallPosition();

        /* -- Find difference between desired and robots' coords -- */
        bool moveToCoord(MoveData *moveData, Vector vector);

        /*  -- Calculate movement of coord differences -- */
        bool moveByDifference(MoveData *moveData, Vector diff);

        void test();

    private:

        bool camVisible;
        float heading;

        PID coordPID = PID(TO_COORD_KP, TO_COORD_KI, TO_COORD_KD, TO_COORD_MAX_SPEED);


};


#endif