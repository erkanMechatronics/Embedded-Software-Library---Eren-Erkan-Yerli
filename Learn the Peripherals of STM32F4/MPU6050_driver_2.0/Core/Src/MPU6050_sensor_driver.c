/*
 * MPU6050_sensor_driver.c
 *
 *  Created on: Apr 7, 2024
 *      Author: erkan
 */


#include "MPU6050_sensor_driver.h"


sensor_status_e sensor_test_device(uint8_t chipAdd)
{
	HAL_StatusTypeDef status;


	status = HAL_I2C_IsDeviceReady(I2C_Handler, chipAdd, 1, 100);

	if(status != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}

uint8_t sensor_read_register8(uint8_t chipAdd, uint8_t regAdd)
{
	uint8_t data;

	HAL_I2C_Mem_Read(I2C_Handler,chipAdd, regAdd,1, &data, 1, 100);

	return data;
}

uint16_t sensor_read_register16(uint8_t chipAdd,uint8_t regAdd)
{
	uint8_t buffer[2];
	uint16_t data;

	HAL_I2C_Mem_Read(I2C_Handler, chipAdd, regAdd, 1, buffer, 2, 100);


	data = (buffer[1] << 8) | (buffer[0]);

	return data;
}

sensor_status_e sensor_write_register8(uint8_t chipAdd,uint8_t regAdd,uint8_t data)
{
	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Write(I2C_Handler, chipAdd, regAdd, 1, &data, 1, 100);

	if(status != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}

sensor_status_e sensor_write_register16(uint8_t chipAdd,uint8_t regAdd,uint16_t data)
{
	uint8_t data2beWritten[2];

	data2beWritten[0] = (uint8_t) ((data >> 8) & 0xFF);
	data2beWritten[1] = (uint8_t)(data & 0xFF);

	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Write(I2C_Handler, chipAdd, regAdd, 1, data2beWritten, 2, 100);

	if(status != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}

sensor_status_e sensor_read_bytes(uint8_t chipAdd,uint8_t regAdd,uint8_t* buffer,uint8_t size)
{
	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Read(I2C_Handler, chipAdd, regAdd, 1, buffer, size, 100);

	if(status != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}

sensor_status_e sensor_write_bytes(uint8_t chipAdd,uint8_t regAdd,uint8_t* buffer,uint8_t size)
{
	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Write(I2C_Handler, chipAdd, regAdd, 1, buffer, size, 100);

	if(status != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}

