/*
 * AD5621.h
 *
 *  Created on: Oct 5, 2024
 *      Author: erkan
 */

#ifndef INC_AD5621_H_
#define INC_AD5621_H_

#include "stm32f1xx_hal.h"



void SPI_CS_LOW(void);
void SPI_CS_HIGH(void);





typedef enum
{
	COM_ERROR = 0x00,
	COM_READY = 0x01,
}communication_status_e;


communication_status_e checkCommunication_AD5621(SPI_HandleTypeDef *hspi);
communication_status_e SPI_Write_AD5621(SPI_HandleTypeDef *hspi,uint16_t data);






#endif /* INC_AD5621_H_ */
