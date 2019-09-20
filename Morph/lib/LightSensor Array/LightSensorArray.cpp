#include <LightSensorArray.h>

void LightSensorArray::init() {
    // Setup pinmode for each MUX
    for (int i = 0; i < 4; i++){
        pinMode(controller1[i], OUTPUT);
        pinMode(controller2[i], OUTPUT);
    }
    pinMode(MUX_A_OUT, INPUT);
    pinMode(MUX_B_OUT, INPUT);

    calibrate();
}

void LightSensorArray::calibrate() {
    // Read each sensor and save green values
    for (int i = 0; i < LS_NUM; i++) {
        int defaultValue = 0;

        for (int j = 0; j < LS_CALIBRATION_COUNT; j++) {
            defaultValue += readSensor(i);
        }
        thresholds[i] = round((defaultValue / (double)LS_CALIBRATION_COUNT) + LS_CALIBRATION_BUFFER);
	}
}

int LightSensorArray::readSensor(int sensor){
    // Read from sensor and return light value
    int channel = pins[sensor];
    bool mux1 = (channel < 16);
    channel = mux1 ? channel : channel - 16;
    for (int i = 0; i < 4; i++){
        int control = mux1 ? controller1[i] : controller2[i];
        digitalWriteFast(control, channel >> i & 0x1);
    }
    return  (mux1 ? analogRead(MUX_A_OUT) : analogRead(MUX_B_OUT));
}

void LightSensorArray::update(float heading){
    // Reads all 32 Light Sensors
    for (int i = 0; i < LS_NUM; i++){
        onWhite[i] = (readSensor(i) > thresholds[i]);
    }

    // Updates onWhite state if others around it are
    for (int i = 0; i < LS_NUM; i++){
        if (!onWhite[i]){
            if (onWhite[mod(i-1, LS_NUM)] && onWhite[mod(i+1, LS_NUM)]){
                onWhite[i] = true;
            }
        }
        #if DEBUG_LIGHT
            Serial.print(onWhite[i]);
            if ( i != LS_NUM - 1){
                Serial.print(" ");
            } else{
                Serial.println();
                delay(10);
            }
        #endif
    }

    calculateClusters();
    calculateLine();
    calculateLineData(heading);
}

void LightSensorArray::calculateClusters() {
    // Finds clusters of activated lightsensors

    // Reset Values
    numClusters = 0;
    findClusterStart = 1;

    for (int i = 0; i < 4; i++){
        starts[i] = -1;
        ends[i] = -1;
    }

    for (int i = 0; i < LS_NUM; i++){ // Loop through ls' to find clusters
        if (findClusterStart){ //Find first cluster value
            if (onWhite[i]){ 
                findClusterStart = 0;
                starts[numClusters] = i;
                numClusters += 1;
            }
        } else { //Found start of cluster, find how many sensors
            if (!onWhite[i]){ // Cluster ended 1 ls ago
                findClusterStart = 1;
                ends[numClusters - 1] = i - 1;
            }
        }
    }
     //If final light sensor sees white end cluster before, on last ls
    if (onWhite[LS_NUM - 1]){
        ends[numClusters - 1] = LS_NUM -1;
    }
     // If first and last light sensor see line, merge both clusters together
    if (numClusters > 1){
        if (onWhite[0] && onWhite[LS_NUM - 1]){
            starts[0] = starts[numClusters - 1];
            starts[numClusters - 1] = -1;
            ends[numClusters - 1] = -1;
            numClusters -=  1;
        }
    }
}


