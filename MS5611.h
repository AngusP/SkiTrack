/*
 *           MS5611 Didital Barometer & Thermometer Library
 *                               HEADER
 */


#include "Arduino.h"
#include <SPI.h>
#include <math.h>

/*
  NOTE:
A double is the same as int32_t
*/

/* Command set. See Datasheet. */
#define MS5611_CMD_RESET               0x1E
#define MS5611_CMD_D1                  0x40
#define MS5611_CMD_PRES                MS5611_CMD_D1
#define MS5611_CMD_D2                  0x50
#define MS5611_CMD_TEMP                MS5611_CMD_D2
#define MS5611_CMD_ADC_READ            0x00
#define MS5611_CMD_PROM_READ_RE        0xA0
#define MS5611_CMD_PROM_READ_C1        0xA2
#define MS5611_CMD_PROM_READ_C2        0xA4
#define MS5611_CMD_PROM_READ_C3        0xA6
#define MS5611_CMD_PROM_READ_C4        0xA8
#define MS5611_CMD_PROM_READ_C5        0xAA
#define MS5611_CMD_PROM_READ_C6        0xAC
#define MS5611_CMD_PROM_READ_CR        0xAE

/* Oversampling Ratios */
#define MS5611_OSR_256       0b00000000
#define MS5611_OSR_512       0b00000010
#define MS5611_OSR_1024      0b00000100
#define MS5611_OSR_2048      0b00000110
#define MS5611_OSR_4096      0b00001000


/* Conversion Times */
#define MS5611_TYP_256       0.54
#define MS5611_TYP_512       1.06
#define MS5611_TYP_1024      2.08
#define MS5611_TYP_2048      4.13
#define MS5611_TYP_4096      8.22

#define MS5611_MAX_256       0.60
#define MS5611_MAX_512       1.17
#define MS5611_MAX_1024      2.28
#define MS5611_MAX_2048      4.54
#define MS5611_MAX_4096      9.04


/*
 * NOTE:
 * D1 and D2 commands are as follows:
 * $ MS5611_CMD_D1 + MS5611_OSR_4096
 * = 0x48 or 0x50
 */


class ms56 {
  
  public:
    ms56(int cs_pin);
    void init();
    void write(byte reg);
    uint8_t read();
    bool ready();
    int32_t pressure();
    void calculate();
    int32_t temperature();
    int32_t getPressure();
    int32_t getTemperature();
    float altitude( int32_t pressure );
    uint32_t readADC();
    uint16_t read16Bits(byte reg);
    void printConsts();
    void reset();

  private:
    int CS_PIN;
    uint8_t STATE;
    uint32_t TIMER;
    
    uint32_t D1;    // Digital pressure value
    uint32_t D2;    // Digital temperature value
    int16_t C1;     // SENS t1    -- Pressure sensitivity
    int16_t C2;     // OFF t1     -- Pressure offset
    int16_t C3;     // TCS        -- Temperature coefficient of pressure sensitivity
    int16_t C4;     // TCO        -- Temperature coefficient of pressure offset
    int16_t C5;     // Tref       -- Reference temperature
    int16_t C6;     // TEMPSENS   -- Temperature coefficient of the temerature
    int32_t dT;     // Difference between reference and actual temperature
    int32_t T;      // The Temperature
    uint32_t RT;    // Raw temperature
    int32_t T2;     // Temperature compensation
    int64_t OFF;    // Offset at actual temperature
    int64_t SENS;   // Sensitivity at actual temperature
    int32_t P;      // The Pressure
    uint32_t RP;    // Raw pressure
  
};
