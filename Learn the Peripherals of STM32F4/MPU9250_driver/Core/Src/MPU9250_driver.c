/*
 * MPU9250_driver.c
 *
 *  Created on: Apr 4, 2024
 *      Author: erkan
 */

#include "MPU9250_driver.h"

sensor_status_e checkCommunicationMPU9250(uint8_t deviceAdd)
{
	if(HAL_I2C_IsDeviceReady(&hi2c1, deviceAdd, 1,100) != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}

uint8_t readRegisterMPU9250(uint8_t deviceAdd,uint8_t address)
{
	uint8_t returnVal = 0;

	HAL_I2C_Mem_Read(&hi2c1, deviceAdd, address, 1, (uint8_t*)&returnVal, 1, 100);

	return returnVal;

}


sensor_status_e writeRegisterMPU9250(uint8_t deviceAdd,uint8_t address,uint8_t* data)
{
	if(HAL_I2C_Mem_Write(&hi2c1, deviceAdd, address, 1,(uint8_t*)&data, 1, 100) != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}

uint8_t findDeviceAddress(void)
{
	uint8_t deviceAdd;

	for(int i = 255;i >= 0;i++)
	{
		if(HAL_I2C_IsDeviceReady(&hi2c1, i, 1, 100) == HAL_OK)
		{

			deviceAdd = i;
			break;

		}
	}
	return deviceAdd;
}

sensor_status_e resetDeviceMPU9250(uint8_t deviceAdd)
{






}

