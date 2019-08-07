#include "Tssp.h"


void Tssp::init(){
    for (int i = 0; i < TSSP_NUM; i++){
        pinMode(tsspPins[i], INPUT);
    }
    double temp_angle;	

     for (int i = 0; i < TSSP_NUM; i++){	
        temp_angle = degreesToRadians(i * (360/TSSP_NUM));	

        scaledCos[i] = cos(temp_angle);	
        scaledSin[i] = sin(temp_angle);	
    }
}

void Tssp::read(){
    for (int i = 0; i < 255; i++){
        updateOnce();
    }
    finishRead();
}

void Tssp::updateOnce(){
    for (int i = 0; i < TSSP_NUM; i++){
        tempValues[i] += 1 - digitalRead(tsspPins[i]);
    }
    tsspCounter++;
}


void Tssp::finishRead(){
    for (int i = 0; i < TSSP_NUM; i++){
        values[i] = 100 * tempValues[i] / 255;
        tempValues[i] = 0;
        sortedValues[i] = 0;
        indexes[i] = 0;

        #if DEBUG_TSSP
            Serial.print(values[i]);
            if (i != TSSP_NUM - 1){
                Serial.print(" ");
            }else{
                Serial.println();
            }
        #endif
    }
    tsspCounter = 0;

    sortValues();
    calculateAngleStrength(4);
}

void Tssp::sortValues(){
    for (int i = 0; i < TSSP_NUM; i++){
        for (int j = 0; j < TSSP_NUM; j++){
            if (values[i] > sortedValues[j]){
                if (j <= i){
                    ARRAYSHIFTDOWN(sortedValues, j, i);
                    ARRAYSHIFTDOWN(indexes, j, i);
                }
                sortedValues[j] = values[i];
                indexes[j] = i;
                break;
            }
        }
    }
}

void Tssp::calculateAngleStrength(uint8_t n){
    int16_t x = 0;
    int16_t y = 0;

    for (int i = 0; i < n; i++){
        x += sortedValues[i] * cos(degreesToRadians(indexes[i] * 20));
        y += sortedValues[i] * sin(degreesToRadians(indexes[i] * 20));
    }

    strength = sqrt(x * x + y * y);
    ballVisible = (strength != 0);
    angle = ballVisible ? doubleMod(radiansToDegrees(atan2(y, x)), 360) : TSSP_NO_BALL;
}

uint16_t Tssp::getAngle(){
    return angle;
}

uint16_t Tssp::getStrength(){
    return strength;
}