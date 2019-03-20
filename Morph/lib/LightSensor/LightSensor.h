#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>
#include <Common.h>
#include <Define.h>

class LightSensor {
    public:
        LightSensor();
        void lightSensorSetup(int in);
        void setThresh(int thresh);
        int read();
        bool onWhite();
    private:
        int threshold,inPin,readVal;
};

#endif