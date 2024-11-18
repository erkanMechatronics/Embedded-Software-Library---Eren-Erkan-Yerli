/*
 * BMP180.c
 *
 *  Created on: Jun 5, 2024
 *      Author: erkan
 */

#include "BMP180.h"


sensor_status_e BMP180_device_reset(uint8_t dev_address)
{
	uint8_t data;
	data = 0xB6;

	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Write(I2C_HANDLER, dev_address, SOFT_RESET, 1, &data, 1, 100);

	if(status != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}


sensor_readiness_e BMP180_chip_ID(uint8_t dev_address)
{
	uint8_t returnVal;

	HAL_I2C_Mem_Read(I2C_HANDLER, dev_address, ID_REG, 1, &returnVal, 1, 100);

	if(returnVal == 0x55)
	{
		return SENSOR_READY;
	}
	else
	{
		return SENSOR_NREADY;
	}
}

uint16_t BMP180_getCalib_data(uint8_t dev_address)
{
	uint8_t  calibration_data_temp[22];
	int16_t calibration_data[11];

	HAL_I2C_Mem_Read(I2C_HANDLER, dev_address, AC1_MSB, 1, calibration_data_temp,22, 100);

	for(int i = 0;i < 11;i++)
	{
		calibration_data[i] = (calibration_data_temp[2 * i] << 8) | calibration_data_temp[2 * i + 1];
	}

	return calibration_data;
}

sensor_status_e BMP180_write_data(uint8_t dev_address,uint8_t reg_address,uint8_t data)
{
	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Write(I2C_HANDLER,dev_address,reg_address,1,&data,1,100);

	if(status != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}

uint8_t BMP180_read_data(uint8_t dev_address,uint8_t reg_address)
{
	uint8_t returnData;

	HAL_StatusTypeDef status;

	HAL_I2C_Mem_Read(I2C_HANDLER, dev_address,reg_address , 1, &returnData,1, 100);

	return returnData;
}

sensor_status_e BMP180_check_sensor(uint8_t dev_address)
{
	HAL_StatusTypeDef status;

	status = HAL_I2C_IsDeviceReady(I2C_HANDLER, dev_address, 2, 100);

	if(status != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}
