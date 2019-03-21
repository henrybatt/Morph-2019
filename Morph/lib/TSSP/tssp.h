#ifndef TSSP_H
#define TSSP_H

#include <Arduino.h>
#include <Common.h>

class Tssp
{
    public:
        tssp();
        void findValues();
        double getBallDir();
        double getBallStr();
        bool getBallVisible();

    

    private:
        void findAngle();
        void findStr();
        void read();
        void updateOnce();
        void filterTssps();
        void finishedRead();
        void findTssps();

        int tsspPins[TSSP_NUM] = {TSSP_PIN_0,TSSP_PIN_1,TSSP_PIN_2,TSSP_PIN_3,TSSP_PIN_4,TSSP_PIN_5,TSSP_PIN_6,TSSP_PIN_7,TSSP_PIN_8,TSSP_PIN_9,TSSP_PIN_10,TSSP_PIN_11,TSSP_PIN_12,TSSP_PIN_13,TSSP_PIN_14,TSSP_PIN_15,TSSP_PIN_16,TSSP_PIN_17}

}
