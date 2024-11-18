/*
 * MPU6050_driver.c
 *
 *  Created on: Mar 15, 2024
 *      Author: Eren Erkan Yerli
 */

// Burada tasarlanan katman sensöre özel fonksiyonların kullanımı içindir.

#include "MPU6050_driver.h"
#include "main.h"
#include "sensordriver.h"

sensor_status_e MPU6050_read_id(void)
{
	uint8_t candidateAddress;

	HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDRESS, WHO_AM_I, 1, &candidateAddress,1, 100);

	if(candidateAddress == 0x68)
	{
		return SENSOR_OK;
	}
	else
	{
		return SENSOR_ERROR;
	}
}

sensor_status_e MPU6050_test_sensor(void)
{
	HAL_StatusTypeDef status;

	status = HAL_I2C_IsDeviceReady(&hi2c1, DEVICE_ADDRESS, 4, 100);

	if(!(status == HAL_OK))
	{
		return SENSOR_ERROR;
	}

	return SENSOR_OK;
}


sensor_status_e MPU6050_read_data(SensorData_t *pSensorData)
{
	uint8_t buffer[14];
	sensor_status_e status;

	status = sensor_read_registers(DEVICE_ADDRESS,MPU_REG_ACCEL_XOUT_H,buffer,14);

	if(status == SENSOR_OK)
	{
		pSensorData->accRaw.X = (buffer[0] << 8) | buffer[1];
		pSensorData->accRaw.Y = (buffer[2] << 8) | buffer[3];
		pSensorData->accRaw.Z = (buffer[4] << 8) | buffer[5];

		pSensorData->gyroRaw.X = (buffer[8] << 8) | buffer[9];
		pSensorData->gyroRaw.Y = (buffer[10] << 8) | buffer[11];
		pSensorData->gyroRaw.Z = (buffer[12] << 8) | buffer[13];

		pSensorData->acc.X = pSensorData->accRaw.X / pSensorData->acc_co;
		pSensorData->acc.Y = pSensorData->accRaw.Y / pSensorData->acc_co;
		pSensorData->acc.Z = pSensorData->accRaw.Z / pSensorData->acc_co;

		pSensorData->gyro.X = pSensorData->gyroRaw.X / pSensorData->gyro_co;
		pSensorData->gyro.Y = pSensorData->gyroRaw.X / pSensorData->gyro_co;
		pSensorData->gyro.Z = pSensorData->gyroRaw.X / pSensorData->gyro_co;

		return SENSOR_OK;
	}
	else
	{
		return SENSOR_ERROR;
	}

}

sensor_status_e MPU6050_initialize( SensorData_t *pSensor, fs_sel_e gyroConfig, afs_sel_e acc_config )
{
	uint8_t gyroConfigData = gyroConfig << 3;
	uint8_t accConfigData  = acc_config << 3;
	uint8_t buffer[2];
	buffer[0] = gyroConfigData;
	buffer[1] = accConfigData;

	double acc_co_array[4] = {16384,8192,4096,2048};
	double gyro_co_array[4] = {131,65.5,32.8,16.4};

	pSensor->acc_co = acc_co_array[acc_config];
	pSensor->gyro_co = gyro_co_array[gyroConfig];

	if(HAL_I2C_Mem_Write(&hi2c1, DEVICE_ADDRESS, MPU_REG_GYRO_CONFIG, 1, buffer,2, 100) != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}

}

sensor_status_e MPU6050_set_sleep_mode(sleepmode_e sleemode)
{
	sleemode = sleemode << 6;

	if(HAL_I2C_Mem_Write(&hi2c1, DEVICE_ADDRESS, MPU_REG_PWR_MGMT_1, 1, &sleemode, 1, 100) != HAL_OK)
	{
		return SENSOR_ERROR;
	}

	return SENSOR_OK;
}



