/**
 * 
 *   A P M    2    S K I    T R A C K E R
 *
 *   Kinda stupid but why not
 *
**/

/*
The other sensors (in addition to the GPS) output NMEA style information.
HMC5883L Magnetometer:              $MAGNT
MPU6000 Accel. & Gyro:              $MPUAG
MS5611 Calibration constants:       $BARCS
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

  /* Baud matched with MT3329 rate */
  Serial.begin(38400);
  
  mag.init();
  mpu.init();
  baro.init();
  gps.init();
  
  /* Output frequency in Hz {1,4,10} */
  gps.rate(1);

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

  

  /* Record GPS data when available:
  while( Serial1.available() ){
    Serial.write(Serial1.read());
    cstate = !cstate;
    digitalWrite(cled, cstate);
  }*/

  /* Every second send the magnetometer values */
  if(millis() % 1000 == 0){

    astate = !astate;
    digitalWrite(aled, astate);

    baro.read();

    Serial.print("RP: ");
    Serial.print(baro.getRawPressure());
    Serial.print(", RT:");
    Serial.print(baro.getRawTemperature());
    Serial.print(", P:");
    Serial.print(baro.getPressure());
    Serial.print(", T:");
    Serial.println(baro.getTemperature());

    /*mx = mag.getMag('x');
    my = mag.getMag('y');
    mz = mag.getMag('z');
    */
    /* Sends the data over Serial */
    //mag.packet(mx,my,mz,false);
  }
}
