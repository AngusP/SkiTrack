/*
 *           MT3329 GPS Module Library
 *                  SOURCE FILE
 */


#include "MT3329.h"


mt33::mt33() {
  
  /* UART Baud rate, default 38400 */
  BAUD = 38400;
  
}

void mt33::init() {
  Serial1.begin(BAUD);
  /* Put the MT3329 GPS into NMEA Sentence mode: */
  Serial1.print("$PGCMD,16,1,1,1,1,1*6B\r\n");
}
