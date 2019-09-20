#ifndef BLUETOOTHDATA_H
#define BLUETOOTHDATA_H

#include <Arduino.h>
#include <Common.h>
// #include <BallData.h>

struct BluetoothData{

    BallData ballData; // Ball Info 
    LineData lineData; // Line Info
    Mode playMode; // playMode
    uint16_t heading;

    BluetoothData(){
        ballData = BallData();
        lineData = LineData();
        playMode = Mode::undecided;
        heading = 0;
    }

    BluetoothData(BallData ballData, LineData lineData, Mode playMode, uint16_t heading) : ballData(ballData), lineData(lineData), playMode(playMode), heading(heading) {}
};



#endif