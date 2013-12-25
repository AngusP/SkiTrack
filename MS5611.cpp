/*
 *           MS5611 Didital Barometer & Thermometer Library
 *                             SOURCE FILE
 */


#include "MS5611.h"


ms56::ms56(int cs_pin){

  /* Chip select pin, pin 40 on APM 2 */
  CS_PIN = cs_pin;
  
  pinMode(CS_PIN, OUTPUT);

  int16_t C1 = 0;
  int16_t C2 = 0;
  int16_t C3 = 0;
  int16_t C4 = 0;
  int16_t C5 = 0;
  int16_t C6 = 0;

}

void ms56::init() {
  /* Set the SPI clock speed to high = 8MHz. Default SPI_CLOCK_DIV4 = 4MHz */
  SPI.setClockDivider( SPI_CLOCK_DIV2 );
  
  delay(5);
  
  /* Read the constants from the PROM: */
  
  C1 = ms56::read16Bits(MS5611_CMD_PROM_READ_C1);
  C2 = ms56::read16Bits(MS5611_CMD_PROM_READ_C2);
  C3 = ms56::read16Bits(MS5611_CMD_PROM_READ_C3);
  C4 = ms56::read16Bits(MS5611_CMD_PROM_READ_C4);
  C5 = ms56::read16Bits(MS5611_CMD_PROM_READ_C5);
  C6 = ms56::read16Bits(MS5611_CMD_PROM_READ_C6);

}


int32_t ms56::calcTemp( uint32_t rawTemp, int16_t C5, int16_t C6 ){
  
  int32_t dT, TEMP;
  int64_t T2 = 0;

  dT = rawTemp - (C5 * 256);
  TEMP = 2000 + dT * (C6 / 8388608);
  
  if(TEMP < 2000){
    T2 = sq(dT) / 2147483648;
  }

  return (TEMP - T2);

}


void ms56::write(byte reg) {
  byte dump;
  digitalWrite(CS_PIN, LOW);
  dump = SPI.transfer(reg);
  digitalWrite(CS_PIN, HIGH);
}


void ms56::reset() {
  byte dump;
  digitalWrite(CS_PIN, LOW);
  dump = SPI.transfer(MS5611_CMD_RESET);
  digitalWrite(CS_PIN, HIGH);
}


uint32_t ms56::readADC() {
  byte dump,byteH,byteM,byteL;
  uint32_t return_value;

  digitalWrite(CS_PIN, LOW);
  dump = SPI.transfer(MS5611_CMD_ADC_READ);
  byteH = SPI.transfer(0);
  byteM = SPI.transfer(0);
  byteL = SPI.transfer(0);
  digitalWrite(CS_PIN, HIGH);

  return_value = (((uint32_t)byteH)<<16) | (((uint32_t)byteM)<<8) | (byteL);
  return (return_value);
}


uint16_t ms56::read16Bits(byte reg) {
  byte dump,byteH,byteL;
  uint16_t return_value;
  byte addr = reg;
  
  digitalWrite(CS_PIN, LOW);
  dump = SPI.transfer(addr);
  byteH = SPI.transfer(0);
  byteL = SPI.transfer(0);
  digitalWrite(CS_PIN, HIGH);
  return_value = ((uint16_t)byteH<<8) | (byteL);
  return(return_value);
}


/* Debug function to print constants out: */
void ms56::printConsts() {
  Serial.print("$BARCS,");
  Serial.print(C1);
  Serial.print(",");
  Serial.print(C2);
  Serial.print(",");
  Serial.print(C3);
  Serial.print(",");
  Serial.print(C4);
  Serial.print(",");
  Serial.print(C5);
  Serial.print(",");
  Serial.print(C6);
  Serial.print("\r\n");
}
