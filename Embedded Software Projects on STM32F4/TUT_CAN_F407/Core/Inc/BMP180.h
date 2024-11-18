/*
 * BMP180.h
 *
 *  Created on: Jun 5, 2024
 *      Author: erkan
 */

#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "main.h"

#ifndef INC_BMP180_H_
#define INC_BMP180_H_

#define DEVICE_READ 0xEF
#define DEVICE_WRITE 0xEE

// Register addresses

// Calibration Data
#define AC1_LSB 0xAB
#define AC1_MSB 0xAA
#define AC2_LSB 0xAD
#define AC2_MSB 0xAC
#define AC3_LSB 0xAF
#define AC3_MSB 0xAE
#define AC4_LSB 0xB1
#define AC4_MSB 0xB0
#define AC5_LSB 0xB3
#define AC5_MSB 0xB2
#define AC6_LSB 0xB5
#define AC6_MSB 0xB4
#define B1_LSB  0xB7
#define B1_MSB  0xB6
#define B2_LSB  0xB9
#define B2_MSB  0xB8
#define MB_LSB  0xBB
#define MB_MSB  0xBA
#define MC_LSB  0xBD
#define MC_MSB  0xBC
#define MD_LSB  0xBF
#define MD_MSB  0xBE

// General Purpose Registers
#define OUT_XLSB 0xF8
#define OUT_LSB  0xF7
#define OUT_MSB  0xF6
#define CTRL_MEAS 0xF4
#define SOFT_RESET 0xE0
#define ID_REG     0xD0

#define TEMP_CONV_45   0x2E
#define PRES_CONV_45   0x34
#define PRES_CONV_75   0x74
#define PRES_CONV_135  0xB4
#define PRES_CONV_255  0xF4


typedef enum
{
	SENSOR_OK,
	SENSOR_ERROR
}sensor_status_e;


typedef enum
{
	SENSOR_NREADY,
	SENSOR_READY
}sensor_readiness_e;


typedef enum
{
	SINGLE_TIME,
	SECOND_TIME,
	THIRD_TIME,
	FORTH_TIME
}oversampling_ratio_e;


void BMP180_soft_reset(uint8_t dev_address);
sensor_readiness_e BMP180_chip_ID(void);
int16_t* BMP180_getCalib_data(int16_t* calibration_data);
sensor_status_e BMP180_write_data(uint8_t reg_address,uint8_t data);
uint8_t BMP180_read_data(uint8_t reg_address);
sensor_status_e BMP180_check_sensor(void);
float BMP180_read_utemp(void);
float BMP180_read_rtemp(void);
double BMP180_read_upres(oversampling_ratio_e oss);
double BMP180_read_rpres(oversampling_ratio_e oss);


extern I2C_HandleTypeDef hi2c1;
#define I2C_HANDLER &hi2c1




#endif /* INC_BMP180_H_ */
