#include <Camera.h>

void Camera::init(){
    cameraSerial.begin(9600);
}


void Camera::read(){
    if(cameraSerial.available() >= CAM_BUFFER_NUM) {
        if(cameraSerial.read() == CAM_START_NUM) {
            for (int i = 1; i <= CAM_BUFFER_NUM; i++){
                while (!cameraSerial.available());
                camBuffer[i] = cameraSerial.read();             
            }
            yangle = camBuffer[1];
            ydist = camBuffer[2];
            bangle = camBuffer[3];
            bdist = camBuffer[4];

            #if DEBUG_CAMERA
                Serial.print("Yellow Angle: ");
                Serial.print(yangle);
                Serial.print(", Yellow Dist: ");
                Serial.print(ydist);
                Serial.print(", Blue Angle: ");
                Serial.print(bangle);
                Serial.print(", Blue Dist: ");
                Serial.println(bdist);
            #endif
            

        }
    }
}