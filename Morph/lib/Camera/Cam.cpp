#include <Cam.h>
#include <Define.h>

// Camera library, by Matt Young
// format: 0xB, bfound, bx, by, yfound, yx, yy, ox, oy, ofound, 0xE (11 bytes total)

void Camera::setup(){
    CAM_SERIAL.begin(115200);
    lastCall = millis();
}

void Camera::read(){
    // Read raw data from OpenMV over serial
    memset(buf, -1, sizeof(buf));

    // TODO remove 20ms wait? or shorten it? ask FG&B
    if (/*millis() - lastCall >= 20 && */CAM_SERIAL.available() >= CAM_DATA_LENGTH){
        // Serial.println(CAM_SERIAL.peek());
        if (CAM_SERIAL.read() == CAM_BEGIN_BYTE && CAM_SERIAL.peek() == CAM_BEGIN_BYTE){
            // Serial.println("Found start byte");
            // force wait for the rest of the data to come in, then read it into the buffer
            for (int i = 0; i < CAM_DATA_LENGTH; i++){
                while(!CAM_SERIAL.available());
                buf[i] = CAM_SERIAL.read();
            }

            // if(buf[CAM_DATA_LENGTH] == CAM_END_BYTE){
                blue.exists = buf[1];
                blue.x = buf[2] - CAM_CENTRE_X;
                blue.y = buf[3] - CAM_CENTRE_Y;

                yellow.exists = buf[4];
                yellow.x = buf[5] - CAM_CENTRE_X;
                yellow.y = buf[6] - CAM_CENTRE_Y;

                lastCall = millis();
            // }
            // for(int i = 0; i < CAM_DATA_LENGTH; i++){
            //     Serial.print(buf[i]);
            //     Serial.print(" ");
            // }
            // Serial.println();
        }
    }
}

void Camera::calc(){
    // calculate goaldir and goallength
    blue.angle = doubleMod(450 - roundf(TO_DEGREES * atan2f(blue.y, blue.x)), 360);
    blue.length = sqrtf(sq(blue.x) + sq(blue.y));

    yellow.angle = doubleMod(450 - roundf(TO_DEGREES * atan2f(yellow.y, yellow.x)), 360);
    yellow.length = sqrtf(sq(yellow.x) + sq(yellow.y));
}