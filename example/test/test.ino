#include <Wire.h>
#include "MPU6050.h"

MPU6050 mpu6050(Wire);

long timer = 0;

void setup(){
 Serial.begin(9600);
 Wire.begin();
 mpu6050.begin();
}
void loop(){
 if (millis() - timer > 1000){
  
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
