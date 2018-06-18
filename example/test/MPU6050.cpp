#include "MPU6050.h"
#include "Arduino.h"

MPU6050::MPU6050(TwoWire &w, float aC, float gC){
  wire = &w;  
  accCoef = aC;
  gyroCoef = gC;
}

byte MPU6050::readRegister(byte addr, byte reg) {
  wire->beginTransmission(addr);
  wire->write(reg);
  wire->endTransmission(true);
  wire->requestFrom((uint8_t)addr, (size_t)2);
  byte data =  wire->read();
  wire->read();
  return data;
}

void MPU6050::writeMPU6050(byte addr, byte reg, byte data){
  wire->beginTransmission(addr);
  wire->write(reg);
  wire->write(data);
  wire->endTransmission();
}

void MPU6050::begin(){
  writeMPU6050(MPU6050_ADDR, MPU6050_SMPLRT_DIV, 0x00);
  writeMPU6050(MPU6050_ADDR, MPU6050_CONFIG, 0x00);
  writeMPU6050(MPU6050_ADDR, MPU6050_GYRO_CONFIG, 0x08);
  writeMPU6050(MPU6050_ADDR, MPU6050_ACCEL_CONFIG, 0x00);
  writeMPU6050(MPU6050_ADDR, MPU6050_PWR_MGMT_1, 0x01);
}

int16_t MPU6050::read16bit(byte addr, byte startReg){
  wire->beginTransmission(addr);
  wire->write(startReg);
  wire->endTransmission(false);
  wire->requestFrom((int)addr, 2);
  
  return wire->read()<<8 | wire->read();
}

void MPU6050::offset(byte addr, byte startReg){
  int x = 0,y = 0,z = 0;
  for (int i = 0; i < 1000; i++){
    getAllData(addr, startReg);
    OS_AX += rawAccX;
    OS_AY += rawAccY;
    OS_AZ += rawAccZ;
    OS_X += rawGyroX;
    OS_Y += rawGyroY;
    OS_Z += rawGyroZ;
  }
  OS_AX = OS_AX/1000;
  OS_AY = OS_AY/1000;
  OS_AZ = OS_AZ/1000;
  OS_X = OS_X/1000;
  OS_Y = OS_Y/1000;
  OS_Z = OS_Z/1000;
}

void MPU6050::getAllData(byte addr, byte startReg){
  wire->beginTransmission(addr);
  wire->write(startReg);
  wire->endTransmission(false);
  wire->requestFrom((int)addr, 14);
  
  rawAccX = wire->read()<<8 | wire->read();
  rawAccY = wire->read()<<8 | wire->read();
  rawAccZ = wire->read()<<8 | wire->read();
  rawTemp = wire->read()<<8 | wire->read();
  rawGyroX = wire->read()<<8 | wire->read();
  rawGyroY = wire->read()<<8 | wire->read();
  rawGyroZ = wire->read()<<8 | wire->read();
}