void LightSensorArray::calculateLine() {
    if (numClusters > 0){
        double cluster1Angle = midAngleBetween(starts[0] * LS_NUM_MULTIPLIER, ends[0] * LS_NUM_MULTIPLIER);
        double cluster2Angle = midAngleBetween(starts[1] * LS_NUM_MULTIPLIER, ends[1] * LS_NUM_MULTIPLIER);
        double cluster3Angle = midAngleBetween(starts[2] * LS_NUM_MULTIPLIER, ends[2] * LS_NUM_MULTIPLIER);

        if (numClusters == 1){
            angle = cluster1Angle;
            size = 1 - cos(degreesToRadians(angleBetween(starts[0] * LS_NUM_MULTIPLIER, ends[0] * LS_NUM_MULTIPLIER) / 2.0));

        } else if (numClusters ==2){
            angle = angleBetween(cluster1Angle, cluster2Angle) <= 180 ? midAngleBetween(cluster1Angle, cluster2Angle) : midAngleBetween(cluster2Angle, cluster1Angle);
            size = 1 - cos(degreesToRadians(angleBetween(cluster1Angle, cluster2Angle) <= 180 ? angleBetween(cluster1Angle, cluster2Angle) / 2.0 : angleBetween(cluster2Angle, cluster1Angle) / 2.0));

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

void LightSensorArray::calculateLineData(float heading){
    // --- Calculate onField state and line angle and size --- //

    bool onLine = (angle != NO_LINE_ANGLE); // Determine if seeing line
    double lineAngle = !onLine ? -1 : doubleMod(angle + heading, 360); // If line visible find angle
    double lineSize = size; 

    if (lineInfo.onField){
        if (onLine){ 
            // Just seen line, change onField status and record angle
            lineInfo.onField = false;
            lineInfo.angle = lineAngle;
            lineInfo.size = lineSize;
        }
    } else { 
        // Off field, determine how to return
        if (lineInfo.size == 3){
            if (onLine){
                // Outside field but touching line
                lineInfo.angle = doubleMod(lineAngle + 180, 360);
                lineInfo.size = 2 - lineSize;
            }
        } else {
            //Somewhere on line, find what side
            if (!onLine){
                //No line but recently on
                if (lineInfo.size <= 1){
                    // Was inside line, returned to field
                    lineInfo.onField = true;
                    lineInfo.angle = -1;
                    lineInfo.size = 0;
                } else {
                    // Was outside line, now over
                    lineInfo.size = 3;
                }
            } else {
                // Still on line, decide what side
                if (smallestAngleBetween(lineInfo.angle, lineAngle) <= 90){
                    // Angles between 90 degrees, inside of field, save new angle
                    lineInfo.angle = lineAngle;
                    lineInfo.size = lineSize;
                } else {
                    // Angle changed by more than 90 degrees, outside of field, modify angle
                    lineInfo.angle = doubleMod(lineAngle + 180, 360);
                    lineInfo.size = 2 - lineSize;
                }
            }
        }
    }

    #if DEBUG_LINE_DATA
        Serial.print(lineInfo.angle);
        Serial.print("\t");
        Serial.println(lineInfo.size);
    #endif


}

MoveData LightSensorArray::calculateOutAvoidance(float heading, MoveData calcMove){
    // --- Calculate angle and speed to return to field --- //
    if (!lineInfo.onField){
        //Not on field, return
        if (lineInfo.size > LINE_SIZE_BIG){
            //Nearly off line, return
            calcMove.speed = lineInfo.size == 3 ? LINE_OVER_SPEED : lineInfo.size * LINE_SPEED; // Avoid line based on how far over
            calcMove.angle = mod(lineInfo.angle + 180 - heading, 360);                          // Mod angle by 180 to reverse direction to go back over line
        } else if (lineInfo.size > LINE_SIZE_SMALL && isOutsideLine(heading, calcMove.angle)){
            //Just touching line but orbit wants to go out, sit still
            calcMove.angle = -1;
            calcMove.speed = 0;
        }
    }

    return calcMove;
}


bool LightSensorArray::isOutsideLine(float heading, double angle){
    // --- Calculate if ball is outside off line based off line angle and current orbit --- //

    if (lineInfo.onField){
        // No line visible
        return false;
    }

    if (mod(lineInfo.angle, 90) > LINE_CORNER_ANGLE_THRESHOLD && mod(lineInfo.angle, 90) < 90 - LINE_CORNER_ANGLE_THRESHOLD){
        // If mod of angle greater than value line curves, must be corner
        // If orbit angle and line angle between 90 or 180 respectively must be trying to move out 
        return (angleIsInside(doubleMod(lineInfo.angle - 135 - LINE_BUFFER_CORNER, 360), doubleMod(lineInfo.angle + 135 + LINE_BUFFER_CORNER, 360), mod(angle + heading, 360)));
    } else {
        // On side
        return (angleIsInside(doubleMod(lineInfo.angle - 90 - LINE_BUFFER, 360), doubleMod(lineInfo.angle + 90 + LINE_BUFFER, 360), mod(angle + heading, 360)));
    }
}


