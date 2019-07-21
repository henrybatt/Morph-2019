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


void Camera::calc(int heading) {
    read();
    // Calculates goal angle and length 
    yellow.angle = mod(450 - round(degrees(atan2(yellow.y, yellow.x))), 360);
    yellow.length = (sqrt(pow(yellow.x, 2) + pow(yellow.y, 2)));

    blue.angle = mod(450 - round(degrees(atan2(blue.y, blue.x))), 360);
    blue.length = (sqrt(pow(blue.x, 2) + pow(blue.y, 2)));

    attackAngle = ATTACK_GOAL_YELLOW ? mod(yellow.angle + heading, 360) : mod(blue.angle + heading, 360);
    defendAngle = ATTACK_GOAL_YELLOW ? mod(blue.angle + heading, 360) : mod(yellow.angle + heading, 360);


#if DEBUG_CAMERA
        Serial.print("Yellow Angle: ");
        Serial.print(yellow.angle);
        Serial.print(", Yellow Length: ");
        Serial.print(yellow.length);
        Serial.print(", Blue Angle: ");
        Serial.print(blue.angle);
        Serial.print(", Blue Length: ");
        Serial.println(blue.length);
    #endif
}

bool Camera::attackVisible(){
    return ATTACK_GOAL_YELLOW ? yellow.exist : blue.exist;
}

bool Camera::defendVisible(){
    return ATTACK_GOAL_YELLOW ? blue.exist : yellow.exist;
}

bool Camera::goalVisible(){
    return attackVisible() || defendVisible();
}

void Camera::goalTrack(){
    if (attackVisible()){
        facingGoal = true;
    } else {
        facingGoal = false;
    }
}
