#ifndef BME280_REGISTERS_H
#define BME280_REGISTERS_H



#define BME280_CHIP_ID          0x60
#define BME280_RESET            0xE0
#define BME280_CTRL_HUM         0xF2
#define BME280_I2C_ADDRESS      0x76

#define HUM_LSB                 0xFE
#define HUM_MSB                 0xFD
#define TEMP_XLSB               0xFC
#define TEMP_LSB                0xFB
#define TEMP_MSB                0xFA
#define PRESS_XLSB              0xF9
#define PRESS_LSB               0xF8
#define PRESS_MSB               0xF7
#define CONFIG                  0xF5
#define CTRL_MEAS               0xF4
#define STATUS                  0xF3

#define BME280_DIG_T1           0x88
#define BME280_DIG_T2           0x8A
#define BME280_DIG_T3           0x8C
#define BME280_DIG_P1           0x8E
#define BME280_DIG_P2           0x90       
#define BME280_DIG_P3           0x92
#define BME280_DIG_P4           0x94
#define BME280_DIG_P5           0x96    
#define BME280_DIG_P6           0x98
#define BME280_DIG_P7           0x9A
#define BME280_DIG_P8           0x9C
#define BME280_DIG_P9           0x9E
#define BME280_DIG_H1           0xA1
#define BME280_DIG_H2           0xE1
#define BME280_DIG_H3           0xE3
#define BME280_DIG_H4           0xE4
#define BME280_DIG_H5           0xE5


#define BME280_I2C_TIMEOUT      1000


#endif