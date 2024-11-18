/*
 * led_driver.c
 *
 *  Created on: Sep 30, 2023
 *      Author: erkan
 */

#include "stm32f4xx_hal.h"

void leddriver_init(void)
{
	RCC->AHB1ENR = 0x00000008;

	GPIOD->MODER = 0x01000000;
	GPIOD->OTYPER = 0x00000000;
	GPIOD->OSPEEDR = 0x00000000;
	GPIOD->PUPDR = 0x00000000;

}

void leddriver_on(void)
{
	GPIOD->ODR = 0x00001000;
}

void leddriver_off(void)
{
	GPIOD->ODR = 0x00000000;
}
