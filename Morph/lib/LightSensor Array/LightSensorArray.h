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

    void read();
    int readSensor(int sensor);
    void changeMUXChannel1(int channel);
    void changeMUXChannel2(int channel);

    void calculateClusters(bool doneFillInSensors = false);
    void fillInSensors();
    void calculateLine();
    void resetStartEnds();

    void calibrate();

    double getLineAngle();
    double getLineSize();

    void updateLineLocation();

    bool data[LS_NUM]; // Array of if sensors see white or not
    bool filledInData[LS_NUM]; // Data after sensors are filled in (if an off sensor has two adjacent on sensors, it will be turned on)

    int thresholds[LS_NUM]; // Thresholds for each sensor. A sensor is on if reading > threshold

    int starts[4]; // Array of cluster start indexes
    int ends[4]; // Array of cluster end indexes

    int numClusters = 0; // Number of clusters found

    int info[LS_NUM];

private:
    void resetClusters();

    // int muxChannels[LS_NUM] = {LS_7, LS_6, LS_5, LS_4, LS_3, LS_2, LS_1, LS_32, LS_31, LS_30, LS_29, LS_28, LS_27, LS_26, LS_25, LS_24, LS_23, LS_22, LS_21, LS_20, LS_19, LS_18, LS_17, LS_16, LS_15, LS_14, LS_13, LS_12, LS_11, LS_10, LS_9, LS_8};      // Multiplexer channels for each sensor (5-36)
    int muxChannels[LS_NUM] = {LS_6, LS_6, LS_5, LS_4, LS_3, LS_2, LS_1, LS_32, LS_31, LS_30, LS_29, LS_28, LS_27, LS_26, LS_25, LS_24, LS_23, LS_22, LS_21, LS_20, LS_19, LS_18, LS_17, LS_16, LS_15, LS_14, LS_13, LS_13, LS_11, LS_10, LS_9, LS_8};     // Multiplexer channels for each sensor (5-36)

    // int muxChannels[LS_NUM] = {LS_1, LS_2, LS_3, LS_4, LS_5, LS_6, LS_7, LS_8, LS_9, LS_10, LS_11, LS_12, LS_13, LS_14, LS_15, LS_16, LS_17, LS_18, LS_19, LS_20, LS_21, LS_22, LS_23, LS_24, LS_25, LS_26, LS_27, LS_28, LS_29, LS_30, LS_31, LS_32};

    double angle = -1; // Line angle
    double size = -1; // Line size
};

#endif // LIGHT_SENSOR_ARRAY_H
