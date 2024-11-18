/*
 * Nokia5110.h
 *
 *  Created on: Dec 21, 2023
 *      Author: Eren Erkan Yerli
 */

#include "main.h"
#include "stdbool.h"

#ifndef SRC_NOKIA5110_H_
#define SRC_NOKIA5110_H_

extern SPI_HandleTypeDef hspi2;
extern DMA_HandleTypeDef hdma_spi2_tx;

bool LCD5110_Init(void);
void LCD5110_Reset(void);
bool LCD5110_Update(void);
bool LCD5110_Write(uint8_t data1, uint8_t mode1);
bool LCD5110_PixelWrite(uint8_t x,uint8_t y,bool state);
void LCD5110_Clear(void);
void LCD5110_BufferWrite(uint8_t* data,uint16_t length);


#endif /* SRC_NOKIA5110_H_ */
