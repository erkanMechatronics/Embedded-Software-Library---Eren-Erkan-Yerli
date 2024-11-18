/*
 * BME280_driver.c
 *
 *  Created on: Mar 24, 2024
 *      Author: erkan
 */

#include "BME280_driver.h"


Sensor_status_e sensor_read_ID(uint8_t chipAdd,uint8_t *buffer)
{
	HAL_I2C_Mem_Read(I2C_HANDLER, chipAdd, DEVICE_ID, 1, buffer, 1, 100);

	if(*buffer == 0x60)
	{
		return SENSOR_OK;
	}
	else
	{
		return SENSOR_ERROR;
	}
}

Sensor_status_e sensor_reset(uint8_t chipAdd,uint8_t* databuffer)
{
	*databuffer = DEVICE_RESET_INSTR;

	if(HAL_I2C_Mem_Write(I2C_HANDLER,chipAdd,DEVICE_RESET_REG,1,databuffer,1,100) != HAL_OK)
	{
		return SENSOR_OK;
	}
	else
	{
		return SENSOR_ERROR;
	}
}

Sensor_status_e sensor_config_sensor(uint8_t chipAdd,uint8_t *configData,standby_timeMS_e standbyTime,sensor_filterco_e filter,sensor_spi_e spiStatus)
{
    *configData = (standbyTime << 5) | (filter << 2) | (spiStatus);

    if(HAL_I2C_Mem_Write(I2C_HANDLER, chipAdd, CONFIG, 1, configData, 1,100) != HAL_OK)
    {
    	return SENSOR_ERROR;
    }
    else
    {
    	return SENSOR_OK;
    }
}

Sensor_status_e sensor_config_meas(uint8_t chipAdd,uint8_t* configMeasData,uint8_t* configHumData,Sensor_oversamplingRate_e osrs_t,Sensor_oversamplingRate_e osrs_p,Sensor_oversamplingRate_e osrs_h,Sensor_mode_e mode)
{
	HAL_StatusTypeDef status1;
	HAL_StatusTypeDef status2;

	*configMeasData = (osrs_t << 5) | (osrs_p << 2) | (mode);
	*configHumData = osrs_h;

	status1 = HAL_I2C_Mem_Write(I2C_HANDLER,chipAdd,CTRL_MEAS, 1, configMeasData,1,100);
	HAL_Delay(1);
	status2 = HAL_I2C_Mem_Write(I2C_HANDLER, chipAdd, CTRL_HUM, 1,configHumData, 1,100);

	if((status1 == HAL_OK) && (status2 == HAL_OK))
	{
		return SENSOR_OK;
	}
	else
	{
		return SENSOR_ERROR;
	}

}

Sensor_status_e sensor_readRaw_PressTempHum(uint8_t chipAdd,Sensor_data* pSensorBuffer)
{
	uint8_t buffer[8];

	if(HAL_I2C_Mem_Read(I2C_HANDLER, chipAdd,PRESS_MSB,1,buffer,8,100) == HAL_OK)
	{
		pSensorBuffer->pressRaw = (buffer[0] << 12) | (buffer[1] << 4) | (buffer[2] >> 4);
		pSensorBuffer->tempRaw  = (buffer[3] << 12) | (buffer[4] << 4) | (buffer[5] >> 4);
		pSensorBuffer->humRaw   = (buffer[6] << 8)  | (buffer[7]);
		return SENSOR_OK;
	}
	else
	{
		return SENSOR_ERROR;
	}
}










