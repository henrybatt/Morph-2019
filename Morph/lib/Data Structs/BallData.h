#ifndef BALLDATA_H
#define BALLDATA_H


struct BallData{
    uint16_t angle;
    uint16_t strength;
    bool exist;
    bool isOut;

    BallData() {
        angle = TSSP_NO_BALL;
        strength = 0;
    }

    BallData(uint16_t angle, uint16_t strength, bool exist, bool isOut) : angle(angle), strength(strength), exist(exist), isOut(isOut) {}
};

extern BallData ballInfo;

#endif