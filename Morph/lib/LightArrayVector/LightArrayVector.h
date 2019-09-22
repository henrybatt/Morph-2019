#ifndef LIGHT_ARRAY_VECTOR_H
#define LIGHT_ARRAY_VECTOR_H

#include <Arduino.h>
#include <Common.h>
#include <Pins.h>
#include <Define.h>
#include <Debug.h>
#include <MoveData.h>
#include <LineData.h>


// Array of light sensors
class LightArrayVector {
    public:
        LightArrayVector() {}

        // LineData lineInfo;

        void init();
        void update();
        // bool isOutsideLine(double angle);

        MoveData calculateOutAvoidance(MoveData calcMovement);

        // LineData getLineData();

        double vectorAngle = NO_LINE_ANGLE;


    private:

        void calibrate(); // Finds threshold values
        int readSensor(int sensor); // Read sensor values
        void calcVectorAngle(); // Calculate line angle
        // void calcLineData();

        int controller1[4] = {MUX_A_0, MUX_A_1, MUX_A_2, MUX_A_3}; // MUX binary pins
        int controller2[4] = {MUX_B_0, MUX_B_1, MUX_B_2, MUX_B_3};

        int thresholds[LS_NUM] = {0}; // Threshold of field for each sensor
        bool onWhite[LS_NUM] = {0}; // If light sensor see white. If reading > threshold

        double vectorX, vectorY; // Vector X & Y


        #if ROBOT
            int pins[LS_NUM] = {LS_7, LS_6, LS_5, LS_4, LS_3, LS_2, LS_1, LS_32, LS_31, LS_30, LS_29, LS_28, LS_27, LS_26, LS_25, LS_24, LS_23, LS_22, LS_21, LS_20, LS_19, LS_18, LS_17, LS_16, LS_15, LS_14, LS_13, LS_12, LS_11, LS_10, LS_9, LS_8}; // Multiplexer channels for each sensor - Clockwise
            // int pins[LS_NUM] = {LS_7, LS_8, LS_9, LS_10, LS_11, LS_12, LS_13, LS_14, LS_15, LS_16, LS_17, LS_18, LS_19, LS_20, LS_21, LS_22, LS_23, LS_24, LS_25, LS_26, LS_27, LS_28, LS_29, LS_30, LS_31, LS_32, LS_1, LS_2, LS_3, LS_4, LS_5, LS_6}; // Anticlockwise
        #else
            int pins[LS_NUM] = {LS_23, LS_22, LS_21, LS_20, LS_19, LS_18, LS_17, LS_16, LS_15, LS_14, LS_13, LS_12, LS_11, LS_10, LS_9, LS_8, LS_7, LS_6, LS_5, LS_4, LS_3, LS_2, LS_1, LS_32, LS_31, LS_30, LS_29, LS_28, LS_27, LS_26, LS_25, LS_24}; // Multiplexer channels for each sensor - Clockwise
            // int pins[LS_NUM] = {LS_23, LS_24, LS_25, LS_26, LS_27, LS_28, LS_29, LS_30, LS_31, LS_32, LS_1, LS_2, LS_3, LS_4, LS_5, LS_6, LS_7, LS_8, LS_9, LS_10, LS_11, LS_12, LS_13, LS_14, LS_15, LS_16, LS_17, LS_18, LS_19, LS_20, LS_21, LS_22}; // Anticlockwise
        #endif

};

#endif