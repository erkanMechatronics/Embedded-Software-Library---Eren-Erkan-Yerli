/*
 * BME280_driver.h
 *
 *  Created on: Mar 24, 2024
 *      Author: erkan
 */

#include "main.h"

#ifndef INC_BME280_DRIVER_H_
#define INC_BME280_DRIVER_H_

#define DEVICE_ADDRESS     0x76 << 1

#define CTRL_HUM           0xF2
#define STATUS             0xF3
#define CTRL_MEAS          0xF4
#define CONFIG             0xF5

#define PRESS_MSB          0xF7
#define PRESS_LSB          0xF8
#define PRESS_XLSB         0xF9
#define TEMP_MSB           0xFA
#define TEMP_LSB 	       0xFB
#define TEMP_XLSB  	       0xFC
#define HUM_LSB    	       0xFE
#define HUM_MSB            0xFD

#define DEVICE_RESET_REG   0xE0
#define DEVICE_RESET_INSTR 0xB6

#define RESET              0xE0
#define DEVICE_ID          0xD0

extern I2C_HandleTypeDef hi2c1;

#define I2C_HANDLER &hi2c1

typedef struct
{
	uint16_t humRaw;
	uint32_t tempRaw;
	uint32_t pressRaw;
}Sensor_data;

typedef enum
{
	SLEEP_MODE    = 0u,
	FORCED1_MODE  = 1u,
	FORCED2_MODE  = 2u,
	NORMAL_MODE   = 3u,
}Sensor_mode_e;

typedef enum
{
	OVERSAMPLING_OFF = 0u,
	OVERSAMPLING_1   = 1u,
	OVERSAMPLING_2   = 2u,
	OVERSAMPLING_4   = 3u,
	OVERSAMPLING_8   = 4u,
	OVERSAMPLING_16  = 5u,
}Sensor_oversamplingRate_e;

typedef enum
{
	SENSOR_OK,
	SENSOR_ERROR,
}Sensor_status_e;

typedef enum
{
	ST_TIME_05   =  0u,   //  0.5 ms
	ST_TIME_625  =  1u,  // 62.5ms
	ST_TIME_125  =  2u,  //  125 ms
    ST_TIME_250  =  3u,  //  250 ms
	ST_TIME_500  =  4u,  //  500 ms
	ST_TIME_1000 =  5u, // 1000 ms
	ST_TIME_10   =  6u,   //   10 ms
	ST_TIME_20   =  7u,   //   20 ms
}standby_timeMS_e;

typedef enum
{
	FILTER_OFF   =  0u,
	FILTER_CO_2  =  1u,
	FILTER_CO_4  =  2u,
	FILTER_CO_8  =  3u,
	FILTER_CO_16 =  4u,
}sensor_filterco_e;

typedef enum
{
	SPI_MODE_OFF  = 0u,
	SPI_MODE_ON   = 1u,
}sensor_spi_e;

Sensor_status_e sensor_read_ID(uint8_t chipAdd,uint8_t *buffer);
Sensor_status_e sensor_reset(uint8_t chipAdd,uint8_t* databuffer);
Sensor_status_e sensor_config_sensor(uint8_t chipAdd,uint8_t *configData,standby_timeMS_e standbyTime,sensor_filterco_e filter,sensor_spi_e spiStatus);
Sensor_status_e sensor_config_meas(uint8_t chipAdd,uint8_t* configMeasData,uint8_t* configHumData,Sensor_oversamplingRate_e osrs_t,Sensor_oversamplingRate_e osrs_p,Sensor_oversamplingRate_e osrs_h,Sensor_mode_e mode);
Sensor_status_e sensor_readRaw_PressTempHum(uint8_t chipAdd,Sensor_data* pSensorBuffer);


#endif /* INC_BME280_DRIVER_H_ */
