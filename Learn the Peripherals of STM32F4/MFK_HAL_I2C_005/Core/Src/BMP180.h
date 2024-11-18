/*
 * BMP180.h
 *
 *  Created on: Dec 1, 2023
 *      Author: Eren Erkan Yerli
 */

#ifndef SRC_BMP180_H_
#define SRC_BMP180_H_

#define BMP180_WRITE 0xEE
#define BMP180_READ 0xEF

// BMP180 Calibration Address
#define BMP180_CALIB_ADDRESS 0xAA


#define BMP180_CALIB_VALUE_LENGTH 22
#include "stdint.h"

#include "stm32f4xx.h"

extern I2C_HandleTypeDef hi2c1;

void BMP180_Init(void);
void BMP180_GetCalibration(void);
void BMP180_Get_Calibration_Value(void);
void BMP180_Get_Uncompensated_Temp(void);
void BMP180_Get_Temp(void);
void BMP180_Get_Uncompensated_Pressure(void);
void BMP180_Get_Pressure(void);

// Calibration Values


#endif /* SRC_BMP180_H_ */
