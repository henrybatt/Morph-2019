#ifndef LIGHTSENSORCONTROLLER_H
#define LIGHTSENSORCONTROLLER_H

#include <Arduino.h>
#include <LightSensor.h>
#include <Common.h>
#include <Define.h>
#include <Debug.h>
#include <Pins.h>


class LightSensorController{
    public:
        LightSensorController();
        void init();
        void read();
        int lightValues[LS_NUM];
        bool onWhite[LS_NUM];

        void calculateClusters(bool doneFillInSensors = false);
        void fillInSensors();
        void calculateLine();
        void resetStartEnds();

        // void calibrate();

        double getLineAngle();
        double getLineSize();

        LightSensor lightArray[LS_NUM] = {LightSensor()};

        bool filledInData[LS_NUM];
        bool oneWhite[LS_NUM];
        uint16_t thresholds[LS_NUM];
        int starts[4];
        int ends[4];
        int numClusters = 0; 
    private:
        void resetClusters();
        double angle;
        double size;
        int lightPins[LS_NUM] = {LS_1, LS_2, LS_3, LS_4, LS_5, LS_6, LS_7, LS_8, LS_9, LS_10, LS_11, LS_12, LS_13, LS_14, LS_15, LS_16, LS_17, LS_18, LS_19, LS_20, LS_21, LS_22, LS_23, LS_24, LS_25, LS_26, LS_27, LS_28, LS_29, LS_30, LS_31, LS_32};
};

#endif