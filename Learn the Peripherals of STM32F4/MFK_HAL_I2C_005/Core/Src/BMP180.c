/*
 * BMP180.c
 *
 *  Created on: Dec 1, 2023
 *      Author: Eren Erkan Yerli
 */

#include "BMP180.h"

int16_t AC1;
int16_t AC2;
int16_t AC3;
int16_t AC4;
int16_t AC5;
int16_t AC6;
int16_t B1;
int16_t B2;
int16_t MB;
int16_t MC;
int16_t MD;

// Temperature Variables
int16_t UnCompTemp;

float Temp;
int32_t tX1,tX2,tB5;


// Pressure Variables
int8_t UnCompPresRegVal;
int32_t UnCompPres;
float Pres,Pres_atm;
int32_t pX1,pX2,pX3,pB6,pB7,pB3,pB4;

void BMP180_Init()
{
	if(HAL_I2C_IsDeviceReady(&hi2c1, BMP180_READ, 1, 100) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,1);
	}

	BMP180_Get_Calibration_Value();
}

void BMP180_Get_Calibration_Value()
{
	int a = 0;
	uint8_t calibration_buffer[BMP180_CALIB_VALUE_LENGTH] = {0};

	HAL_I2C_Mem_Read(&hi2c1, BMP180_READ, BMP180_CALIB_ADDRESS, 1,calibration_buffer, BMP180_CALIB_VALUE_LENGTH, 100);

	AC1 =  (int16_t)((calibration_buffer[a] << 8) | calibration_buffer[a+1]);a+=2;
	AC2 =  (int16_t)((calibration_buffer[a] << 8) | calibration_buffer[a+1]);a+=2;
	AC3 =  (int16_t)((calibration_buffer[a] << 8) | calibration_buffer[a+1]);a+=2;
	AC4 =  (int16_t)((calibration_buffer[a] << 8) | calibration_buffer[a+1]);a+=2;
	AC5 =  (int16_t)((calibration_buffer[a] << 8) | calibration_buffer[a+1]);a+=2;
	AC6 =  (int16_t)((calibration_buffer[a] << 8) | calibration_buffer[a+1]);a+=2;
	B1  =  (int16_t)((calibration_buffer[a] << 8) | calibration_buffer[a+1]);a+=2;
	B2  =  (int16_t)((calibration_buffer[a] << 8) | calibration_buffer[a+1]);a+=2;
	MB  =  (int16_t)((calibration_buffer[a] << 8) | calibration_buffer[a+1]);a+=2;
	MC  =  (int16_t)((calibration_buffer[a] << 8) | calibration_buffer[a+1]);a+=2;
	MD  =  (int16_t)((calibration_buffer[a] << 8) | calibration_buffer[a+1]);a+=2;


	if((AC1 == 0x0000) || (AC1 == 0xFFFF))
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,1);
		while(1);
	}
	if((AC2 == 0x0000) || (AC2 == 0xFFFF))
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,1);
		while(1);
	}
	if((AC3 == 0x0000) || (AC3 == 0xFFFF))
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,1);
		while(1);
	}
	if((AC4 == 0x0000) || (AC4 == 0xFFFF))
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,1);
		while(1);
	}
	if((AC5 == 0x0000) || (AC5 == 0xFFFF))
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,1);
		while(1);
	}
	if((AC6 == 0x0000) || (AC6 == 0xFFFF))
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,1);
		while(1);
	}
	if((B1 == 0x0000) || (B1 == 0xFFFF))
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,1);
		while(1);
	}
	if((B2 == 0x0000) || (B2 == 0xFFFF))
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,1);
		while(1);
	}
	if((MB == 0x0000) || (MB == 0xFFFF))
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,1);
		while(1);
	}
	if((MC == 0x0000) || (MC == 0xFFFF))
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,1);
		while(1);
	}
	if((MD == 0x0000) || (MD == 0xFFFF))
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,1);
		while(1);
	}

}

void BMP180_Get_Uncompensated_Temp(void)
{
	uint8_t wData[1];
	uint8_t rData[2] = {0};
	wData[0] = 0x2E;

	HAL_I2C_Mem_Write(&hi2c1, BMP180_WRITE, 0xF4, 1, wData, 1, 100);
	HAL_Delay(5);

	HAL_I2C_Mem_Read(&hi2c1, BMP180_READ, 0xF6,1, rData, 2, 100);

	UnCompTemp = (int16_t)((rData[0] << 8) | rData[1]);


}

void BMP180_Get_Temp()
{
	BMP180_Get_Uncompensated_Temp();


	tX1 = ((int32_t)UnCompTemp - (int32_t)AC6)*(int32_t)AC5 / 32.768;
	tX2 = (int32_t)MC * 2048 / (tX1 + (int32_t)MD);

	if((tX1 == 0x0000) | (MD == 0x0000))
	{
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,1);
		while(1);
	}


	tB5 = tX1 + tX2;

	Temp = (float)((tB5 + 8)/16 * 0.1);

}

void BMP180_Get_Uncompensated_Pressure(void)
{
	uint8_t wData2[1];
	uint8_t rData2[3] = {0};

	wData2[0] = 0x34 | (0x03 << 6);

	HAL_I2C_Mem_Write(&hi2c1, 0xEE, 0xF4, 1, wData2, 1, 100);
	HAL_Delay(26);

	HAL_I2C_Mem_Read(&hi2c1, 0xEF, 0xF6, 1, rData2, 3, 100);

	UnCompPres = ((rData2[0] << 16) | (rData2[1] << 8) | rData2[0]) >> (8 - (uint8_t)(0x03));

}

void BMP180_Get_Pressure(void)
{
	BMP180_Get_Uncompensated_Pressure();

	pB6 = tB5 - 4000;
	pX1 = (B2*(pB6 * pB6 / 4096))/ 2048;
	pX2 = AC2*pB6 / 2048;
	pX3 = pX1 + pX2;
	pB3 = ((((long)AC1 * 4 + pX3) << (uint8_t)0x03)+ 2)/4;

	pX1 = AC3*pB6/8192;
	pX2 = (B1 * (pB6 * pB6/4096))/65536;
	pX3 = ((pX1 + pX2) + 2)/4;

	pB4 = AC4*(unsigned long)(pX3 + 32768)/32768;
	pB7 = ((unsigned long)UnCompPres - pB3)*(50000 >> (uint8_t)0x03);

	if(pB7 < 0x80000000)
	{
		Pres = (pB7 * 2)/pB4;
	}
	else
	{
		Pres = (pB7 / pB4)*2;
	}
	pX1 = (Pres / 256) * (Pres / 256);
	pX1 = (pX1*3038)/65536;
	pX2 = (-7357 * Pres)/65536;

	Pres = Pres + (pX1 + pX2 + 3791)/16; // Pa Cinsinden
	Pres_atm = Pres * 0.00000986923;     // Atm Cinsinden
}







