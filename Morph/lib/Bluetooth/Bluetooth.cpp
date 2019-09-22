#include <Bluetooth.h>

void Bluetooth::init(){
    bluetoothSerial.begin(BLUETOOTH_BAUD);
}

void Bluetooth::update(BluetoothData data){

    thisData = data;

    if (sendTimer.timeHasPassed()){
        send();
    }

    recieve();

}


void Bluetooth::send(){

    // Starting Byte
    bluetoothSerial.write(BLUETOOTH_START_BYTE);

    // Ball Angle
    bluetoothSerial.write(highByte(thisData.ballData.angle));
    bluetoothSerial.write(lowByte(thisData.ballData.angle));

    // Ball Strength
    bluetoothSerial.write(highByte(thisData.ballData.strength));
    bluetoothSerial.write(lowByte(thisData.ballData.strength));

    // Ball Out
    bluetoothSerial.write(thisData.ballData.isOut);

    // OnField
    bluetoothSerial.write(thisData.lineData.onField);

    // PlayMode
    bluetoothSerial.write(thisData.playMode);

    // Heading
    bluetoothSerial.write(highByte(thisData.heading));
    bluetoothSerial.write(lowByte(thisData.heading));

    // Robot Position
    bluetoothSerial.write(highByte(round(thisData.robotPosition.i)));
    bluetoothSerial.write(lowByte(round(thisData.robotPosition.j)));


}

void Bluetooth::recieve(){

    while (bluetoothSerial.available() >= BLUETOOTH_PACKET_SIZE){
        uint8_t firstByte = bluetoothSerial.read();

        if (firstByte == BLUETOOTH_START_BYTE){
            uint8_t bluetoothBuffer[BLUETOOTH_PACKET_SIZE - 1];

            for (int i = 0; i < BLUETOOTH_PACKET_SIZE - 1; i++){
                bluetoothBuffer[i] = bluetoothSerial.read();
            }

            disconnectTimer.update();

            otherData.ballData = BallData((bluetoothBuffer[0] << 8) | bluetoothBuffer[1], (bluetoothBuffer[2] << 8) | bluetoothBuffer[3], bluetoothBuffer[4]);
            otherData.lineData = LineData(-1, 0, bluetoothBuffer[5]);
            otherData.playMode = static_cast<Mode>(bluetoothBuffer[6]);
            otherData.heading = (bluetoothBuffer[7] << 8 | bluetoothBuffer[8]);


        }
    }

    isConnected = !disconnectTimer.timeHasPassedNoUpdate();

    if (isConnected){
        if (!previouslyConnected){
            previouslyConnected = true;
        }
    } else {
        otherData = BluetoothData();
    }
   
}