/*
 * MPU6050_sensor_driver.h
 *
 *  Created on: Apr 7, 2024
 *      Author: erkan
 */


#ifndef INC_MPU6050_SENSOR_DRIVER_H_
#define INC_MPU6050_SENSOR_DRIVER_H_

#include "stdint.h"
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;
#define I2C_Handler &hi2c1




typedef enum
{
	SENSOR_OK,
	SENSOR_ERROR,
}sensor_status_e;



sensor_status_e sensor_test_device(uint8_t chipAdd);
uint8_t sensor_read_register8(uint8_t chipAdd, uint8_t regAdd);
uint16_t sensor_read_register16(uint8_t chipAdd,uint8_t regAdd);
sensor_status_e sensor_write_register8(uint8_t chipAdd,uint8_t regAdd,uint8_t data);
sensor_status_e sensor_write_register16(uint8_t chipAdd,uint8_t regAdd,uint16_t data);
sensor_status_e sensor_read_bytes(uint8_t chipAdd,uint8_t regAdd,uint8_t* buffer,uint8_t size);
sensor_status_e sensor_write_bytes(uint8_t chipAdd,uint8_t regAdd,uint8_t* buffer,uint8_t size);



#endif /* INC_MPU6050_SENSOR_DRIVER_H_ */
