/**
 * 
 *   A P M    2    S K I    T R A C K E R
 *
 *   Kinda stupid but why not
 *
**/


#include <Wire.h>
#include "HMC5883L.h"
#include "MPU6000.h"
#include "MS5611.h"
#include "MT3329.h"

hmc hmc;
mpu mpu;
ms56 ms56;
mt33 mt33;
 
void setup() {
  
  Serial.begin(38400);
  
  hmc.init();
  mpu.init();
  ms56.init();
  mt33.init();
  
  pinMode(27, OUTPUT);
  digitalWrite(27, HIGH);
  
}

void loop() {

  while( Serial1.available() ){
    Serial.write(Serial1.read());
  }
  
  if( millis() % 1000 <= 10 ){
    Serial.println( hmc.getMag('x') );
  }

}
