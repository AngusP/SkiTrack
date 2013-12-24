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

/**
 * NMEA SENTENCES:
 * 
 * $GPGGA,224109.000,5118.1937,N,00054.4620,W,1,4,2.25,102.7,M,47.3,M,,*47
 * $GPGSA,A,3,12,24,15,22,,,,,,,,,2.45,2.25,0.97*0B
 * $GPGSV,3,1,10,24,86,356,34,12,49,219,23,15,42,169,20,17,33,063,*7D
 * $GPGSV,3,2,10,22,24,287,25,18,22,250,,14,16,314,,25,12,228,*73
 * $GPGSV,3,3,10,26,08,145,,01,03,012,*75
 * $GPRMC,224109.000,A,5118.1937,N,00054.4620,W,0.00,97.06,231213,,,A*48
 * $GPVTG,97.06,T,,M,0.00,N,0.00,K,A*05
 * $PGACK,16,3*6A
**/


/* NOTE:
     To Change Baud Rate:
     $PMTK251,4800*14
     $PMTK251,9600*17
     $PMTK251,19200*22
     $PMTK251,38400*27
*/
