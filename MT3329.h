/*
 *           MT3329 GPS Module Library
 *                    HEADER
 */


#include "Arduino.h"

class mt33 {
  
  public:
    mt33();
    void init();
  
  
  private:
    unsigned int BAUD;
  
};
