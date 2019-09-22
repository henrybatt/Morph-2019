#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <Common.h>
#include <Timer.h>
#include <BluetoothData.h>

class Bluetooth{

    public:
        void init();
        void update(BluetoothData data);

        bool isConnected;
        bool previouslyConnected;

        BluetoothData otherData = BluetoothData();

    private:

        void send();
        void recieve();

        BluetoothData thisData = BluetoothData();

        Timer disconnectTimer = Timer(BLUETOOTH_DISCONNECT_TIME);
        Timer sendTimer = Timer(BLUETOOTH_UPDATE_TIME);

};



#endif