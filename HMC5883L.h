/*
 *           HMC588L Magnetometer Interface Library
 *                          HEADER
 */


#include "Arduino.h"
#include <Wire.h>

class hmc{
  
  public:
    hmc();
    void init();
    int getMag( char dir );
    void packet( long mx, long my, long mz, bool printMagnitude );
    
  private:
    int HMC_ADDR;
    int CONF_A, CONF_B;
    int MODE;
    int X0;
    int X1;
    int Y0;
    int Y1;
    int Z0;
    int Z1;
  
};
