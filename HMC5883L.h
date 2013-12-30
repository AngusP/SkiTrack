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
    void read();
    int getMag( char dir );
    void stream();
    void packet();
    
  private:
    int mx;
    int my;
    int mz;
    
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
