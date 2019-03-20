#include "LightSensor.h"

LightSensor::LightSensor(){

}

void LightSensor::lightSensorSetup(int in){
    inPin = in;
    pinMode(inPin,INPUT);
}

void LightSensor::setThresh(int thresh){
    threshold = thresh;
}

int LightSensor::read(){
    readVal = analogRead(inPin);
}

bool LightSensor::onWhite(){
    read();
    return (readVal > threshold);
}

