#ifndef POINT_H
#define POINT_H

#include <Arduino.h>
#include <Common.h>

class Coord {

    public:
        Coord(){
            x = 0;
            y = 0;
        }
        Coord(double x, double y) : x(x), y(y) {}

        double getAngle(){
            // --- Find angle to coord --- // 
            return doubleMod(90 - radiansToDegrees(atan2(y, x)), 360);
        }

        double getMagnitude(){
            // --- Calculate magnitude --- //
            return sqrt(x * x + y * y);
        }

        void getCartesian(double angle, double magnitude){
            // --- Convert from polar to cartesian form --- //
            double pAngle = doubleMod(90 - angle, 360);

            x = magnitude * cos(degreesToRadians(pAngle));
            y = magnitude * sin(degreesToRadians(pAngle));
        }

        Coord subtract(Coord other){
            // --- Subtract two coords from eachother --- //
            return Coord(x - other.x, y - other.y);
        }


    double x;
    double y;
};


#endif