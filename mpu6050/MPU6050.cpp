#include "MPU6050.h"
#include "Arduino.h"

MPU6050::MPU6050(TwoWire &w, float aC, float gC){
	wire = &w;	
	accCoef = aC;
	gyroCoef = gC;
}

int16_t MPU6050::wireRead(){return wire->read() << 8 | wire->read(); }