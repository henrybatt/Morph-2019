#include <Camera.h>

void Camera::init(){
    cameraSerial.begin(9600);
    newCamData = true;
    read();
}


void Camera::read(){
    if (cameraSerial.available() >= CAM_BUFFER_NUM) {
        if(cameraSerial.read() == CAM_START_NUM) {
            newCamData = true;
            for (int i = 0; i < CAM_BUFFER_NUM - 1; i++){
                while (!cameraSerial.available());
                camBuffer[i] = cameraSerial.read();
            }

            yellow = {.x = camBuffer[0], .y = camBuffer[1], .visible = camBuffer[4]};
            blue = {.x = camBuffer[2], .y = camBuffer[3], .visible = camBuffer[5]};

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


void Camera::calc() {

    blue.visible = false;

    #if ATTACK_GOAL_YELLOW
        calculateGoal(&attack, yellow, false);
        calculateGoal(&defend, blue, true);
    #else
        calculateGoal(&attack, blue, false);
        calculateGoal(&defend, yellow, true);
    #endif


    #if DEBUG_CAMERA
        Serial.print("Attack Angle: ");
        Serial.print(attack.angle);
        Serial.print(", Attack distance: ");
        Serial.print(attack.distance);
        Serial.print(", Attack visible: ");
        Serial.print(attack.visible);
        Serial.print(", Defend Angle: ");
        Serial.print(defend.angle);
        Serial.print(", Defend distance: ");
        Serial.print(defend.distance);
        Serial.print(", Defend visible: ");
        Serial.println(defend.visible);
    #endif
}


void Camera::calculateGoal(goalData *goal, camImage image, bool defend){
    *goal = {.angle = defend ? mod(calculateAngle(image) + 180, 360) : calculateAngle(image), 
    .distance = calculateDistance(image), .visible = image.visible, .face = goal->face};
}


int Camera::calculateAngle(camImage image){
    int x = image.x - (CAM_IMAGE_WIDTH / 2);
    int y = image.y - (CAM_IMAGE_HEIGHT / 2);

    return mod(450 - round(radiansToDegrees(atan2(y,x))), 360);
}


int Camera::calculateDistance(camImage image){
    int x = image.x - (CAM_IMAGE_WIDTH / 2);
    int y = image.y - (CAM_IMAGE_HEIGHT / 2);

    return sqrt(x * x + y * y);
}


bool Camera::newData(){
    bool data = newCamData;
    newCamData = false;

    return data;
}


void Camera::update(){
    read();
    if (newData()){
        calc();
    }
}


void Camera::goalTrack(){
    attack.face = attack.visible ? true : false; //Set as additional value to allow manual modification
    defend.face = defend.visible ? true : false;
}


double Camera::closestDistance(){
    if(attack.visible || defend.visible){
        if(!attack.visible){
            return defend.distance;
        } else if (!defend.visible){
            return attack.distance;
        } else {
            return min(attack.distance, defend.distance);
        }
    }
    return 0;
}


bool Camera::attackClosest(){
    return closestDistance() == attack.distance;
}