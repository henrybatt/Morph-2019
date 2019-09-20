#include "Vector.h"


Vector::Vector(double _x, double _y, bool cartesian){
    cartesian ? getPolar(_x, _y) : getCartesian(_x, _y);
}


void Vector::getPolar(double _i, double _j){
    i = _i;
    j = _j;

    arg = getArg(_i, _j);
    mag = getMag(_i, _j);
}


void Vector::getCartesian(double _arg, double _mag){
    arg = _arg;
    mag = _mag;

    i = getI(_arg, _mag);
    j = getJ(_arg, _mag); 
}


double Vector::getArg(double _i, double _j){
    return doubleMod(90 - radiansToDegrees(atan2(_j, _i)), 360);
}


double Vector::getMag(double _i, double _j){
    return sqrt(_i * _i + _j * _j);
}


double Vector::getI(double _arg, double _mag){
    return _mag * sin(degreesToRadians(_arg));
}


double Vector::getJ(double _arg, double _mag){
    return _mag * cos(degreesToRadians(_arg));
}


bool Vector::exists(){
    return mag!= 0;
}


bool Vector::between(double leftAngle, double rightAngle){
    return isAngleBetween(arg, leftAngle, rightAngle);
}


Vector Vector::operator+(Vector vector2){
    return Vector(i + vector2.i, j + vector2.j);
}


Vector Vector::operator-(Vector vector2){
    return Vector(i - vector2.i, j - vector2.j);
}


Vector Vector::operator*(double scalar){
    return Vector(arg, mag * scalar, false);
}


Vector Vector::operator/(double scalar){
    return Vector(arg, mag / scalar, false);
}


bool Vector::operator==(Vector vector2){
    return mag == vector2.mag;
}


bool Vector::operator!=(Vector vector2){
    return mag != vector2.mag;
}


bool Vector::operator<(Vector vector2){
    return mag < vector2.mag;
}


bool Vector::operator<=(Vector vector2){
    return mag <= vector2.mag;
}


bool Vector::operator>(Vector vector2){
    return mag > vector2.mag;
}


bool Vector::operator>=(Vector vector2){
    return mag >= vector2.mag;
}
