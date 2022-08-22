#include "port.h"
#include "mb.h"
#include "mb_m.h"
#include "mbport.h"

#if MB_MASTER_RTU_ENABLED > 0 || MB_MASTER_ASCII_ENABLED > 0

/* ----------------------- User defenitions ---------------------------------*/
static uint16_t timeout = 0;
volatile uint16_t counter = 0;

/* ----------------------- Start implementation -----------------------------*/
BOOL xMBMasterPortTimersInit( USHORT usTimeOut50us, void *dHTIM )
{
    return TRUE;
}

void vMBMasterPortTimersT35Enable()
{
}

void vMBMasterPortTimersConvertDelayEnable()
{

}

void vMBMasterPortTimersRespondTimeoutEnable()
{

}

void vMBMasterPortTimersDisable()
{
}

#endif
