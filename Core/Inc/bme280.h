#ifndef BME280_H
#define BME280_H

#include "main.h"
#include "bme280_registers.h"
#include <stdint.h>

typedef struct
{
    I2C_HandleTypeDef *bme280_i2c;
    uint8_t address;
    uint16_t t1, p1;
    int16_t t2, t3, p2, p3, p4, p5, p6, p7, p8, p9, h2, h4, h5;
    __u_char h1, h3;
} BME280_t;

uint8_t BME280_init(BME280_t *bme, I2C_HandleTypeDef *handler, uint8_t address);
float read_temperature();
float read_humidity();
float read_pressure();

uint8_t read_8(BME280_t *bme, uint8_t reg);
void write_8(BME280_t *bme, uint8_t reg, uint8_t value);
uint8_t read_16(BME280_t *bme, uint8_t reg);

#endif