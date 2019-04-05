#ifndef TSSP_H
#define TSSP_H

#include <Arduino.h>
#include <Common.h>
#include <Define.h>
#include <Debug.h>
#include <Math.h>

class Tssp{
    public:
        void init();
        void updateOnce();
        void finishRead();
        void sortValues();
        void calculateAngleStrength(uint8_t n);

        uint16_t getAngle();
        uint16_t getStrength();

        uint16_t values[TSSP_NUM] = {0};
        uint16_t sortedValues[TSSP_NUM] = {0};
        uint8_t indexes[TSSP_NUM] = {0};
        uint16_t tsspCounter = 0;

      private:
        uint16_t tempValues[TSSP_NUM] = {0};

        uint16_t angle = 0;
        uint16_t strength = 0;
        double scaledSin[TSSP_NUM] = {0};
        double scaledCos[TSSP_NUM] = {0};

        // int tsspPins[TSSP_NUM] = {TSSP_PIN_0, TSSP_PIN_1, TSSP_PIN_2, TSSP_PIN_3, TSSP_PIN_4, TSSP_PIN_5, TSSP_PIN_6, TSSP_PIN_7, TSSP_PIN_8, TSSP_PIN_9, TSSP_PIN_10, TSSP_PIN_11, TSSP_PIN_12, TSSP_PIN_13, TSSP_PIN_14, TSSP_PIN_15, TSSP_PIN_16, TSSP_PIN_17} int tsspPins[TSSP_NUM] = {TSSP_PIN_0, TSSP_PIN_1, TSSP_PIN_2, TSSP_PIN_3, TSSP_PIN_4, TSSP_PIN_5, TSSP_PIN_6, TSSP_PIN_7, TSSP_PIN_8, TSSP_PIN_9, TSSP_PIN_10, TSSP_PIN_11, TSSP_PIN_12, TSSP_PIN_13, TSSP_PIN_14, TSSP_PIN_15, TSSP_PIN_16, TSSP_PIN_17} 
        int tsspPins[TSSP_NUM] = {TSOP_PIN_0, TSOP_PIN_1, TSOP_PIN_2, TSOP_PIN_3, TSOP_PIN_4, TSOP_PIN_5, TSOP_PIN_6, TSOP_PIN_7, TSOP_PIN_8, TSOP_PIN_9, TSOP_PIN_10, TSOP_PIN_11};
};

#endif