/*
 * iex.c
 *
 *  Created on: Jun 27, 2021
 *      Author: Robi
 */

#include "main.h"
#include "iex.h"

//#include "stm32f1xx_hal_uart.h"

uint_32 CAN_NADFilter=0, CAN;
volatile APP_DEBUG AppDebug;

void IEX_Init (void)
{
	AppDebug.CAN = CFGAPP_DEBUG_LEVEL_CAN;
	CAN_NADFilter= CAN_NADFilter_VALUE;

}

/** @brief Prepares D13 ERR data to be sent to TCP server.
 *
  */
uint_32 CANBus_Parse_RX_Message (uint_32 ID,uint_32 msg_size, unsigned char dptr [])
{
  int iex_cmd;
  long iex_NAD;
  int iex_arg;
  int slot;
  int card_id;
  int iex_slot;
  uint_8 ii, iex_dir, iex_class;
  uint_16 ix_temp,bitmask;
  int maxi;


  iex_cmd = ID >> 21;
  iex_NAD = ID & 0x1fffff;
  iex_arg = iex_cmd & ARG_MASK;
  iex_dir = (iex_cmd & DIR_MASK) >> 3;
  iex_class = (iex_cmd & CLASS_MASK) >> 4 ;

  if (msg_size >= 0) {
	  iex_slot = 0;  //not used


      if (1) {
           if ( 1 ) {

              if ((iex_cmd & (CLASS_MASK | DIR_MASK))== IX_DATA)  {       /* group of IX variables */
                      if (iex_arg==IX_STATUS)   {  /* Status ID message */

                              if (msg_size==4) {
                                /* statusno sporocilo : status + card_id */

                                APPDBGBF_PRINTF(CAN,256,iex_NAD,"CAN_RX[%5d]: IX_STATUS_ :  Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d| CardID: %d  StatBits: 0x%02x \r\n", iex_NAD, iex_class, iex_dir, iex_arg, iex_NAD, msg_size,dptr[2]*256+dptr[3],dptr[0]*256+dptr[1]);

                              } else {
                                APPDBGBF_PRINTF(CAN,1,iex_NAD,"CAN_RX[WARN]: CANBus_Parse_RX_Message: STATUS_ID CAN message with wrong length: Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d\r\n", iex_class, iex_dir, iex_arg, iex_NAD, msg_size);
                              }
                      } else if  ( msg_size == 1 )  {  /* IX_DATA 1 byte message with arg=0,1,2 (newer modules send such messages) */
                              ix_temp = dptr[0];
                              bitmask = 0x01;
                              APPDBGBF_PRINTF(CAN,2,iex_NAD,"CAN_RX[%5d]: IX_DATA_%2d :  0x%02x  |Slot:%d|Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d|IX:0x%02x \r\n", iex_NAD, iex_arg*4, ix_temp, iex_slot, iex_class, iex_dir, iex_arg, iex_NAD, msg_size,ix_temp);

                      } else if  ( (msg_size == 2)  && (iex_arg == 0) ) {    /* IX_DATA 2 bytes message  inputs 0-15 */
                              ix_temp = dptr[0]+dptr[1]*256;
                              bitmask = 0x0001;
                              APPDBGBF_PRINTF(CAN,2,iex_NAD,"CAN_RX[%5d]: IX_DATA_%2d :0x%04x  |Slot:%d|Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d|IX:0x%04x \r\n", iex_NAD, iex_arg*4, ix_temp, iex_slot, iex_class, iex_dir, iex_arg, iex_NAD, msg_size,ix_temp);

                      } else {
                              APPDBGBF_PRINTF(CAN,1,iex_NAD,"CAN_RX[WARN]: CANBus_Parse_RX_Message: unsupported IXDATA CAN message: Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d|0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\r\n", iex_class, iex_dir, iex_arg, iex_NAD, msg_size,dptr[0],dptr[1],dptr[2],dptr[3],dptr[4],dptr[5],dptr[6],dptr[7]);

                      }


              } else if ((iex_cmd & (CLASS_MASK | DIR_MASK))== QX_DATA)  {       /* group of IX variables */
                      if  ( (msg_size == 1)  && (iex_arg == 0) ) {
                              ix_temp = dptr[0];
                              bitmask = 0x01;
                              APPDBGBF_PRINTF(CAN,2,iex_NAD,"CAN_RX[%5d]: QX_DATA_%2d :  0x%02x  |Slot:%d|Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d|IX:0x%02x \r\n", iex_NAD, iex_arg*4, ix_temp, iex_slot, iex_class, iex_dir, iex_arg, iex_NAD, msg_size,ix_temp);

                      } else if  ( (msg_size >= 2) && (iex_arg == 0) ) {
                              ix_temp = dptr[0]*256+dptr[1];
                              bitmask = 0x0001;
                              APPDBGBF_PRINTF(CAN,2,iex_NAD,"CAN_RX[%5d]: QX_DATA_%2d :0x%04x  |Slot:%d|Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d|IX:0x%04x \r\n", iex_NAD, iex_arg*4, ix_temp, iex_slot, iex_class, iex_dir, iex_arg, iex_NAD, msg_size,ix_temp);

                      } else {
                              APPDBGBF_PRINTF(CAN,1,iex_NAD,"CAN_RX[WARN]: CANBus_Parse_RX_Message: unsupported QXDATA CAN message: Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d|0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\r\n", iex_class, iex_dir, iex_arg, iex_NAD, msg_size,dptr[0],dptr[1],dptr[2],dptr[3],dptr[4],dptr[5],dptr[6],dptr[7]);

                      }
              } else if ((iex_cmd & (CLASS_MASK | DIR_MASK))==IW_DATA) {    /* group of IW variables */

                      APPDBGBF_PRINTF(CAN,2,iex_NAD,"CAN_RX[%5d]: IW_DATA_%2d :|Slot:%d|Class:%d|Dir:%d|Arg:%d|NAD:%5d|Len:%d| %2d:[%5d] %2d:[%5d] %2d:[%5d] %2d:[%5d]\r\n", iex_NAD, iex_arg*4, iex_slot, iex_class, iex_dir, iex_arg, iex_NAD, msg_size, iex_arg*4,dptr[0]*256 + dptr[1], iex_arg*4+1,dptr[2]*256 + dptr[3], iex_arg*4+2,dptr[4]*256 + dptr[5], iex_arg*4+3,dptr[6]*256 + dptr[7]);


              } else if ((iex_cmd & (CLASS_MASK | DIR_MASK))==QW_DATA) {    /* group of QW variables */
                     APPDBGBF_PRINTF(CAN,2,iex_NAD,"CAN_RX[%5d]: QW_DATA_%2d :|Slot:%d|Class:%d|Dir:%d|Arg:%d|NAD:%5d|Len:%d| %2d:[%5d] %2d:[%5d] %2d:[%5d] %2d:[%5d]\r\n", iex_NAD, iex_arg*4, iex_slot, iex_class, iex_dir, iex_arg, iex_NAD, msg_size, iex_arg*4,dptr[0]*256 + dptr[1], iex_arg*4+1,dptr[2]*256 + dptr[3], iex_arg*4+2,dptr[4]*256 + dptr[5], iex_arg*4+3,dptr[6]*256 + dptr[7]);


              } else if ((iex_cmd & (CLASS_MASK))==BAUDSYNC) {    /* group of QW variables */
                   APPDBGBF_PRINTF(CAN,512,iex_NAD,"CAN_RX[%5d]: BAUDSYNC_ :  Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d|\r\n", iex_NAD, iex_class, iex_dir, iex_arg, iex_NAD, msg_size);


              } else {
                              APPDBGBF_PRINTF(CAN,1,iex_NAD,"CAN_RX[WARN]: CANBus_Parse_RX_Message: unknown CAN message: Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d|0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\r\n", iex_class, iex_dir, iex_arg, iex_NAD, msg_size,dptr[0],dptr[1],dptr[2],dptr[3],dptr[4],dptr[5],dptr[6],dptr[7]);

              }

        }  else {     // Message from unknown module (not yet present in )


        }


      } //if ( FPData.Sett.CAN_NADFilter.Val == 0 ||


  }   //   if (msg_size > 0) {

}
