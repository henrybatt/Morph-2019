#include <LightArrayVector.h>

void LightArrayVector::init() {
    // Setup pinmode for each MUX
    for (int i = 0; i < 4; i++){
        pinMode(controller1[i], OUTPUT);
        pinMode(controller2[i], OUTPUT);
    }
    pinMode(MUX_A_OUT, INPUT);
    pinMode(MUX_B_OUT, INPUT);

    calibrate();
}

void LightArrayVector::calibrate() {
    // Read each sensor and save green values
    for (int i = 0; i < LS_NUM; i++) {
        int defaultValue = 0;

        for (int j = 0; j < LS_CALIBRATION_COUNT; j++) {
            defaultValue += readSensor(i);
        }
        thresholds[i] = round((defaultValue / (double)LS_CALIBRATION_COUNT) + LS_CALIBRATION_BUFFER);
	}
}

int LightArrayVector::readSensor(int sensor){
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

void LightArrayVector::update(){
    // --- Read light sensors and determine if line is visible --- //

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
        // Print onWhite State
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

    calcVectorAngle(); // Calculate Line Angle
}

void LightArrayVector::calcVectorAngle(){
    // --- Calculate VectorAngle on line --- //

    // Reset Variables
    bool active = 0;
    vectorX = 0;
    vectorY = 0;

    for (int i = 0; i < LS_NUM; i++){
        if (onWhite[i]){
            // If light sensor detects line add vector coords 
            active = 1;
            vectorX += sin(degreesToRadians(450 - i * LS_NUM_MULTIPLIER));
            vectorY += cos(degreesToRadians(450 - i * LS_NUM_MULTIPLIER));
        }
    }

    // Convert coords into angle if line visible
    vectorAngle = active ? mod(radiansToDegrees(atan2(vectorY, vectorX)), 360) : NO_LINE_ANGLE;

}

