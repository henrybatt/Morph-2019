#include "LightSensorController.h"

LightSensorController::LightSensorController(){

}

void LightSensorController::setup(){
    for(int i = 0; i < LS_NUM; i++){
        lightArray[i].setup(lightPins[i]);
        #if DEBUG_LIGHT
            Serial.print("LightSensor[");
            Serial.print(lightPins[i]);
            Serial.println("] is on");
        #endif
    }
    calibrate();
}

void LightSensorController::calibrate(){
    for (int i = 0; i < LS_NUM; i++){
        lightArray[i].setThresh(lightThresh[i]);
    }
}

void LightSensorController::read(){
    for (int i = 0; i < LS_NUM; i++){
        lightValues[i] = lightArray[i].read();
        #if DEBUG_LIGHT
            Serial.print("LS");
            Serial.print(i);
            Serial.print(": ");
            Serial.println(lightValues[i]);
        #endif
    }
}


void LightSensorController::update(){
    read();
    updateOnWhite();
    calcVectorAngle();
    if(any){
        if(danger==0){
            initAngle = vectorAngle;
            prevAngle = vectorAngle;
            lineAngle = vectorAngle;
            danger = 1;
        }
        if(danger==1){
            if(inRange(vectorAngle,prevAngle,45)){
                initAngle = vectorAngle;
                lineAngle = vectorAngle;
            }else{
                danger = 2;
            }
        }
        else if(danger==2){
            if(inRange(vectorAngle,initAngle,45)){
                lineAngle = initAngle;
                danger = 1;
            }else{
                lineAngle = initAngle;
            }
        }
    }else{
        if(danger<=1){
            initAngle = -1;
            vectorAngle = -1;
            lineAngle = -1;
            danger = 0;
        }else{
            lineAngle = initAngle;
            vectorAngle = -1;
        }
    }
    prevAngle = vectorAngle;
}

bool LightSensorController::inRange(double value, double target, int range){
    double offset = value;
    value = 0;
    target = correctRange(target - offset, 0, 360);
    if (target <= range || target >= 360 - range){
        return true;
    }else{
        return false;
    }
}

int LightSensorController::correctRange(int value, int max){
    if (value > max){
        while (value > max){
            value -= max;
        }
    }
    return value;
}

int LightSensorController::correctRange(int value, int min, int max){
    if (value > max){
        while (value > max){
            value -= max;
        }
    }
    if (value < min){
        while (value < min){
            value += max;
        }
    }
    return value;
}

int LightSensorController::correctAngleRange(int value, int min, int max){
    if (value > max){
        while (value > max){
            value -= max + 1;
        }
    }
    if (value < min){
        while (value < min){
            value += max + 1;
        }
    }
    return value;
}