#include <Camera.h>

void Camera::init(){
    cameraSerial.begin(9600);
}


void Camera::read(){
    if (cameraSerial.available() >= CAM_BUFFER_NUM) {
        if(cameraSerial.read() == CAM_START_NUM) {
            for (int i = 0; i < CAM_BUFFER_NUM - 1; i++){
                while (!cameraSerial.available());
                camBuffer[i] = cameraSerial.read();
            }

            yellow.x = camBuffer[0] - CAM_IMAGE_WIDTH/2;
            yellow.y = camBuffer[1] - CAM_IMAGE_WIDTH / 2;
            yellow.exist = camBuffer[4];

            blue.x = camBuffer[2] - CAM_IMAGE_WIDTH / 2;
            blue.y = camBuffer[3] - CAM_IMAGE_WIDTH / 2;
            blue.exist = camBuffer[5];  

            #if DEBUG_CAMERA_RAW  
                Serial.print("Yellow: ");
                Serial.print(yellow.x);
                Serial.print(" , ");
                Serial.print(yellow.y);
                Serial.print(" Blue: ");
                Serial.print(blue.x);
                Serial.print(" , ");
                Serial.println(blue.y);
            #endif   

        }
    }
}

void Camera::updateAttack(int angle, int length, bool exist){
    attack.angle = angle;
    attack.length = length;
    attack.exist = exist;
}

void Camera::updateDefend(int angle, int length, bool exist){
    defend.angle = angle;
    defend.length = length;
    defend.exist = exist;
}

void Camera::calc() {
    // Calculates goal angle and length 
    yellow.angle = mod(450 - round(degrees(atan2(yellow.y, yellow.x))), 360);
    yellow.length = (sqrt(pow(yellow.x, 2) + pow(yellow.y, 2)));

    blue.angle = mod(450 - round(degrees(atan2(blue.y, blue.x))), 360);
    blue.length = (sqrt(pow(blue.x, 2) + pow(blue.y, 2)));

    #if DEBUG_CAMERA
            Serial.print("Yellow Angle: ");
            Serial.print(yellow.angle);
            Serial.print(", Yellow Length: ");
            Serial.print(yellow.length);
            Serial.print(", Yellow Exist: ");
            Serial.print(yellow.exist);
            Serial.print(", Blue Angle: ");
            Serial.print(blue.angle);
            Serial.print(", Blue Length: ");
            Serial.print(blue.length);
            Serial.print(", Blue Exist: ");
            Serial.println(blue.exist);
        #endif
    }

void Camera::update(){
    read();
    calc();

    #if ATTACK_GOAL_YELLOW
        updateAttack(yellow.angle, yellow.length, yellow.exist);
        updateDefend(blue.angle, blue.length, blue.exist);
    #else
        updateAttack(blue.angle, blue.length, blue.exist);
        updateDefend(yellow.angle, yellow.length, yellow.exist);
    #endif
}

void Camera::goalTrack(){
    if (attack.exist){
        faceGoal = true;
    } else {
        faceGoal = false;
    }
}
