#ifndef GOALDATA_H
#define GOALDATA_H

#include <Arduino.h>
#include <Common.h>

class GoalData{

    public: 
        uint16_t angle, distance;
        bool face;

        GoalData(){
            angle = -1;
            distance = 0;
        }

        GoalData(uint16_t angle, uint16_t distance) : angle(angle), distance(distance) {}

        bool visible(){
            return angle != 65535;
        }

        int calculateCentimeter(){
            return 0.00000353067 * pow(MATH_E, 0.0288427 * (distance + 500)) - 25.0921;
        }


};


#endif