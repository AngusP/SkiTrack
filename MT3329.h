/*
 *           MT3329 GPS Module Library
 *                    HEADER
 */


#include "Arduino.h"

class mt33 {
  
  public:
    mt33();
    void init();
    void rate( int rate );
  
  
  private:
    unsigned int BAUD;
    int RATE;
  
};


/* NOTE:
     To Change Baud Rate:
     $PMTK251,4800*14
     $PMTK251,9600*17
     $PMTK251,19200*22
     $PMTK251,38400*27
*/
