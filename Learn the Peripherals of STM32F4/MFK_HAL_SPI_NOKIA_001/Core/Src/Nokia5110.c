/*
 * Nokia5110.c
 *
 *  Created on: Dec 21, 2023
 *      Author: Eren Erkan Yerli
 */

#include "Nokia5110.h"

uint8_t frameBuff[504];



bool LCD5110_Init()
{

	LCD5110_Reset();

	if(!LCD5110_Write(0x21,0))
	{
		return false;
	}

	if(!LCD5110_Write(0xC0,0))
	{
		return false;
	}

	if(!LCD5110_Write(0x07,0))
	{
		return false;
	}

	if(!LCD5110_Write(0x13,0))
	{
		return false;
	}

	if(!LCD5110_Write(0x20,0))
	{
		return false;
	}

	if(!LCD5110_Write(0x0C,0))
	{
		return false;
	}

	return true;
}

void LCD5110_Reset(void)
{
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
}

bool LCD5110_Write(uint8_t data1, uint8_t mode1)
{
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,0);

	if(mode1 == 0)
	{
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,0);  // Control if the transmit data is a command.
	}
	else if(mode1 == 1)
	{
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,1);  // Control if the transmit data is a data.
	}
	else
	{
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,1);
		return false;
	}

	HAL_SPI_Transmit_DMA(&hspi2, &data1,1);

	return true;
}

void LCD5110_Clear(void)
{
	for(int i = 0;i < 504;i++)
	{
		frameBuff[i] = 0;
	}

}

bool LCD5110_Update(void)
{
	if(!LCD5110_Write(0x80, 0))
	{
		return false;
	}

	if(!LCD5110_Write(0x40, 0))
	{
		return false;
	}


	LCD5110_BufferWrite(frameBuff,504);

	return true;
}

bool LCD5110_PixelWrite(uint8_t x,uint8_t y,bool state)
{
	int index_x,index_y;

	if((x < 0) | (x >= 84))
	{
		return false;
	}

	if((y < 0) | (y >= 48))
	{
		return false;
	}

	if((state != 0) | (state != 1))
	{
		return false;
	}

	index_y = (y / 8)*84  + x;
	index_x = y % 8;

	if(state == 1)
	{
		frameBuff[index_y] |= (1 << index_x);
	}
	else if(state == 0)
	{
		frameBuff[index_y] &= ~(1 << index_x);
	}

	return true;
}

void LCD5110_BufferWrite(uint8_t* data,uint16_t length)
{
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,0);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,1);

	HAL_SPI_Transmit_DMA(&hspi2, data, length);

}


