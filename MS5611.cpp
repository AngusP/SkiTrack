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


/*
NB: SPI bus must be initialised externally.
*/

void ms56::init() {
  ms56::reset();
  delay(5);
  
  /* Read the constants from the PROM: */
  
  C1 = ms56::read16Bits(MS5611_CMD_PROM_READ_C1);
  C2 = ms56::read16Bits(MS5611_CMD_PROM_READ_C2);
  C3 = ms56::read16Bits(MS5611_CMD_PROM_READ_C3);
  C4 = ms56::read16Bits(MS5611_CMD_PROM_READ_C4);
  C5 = ms56::read16Bits(MS5611_CMD_PROM_READ_C5);
  C6 = ms56::read16Bits(MS5611_CMD_PROM_READ_C6);

  ms56::write(MS5611_CMD_D2 + MS5611_OSR_4096);
  TIMER = millis();
  STATE = 1;
  T = 2000;
  P = 101500;

  dT = 0;
  OFF = 0;
  SENS = 0;

}


void ms56::calculate() {

  dT = RT - (C5*256);
  T = 2000 + (dT * C6) / pow(2,23);

  OFF = (C2 * pow(2,17)) + ((C4 * dT)/pow(2,6));

  SENS = (C1 * pow(2,16)) + ((C3 * dT)/pow(2,7));

  /*if (T < 2000) {
    int64_t T2 = (dT * dT) / 2147483648;
    T = T - T2;
  }*/

  P = ((((RP * SENS) / pow(2,21)) - OFF) / pow(2,16));
}


float ms56::altitude() {

  float tmp_float;
  float altitude;

  tmp_float = (P / 101325.0);
  tmp_float = pow(tmp_float, 0.190295);
  altitude = 44330 * (1.0 - tmp_float);

  return altitude;
}



uint8_t ms56::read()
{
  uint8_t result = 0;

  if (STATE == 1){
    if (ms56::ready()){
      D2=ms56::readADC();   // On state 1 we read temp
      RT = D2;
      STATE++;
      ms56::write(MS5611_CMD_D1 + MS5611_OSR_4096);  // Command to read pressure
      TIMER = millis();
    }
  }else{
    if (STATE == 5){
      if (ms56::ready()){
	D1=ms56::readADC();
	RP = D1;
	ms56::calculate();
	STATE = 1;                // Start again from state = 1
	ms56::write(MS5611_CMD_D2 + MS5611_OSR_4096);// Command to read temperature
	TIMER = millis();
	result = 1;                // New pressure reading
      }
    }else{
      if (ms56::ready()){
	D1=ms56::readADC();
	RP = D1;
	ms56::calculate();
	STATE++;
	ms56::write(MS5611_CMD_D1 + MS5611_OSR_4096);  // Command to read pressure
	TIMER = millis();
	result = 1;               // New pressure reading
      }
    }
  }
  return(result);
}


bool ms56::ready() {
  if( millis() - TIMER > 10 ){
    return true;
  } else {
    return false;
  }
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


int64_t ms56::getPressure() {
  return P;
}
int64_t ms56::getTemperature() {
  return T;
}
uint32_t ms56::getRawPressure() {
  return RP;
}
uint32_t ms56::getRawTemperature() {
  return RT;
}


void ms56::stream() {
  Serial.write(0x42);
  Serial.write(0x00);
  Serial.write((long)P);
  Serial.write(0x00);
  Serial.write((long)T);
  Serial.write(0x00);
  Serial.print("\r\n");
}


void ms56::packet() {
  Serial.print("$BAROT,");
  Serial.print((long)P); // Cut from (long long) to (long)
  Serial.print(",");
  Serial.print((long)T);
  Serial.print("\r\n");
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
