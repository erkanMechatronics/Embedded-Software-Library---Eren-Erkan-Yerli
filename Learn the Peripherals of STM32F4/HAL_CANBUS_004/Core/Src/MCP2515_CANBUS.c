/*
 * MCP2515_CANBUS.c
 *
 *  Created on: Jan 27, 2024
 *      Author: erkan
 */

#include "main.h"
#include "stdbool.h"
#include "MCP2515_CANBUS.h"
#include "MCP2515_SPI.h"

static uint32_t convertReg2ExtendedCANid(uint8_t tempRXBn_EIDH, uint8_t tempRXBn_EIDL, uint8_t tempRXBn_SIDH, uint8_t tempRXBn_SIDL);
static uint32_t convertReg2StandardCANid(uint8_t tempRXBn_SIDH, uint8_t tempRXBn_SIDL) ;
static void convertCANid2Reg(uint32_t tempPassedInID, uint8_t canIdType, id_reg_t *passedIdReg);

ctrl_status_t ctrlStatus;
ctrl_error_status_t errorStatus;
id_reg_t idReg;


bool CANSPI_Initialize(void)
{
	RXF0 RXF0reg;
	RXF1 RXF1reg;
	RXF2 RXF2reg;
	RXF3 RXF3reg;
	RXF4 RXF4reg;
	RXF5 RXF5reg;
	RXM0 RXM0reg;
	RXM1 RXM1reg;

	// Rx Mask Values
	RXM0reg.RXM0SIDH = 0x00;
	RXM0reg.RXM0SIDL = 0x00;
	RXM0reg.RXM0EID8 = 0x00;
	RXM0reg.RXM0EID0 = 0x00;

	RXM1reg.RXM1SIDH = 0x00;
	RXM1reg.RXM1SIDL = 0x00;
	RXM1reg.RXM1EID8 = 0x00;
	RXM1reg.RXM1EID0 = 0x00;

	  /* Rx Filter values */
	RXF0reg.RXF0SIDH = 0x00;
	RXF0reg.RXF0SIDL = 0x00;
	RXF0reg.RXF0EID8 = 0x00;
	RXF0reg.RXF0EID0 = 0x00;

	RXF1reg.RXF1SIDH = 0x00;
	RXF1reg.RXF1SIDL = 0x08;
	RXF1reg.RXF1EID8 = 0x00;
	RXF1reg.RXF1EID0 = 0x00;

	RXF2reg.RXF2SIDH = 0x00;
	RXF2reg.RXF2SIDL = 0x00;
	RXF2reg.RXF2EID8 = 0x00;
	RXF2reg.RXF2EID0 = 0x00;

	RXF3reg.RXF3SIDH = 0x00;
	RXF3reg.RXF3SIDL = 0x00;
	RXF3reg.RXF3EID8 = 0x00;
	RXF3reg.RXF3EID0 = 0x00;

	RXF4reg.RXF4SIDH = 0x00;
	RXF4reg.RXF4SIDL = 0x00;
	RXF4reg.RXF4EID8 = 0x00;
	RXF4reg.RXF4EID0 = 0x00;

	RXF5reg.RXF5SIDH = 0x00;
	RXF5reg.RXF5SIDL = 0x08;
	RXF5reg.RXF5EID8 = 0x00;
	RXF5reg.RXF5EID0 = 0x00;


	if(!MCP2515_SPI_Initialize())
	    return false;

	if(!MCP2515_SetConfigMode())
		return false;

	MCP2515_WriteByteSequence(MCP2515_RXM0SIDH, MCP2515_RXM0EID0,RXM0reg.RXM0SIDH);
	MCP2515_WriteByteSequence(MCP2515_RXM1SIDH, MCP2515_RXM1EID0,RXM1reg.RXM1SIDH);
	MCP2515_WriteByteSequence(MCP2515_RXF0SIDH, MCP2515_RXF0EID0,RXF0reg.RXF0SIDH);
	MCP2515_WriteByteSequence(MCP2515_RXF1SIDH, MCP2515_RXF1EID0,RXF1reg.RXF1SIDH);
	MCP2515_WriteByteSequence(MCP2515_RXF2SIDH, MCP2515_RXF2EID0,RXF2reg.RXF2SIDH);
	MCP2515_WriteByteSequence(MCP2515_RXF3SIDH, MCP2515_RXF3EID0,RXF3reg.RXF3SIDH);
	MCP2515_WriteByteSequence(MCP2515_RXF4SIDH, MCP2515_RXF4EID0,RXF4reg.RXF4SIDH);
	MCP2515_WriteByteSequence(MCP2515_RXF5SIDH, MCP2515_RXF5EID0,RXF5reg.RXF5SIDH);

	MCP2515_WriteByte(MCP2515_RXB0CTRL, 0x04);
	MCP2515_WriteByte(MCP2515_RXB1CTRL, 0x01);

	MCP2515_WriteByte(MCP2515_CNF1, 0x00);

	MCP2515_WriteByte(MCP2515_CNF2, 0xE5);

	MCP2515_WriteByte(MCP2515_CNF3, 0x83);

	if(!MCP2515_SetNormalMode())
		return false;

	return true;
}

uint8_t CANSPI_Transmit(uCAN_MSG *tempCanMsg)
{
	uint8_t returnValue = 0;

	idReg.tempSIDH = 0;
	idReg.tempSIDL = 0;
	idReg.tempEID8 = 0;
	idReg.tempEID0 = 0;

	ctrlStatus.ctrl_status = MCP2515_ReadStatus();

	if(ctrlStatus.TXB0REQ != 1)
	{
		convertCANid2Reg(tempCanMsg->frame.id, tempCanMsg->frame.idType, &idReg);
		MCP2515_LoadTxSequence(MCP2515_LOAD_TXB0SIDH, &(idReg.tempSIDH), tempCanMsg->frame.dlc, &(tempCanMsg->frame.data0));
		MCP2515_RequestToSend(MCP2515_RTS_TXB0);

	}
	else if (ctrlStatus.TXB1REQ != 1)
	{
	    convertCANid2Reg(tempCanMsg->frame.id, tempCanMsg->frame.idType, &idReg);
	    MCP2515_LoadTxSequence(MCP2515_LOAD_TXB1SIDH, &(idReg.tempSIDH), tempCanMsg->frame.dlc, &(tempCanMsg->frame.data0));
	    MCP2515_RequestToSend(MCP2515_RTS_TXB1);

	    returnValue = 1;
	}
	else if (ctrlStatus.TXB2REQ != 1)
	{
		convertCANid2Reg(tempCanMsg->frame.id, tempCanMsg->frame.idType, &idReg);
		MCP2515_LoadTxSequence(MCP2515_LOAD_TXB2SIDH, &(idReg.tempSIDH), tempCanMsg->frame.dlc, &(tempCanMsg->frame.data0));
		MCP2515_RequestToSend(MCP2515_RTS_TXB2);

		returnValue = 1;
	}

	return (returnValue);
}







