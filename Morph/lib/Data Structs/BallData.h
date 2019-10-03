#ifndef BALLDATA_H
#define BALLDATA_H

#include <Arduino.h>
#include <Common.h>
#include <Vector.h>


class BallData{

    public:
        uint16_t angle;
        uint16_t strength;
        bool isOut;

        BallData() {
            angle = TSSP_NO_BALL;
            strength = 0;
        }

        BallData(uint16_t angle, uint16_t strength) : angle(angle), strength(strength) {}

        BallData(uint16_t angle, uint16_t strength, bool isOut) : angle(angle), strength(strength), isOut(isOut) {}
        

        bool visible(){
            return strength != 0;
        }


        double distance(){
            return 123;
        }


        Vector vector(float heading = 0){
            return Vector(doubleMod(angle + heading, 360), distance(), false);
        } 


};

extern BallData ballInfo;

#endif
