#ifndef LIGHT_SENSOR_ARRAY_H
#define LIGHT_SENSOR_ARRAY_H

#include <Arduino.h>
#include <Common.h>
#include <Pins.h>
#include <Define.h>
#include <Debug.h>

// Array of light sensors
class LightSensorArray {
public:
    LightSensorArray() {}

    void init();

    void update();
    double angle = NO_LINE_ANGLE;
    double size = NO_LINE_SIZE;

    double getLineAngle();
    double getLineSize();
 
private:
    void calibrate();
    void readSensor(int sensor);

    void calculateClusters(bool doneFillInSensors = false);
    void fillInSensors();
    void calculateLine();
    void resetStartEnds();


    int controller1[4] = {MUX_A_0, MUX_A_1, MUX_A_2, MUX_A_3};
    int controller2[4] = {MUX_B_0, MUX_B_1, MUX_B_2, MUX_B_3};

    #if ROBOT
        int pins[LS_NUM] = {LS_23, LS_22, LS_21, LS_20, LS_19, LS_18, LS_17, LS_16, LS_15, LS_14, LS_13, LS_12, LS_11, LS_10, LS_9, LS_8, LS_7, LS_6, LS_5, LS_4, LS_3, LS_2, LS_1, LS_32, LS_31, LS_30, LS_29, LS_28, LS_27, LS_26, LS_25, LS_24};
#else
        int pins[LS_NUM] = {LS_7, LS_6, LS_5, LS_4, LS_3, LS_2, LS_1, LS_32, LS_31, LS_30, LS_29, LS_28, LS_27, LS_26, LS_25, LS_24, LS_23, LS_22, LS_21, LS_20, LS_19, LS_18, LS_17, LS_16, LS_15, LS_14, LS_13, LS_12, LS_11, LS_10, LS_9, LS_8}; // Multiplexer channels for each sensor (5-36)
    #endif
    // int pins[LS_NUM] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
    // int pins[LS_NUM] = {LS_1, LS_2, LS_3, LS_4, LS_5, LS_6, LS_7, LS_8, LS_9, LS_10, LS_11, LS_12, LS_13, LS_14, LS_15, LS_16, LS_17, LS_18, LS_19, LS_20, LS_21, LS_22, LS_23, LS_24, LS_25, LS_26, LS_27, LS_28, LS_29, LS_30, LS_31, LS_32};
    double thresholds[LS_NUM] = {0};

    int readValues[LS_NUM] = {0};

    bool onWhite[LS_NUM] = {0};


    void updateLineLocation();

    void resetClusters();

    
    // bool data[LS_NUM]; // Array of if sensors see white or not
    bool filledInData[LS_NUM]; // Data after sensors are filled in (if an off sensor has two adjacent on sensors, it will be turned on)

    // int thresholds[LS_NUM]; // Thresholds for each sensor. A sensor is on if reading > threshold

    int starts[4]; // Array of cluster start indexes
    int ends[4]; // Array of cluster end indexes

    int numClusters = 0; // Number of clusters found

    // int info[LS_NUM];
};

#endif // LIGHT_SENSOR_ARRAY_H
