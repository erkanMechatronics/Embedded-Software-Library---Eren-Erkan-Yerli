/*
 * sensordriver.h
 *
 *  Created on: Mar 15, 2024
 *      Author: Eren Erkan Yerli
 */

#ifndef INC_SENSORDRIVER_H_
#define INC_SENSORDRIVER_H_


#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "MPU6050_driver.h"


sensor_status_e sensor_test_device( uint8_t chipAdd );
uint8_t sensor_read_register8(uint8_t chipAdd, uint8_t regAdd);
int16_t sensor_read_register16(uint8_t chipAdd, uint8_t regAdd);
sensor_status_e sensor_write_register16(uint8_t chipAdd, uint8_t regAdd, uint16_t value);
sensor_status_e sensor_write_register8(uint8_t chipAdd, uint8_t regAdd, uint8_t value);
sensor_status_e sensor_read_registers(uint8_t chipAdd,uint8_t regAdd,uint8_t *buffer,uint8_t size);
sensor_status_e sensor_write_registers(uint8_t chipAdd,uint8_t regAdd,uint8_t *buffer,uint8_t size);


#endif

