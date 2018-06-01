#include "MPU6050_tockn.h"
#include "Arduino.h"

MPU6050::MPU6050(TwoWire &w, float aC, float gC){
	wire = &w;	
	accCoef = aC;
	gyroCoef = gC;
}

void MPU6050::writeMPU6050(byte reg, byte data){
	wire->beginTransmission(MPU6050_ADDR);
	wire->write(reg);
	wire->write(data);
	wire->endTransmission();
}

void MPU6050::begin(){
	writeMPU6050(MPU6050_SMPLRT_DIV, 0x00);
	writeMPU6050(MPU6050_CONFIG, 0x00);
	writeMPU6050(MPU6050_GYRO_CONFIG, 0x08);
	writeMPU6050(MPU6050_ACCEL_CONFIG, 0x00);
	writeMPU6050(MPU6050_PWR_MGMT_1, 0x01);
	this->update();
	angleGyroX = this->getAccAngleX();
	angleGyroY = this->getAccAngleY();
	Serial.println("=================");
	Serial.println(accCoef);
	Serial.println(gyroCoef);
}

byte MPU6050::readMPU6050(byte reg) {
	wire->beginTransmission(MPU6050_ADDR);
	wire->write(reg);
	wire->endTransmission(true);
	wire->requestFrom((uint8_t)MPU6050_ADDR, (size_t)2);
	byte data =  wire->read();
	wire->read();
	return data;
}

void MPU6050::setGyroOffsets(float x, float y, float z){
	gyroXoffset = x;
	gyroYoffset = y;
	gyroZoffset = z;
}

//Процедура калибровки датчика
void MPU6050::calcGyroOffsets(bool console){
	float x = 0, y = 0, z = 0;
	const int COUNT_TEST_READ = 5000;
	int16_t rx, ry, rz;

	if(console){
		Serial.println("calculate gyro offsets");
		Serial.print("DO NOT MOVE A MPU6050");
	}
	for(int i = 0; i < COUNT_TEST_READ; i++){
		if(console && i % 1000 == 0){
			Serial.print(".");
		}
		wire->beginTransmission(MPU6050_ADDR);
		wire->write(0x3B);
		wire->endTransmission(false);
		wire->requestFrom((int)MPU6050_ADDR, 14, (int)true);

		wireRead();
		wireRead();
		wireRead();
		wireRead();
		rx = wireRead();
		ry = wireRead();
		rz = wireRead();

		x += ((float)rx) / 65.5;
		y += ((float)ry) / 65.5;
		z += ((float)rz) / 65.5;
	}

	setGyroOffsets(x / COUNT_TEST_READ, y / COUNT_TEST_READ, z / COUNT_TEST_READ);
	
	if(console){
		Serial.println("Done!!!");
		Serial.print("X : ");Serial.println(gyroXoffset);
		Serial.print("Y : ");Serial.println(gyroYoffset);
		Serial.print("Z : ");Serial.println(gyroZoffset);
		Serial.print("Program will start after 3 seconds");
		delay(3000);
	}
}

void MPU6050::update(){
	getDataFromSensor();
	
	gyroX = calcGyro(rawGyroX);
	gyroY = calcGyro(rawGyroY);
	gyroZ = calcGyro(rawGyroZ);

	accX = calcAcc(rawAccX);
	accY = calcAcc(rawAccY);
	accZ = calcAcc(rawAccZ);

	temp = (rawTemp + 12412.0) / 340.0;

	angleAccX = atan2(accY, accZ + abs(accX)) * 360 / 2.0 / PI;
	angleAccY = atan2(accX, accZ + abs(accY)) * 360 / -2.0 / PI;

	gyroX -= gyroXoffset;
	gyroY -= gyroYoffset;
	gyroZ -= gyroZoffset;
	
	interval = millis() - preInterval;
	angleGyroX += calcAngleGyro(gyroX, interval);
	angleGyroY += calcAngleGyro(gyroY, interval);
	angleGyroZ += calcAngleGyro(gyroZ, interval);
	preInterval = millis();

	angleX = (gyroCoef * angleGyroX) + (accCoef * angleAccX);
	angleY = (gyroCoef * angleGyroY) + (accCoef * angleAccY);
	angleZ = angleGyroZ;
}

void MPU6050::getDataFromSensor(){
	wire->beginTransmission(MPU6050_ADDR);
	wire->write(0x3B);
	wire->endTransmission(false);
	wire->requestFrom((int)MPU6050_ADDR, 14, (int)true);
	
	rawAccX = wireRead();
	rawAccY = wireRead();
	rawAccZ = wireRead();
	rawTemp = wireRead();
	rawGyroX = wireRead();
	rawGyroY = wireRead();
	rawGyroZ = wireRead();
}

float MPU6050::calcAcc(float rawAcc){ return ((float)rawAcc) / 16384.0; }
float MPU6050::calcGyro(float rawGyro){ return ((float)rawGyro) / 65.5; }
float MPU6050::calcAngleGyro(float gyro, long interval){ return gyro * (interval * 0.001); }
int16_t MPU6050::wireRead(){return wire->read() << 8 | wire->read(); }