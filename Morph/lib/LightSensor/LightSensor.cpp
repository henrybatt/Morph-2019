#include "LightSensor.h"

LightSensor::LightSensor(){
}

void LightSensor::init(int in){
    inPin = in;

    pinMode(inPin,INPUT);

    read();
    int defaultValue = readVal;

    for (int i = 0; i < LS_CALIBRATE_COUNT; i++) {
        read();
        defaultValue += readVal;
    }
    threshold = round((int)((double)defaultValue / LS_CALIBRATION_COUNT) + LS_CALIBRATION_BUFFER);
}


bool LightSensor::onWhite(int readVal){
    return (readVal > threshold);
}

int LightSensor::getValue(){
    return readVal;
}

void LightSensor::setThresh(int thresh){
	threshold = thresh;
}
