#ifndef myMPU6050
#define myMPU6050

#include "Arduino.h"
#include "Wire.h"

#define MPU6050_ADDR         0x68
#define MPU6050_SMPLRT_DIV   0x19
#define MPU6050_CONFIG       0x1a
#define MPU6050_GYRO_CONFIG  0x1b
#define MPU6050_ACCEL_CONFIG 0x1c
#define MPU6050_WHO_AM_I     0x75
#define MPU6050_PWR_MGMT_1   0x6b
#define MPU6050_TEMP_H       0x41
#define MPU6050_TEMP_L       0x42
#define MPU6050_data_start   0x3b

class MPU6050{
  public:
    MPU6050(TwoWire &w, float aC = 0.02f, float gC = 0.98f);
    
    byte readRegister(byte addr, byte reg);
    void writeMPU6050(byte addr, byte reg, byte data);
    int16_t read16bit(byte addr, byte reg);

    int16_t test1,test2;
    
    void begin();
  private:
    TwoWire *wire;
    float accCoef, gyroCoef;
    int16_t rawAccX, rawAccY, rawAccZ, rawTemp, rawGyroX, rawGyroY, rawGyroZ;
    
};
#endif

