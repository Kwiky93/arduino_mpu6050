#include <Wire.h>
#include "MPU6050.h"

MPU6050 mpu6050(Wire);

long timer = 0;

void setup(){
 Serial.begin(9600);
 Wire.begin();
}
void loop(){
 if (millis() - timer > 1000){
  
  Serial.println((int)mpu6050.readData(0x68,0x75));
  timer = millis();
 }
}
