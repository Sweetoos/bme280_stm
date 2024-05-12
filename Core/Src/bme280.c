#include "bme280.h"

uint8_t BME280_init(BME280_t *bme, I2C_HandleTypeDef *i2c, uint8_t address)
{
    uint8_t chip_id;
    bme->bme280_i2c = i2c;
    bme->address = address;

    chip_id = read_8(bme, BME280_CHIP_ID);

    if (chip_id != 0x60) // 0x60 is a reset register for id
    {
        return 1;
    }

    return 0;

    bme->t1 = read_16(bme, BME280_DIG_T1);
    bme->t2 = read_16(bme, BME280_DIG_T2);
    bme->t3 = read_16(bme, BME280_DIG_T3);

    bme->p1 = read_16(bme, BME280_DIG_P1);
    bme->p2 = read_16(bme, BME280_DIG_P2);
    bme->p3 = read_16(bme, BME280_DIG_P3);
    bme->p4 = read_16(bme, BME280_DIG_P4);
    bme->p5 = read_16(bme, BME280_DIG_P5);
    bme->p6 = read_16(bme, BME280_DIG_P6);
    bme->p7 = read_16(bme, BME280_DIG_P7);
    bme->p8 = read_16(bme, BME280_DIG_P8);
    bme->p9 = read_16(bme, BME280_DIG_P9);

    bme->h1 = read_16(bme, BME280_DIG_H1);
    bme->h2 = read_16(bme, BME280_DIG_H2);
    bme->h3 = read_16(bme, BME280_DIG_H3);
    bme->h4 = read_16(bme, BME280_DIG_H4);
    bme->h5 = read_16(bme, BME280_DIG_H5);
}

uint8_t read_8(BME280_t *bme, uint8_t reg)
{
    uint8_t value;
    HAL_I2C_Mem_Read(bme->bme280_i2c, bme->address, reg, 1, &value, 1, BME280_I2C_TIMEOUT);
    return value;
}

void write_8(BME280_t *bme, uint8_t reg, uint8_t value)
{
    HAL_I2C_Mem_Write(bme->bme280_i2c, bme->address, reg, 1, &value, 1, BME280_I2C_TIMEOUT);
}

uint8_t read_16(BME280_t *bme, uint8_t reg)
{
    uint8_t value[2];
    HAL_I2C_Mem_Read(bme->bme280_i2c, bme->address, reg, 1, value, 2, BME280_I2C_TIMEOUT);
    return ((value[1] << 1) | value[0]);
}