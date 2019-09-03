#include "bno055.h"
#include "Arduino.h"
#include "i2c_t3.h"

s8 bno055_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt){
    Wire.beginTransmission(dev_addr);	//Start of transmission
	Wire.write(reg_addr);				//Desired start register
	Wire.endTransmission();	            //Stop of transmission
	// delayMicroseconds(150);
	Wire.requestFrom(dev_addr, cnt);	//Request data
	while(Wire.available())				//The slave device may send less than requested
	{
		*reg_data = Wire.read();		//Receive a byte
		reg_data++;						//Increment pointer
	}
	return 0;
}

s8 bno055_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt){
	Wire.beginTransmission(dev_addr);	//Start of transmission
	Wire.write(reg_addr);				//Desired start register
	for(unsigned char index = 0; index < cnt; index++)
	{
		Wire.write(*reg_data);			//Write the data
		reg_data++;						//Increment pointer
	}
	Wire.endTransmission();	//Stop of transmission
	// delayMicroseconds(150);
	return 0;
}

void bno055_delay_ms(u32 ms){
    delay(ms);
}
