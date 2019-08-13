#ifndef ROLE_H
#define ROLE_H

#include "Arduino.h"
#include <MotorController.h>
#include <Motors.h>
#include <Tssp.h>

class Role {
public:
    void init();
    void attack(int cor, int bangle, int bdist);
    void defend(int cor, int bangle, int bdist, int bcor, int goaldist, int goalangle);
private:
    void defenderCalc(int bangle, int bdist, int goaldist, int goalangle);
    void attackerCalc(int bangle, int bdist);
    MotorController Motor;
    Compass compass;
    int mvspeed = 100;
    int moveangle;
};

#endif