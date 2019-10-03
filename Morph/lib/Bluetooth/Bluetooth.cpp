#include <Bluetooth.h>

void Bluetooth::init(){
    BTSerial.begin(BT_BAUD);
}

void Bluetooth::update(BluetoothData data){

    thisData = data;

    send();

    recieve();

}


void Bluetooth::send(){

    // Starting Byte
    BTSerial.write(BT_START_BYTE);

    // Ball Angle
    BTSerial.write(highByte(thisData.ballData.angle));
    BTSerial.write(lowByte(thisData.ballData.angle));

    // Ball Strength
    BTSerial.write(highByte(thisData.ballData.strength));
    BTSerial.write(lowByte(thisData.ballData.strength));

    // Ball Out
    BTSerial.write(thisData.ballData.isOut);

    // OnField
    BTSerial.write(thisData.lineData.onField);

    // PlayMode
    BTSerial.write(thisData.playMode);

    // Heading
    BTSerial.write(highByte(thisData.heading));
    BTSerial.write(lowByte(thisData.heading));

    // Robot Position
    BTSerial.write(highByte(round(thisData.robotPosition.i)));
    BTSerial.write(lowByte(round(thisData.robotPosition.i)));

    BTSerial.write(highByte(round(thisData.robotPosition.j)));
    BTSerial.write(lowByte(round(thisData.robotPosition.j)));

}

void Bluetooth::recieve(){

    while (BTSerial.available() >= BT_PACKET_SIZE){

        if (BTSerial.read() == BT_START_BYTE){
            uint8_t bluetoothBuffer[BT_PACKET_SIZE - 1];

            for (int i = 0; i < BT_PACKET_SIZE - 1; i++){
                bluetoothBuffer[i] = BTSerial.read();
            }

            disconnectTimer.update();

            otherData.ballData = BallData((bluetoothBuffer[0] << 8) | bluetoothBuffer[1], (bluetoothBuffer[2] << 8) | bluetoothBuffer[3], bluetoothBuffer[4]);
            otherData.lineData = LineData(-1, 0, bluetoothBuffer[5]);
            otherData.playMode = static_cast<Mode>(bluetoothBuffer[6]);
            otherData.heading = (bluetoothBuffer[7] << 8 | bluetoothBuffer[8]);
            otherData.robotPosition = Vector((bluetoothBuffer[9] << 8 | bluetoothBuffer[10]), (bluetoothBuffer[11] << 8 | bluetoothBuffer[12]));


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