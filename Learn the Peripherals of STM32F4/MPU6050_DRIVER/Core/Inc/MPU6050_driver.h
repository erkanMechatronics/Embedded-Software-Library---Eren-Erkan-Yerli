/*
 * MPU6050_driver.h
 *
 *  Created on: Mar 15, 2024
 *      Author: Eren Erkan Yerli
 */
#ifndef INC_MPU6050_DRIVER_H_
#define INC_MPU6050_DRIVER_H_



#include "stdint.h"
#include "stm32f4xx_hal.h"


extern I2C_HandleTypeDef hi2c1;


#define ADDRESS_SIZE 1


// Device Address and Registers
#define DEVICE_ADDRESS 0x68 << 1
#define MPU_REG_SELF_TEST_X	( 13 )
#define MPU_REG_SELF_TEST_Y	( 14 )
#define MPU_REG_SELF_TEST_Z	( 15 )
#define MPU_REG_SELF_TEST_A	( 16 )
#define MPU_REG_SMPLRT_DIV	( 25 )
#define MPU_REG_CONFIG	( 26 )
#define MPU_REG_GYRO_CONFIG	( 27 )
#define MPU_REG_ACCEL_CONFIG	( 28 )
#define MPU_REG_ACCEL_XOUT_H	( 59 )
#define MPU_REG_ACCEL_XOUT_L	( 60 )
#define MPU_REG_ACCEL_YOUT_H	( 61 )
#define MPU_REG_ACCEL_YOUT_L	( 62 )
#define MPU_REG_ACCEL_ZOUT_H	( 63 )
#define MPU_REG_ACCEL_ZOUT_L	( 64 )
#define MPU_REG_ACCEL_TEMP_OUT_H ( 65 )
#define MPU_REG_ACCEL_TEMP_OUT_L	( 66 )
#define MPU_REG_GYRO_XOUT_H	( 67 )
#define MPU_REG_GYRO_XOUT_L	( 68 )
#define MPU_REG_GYRO_YOUT_H	( 69 )
#define MPU_REG_GYRO_YOUT_L	( 70 )
#define MPU_REG_GYRO_ZOUT_H	( 71 )
#define MPU_REG_GYRO_ZOUT_L	( 72 )
#define MPU_REG_USER_CTRL	( 106)
#define MPU_REG_PWR_MGMT_1	( 107 )
#define MPU_REG_PWR_MGMT_2	( 108 )
#define MPU_REG_FIFO_COUNTH ( 114 )
#define MPU_REG_FIFO_COUNTL ( 115 )
#define MPU_REG_FIFO_R_W	( 116 )
#define WHO_AM_I 			0x75



typedef enum {
	SENSOR_OK,
	SENSOR_ERROR
}sensor_status_e;


typedef enum {
	FS_250, // 0
	FS_500, // 1
	FS_1000,// 2
	FS_2000,// 3
}fs_sel_e;

typedef enum {
	AFS_2G, //0
	AFS_4G, //1
	AFS_8G, //2
	AFS_16G //3
}afs_sel_e;

typedef enum {
	SLEEPMODE_OFF,
	SLEEPMODE_ON
}sleepmode_e;

typedef struct {
	int16_t X;
	int16_t Y;
	int16_t Z;
}AxisRawVal_t;

typedef struct {
	double X;
	double Y;
	double Z;
}AxisVal_t;

typedef struct {
	AxisRawVal_t accRaw;
	AxisRawVal_t gyroRaw;
	AxisVal_t acc;
	AxisVal_t gyro;
	double acc_co;
	double gyro_co;
}SensorData_t;


sensor_status_e MPU6050_initialize( SensorData_t *pSensor, fs_sel_e gyroConfig, afs_sel_e acc_config );
sensor_status_e MPU6050_set_sleep_mode(sleepmode_e sleemode);
sensor_status_e MPU6050_read_data(SensorData_t *pSensorData);
sensor_status_e MPU6050_test_sensor(void);
sensor_status_e MPU6050_read_id(void);




#endif /* INC_HELLO_H_ */

