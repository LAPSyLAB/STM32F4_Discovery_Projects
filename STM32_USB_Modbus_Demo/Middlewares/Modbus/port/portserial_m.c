#include "port.h"
#include "mb.h"
#include "mbport.h"

#if MB_MASTER_RTU_ENABLED > 0 || MB_MASTER_ASCII_ENABLED > 0

/* ----------------------- Static variables ---------------------------------*/
static uint8_t singlechar;

/* ----------------------- User defenitions ---------------------------------*/
//#define RS485_MASTER_RTS_LOW	HAL_GPIO_WritePin(RS485_RTS_GPIO_Port, RS485_RTS_Pin, GPIO_PIN_RESET)
//#define RS485_MASTER_RTS_HIGH 	HAL_GPIO_WritePin(RS485_RTS_GPIO_Port, RS485_RTS_Pin, GPIO_PIN_SET)

#define RS485_MASTER_RTS_LOW
#define RS485_MASTER_RTS_HIGH

/* ----------------------- Start implementation -----------------------------*/

BOOL xMBMasterPortSerialInit(void *dHUART, ULONG ulBaudRate, void *dHTIM)
{

	return TRUE;
}

void vMBMasterPortSerialEnable(BOOL xRxEnable, BOOL xTxEnable)
{

}

void vMBMasterPortClose(void)
{
}

BOOL xMBMasterPortSerialPutBytes(volatile UCHAR *ucByte, USHORT usSize)
{
	return TRUE;
}

BOOL xMBMasterPortSerialPutByte(CHAR ucByte)
{
	return TRUE;
}

BOOL xMBMasterPortSerialGetByte(CHAR * pucByte)
{
	return TRUE;
}


#endif
