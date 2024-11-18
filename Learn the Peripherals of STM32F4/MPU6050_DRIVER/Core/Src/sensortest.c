/*
 * sensortest.c
 *
 *  Created on: Mar 16, 2024
 *      Author: erkan
 */

#include "sensortest.h"

static SensorData_t sensorData;


void sensorTest_init(void)
{
	MPU6050_initialize(&sensorData, FS_250, AFS_2G);
}

void sensorTest_print_sensor_values(void)
{
	MPU6050_read_data(&sensorData);





}
