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

            yellow.x = camBuffer[0] - (CAM_IMAGE_WIDTH  / 2);
            yellow.y = camBuffer[1] - (CAM_IMAGE_HEIGHT / 2);
            yellow.exist = camBuffer[4];

            blue.x = camBuffer[2] - (CAM_IMAGE_WIDTH / 2);
            blue.y = camBuffer[3] - (CAM_IMAGE_HEIGHT / 2);
            blue.exist = camBuffer[5];  

        }
    }

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

void Camera::updateAttack(int angle, int distance, bool exist, double cm){
    attack.angle = angle;
    attack.distance = distance;
    attack.exist = exist;
    attack.cm = cm;
}

void Camera::updateDefend(int angle, int distance, bool exist, double cm){
    defend.angle = mod(angle + 180, 36);
    defend.distance = distance;
    defend.exist = exist;
    defend.cm = cm;
}

void Camera::calc() {
    // Calculates goal angle and distance 
    yellow.angle = mod(450 - round(degrees(atan2(yellow.y, yellow.x))), 360);
    yellow.distance = (sqrt(pow(yellow.x, 2) + pow(yellow.y, 2)));

    blue.angle = mod(450 - round(degrees(atan2(blue.y, blue.x))), 360);
    blue.distance = (sqrt(pow(blue.x, 2) + pow(blue.y, 2)));

    yellow.cm = centimeterDistance(yellow.distance);
    blue.cm = centimeterDistance(blue.distance);

    #if DEBUG_CAMERA
            Serial.print("Yellow Angle: ");
            Serial.print(yellow.angle);
            Serial.print(", Yellow distance: ");
            Serial.print(yellow.distance);
            Serial.print(", Yellow Exist: ");
            Serial.print(yellow.exist);
            Serial.print(", Blue Angle: ");
            Serial.print(blue.angle);
            Serial.print(", Blue distance: ");
            Serial.print(blue.distance);
            Serial.print(", Blue Exist: ");
            Serial.println(blue.exist);
        #endif
    }

void Camera::update(){
    read();
    blue.exist = false;
    calc();

    #if ATTACK_GOAL_YELLOW
        updateAttack(yellow.angle, yellow.distance, yellow.exist, yellow.cm);
        updateDefend(blue.angle, blue.distance, blue.exist, blue.cm);
    #else
        updateAttack(blue.angle, blue.distance, blue.exist, blue.cm);
        updateDefend(yellow.angle, yellow.distance, yellow.exist, yellow.cm);
    #endif
}

void Camera::goalTrack(){
    if (attack.exist){
        faceGoal = true;
    } else {
        faceGoal = false;
    }
}

double Camera::centimeterDistance(double pixelDistance) {
    return 8.205 * pow(MATH_E, 0.037 * pixelDistance);
}

double Camera::closestDistance(){
    if(yellow.exist || blue.exist){
        if(!yellow.exist){
            return blue.cm;
        } else if (!blue.exist){
            return yellow.cm;
        } else {
            return min(yellow.cm, blue.cm);
        }
    }
    return 0;
}

