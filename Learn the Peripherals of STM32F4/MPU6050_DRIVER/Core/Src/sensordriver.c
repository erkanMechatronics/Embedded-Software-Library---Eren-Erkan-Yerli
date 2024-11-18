/*
 * sensordriver.c
 *
 *  Created on: Mar 15, 2024
 *      Author: Eren Erkan Yerli
 */

// Bu katman esasında herhangi bir cihazla haberleşmeyi sağlayan katmandır.

#include "stm32f4xx_hal.h"
#include "sensordriver.h"
#include "MPU6050_driver.h"


uint8_t sensor_read_register8(uint8_t chipAdd, uint8_t regAdd)
{
	uint8_t returnVal;

	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Read(&hi2c1,chipAdd,regAdd , 1, &returnVal, 1, 100);

	if(status != HAL_OK)
	{
		Error_Handler();
	}

	return returnVal;
}

int16_t sensor_read_register16(uint8_t chipAdd, uint8_t regAdd)
{
	int8_t returnVal[2];
	int16_t returnVal16;

	HAL_I2C_Mem_Read(&hi2c1,chipAdd,regAdd , 1, (uint8_t *)returnVal, 2, 100);

	returnVal16 = (returnVal[0] << 8) | returnVal[1];

	return returnVal16;
}

sensor_status_e sensor_write_register8(uint8_t chipAdd, uint8_t regAdd, uint8_t value)
{
	if(HAL_I2C_Mem_Write(&hi2c1,chipAdd,regAdd,1,&value,1,100) != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}

sensor_status_e sensor_write_register16(uint8_t chipAdd, uint8_t regAdd, uint16_t value)
{
	uint8_t data[2];

	data[0] = value >> 8;
	data[1] = value & (0xFF);

	if(HAL_I2C_Mem_Write(&hi2c1,chipAdd,regAdd, 1, data, 2, 100) != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	return SENSOR_OK;
}

sensor_status_e sensor_read_registers(uint8_t chipAdd,uint8_t regAdd,uint8_t *buffer,uint8_t size)
{
	HAL_I2C_Mem_Read(&hi2c1, chipAdd, regAdd, 1, buffer , size, 100);

//	if(HAL_I2C_Mem_Read(&hi2c1, chipAdd, regAdd, 1, buffer , size, 100) != HAL_OK)
//	{
//		return SENSOR_ERROR;
//	}

	return SENSOR_OK;
}

sensor_status_e sensor_write_registers(uint8_t chipAdd,uint8_t regAdd,uint8_t *buffer,uint8_t size)
{
	if(HAL_I2C_Mem_Read(&hi2c1, chipAdd, regAdd, 1, buffer , size, 100) != HAL_OK)
	{
		return SENSOR_ERROR;
	}

	return SENSOR_OK;
}



