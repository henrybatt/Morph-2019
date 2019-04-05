#include "tssp.h"


void Tssp::init(){
    for (int i = 0; i < TSSP_NUM; i++){
        pinMode(tsspPins[i], INPUT);
    }
    double temp_angle;
    for (int i = 0; i < TSSP_NUM; i++){
        temp_angle = degreesToRadians(i * TSSP_NUM_MULTIPLIER);

        scaledCos[i] = cos(temp_angle);
        scaledSin[i] = sin(temp_angle);
    }
}

void Tssp::updateOnce(){
for (int i = 0; i < TSSP_NUM; i++){
    tempValues[i] += 1 - digitalReadFast(tsspPins[i]);
    }
    tsspCounter++;
}

void Tssp::finishRead(){
    for (int i = 0; i < TSSP_NUM; i++){
        values[i] = 100 * (double)tempValues[i] / (double)tsspCounter;
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
    calculateAngleStrength(TSSP_BEST_TSSP_NUMBER);
}

void Tssp::sortValues(){
    for (uint8_t i = 0; i < TSSP_NUM; i++){
        for (uint8_t j = 0; j < TSSP_NUM; j++){
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

    for (uint8_t i = 0; i < n; i++){
        x += sortedValues[i] * scaledCos[indexes[i]];
        y += sortedValues[i] * scaledSin[indexes[i]];
    }

    if (x == 0 && y == 0){
        angle = TSSP_NO_BALL;
    }
    else{
        Serial.println(atan2(y, x));
        angle = mod(radiansToDegrees(atan2(y, x)), 360);
    }

    strength = sqrt(x * x + y * y);
}

uint16_t Tssp::getAngle(){
    return angle;
}

uint16_t Tssp::getStrength(){
    return strength;
}