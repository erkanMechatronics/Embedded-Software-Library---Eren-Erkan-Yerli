/*
 * MPU9250_driver.h
 *
 *  Created on: Apr 4, 2024
 *      Author: erkan
 */

#ifndef INC_MPU9250_DRIVER_H_
#define INC_MPU9250_DRIVER_H_

#include "stm32f4xx_hal.h"


#define DEVICE_ADDRESS_ACC_GYRO ( 0x68 << 1 )
#define DEVICE_ADDRESS_MAG ( 0x0C << 1 )
#define MPU9250_WHO_AM_I ( 0x75 )
#define AK8963_WHO_AM_I ( 0x00 )
#define I2C_SLV1_ADDR    ( 0x28 )
#define I2C_SLV2_ADDR    ( 0x2B )



extern I2C_HandleTypeDef hi2c1;


// Full Scale Range Accelerometer
typedef enum
{
	AFS_SEL_2g,
	AFS_SEL_4g,
	AFS_SEL_8g,
	AFS_SEL_16g
}accelFSR_e;

// Full Scale Range Gyroscope
typedef enum
{
	FS_SEL_250,
	FS_SEL_500,
	FS_SEL_1000,
	FS_SEL_2000,
}gyroFSR_e;

// Sensor return status
typedef enum
{
	SENSOR_OK,
	SENSOR_ERROR
}sensor_status_e;


sensor_status_e checkCommunicationMPU9250(uint8_t deviceAdd);
uint8_t readRegisterMPU9250(uint8_t deviceAdd,uint8_t address);
sensor_status_e writeRegisterMPU9250(uint8_t deviceAdd,uint8_t address,uint8_t* data);
uint8_t findDeviceAddress(void);
sensor_status_e resetDeviceMPU9250(uint8_t deviceAdd);



#endif /* INC_MPU9250_DRIVER_H_ */
