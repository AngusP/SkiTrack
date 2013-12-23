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

  

  /* Record GPS data when available:
  while( Serial1.available() ){
    // Pass the serial data from the GPS through to the serial port
    Serial.write(Serial1.read());
  }
  */

  /* Every second send the magnetometer values
  if(millis() % 1000 == 0){
    
    long mx = hmc.getMag('x');
    long my = hmc.getMag('y');
    long mz = hmc.getMag('z');
    unsigned long mv = sqrt( sq(mx) + sq(my) + sq(mz) );
    
    Serial.print(mx);
    Serial.print(",");
    Serial.print(my);
    Serial.print(",");
    Serial.print(mz);
    Serial.print(",");
    Serial.println(mv);
    }*/

}
