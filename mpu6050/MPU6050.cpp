#include "MPU6050.h"
#include "Arduino.h"

MPU6050::MPU6050(TwoWire &w, float aC, float gC){
	wire = &w;	
	accCoef = aC;
	gyroCoef = gC;
}

byte MPU6050::readData(byte addr, byte reg) {
	wire->beginTransmission(addr);
	wire->write(reg);
	wire->endTransmission(true);
	wire->requestFrom((uint8_t)addr, (size_t)2);
	byte data =  wire->read();
	wire->read();
	return data;
}

int16_t MPU6050::wireRead(){return wire->read() << 8 | wire->read(); }