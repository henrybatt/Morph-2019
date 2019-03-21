#ifndef LIGHTSENSORCONTROLLER_H
#define LIGHTSENSORCONTROLLER_H

#include <Arduino.h>
#include <LightSensor.h>
#include <Common.h>
#include <Define.h>
#include <Debug.h>


class LightSensorController{
    public:
        LightSensorController();
        void setup();
        void update();
        int lightValues[LS_NUM] = {0};
        int onWhite[LS_NUM] = {0};

        void calibrate();
        int correctRange(int value, int max);
        int correctRange(int value, int min, int max);
        int correctAngleRange(int value, int min, int max);
        void calcVectorAngle();
        void updateOnWhite();
        bool inRange(double value, double target, int range);
        void read();
        LightSensor lightArray[LS_NUM] = {LightSensor()};
        bool any;
        int triggered;
        double vectorX, vectorY;
        double initAngle;
        double prevAngle;
        double vectorAngle;
        double lineAngle;
        int danger = 0;
        int heading = 0;
        bool firstContact = true;
        bool a, b;
};

#endif