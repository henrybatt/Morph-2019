#include <LightSensorArray.h>

void LightSensorArray::init() {
    pinMode(MUX_A0, OUTPUT);
    pinMode(MUX_A1, OUTPUT);
    pinMode(MUX_A2, OUTPUT);
    pinMode(MUX_A3, OUTPUT);

    pinMode(MUX_A4, OUTPUT);
    pinMode(MUX_A5, OUTPUT);
    pinMode(MUX_A6, OUTPUT);
    pinMode(MUX_A7, OUTPUT);

    pinMode(MUX_OUT_1, INPUT);
    pinMode(MUX_OUT_2, INPUT);
    calibrate();
}

void LightSensorArray::changeMUXChannel1(int channel) {
        digitalWriteFast(MUX_A0, channel & 0x1);
        digitalWriteFast(MUX_A1, (channel >> 1) & 0x1);
        digitalWriteFast(MUX_A2, (channel >> 2) & 0x1);
        digitalWriteFast(MUX_A3, (channel >> 3) & 0x1);
}

void LightSensorArray::changeMUXChannel2(int channel) {
        digitalWriteFast(MUX_A4, channel & 0x1);
        digitalWriteFast(MUX_A5, (channel >> 1) & 0x1);
        digitalWriteFast(MUX_A6, (channel >> 2) & 0x1);
        digitalWriteFast(MUX_A7, (channel >> 3) & 0x1);

}

void LightSensorArray::calibrate() {
    // Read each sensor and save green values

    for (int i = 0; i < LS_NUM; i++) {
        int defaultValue = 0;

        for (int j = 0; j < LS_CALIBRATION_COUNT; j++) {
            defaultValue += readSensor(i);
        }

        thresholds[i] = round(((double)defaultValue / LS_CALIBRATION_COUNT) + LS_CALIBRATION_BUFFER);

	}
}

int LightSensorArray::readSensor(int sensor) {
    if (sensor <= 6 || sensor >=  23){
        changeMUXChannel1(muxChannels[sensor]);
        return analogRead(MUX_OUT_1);
    } else if (sensor >= 7 || sensor <= 22){
        changeMUXChannel2(muxChannels[sensor]);
        return analogRead(MUX_OUT_2);
    }
}

void LightSensorArray::read() {
    // Read all 36 sensors
    for (int i = 0; i < LS_NUM; i++) {
        data[i] = readSensor(i) > thresholds[i];
    }

#if DEBUG_LIGHT
        for(int i =0; i < LS_NUM; i++){
            Serial.print(readSensor(i));
            Serial.print(" ");
        }
        Serial.println();
    #endif

    

    calculateClusters();
    calculateLine();

}

void LightSensorArray::calculateClusters(bool doneFillInSensors) {
    bool *lightData = !doneFillInSensors ? data : filledInData;
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

void LightSensorArray::fillInSensors() {
    for (int i = 0; i < LS_NUM; i++) {
        filledInData[i] = data[i];

        if (!data[i] && data[mod(i - 1, LS_NUM)] && data[mod(i + 1, LS_NUM)]) {
            filledInData[i] = true;
        }
    }

    calculateClusters(true);
}

void LightSensorArray::calculateLine() {
    if (numClusters > 0){
        double cluster1Angle = midAngleBetween(starts[0] * LS_NUM_MULTIPLIER, ends[0] * LS_NUM_MULTIPLIER);
        double cluster2Angle = midAngleBetween(starts[1] * LS_NUM_MULTIPLIER, ends[1] * LS_NUM_MULTIPLIER);
        double cluster3Angle = midAngleBetween(starts[2] * LS_NUM_MULTIPLIER, ends[2] * LS_NUM_MULTIPLIER);

        if (numClusters == 1){
            angle = cluster1Angle;
            size = 1 - cos(degreesToRadians(angleBetween(starts[0] * LS_NUM_MULTIPLIER, ends[0] * LS_NUM_MULTIPLIER) / 2.0));
            // size = 1 - RADIANS_TO_DEGREES * cos(DEGREES_TO_RADIANS * (angleBetween(clusterStarts[0] * LS_INTERVAL_ANGLE, clusterEnds[0] * LS_INTERVAL_ANGLE) / 2.0));

        } else if (numClusters ==2){
            angle = angleBetween(cluster1Angle, cluster2Angle) <= 180 ? midAngleBetween(cluster1Angle, cluster2Angle) : midAngleBetween(cluster2Angle, cluster1Angle);
            size = 1 - cos(degreesToRadians(angleBetween(cluster1Angle, cluster2Angle) <= 180 ? angleBetween(cluster1Angle, cluster2Angle) / 2.0 : angleBetween(cluster2Angle, cluster1Angle) / 2.0));
            // size = 1 - RADIANS_TO_DEGREES * cos(DEGREES_TO_RADIANS * (angleBetween(cluster1Angle, cluster2Angle) <= 180 ? angleBetween(clusterEnds[0] * LS_INTERVAL_ANGLE, clusterStarts[1] * LS_INTERVAL_ANGLE) / 2.0 : angleBetween(clusterEnds[1] * LS_INTERVAL_ANGLE, clusterStarts[0] * LS_INTERVAL_ANGLE) / 2.0));

        } else {
            double angleDiff12 = angleBetween(cluster1Angle, cluster2Angle);
            double angleDiff23 = angleBetween(cluster2Angle, cluster3Angle);
            double angleDiff31 = angleBetween(cluster3Angle, cluster1Angle);
            double biggestAngle = max(angleDiff12, max(angleDiff23, angleDiff31));
            if (biggestAngle == angleDiff12){
                angle = midAngleBetween(cluster2Angle, cluster1Angle);
                size = angleBetween(cluster2Angle, cluster1Angle) <= 180 ? 1 - cos(degreesToRadians(angleBetween(cluster2Angle, cluster1Angle) / 2.0)) : 1;
            } else if (biggestAngle == angleDiff23){
                angle = midAngleBetween(cluster3Angle, cluster2Angle);
                size = angleBetween(cluster3Angle, cluster2Angle) <= 180 ? 1 - cos(degreesToRadians(angleBetween(cluster3Angle, cluster2Angle) / 2.0)) : 1;
            } else {
                angle = midAngleBetween(cluster1Angle, cluster3Angle);
                size = angleBetween(cluster1Angle, cluster3Angle) <= 180 ? 1 - cos(degreesToRadians(angleBetween(cluster1Angle, cluster3Angle) / 2.0)) : 1;
            }
        }
    } else {
        angle = NO_LINE_ANGLE;
        size = NO_LINE_SIZE;
    }
}

void LightSensorArray::resetStartEnds() {
    for (int i = 0; i < 4; i++) {
        starts[i] = LS_ES_DEFAULT;
        ends[i] = LS_ES_DEFAULT;
    }
}

double LightSensorArray::getLineAngle() {
    return angle;
}

double LightSensorArray::getLineSize() {
    return size;
}

