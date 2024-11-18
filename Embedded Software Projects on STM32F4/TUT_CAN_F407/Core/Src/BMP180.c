/*
 * BMP180.c
 *
 *  Created on: Jun 5, 2024
 *      Author: erkan
 */

#include "BMP180.h"
#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "math.h"

/*
 *
 * İlk önce kalibrasyon değerlerini BMP180'den al ve kontrol et.
 * Ondan sonra sıcaklığı ölç. Parmağını koy sıcaklık değişiyor mu gözlemle.
 * En sonda da basıncı ölç. Bu işlemler bittikten sonra bu bilgileri canbus ile ilet.
 *
 *
 *
 */





sensor_status_e BMP180_device_reset(uint8_t dev_address)
{
	uint8_t data;
	data = 0xB6;

	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Write(I2C_HANDLER, dev_address, SOFT_RESET, 1, &data, 1, 100);

	if(status != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}


sensor_readiness_e BMP180_chip_ID(void)
{
	uint8_t returnVal;

	HAL_I2C_Mem_Read(I2C_HANDLER, DEVICE_READ, ID_REG, 1, &returnVal, 1, 100);

	if(returnVal == 0x55)
	{
		return SENSOR_READY;
	}
	else
	{
		return SENSOR_NREADY;
	}
}

int16_t* BMP180_getCalib_data(int16_t* calibration_data)
{
	uint8_t  calibration_data_temp[22];


	HAL_I2C_Mem_Read(I2C_HANDLER, DEVICE_READ, AC1_MSB, 1, calibration_data_temp,22, 100);

	for(int i = 0;i < 11;i++)
	{
		calibration_data[i] = (calibration_data_temp[2 * i] << 8) | calibration_data_temp[2 * i + 1];
	}

	return calibration_data;
}

sensor_status_e BMP180_write_data(uint8_t reg_address,uint8_t data)
{
	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Write(I2C_HANDLER,DEVICE_WRITE,reg_address,1,&data,1,100);

	if(status != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}

uint8_t BMP180_read_data(uint8_t reg_address)
{
	uint8_t returnData;


	HAL_I2C_Mem_Read(I2C_HANDLER, DEVICE_READ,reg_address , 1, &returnData,1, 100);

	return returnData;
}

sensor_status_e BMP180_check_sensor(void)
{
	HAL_StatusTypeDef status;

	status = HAL_I2C_IsDeviceReady(I2C_HANDLER, DEVICE_READ, 2, 100);

	if(status != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}

float BMP180_read_utemp(void)
{
	BMP180_write_data(CTRL_MEAS,TEMP_CONV_45);
	HAL_Delay(4.5);

	uint8_t msb,lsb;

	msb = BMP180_read_data(OUT_MSB);
	lsb = BMP180_read_data(OUT_LSB);

	float ucomTemp;

	ucomTemp = (msb << 8) | lsb;

	return ucomTemp;
}

float BMP180_read_rtemp(void)
{
	float x1,x2,b5,realTemp,ut;
	int16_t calibration_data[11];

	BMP180_getCalib_data(calibration_data);
	ut = BMP180_read_utemp();

	x1 = (ut - calibration_data[5])* calibration_data[4] / pow(2,15);
	x2 = calibration_data[9] * pow(2,11) / (x1 + calibration_data[10]);
	b5 = x1 + x2;

	realTemp = (b5 + 8) / pow(2,4);

	realTemp = realTemp / 10;

	return realTemp;
}


double BMP180_read_upres(oversampling_ratio_e oss)
{
	uint8_t data;
	float delay;
	double ucomPres;


	switch (oss)
	{
		case 0:
			delay = 4.5;
		case 1:
			delay = 7.5;
		case 2:
			delay = 13.5;
		case 3:
			delay = 25.5;
	}


	data = PRES_CONV_45 | (oss << 6);

	BMP180_write_data(CTRL_MEAS,data);

	HAL_Delay(delay);

	uint8_t msb,lsb,xlsb;

	msb  = BMP180_read_data(OUT_MSB);
	lsb  = BMP180_read_data(OUT_LSB);
	xlsb = BMP180_read_data(OUT_XLSB);

	ucomPres = ((msb << 16) | (lsb << 8) | xlsb) >> (8 - oss);

	return ucomPres;
}


double BMP180_read_rpres(oversampling_ratio_e oss)
{
	long x1,x2,x3,b5,ut,up;
	long b3,b6;
	double realPres;

	unsigned long b4,b7;

	ut = BMP180_read_utemp();
	up = BMP180_read_upres(SINGLE_TIME);
	int16_t calibration_data[11];

	BMP180_getCalib_data(calibration_data);


	x1 = (ut - calibration_data[5])* calibration_data[4] / pow(2,15);
	x2 = calibration_data[9] * pow(2,11) / (x1 + calibration_data[10]);
	b5 = x1 + x2;


	b6 = b5 - 4000;
	x1 = (calibration_data[7]*(b6*b6 / pow(2,12))) / pow(2,11);
	x2 = calibration_data[1] * b6 / pow(2,11);
	x3 = x1 + x2;
	b3 = (((calibration_data[0] * 4 + x3) << oss) + 2) / 4;
	x1 = calibration_data[2] * b6 / pow(2,13);
	x2 = calibration_data[6] * (b6 * b6 / pow(2,12))/ pow(2,16);
	x3 = ((x1 + x2) + 2) / 4;

	b4 = calibration_data[3]*(unsigned long)(x3 + 32768)/pow(2,15);
	b7 = ((unsigned long)up - b3)*(50000 >> oss);

	if(b7 < 0x80000000)
	{
		realPres = (b7 * 2) / b4;
	}
	else
	{
		realPres = (b7 / b4) * 2;
	}

	x1 = (realPres / pow(2,8))*(realPres / pow(2,8));
	x1 = (x1 * 3038) / pow(2,16);
	x2 = (-7357 * realPres) / pow(2,16);

	realPres = realPres + (x1 + x2 + 3791) / pow(2,4);

	// Turn Pascal to Bar


	return realPres;
}







