/*
 * ws2812.c
 *
 *  Created on: Aug 26, 2024
 *      Author: erkan
 */

#include <main.h>
#include <ws2812.h>


void setLED (uint8_t LED_Data[8][4],int led,uint8_t GREEN,uint8_t RED,uint8_t BLUE)
{
	LED_Data[led][0] = led;
	LED_Data[led][1] = GREEN;
	LED_Data[led][2] = RED;
	LED_Data[led][3] = BLUE;
}

void ws2812_write (uint8_t GREEN,uint8_t RED,uint8_t BLUE)
{
	uint32_t data;

	data = (GREEN << 16) | (RED << 8) | (BLUE);
	uint8_t sendData[24];
	int indx = 0;

	for(int i = 23;i >= 0;i--)
	{
		if(((data >> i)&0x01) == 1) sendData[indx++] = 0b110;
		else sendData[indx++] = 0b100;
	}


	HAL_SPI_Transmit(&hspi1, sendData , 24, 100);
}

void ws2812_send(uint8_t LED_Data[8][4])
{
	for(int i = 0;i < 8;i++)
	{
		ws2812_write(LED_Data[i][1],LED_Data[i][2],LED_Data[i][3]);
	}
}





