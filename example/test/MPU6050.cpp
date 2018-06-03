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
  wire->endTransmission(false);//TODO
  wire->requestFrom((int)addr, 2, true);//TODO
  
  return wire->read()<<8 | wire->read();
}

