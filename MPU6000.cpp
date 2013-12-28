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


void mpu::read() {
  uint8_t reg_msb, reg_lsb;
  
  /* Accelerometer: */
  reg_msb = mpu::readReg( MPU6000_ACCX_MSB );
  reg_lsb = mpu::readReg( MPU6000_ACCX_LSB );
  accx = reg_msb<<8|reg_lsb;

  reg_msb = mpu::readReg( MPU6000_ACCY_MSB );
  reg_lsb = mpu::readReg( MPU6000_ACCY_LSB );
  accy = reg_msb<<8|reg_lsb;

  reg_msb = mpu::readReg( MPU6000_ACCZ_MSB );
  reg_lsb = mpu::readReg( MPU6000_ACCZ_LSB );
  accz = reg_msb<<8|reg_lsb;

  /* Gyroscope: */
  reg_msb = mpu::readReg( MPU6000_GYRX_MSB );
  reg_lsb = mpu::readReg( MPU6000_GYRX_LSB );
  gyrx = reg_msb<<8|reg_lsb;

  reg_msb = mpu::readReg( MPU6000_GYRY_MSB );
  reg_lsb = mpu::readReg( MPU6000_GYRY_LSB );
  gyry = reg_msb<<8|reg_lsb;

  reg_msb = mpu::readReg( MPU6000_GYRZ_MSB );
  reg_lsb = mpu::readReg( MPU6000_GYRZ_LSB );
  gyrz = reg_msb<<8|reg_lsb;

  /* Thermometer: */
  reg_msb = mpu::readReg( MPU6000_TEMP_MSB );
  reg_lsb = mpu::readReg( MPU6000_TEMP_LSB );
  temp = reg_msb<<8|reg_lsb;
}


uint8_t mpu::readReg( byte reg ) {
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


void mpu::packet() {
  Serial.print("$MPUAG,");
  Serial.print(mpu::getAX());
  Serial.print(",");
  Serial.print(mpu::getAY());
  Serial.print(",");
  Serial.print(mpu::getAZ());
  Serial.print(",");
  Serial.print(mpu::getGX());
  Serial.print(",");
  Serial.print(mpu::getGY());
  Serial.print(",");
  Serial.print(mpu::getGZ());
  Serial.print(",");
  Serial.print(mpu::getTemp());
  Serial.print("\r\n");
}


int16_t mpu::getAX() { return accx; }
int16_t mpu::getAY() { return accy; }
int16_t mpu::getAZ() { return accz; }

int16_t mpu::getGX() { return gyrx; }
int16_t mpu::getGY() { return gyry; }
int16_t mpu::getGZ() { return gyrz; }

int16_t mpu::getTemp() { return temp; }
