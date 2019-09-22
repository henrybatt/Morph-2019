#ifndef LIGHT_SENSOR_ARRAY_H
#define LIGHT_SENSOR_ARRAY_H

#include <Arduino.h>
#include <Common.h>
#include <Pins.h>
#include <Define.h>
#include <Debug.h>
#include <MoveData.h>
#include <LineData.h>

// Array of light sensors
class LightSensorArray {
public:
    LightSensorArray() {}

    void init();
    void update(float heading);

    double angle = NO_LINE_ANGLE;
    double size = NO_LINE_SIZE;

    void calculateOutAvoidance(MoveData *calcMove, float heading);

    bool isOutsideLine(float heading, double angle);


private:

    void calibrate(); // Finds threshold values
    int readSensor(int sensor); // Read sensor values
    void calculateClusters(); // Find num of clusters
    void calculateLine(); // Calculate angle of line

    void calculateLineData(float heading);

    int controller1[4] = {MUX_A_0, MUX_A_1, MUX_A_2, MUX_A_3}; // MUX binary pins
    int controller2[4] = {MUX_B_0, MUX_B_1, MUX_B_2, MUX_B_3};

    int thresholds[LS_NUM] = {0}; // Threshold of field for each sensor
    bool onWhite[LS_NUM] = {0}; // If light sensor see white. If reading > threshold

    int starts[4]; // Array of cluster start indexes
    int ends[4]; // Array of cluster end indexes

    int numClusters = 0; // Number of clusters found
    bool findClusterStart; // If cluster has begun


    #if ROBOT
        int pins[LS_NUM] = {LS_7, LS_6, LS_5, LS_4, LS_3, LS_2, LS_1, LS_32, LS_31, LS_30, LS_29, LS_28, LS_27, LS_26, LS_25, LS_24, LS_23, LS_22, LS_21, LS_20, LS_19, LS_18, LS_17, LS_16, LS_15, LS_14, LS_13, LS_12, LS_11, LS_10, LS_9, LS_8}; // Multiplexer channels for each sensor (5-36)
    #else
        int pins[LS_NUM] = {LS_23, LS_22, LS_21, LS_20, LS_19, LS_18, LS_17, LS_16, LS_15, LS_14, LS_13, LS_12, LS_11, LS_10, LS_9, LS_8, LS_7, LS_6, LS_5, LS_4, LS_3, LS_2, LS_1, LS_32, LS_31, LS_30, LS_29, LS_28, LS_27, LS_26, LS_25, LS_24};
    #endif

};

#endif
