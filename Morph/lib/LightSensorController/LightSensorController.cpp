#include "LightSensorController.h"

LightSensorController::LightSensorController(){

}

void LightSensorController::init(){
    for(int i = 0; i < LS_NUM; i++){
        lightArray[i].init(lightPins[i]);
        #if DEBUG_LIGHT
            Serial.print("LightSensor[");
            Serial.print(lightPins[i]);
            Serial.println("] is on");
        #endif
    }
}

void LightSensorController::read(){
    for (int i = 0; i < LS_NUM; i++){
        onWhite[i] = lightArray[i].onWhite();
        lightArray[i].read();
        // Serial.print(2);
        // Serial.print(" , ");
        // Serial.println(lightArray[2].getValue());
        // Serial.println(analogRead(A10));
        digitalWriteFast(A10, LOW);

        digitalWriteFast(A10, 1 & 0x1);
        digitalWriteFast(A10, HIGH);
        // Serial.print(analogRead(A10));
        // Serial.print(" , ");
        // Serial.println(analogRead(A11));

        // #if DEBUG_LIGHT
        //     Serial.print("LS");
        //     Serial.print(i);
        //     Serial.print(": ");
        //     Serial.print(lightValues[0]);
        //     Serial.print(" On White: ");
        //     Serial.println(onWhite[0]);
        // #endif
    }
    calculateClusters();
    calculateLine();
}

void LightSensorController::calculateClusters(bool doneFillInSensors) {
    bool *lightData = !doneFillInSensors ? onWhite : filledInData;

    resetStartEnds();

    int index = 0;
    
    bool previousValue = false;

    for (int i = 0; i < LS_NUM; i++) {
        if (lightData[i] && !previousValue) {
            starts[index] = i;
        }

        if (!lightData[i] && previousValue) {
            ends[index] = i - 1;
            index++;

            if (index > 3) {
                if (!doneFillInSensors) {
                    fillInSensors();
                } else {
                    resetStartEnds();
                    numClusters = 0;
                }

                return;
            }
        }

        previousValue = lightData[i];
    }

    int tempNumClusters = (int)(starts[0] != LS_ES_DEFAULT) + (int)(starts[1] != LS_ES_DEFAULT) + (int)(starts[2] != LS_ES_DEFAULT) + (int)(starts[3] != LS_ES_DEFAULT);

    if (tempNumClusters != index) {

        if (starts[0] == 0) {
            starts[0] = starts[index];
        } else {
            ends[index] = LS_NUM - 1;
            index++;

            if (index > 3) {
                if (!doneFillInSensors) {
                    fillInSensors();
                } else {
                    resetStartEnds();
                    numClusters = 0;
                }

                return;
            }
        }
    }

    numClusters = index;
}

void LightSensorController::fillInSensors() {
    for (int i = 0; i < LS_NUM; i++) {
        filledInData[i] = onWhite[i];

        if (!onWhite[i] && onWhite[mod(i - 1, LS_NUM)] && onWhite[mod(i + 1, LS_NUM)]) {
            filledInData[i] = true;
        }
    }

    calculateClusters(true);
}

void LightSensorController::calculateLine() {
    if (numClusters == 0) {
        angle = NO_LINE_ANGLE;
        size = NO_LINE_SIZE;
    } else {
        double cluster1Angle = midAngleBetween(starts[0] * LS_NUM_MULTIPLIER, ends[0] * LS_NUM_MULTIPLIER);
        double cluster2Angle = midAngleBetween(starts[1] * LS_NUM_MULTIPLIER, ends[1] * LS_NUM_MULTIPLIER);
        double cluster3Angle = midAngleBetween(starts[2] * LS_NUM_MULTIPLIER, ends[2] * LS_NUM_MULTIPLIER);

        if (numClusters == 1) {
            angle = cluster1Angle;
            size = 1 - cos(degreesToRadians(angleBetween(starts[0] * LS_NUM_MULTIPLIER, ends[0] * LS_NUM_MULTIPLIER) / 2.0));
        } else if (numClusters == 2) {
            angle = angleBetween(cluster1Angle, cluster2Angle) <= 180 ? midAngleBetween(cluster1Angle, cluster2Angle) : midAngleBetween(cluster2Angle, cluster1Angle);
            size = 1 - cos(degreesToRadians(angleBetween(cluster1Angle, cluster2Angle) <= 180 ? angleBetween(cluster1Angle, cluster2Angle) / 2.0 : angleBetween(cluster2Angle, cluster1Angle) / 2.0));
        } else {
            double angleDiff12 = angleBetween(cluster1Angle, cluster2Angle);
            double angleDiff23 = angleBetween(cluster2Angle, cluster3Angle);
            double angleDiff31 = angleBetween(cluster3Angle, cluster1Angle);

            double biggestAngle = max(angleDiff12, max(angleDiff23, angleDiff31));

            if (angleDiff12 == biggestAngle) {
                angle = midAngleBetween(cluster2Angle, cluster1Angle);
                size = angleBetween(cluster2Angle, cluster1Angle) <= 180 ? 1 - cos(degreesToRadians(angleBetween(cluster2Angle, cluster1Angle) / 2.0)) : 1;
            } else if (angleDiff23 == biggestAngle) {
                angle = midAngleBetween(cluster3Angle, cluster2Angle);
                size = angleBetween(cluster3Angle, cluster2Angle) <= 180 ? 1 - cos(degreesToRadians(angleBetween(cluster3Angle, cluster2Angle) / 2.0)) : 1;
            } else {
                angle = midAngleBetween(cluster1Angle, cluster3Angle);
                size = angleBetween(cluster1Angle, cluster3Angle) <= 180 ? 1 - cos(degreesToRadians(angleBetween(cluster1Angle, cluster3Angle) / 2.0)) : 1;
            }
        }
    }
}

void LightSensorController::resetStartEnds() {
    for (int i = 0; i < 4; i++) {
        starts[i] = LS_ES_DEFAULT;
        ends[i] = LS_ES_DEFAULT;
    }
}

double LightSensorController::getLineAngle() {
    return angle;
}

double LightSensorController::getLineSize() {
    return size;
}
