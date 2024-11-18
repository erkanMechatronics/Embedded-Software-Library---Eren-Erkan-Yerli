/*
 * NRF24L01_driver.c
 *
 *  Created on: Apr 6, 2024
 *      Author: erkan
 */

#include "NRF24L01_driver.h"


void CS_SPI_ON()
{
	HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
}

void CS_SPI_OFF()
{
	HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);
}

void CE_DEVICE_ON()
{
	HAL_GPIO_WritePin(CE_PORT,CE_PIN,GPIO_PIN_SET);
}

void CE_DEVICE_OFF()
{
	HAL_GPIO_WritePin(CE_PORT,CE_PIN,GPIO_PIN_RESET);
}


// write a single byte to the particular register
sensor_status_e NRF24L01_WriteByte(uint8_t address,uint8_t data)
{
	uint8_t buffer[2];
	HAL_StatusTypeDef status;

	address &= ~(1 << 7);
	address &= ~(1 << 6);
	address |=  (1 << 5);

	buffer[0] = address;
	buffer[1] = data;

	CS_SPI_ON();
	status = HAL_SPI_Transmit(SPI_HANDLER, buffer,2, 100);
	CS_SPI_OFF();

	if(status != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}

// write multiple bytes starting from a particular register
sensor_status_e NRF24L01_WriteMultiBytes(uint8_t address,uint8_t *data,uint8_t size)
{
	HAL_StatusTypeDef status;

	address &= ~(1 << 7);
	address &= ~(1 << 6);
	address |=  (1 << 5);

	CS_SPI_ON();

	HAL_SPI_Transmit(SPI_HANDLER,&address, 1, 100);
	HAL_SPI_Transmit(SPI_HANDLER,data,size,100);

	CS_SPI_OFF();

	if(status != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}
}

// read a byte from a particular register
sensor_status_e NRF24L01_ReadByte(uint8_t address)
{
	uint8_t data;

	HAL_StatusTypeDef status1;
	HAL_StatusTypeDef status2;

	CS_SPI_ON();

	HAL_SPI_Transmit(SPI_HANDLER,&address, 1, 100);
	HAL_SPI_Receive(SPI_HANDLER, &data, 1, 100);

	CS_SPI_OFF();

	if((status1 == HAL_OK) && (status2 == HAL_OK))
	{
		return SENSOR_OK;
	}
	else
	{
		return SENSOR_ERROR;
	}

}

// read multiples bytes starting from a particular register
sensor_status_e NRF24L01_ReadMultiBytes(uint8_t address,uint8_t *buffer,uint8_t size)
{
	HAL_StatusTypeDef status1;
	HAL_StatusTypeDef status2;

	CS_SPI_ON();

	HAL_SPI_Transmit(SPI_HANDLER, &address, 1, 100);
	HAL_SPI_Receive(SPI_HANDLER,buffer,size,100);

	CS_SPI_OFF();

	if((status1 == HAL_OK) && (status2 == HAL_OK))
	{
		return SENSOR_OK;
	}
	else
	{
		return SENSOR_ERROR;
	}

}


sensor_status_e NRF24L01_SendCommand(uint8_t command)
{
	HAL_StatusTypeDef status;

	CS_SPI_ON();

	status = HAL_SPI_Transmit(SPI_HANDLER, &command,1, 100);

	CS_SPI_OFF();

	if(status != HAL_OK)
	{
		return SENSOR_ERROR;
	}
	else
	{
		return SENSOR_OK;
	}

}

/*
 *
 * Before configuring registers or generally the corresponding module it's important to
 * disable the chip and set the CS SPI pin to high level to ensure that it's not listening
 * to the SPI bus. After all the configuration process it would be important to set the CS SPI
 * pin to low level again for listening to the spi bus and its also necessary to bring the
 * module chip to active mode back.
 *
 */



sensor_status_e NRF24L01_Init()
{
	CS_SPI_OFF();
	CE_DEVICE_OFF();

	NRF24L01_WriteByte(CONFIG, 0x00);
	NRF24L01_WriteByte(EN_AA,0x00);
	NRF24L01_WriteByte(EN_RXADDR,0x00);
	NRF24L01_WriteByte(SETUP_AW,0x03);
	NRF24L01_WriteByte(SETUP_RETR, 0x00);
	NRF24L01_WriteByte(RF_CH,0x00);
	NRF24L01_WriteByte(RF_SETUP,0x0E);

	CE_DEVICE_ON();
	CS_SPI_ON();

}

// set up the TX Mode
sensor_status_e NRF24L01_TxMode(uint8_t *address,uint8_t channel)
{
	CS_SPI_OFF();
	CE_DEVICE_OFF();

	NRF24L01_WriteByte(RF_CH, channel); // select the channel
	NRF24L01_WriteMultiBytes(TX_ADDR, address, 5);


}






