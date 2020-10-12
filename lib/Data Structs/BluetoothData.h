#ifndef BLUETOOTHDATA_H
#define BLUETOOTHDATA_H

#include <Arduino.h>
#include <Common.h>
#include <BallData.h>
#include <LineData.h>
#include <Mode.h>
#include <Vector.h>


struct BluetoothData{

    BallData ballData; // Ball Info 
    LineData lineData; // Line Info
    Mode playMode; // playMode
    uint16_t heading; // IMU Heading
    Vector robotPosition; // Cartesian Robot Coords
    int defendDistance;

    BluetoothData(){
        ballData = BallData();
        lineData = LineData();
        playMode = Mode::undecided;
        heading = 0;
        robotPosition = Vector(0,0);
        defendDistance = 0;
    }

    BluetoothData(BallData ballData, LineData lineData, Mode playMode, uint16_t heading, Vector robotPosition, int defendDistance) : ballData(ballData), lineData(lineData), playMode(playMode), heading(heading), robotPosition(robotPosition), defendDistance(defendDistance){}
};



#endif