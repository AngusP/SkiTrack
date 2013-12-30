/**
 * 
 *   A P M    2    S K I    T R A C K E R
 *
 *   Kinda stupid but why not
 *
**/

/*
The other sensors (in addition to the GPS) output NMEA style information.
HMC5883L Magnetometer:              $MAGNT,mx,my,mz
MPU6000 Accel. & Gyro:              $MPUAG,ax,ay,az,gx,gy,gz,t
MS5611 Barometer & Thermometer:     $BAROT,p,t
MS5611 Calibration constants:       $BARCS,C1,C2,C3,C4,C5,C6

They also have a Hex based serial stream:
HMC5883L Magnetometer:              0x40
MPU6000 Accel. & Gyro               0x41
MS5611 Barometer & Thermometer:     0x42

Stream is delimited by 0x00 nstead of ','
*/

/* C, B, A LED pins: */
const int cled = 25;
const int bled = 26;
const int aled = 27;
bool cstate = 0;
bool bstate = 0;
bool astate = 0;


#include <Wire.h>
#include <SPI.h>
#include "HMC5883L.h"
#include "MPU6000.h"
#include "MS5611.h"
#include "MT3329.h"

hmc mag = hmc();
mpu mpu;
ms56 baro = ms56(40);
mt33 gps = mt33();

long mx;
long my;
long mz;
 
void setup() {
  
  SPI.begin();
  SPI.setClockDivider( SPI_CLOCK_DIV16 ); //1 MHz
  delay(5);
  SPI.setBitOrder(MSBFIRST);

  /* Baud higher than MT3329 rate */
  Serial.begin(115200);
  
  mag.init();
  mpu.init();
  baro.init();
  gps.init();
  
  /* Output frequency in Hz {1,4,10} */
  gps.rate(4);

  /* Notification LEDs */
  pinMode(cled, OUTPUT);
  pinMode(bled, OUTPUT);
  pinMode(aled, OUTPUT);

  baro.reset();
  delay(20);

  digitalWrite(cled, LOW);
  
  baro.printConsts();
  
}



void loop() {

  /* Record GPS data when available: */
  while( Serial1.available() ){
    Serial.write(Serial1.read());
    cstate = !cstate;
    digitalWrite(cled, cstate);
  }

  /* Send sensor data at a higher rate, ~25 FPS */
  if(millis() % 40 == 0){

    astate = !astate;
    digitalWrite(aled, astate);

    baro.read();
    baro.packet();

    mpu.read();
    mpu.packet();

    mag.read();
    mag.packet();
  }
}
