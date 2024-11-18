/*
 * AD5621.c
 *
 *  Created on: Oct 5, 2024
 *      Author: erkan
 */

#include "AD5621.h"



communication_status_e checkCommunication_AD5621(SPI_HandleTypeDef *hspi)
{
	HAL_SPI_StateTypeDef checkCom;

	SPI_CS_LOW();
	checkCom = HAL_SPI_GetState(hspi);
	SPI_CS_HIGH();

	if(checkCom != HAL_SPI_STATE_READY)
	{
		return COM_ERROR;
	}
	else
	{
		return COM_READY;
	}
}

communication_status_e SPI_Write_AD5621(SPI_HandleTypeDef *hspi,uint16_t data)
{
	HAL_SPI_StateTypeDef checkCom;

	SPI_CS_LOW();

	checkCom = HAL_SPI_Transmit(hspi,(uint8_t *)&data, 1, 1000);

	SPI_CS_HIGH();

	if(checkCom != HAL_SPI_STATE_READY)
	{
		return COM_ERROR;
	}
	else
	{
		return COM_READY;
	}

}




void SPI_CS_LOW(void)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
}


void SPI_CS_HIGH(void)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
}



