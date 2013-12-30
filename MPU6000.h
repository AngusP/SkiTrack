/*
 *           MPU-6000 Accelerometer + Gyroscope Library
 *                            HEADER
 */


#include "Arduino.h"
#include <SPI.h>

/*
  NOTE:
  MPU6000 Chip Select is on PB0 SS (Digital 53)
  MISO and MOSI are connected normally through the TXB0104
*/

#define MPU6000_ACCX_MSB 0x3B
#define MPU6000_ACCX_LSB 0x3C
#define MPU6000_ACCY_MSB 0x3D
#define MPU6000_ACCY_LSB 0x3E
#define MPU6000_ACCZ_MSB 0x3F
#define MPU6000_ACCZ_LSB 0x40

#define MPU6000_GYRX_MSB 0x43
#define MPU6000_GYRX_LSB 0x44
#define MPU6000_GYRY_MSB 0x45
#define MPU6000_GYRY_LSB 0x46
#define MPU6000_GYRZ_MSB 0x47
#define MPU6000_GYRZ_LSB 0x48

#define MPU6000_TEMP_MSB 0x41
#define MPU6000_TEMP_LSB 0x42


class mpu {
  
  public:
    mpu();
    void init();
    void read();
    uint8_t readReg( byte reg );
    void write( byte reg, byte data );
    void stream();
    void packet();

    int16_t getAX();
    int16_t getAY();
    int16_t getAZ();

    int16_t getGX();
    int16_t getGY();
    int16_t getGZ();

    int16_t getTemp();
    
  private:
    int CS_PIN;
    
    int16_t accx;
    int16_t accy;
    int16_t accz;
    
    int16_t gyrx;
    int16_t gyry;
    int16_t gyrz;
    
    int16_t temp;
};
