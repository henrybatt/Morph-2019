#ifndef VECTOR_H
#define VECTOR_H

#include <Arduino.h>
#include <Common.h>
#include <Define.h>
#include <Debug.h>



class Vector {

    public:

        /* -- I & J or Arg & Mag -- */
        Vector(double _x, double _y, bool cartesian = true);

        /* -- Vector Exists -- */
        bool exists();

        /* -- Vector is between two angles -- */
        bool between(double leftAngle, double rightAngle);


        double i, j;
        double arg, mag;


        /* -- Operators -- */
        Vector operator+(Vector vector2);
        Vector operator-(Vector vector2);
        Vector operator*(double scalar);
        Vector operator/(double scalar);

        bool operator==(Vector vector2);
        bool operator!=(Vector vector2);
        bool operator<(Vector vector2);
        bool operator<=(Vector vector2);
        bool operator>(Vector vector2);
        bool operator>=(Vector vector2);

    private:

        /* -- Calculate Argument -- */
        double getArg(double _i, double _j);

        /* -- Calculate magnitude -- */
        double getMag(double _i, double _j);

        /* -- Calculate I -- */
        double getI(double _arg, double _mag);

        /* -- Calculate J -- */
        double getJ(double _arg, double _mag);

        /* -- Convert to Polar -- */
        void getPolar(double _i, double _j);

        /* -- Convert to cartesian -- */
        void getCartesian(double _arg, double _mag);

    

};


#endif