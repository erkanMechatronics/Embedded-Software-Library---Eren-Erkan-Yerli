/*
 * ws2812.h
 *
 *  Created on: Aug 26, 2024
 *      Author: erkan
 */

#ifndef INC_WS2812_H_
#define INC_WS2812_H_

extern SPI_HandleTypeDef hspi1;

void ws2812_write (uint8_t GREEN,uint8_t RED,uint8_t BLUE);
void setLED (uint8_t LED_Data[8][4],int led,uint8_t GREEN,uint8_t RED,uint8_t BLUE);
void ws2812_send(uint8_t LED_Data[8][4]);

#endif /* INC_WS2812_H_ */
