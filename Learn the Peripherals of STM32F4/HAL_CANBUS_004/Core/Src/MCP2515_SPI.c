/*
 * MCP2515_SPI.c
 *
 *  Created on: Jan 27, 2024
 *      Author: erkan
 */

#include "main.h"
#include "stdbool.h"
#include "MCP2515_SPI.h"

#define MCP2515_CS_LOW() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0)
#define MCP2515_CS_HIGH() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1)

uint8_t loop = 0;

bool MCP2515_SPI_Initialize(void)
{
	  MCP2515_CS_HIGH();

	  uint8_t loop = 10;

	  do {

	    if(HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_READY)
	      return true;

	    loop--;
	  } while(loop > 0);

	  return false;
}

bool MCP2515_SetConfigMode(void)
{
	MCP2515_WriteByte(MCP2515_CANCTRL,0x80);

	loop = 10;

	do {
		if((MCP2515_ReadByte(MCP2515_CANSTAT) & 0xE0) == 0x80)
			return true;

	    loop--;
	} while(loop > 0);

	return false;
}

bool MCP2515_SetNormalMode(void)
{
	MCP2515_WriteByte(MCP2515_CANCTRL,0x00);

	loop = 10;

	do {
		if((MCP2515_ReadByte(MCP2515_CANSTAT) & 0xE0) == 0x00)
			return true;

	    loop--;
	} while(loop > 0);

	return false;
}

bool MCP2515_SetSleepMode(void)
{
	MCP2515_WriteByte(MCP2515_CANCTRL,0x20);

	loop = 10;

	do {
		if((MCP2515_ReadByte(MCP2515_CANSTAT) & 0xE0) == 0x20)
			return true;

	    loop--;
	} while(loop > 0);

	return false;
}

bool MCP2515_SetLoopBackMode(void)
{
	MCP2515_WriteByte(MCP2515_CANCTRL,0x40);

	loop = 10;

	do {
		if((MCP2515_ReadByte(MCP2515_CANSTAT) & 0xE0) == 0x40)
			return true;

	    loop--;
	} while(loop > 0);

	return false;
}

bool MCP2515_SetListenOnlyMode(void)
{
	MCP2515_WriteByte(MCP2515_CANCTRL,0x60);

	loop = 10;

	do {
		if((MCP2515_ReadByte(MCP2515_CANSTAT) & 0xE0) == 0x60)
			return true;

	    loop--;
	} while(loop > 0);

	return false;
}


void MCP2515_Reset(void)
{
	MCP2515_CS_LOW();

	MCP2515_SPI_Transfer(MCP2515_RESET);

	MCP2515_CS_HIGH();
}

void MCP2515_SPI_Transfer(uint8_t data)
{
	HAL_SPI_Transmit(&hspi1,&data ,1, 100);
}

void MCP2515_SPI_TransferBuffer(uint8_t data, uint8_t length)
{
  HAL_SPI_Transmit(&hspi1, &data, length, 100);
}

uint8_t MCP2515_SPI_Receive(void)
{
  uint8_t returnVal;

  HAL_SPI_Receive(&hspi1, &returnVal, 1, 100);

  return returnVal;
}

void MCP2515_SPI_ReceiveBuffer(uint8_t returnVal,uint8_t length)
{
	HAL_SPI_Receive(&hspi1,&returnVal,length,100);
}

uint8_t MCP2515_ReadByte(uint8_t address)
{
  uint8_t returnVal;

  MCP2515_CS_LOW();

  MCP2515_SPI_Transfer(MCP2515_READ); // Read Instruction Byte
  MCP2515_SPI_Transfer(address);      // Address Byte
  returnVal = MCP2515_SPI_Receive();  // Data Return

  MCP2515_CS_HIGH();

  return returnVal;
}

void MCP2515_WriteByte(uint8_t address,uint8_t data)
{
	MCP2515_CS_LOW();

	MCP2515_SPI_Transfer(MCP2515_WRITE); // Write Instruction Byte
	MCP2515_SPI_Transfer(address);       // Address Byte
	MCP2515_SPI_Transfer(data);          // Data Output

	MCP2515_CS_HIGH();
}

void MCP2515_BitModify(uint8_t address,uint8_t mask,uint8_t data)
{
	MCP2515_CS_LOW();

	MCP2515_SPI_Transfer(MCP2515_BITMODIFY);
	MCP2515_SPI_Transfer(address);
	MCP2515_SPI_Transfer(mask);
	MCP2515_SPI_Transfer(data);

	MCP2515_CS_HIGH();
}

void MCP2515_ReadRxBuffer(uint8_t instruction,uint8_t data,uint8_t length)
{
	MCP2515_CS_LOW();

	MCP2515_SPI_Transfer(instruction);
	MCP2515_SPI_ReceiveBuffer(data,length);

	MCP2515_CS_HIGH();
}

uint8_t MCP2515_ReadStatus()
{
	uint8_t returnVal;

	MCP2515_CS_LOW();

	MCP2515_SPI_Transfer(MCP2515_READSTATUS);
	returnVal = MCP2515_SPI_Receive();

	MCP2515_CS_HIGH();

	return returnVal;
}

uint8_t MCP2515_RxStatus()
{
	uint8_t returnVal;

	MCP2515_CS_LOW();

	MCP2515_SPI_Transfer(MCP2515_RXSTATUS);
	returnVal = MCP2515_SPI_Receive();

	MCP2515_CS_HIGH();

	return returnVal;
}

void MCP2515_RequestToSend(uint8_t instruction)
{
	MCP2515_CS_LOW();

	MCP2515_SPI_Transfer(instruction);

	MCP2515_CS_HIGH();
}

void MCP2515_LoadTxBuffer(uint8_t instruction,uint8_t data)
{
	MCP2515_CS_LOW();

	MCP2515_SPI_Transfer(instruction);
	MCP2515_SPI_Transfer(data);

	MCP2515_CS_HIGH();
}



void MCP2515_ReadRxSequence(uint8_t instruction,uint8_t data,uint8_t length)
{
	MCP2515_CS_LOW();

	MCP2515_SPI_ReceiveBuffer(data,length);

	MCP2515_CS_HIGH();
}

void MCP2515_LoadTxSequence(uint8_t instruction,uint8_t idReg,uint8_t dlc,uint8_t data)
{
	MCP2515_CS_LOW();

	MCP2515_SPI_Transfer(instruction);
	MCP2515_SPI_TransferBuffer(idReg, 4);
	MCP2515_SPI_Transfer(dlc);
	MCP2515_SPI_TransferBuffer(data,dlc);

	MCP2515_CS_HIGH();
}


void MCP2515_WriteByteSequence(uint8_t startAddress, uint8_t endAddress, uint8_t data)
{
  MCP2515_CS_LOW();

  MCP2515_SPI_Transfer(MCP2515_WRITE);
  MCP2515_SPI_Transfer(startAddress);
  MCP2515_SPI_TransferBuffer(data, (endAddress - startAddress + 1));

  MCP2515_CS_HIGH();
}
