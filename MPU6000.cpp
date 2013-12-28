/*
 *           MPU-6000 Accelerometer + Gyroscope Library
 *                          SOURCE FILE
 */


#include "MPU6000.h"


mpu::mpu() {
  CS_PIN = 53;
  pinMode(CS_PIN, OUTPUT);
}

void mpu::init() {
  accx = 0;
  accy = 0;
  accz = 0;
  gyrx = 0;
  gyry = 0;
  gyrz = 0;
  temp = 0;

  // DEVICE_RESET @ PWR_MGMT_1, reset device
  mpu::write(0x6B,0x80);
  delay(150);
  // TEMP_DIS @ PWR_MGMT_1, wake device and select GyroZ clock
  mpu::write(0x6B,0x03);
  delay(150);
  // I2C_IF_DIS @ USER_CTRL, disable I2C interface
  mpu::write(0x6A,0x10);
  delay(150);
  // SMPRT_DIV @ SMPRT_DIV, sample rate at 1000Hz
  mpu::write(0x19,0x00);
  delay(150);
  // DLPF_CFG @ CONFIG, digital low pass filter at 42Hz
  mpu::write(0x1A,0x03);
  delay(150);
  // FS_SEL @ GYRO_CONFIG, gyro scale at 250dps
  mpu::write(0x1B,0x00);
  delay(150);
  // AFS_SEL @ ACCEL_CONFIG, accel scale at 2g (1g=8192)
  mpu::write(0x1C,0x00);
  delay(150);
}


uint8_t mpu::read( byte reg ) {
  uint8_t dump;
  uint8_t return_value;
  uint8_t addr = reg|0x80;

  digitalWrite(CS_PIN,LOW);
  dump = SPI.transfer(addr);
  return_value = SPI.transfer(0x00);
  digitalWrite(CS_PIN,HIGH);
  return(return_value);
}


void mpu::write( byte reg, byte data ) {
  uint8_t dump;
  digitalWrite(CS_PIN,LOW);
  dump = SPI.transfer(reg);
  dump = SPI.transfer(data);
  digitalWrite(CS_PIN,HIGH);
}


int16_t mpu::getAX() {
  uint8_t accx_msb = mpu::read( MPU6000_ACCX_MSB );
  uint8_t accx_lsb = mpu::read( MPU6000_ACCX_LSB );
  accx = accx_msb<<8|accx_lsb;
  return accx;
}

int16_t mpu::getAY() {
  uint8_t accy_msb = mpu::read( MPU6000_ACCY_MSB );
  uint8_t accy_lsb = mpu::read( MPU6000_ACCY_LSB );
  accy = accy_msb<<8|accy_lsb;
  return accy;
}

int16_t mpu::getAZ() {
  uint8_t accz_msb = mpu::read( MPU6000_ACCZ_MSB );
  uint8_t accz_lsb = mpu::read( MPU6000_ACCZ_LSB );
  accz = accz_msb<<8|accz_lsb;
  return accz;
}


int16_t mpu::getGX() { return gyrx; }
int16_t mpu::getGY() { return gyry; }
int16_t mpu::getGZ() { return gyrz; }

int16_t mpu::getTemp() { return temp; }
