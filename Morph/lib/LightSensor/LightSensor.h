#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>
#include <Common.h>
#include <Define.h>
#include <Pins.h>

class LightSensor {
    public:
        LightSensor();
        void init(int in);

        int read();
        bool onWhite();
        int getValue();
    private:
        int threshold,inPin,readVal;
};

#endif