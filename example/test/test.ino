#include <Wire.h>
#include "MPU6050.h"

MPU6050 mpu6050(Wire);

long timer = 0;
float test = 0;

void setup(){
 Serial.begin(9600);
 Wire.begin();
 mpu6050.begin();
 Serial.print("Gyro conf: ");
 Serial.println((String)mpu6050.readRegister(0x68, 0x1b));
 Serial.print("Acce conf: ");
 Serial.println((String)mpu6050.readRegister(0x68, 0x1c));
 mpu6050.offset(0x68,0x3b);
 Serial.println("Gyro & Accel Offsets:");
 Serial.print("GX: "); Serial.print(mpu6050.OS_X);
 Serial.print("\tGY: "); Serial.print(mpu6050.OS_Y);
 Serial.print("\tGZ: "); Serial.print(mpu6050.OS_Z);
 Serial.print("\tAX: "); Serial.print(mpu6050.OS_AX);
 Serial.print("\tAY: "); Serial.print(mpu6050.OS_AY);
 Serial.print("\tAZ: "); Serial.println(mpu6050.OS_AZ);
}
void loop(){
  
 if (millis() - timer > 1000){
    mpu6050.getAllData(0x68, 0x3b);
    Serial.print(mpu6050.rawGyroX);
    Serial.print(" : ");
    test = (mpu6050.rawGyroX/65.5-mpu6050.OS_X)*1/1000;
    Serial.println(test);
//    Serial.print(" : ");
//  Serial.println((int)mpu6050.readData(0x68,0x75));
//  Serial.print((int)mpu6050.readData(0x68,0x3b));
//  Serial.print(" : ");
//  Serial.print(mpu6050.rawAccY);
//  Serial.print(" : ");
//  Serial.print(mpu6050.rawAccZ);
//  Serial.print(" : ");
//  Serial.print(mpu6050.rawTemp);
//  Serial.print(" : ");
//  Serial.print(mpu6050.rawGyroX);
//  Serial.print(" : ");
//  Serial.print(mpu6050.rawGyroY);
//  Serial.print(" : ");
//  Serial.println(mpu6050.rawGyroZ);
  timer = millis();
 }
}
