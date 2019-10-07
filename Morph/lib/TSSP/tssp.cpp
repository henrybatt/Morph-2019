#include "TSSP.h"


void TSSP::init(){
    for (int i = 0; i < TSSP_NUM; i++){
        pinMode(pins[i], INPUT);
    }

}

void TSSP::read(){
    // Read each sensor as set number of times and sort read values into array

    // while (readCount < TSSP_READ_NUM){
    //     readOnce();
    // }
    for (int i = 0; i < TSSP_READ_NUM; i++){
        readOnce();
    }

    finishedRead();
}


void TSSP::readOnce(){
    for (int i = 0; i < TSSP_NUM; i++){
        readValues[i] += digitalReadFast(pins[i]) ^ 1;
    }

    readCount++;

}


void TSSP::finishedRead(){

    for (int i = 0; i < TSSP_NUM; i++){
        values[i] = 100 * readValues[i] / TSSP_READ_NUM;
        readValues[i] = 0;
        sortedValues[i] = 0;
        indexes[i] = 0;

        #if DEBUG_TSSP
            Serial.print(values[i]);
            if (i != TSSP_NUM - 1){
                Serial.print("\t");
            } else {
                Serial.println("");
            }
        #endif
    }

    readCount = 0;

    sortValues();
    calculateAngleStrength(4);

}



void TSSP::sortValues(){
    //Sort TSSP values & indexes from greatest to least

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

void TSSP::calculateAngleStrength(int n){
    int16_t x = 0;
    int16_t y = 0;

    for (int i = 0; i < n; i++){
        x += sortedValues[i] * cos(degreesToRadians(indexes[i] * TSSP_NUM_MULTIPLIER));
        y += sortedValues[i] * sin(degreesToRadians(indexes[i] * TSSP_NUM_MULTIPLIER));
    }

    double strength = sqrt(x * x + y * y);
    double angle = strength != 0 ? doubleMod(radiansToDegrees(atan2(y, x)), 360) : TSSP_NO_BALL;

    ballInfo = BallData(angle, strength);

    #if DEBUG_BALL_DATA
        Serial.print(ballInfo.angle);
        Serial.print("\t");
        Serial.println(ballInfo.strength);

    #endif

}



double TSSP::calcAngleAddition(){
    double value = ballInfo.angle > 180 ? ballInfo.angle - 360 : ballInfo.angle;
    double ballAngleDifference = findSign(value) * fmin(90, 0.4 * pow(MATH_E, 0.15 * smallestAngleBetween(ballInfo.angle, 0)));
    double strengthFactor = constrain(ballInfo.strength / BALL_CLOSE_STRENGTH, 0, 1);
    double distanceMultiplier = constrain((0.02 * strengthFactor * pow(MATH_E, 4.5 * strengthFactor)), 0.1, 1);
    angleAddition = ballAngleDifference * distanceMultiplier;
    return angleAddition;
}
