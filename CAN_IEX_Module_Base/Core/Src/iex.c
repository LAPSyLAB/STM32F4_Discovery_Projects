/*
 * iex.c
 *
 *  Created on: Jun 27, 2021
 *      Author: Robi
 */

#include "main.h"
#include "iex.h"
#include "can.h"

//#include "stm32f1xx_hal_uart.h"

uint_32 CAN_NADFilter=0, CAN;
volatile APP_DEBUG AppDebug;


volatile char iex_got_output_data_bits0[10]    ="OUTBITS_0";
volatile char iex_send_input_data_bits0[10]    ="INPBITS_0";
volatile char iex_send_input_data_words0[11]   ="INPWORDS_0";
volatile char iex_send_input_data_words4[11]   ="INPWORDS_4";
volatile char iex_send_status_data_bits0[10]   ="STATUS";
volatile char iex_got_output_data_words0[11]   ="OUTWORDS_0";
volatile char iex_got_output_system_words0[11] ="OUTWORDS_S";
volatile char iex_got_direction_from_plc[6]   ="P-->I";
volatile char iex_got_direction_from_iex[6]   ="P<--I";
volatile char iex_got_unknown[5]="????";

volatile char temp_str[64];


char * parse_iex_command(volatile unsigned char cmd);
void CANBus_print_message (uint8_t TXbuffer[],  uint8_t MData[],uint8_t MLen);





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
  int iex_slot;
  uint_8 bitmask, iex_dir, iex_class;
  uint_16 ix_temp;



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
                              APPDBGBF_PRINTF(CAN,2,iex_NAD,"CAN_RX[%5d]: IX_DATA_%2d :  0x%02x  |Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d|IX:0x%02x \r\n", iex_NAD, iex_arg*4, ix_temp, iex_class, iex_dir, iex_arg, iex_NAD, msg_size,ix_temp);

                      } else if  ( (msg_size == 2)  && (iex_arg == 0) ) {    /* IX_DATA 2 bytes message  inputs 0-15 */
                              ix_temp = dptr[0]+dptr[1]*256;
                              bitmask = 0x0001;
                              APPDBGBF_PRINTF(CAN,2,iex_NAD,"CAN_RX[%5d]: IX_DATA_%2d :0x%04x  |Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d|IX:0x%04x \r\n", iex_NAD, iex_arg*4, ix_temp, iex_class, iex_dir, iex_arg, iex_NAD, msg_size,ix_temp);

                      } else {
                              APPDBGBF_PRINTF(CAN,1,iex_NAD,"CAN_RX[WARN]: CANBus_Parse_RX_Message: unsupported IXDATA CAN message: Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d|0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\r\n", iex_class, iex_dir, iex_arg, iex_NAD, msg_size,dptr[0],dptr[1],dptr[2],dptr[3],dptr[4],dptr[5],dptr[6],dptr[7]);

                      }


              } else if ((iex_cmd & (CLASS_MASK | DIR_MASK))== QX_DATA)  {       /* group of IX variables */
                      if  ( (msg_size == 1)  && (iex_arg == 0) ) {
                              ix_temp = dptr[0];
                              bitmask = 0x01;
                              APPDBGBF_PRINTF(CAN,2,iex_NAD,"CAN_RX[%5d]: QX_DATA_%2d :  0x%02x  |Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d|IX:0x%02x \r\n", iex_NAD, iex_arg*4, ix_temp, iex_class, iex_dir, iex_arg, iex_NAD, msg_size,ix_temp);

                              if (iex_NAD == NAD_default)  { // Message for this node - transfer QX data to actual outputs - LEDs !!!
                         	  	 // TODO: Transfer received outputs state to real pins

                              }

                      } else if  ( (msg_size >= 2) && (iex_arg == 0) ) {
                              ix_temp = dptr[0]*256+dptr[1];
                              bitmask = 0x0001;
                              APPDBGBF_PRINTF(CAN,2,iex_NAD,"CAN_RX[%5d]: QX_DATA_%2d :0x%04x  |Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d|IX:0x%04x \r\n", iex_NAD, iex_arg*4, ix_temp, iex_class, iex_dir, iex_arg, iex_NAD, msg_size,ix_temp);

                      } else {
                              APPDBGBF_PRINTF(CAN,1,iex_NAD,"CAN_RX[WARN]: CANBus_Parse_RX_Message: unsupported QXDATA CAN message: Class:%d|Dir:%d|Arg:%d|NAD:%d|Len:%d|0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\r\n", iex_class, iex_dir, iex_arg, iex_NAD, msg_size,dptr[0],dptr[1],dptr[2],dptr[3],dptr[4],dptr[5],dptr[6],dptr[7]);

                      }
              } else if ((iex_cmd & (CLASS_MASK | DIR_MASK))==IW_DATA) {    /* group of IW variables */

                      APPDBGBF_PRINTF(CAN,2,iex_NAD,"CAN_RX[%5d]: IW_DATA_%2d :|Class:%d|Dir:%d|Arg:%d|NAD:%5d|Len:%d| %2d:[%5d] %2d:[%5d] %2d:[%5d] %2d:[%5d]\r\n", iex_NAD, iex_arg*4, iex_class, iex_dir, iex_arg, iex_NAD, msg_size, iex_arg*4,dptr[0]*256 + dptr[1], iex_arg*4+1,dptr[2]*256 + dptr[3], iex_arg*4+2,dptr[4]*256 + dptr[5], iex_arg*4+3,dptr[6]*256 + dptr[7]);


              } else if ((iex_cmd & (CLASS_MASK | DIR_MASK))==QW_DATA) {    /* group of QW variables */
                     APPDBGBF_PRINTF(CAN,2,iex_NAD,"CAN_RX[%5d]: QW_DATA_%2d :|Class:%d|Dir:%d|Arg:%d|NAD:%5d|Len:%d| %2d:[%5d] %2d:[%5d] %2d:[%5d] %2d:[%5d]\r\n", iex_NAD, iex_arg*4, iex_class, iex_dir, iex_arg, iex_NAD, msg_size, iex_arg*4,dptr[0]*256 + dptr[1], iex_arg*4+1,dptr[2]*256 + dptr[3], iex_arg*4+2,dptr[4]*256 + dptr[5], iex_arg*4+3,dptr[6]*256 + dptr[7]);


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





//*----------------------------------------------------------------------------
/*! \fn char CANSend(volatile unsigned long Id, volatile unsigned char MessageData[],volatile unsigned char MessageLen,volatile unsigned char MessageType, volatile unsigned char Debug)
    \brief Main CANBUS sending procedure.\n\n
    Tries to send CAN message for CAN_SEND_RETRIES times, otherwise continues...
     */
//*----------------------------------------------------------------------------
unsigned char CANBus_Send(volatile unsigned long Id, volatile unsigned char MessageData[],volatile unsigned char MessageLen,volatile unsigned char MessageType, volatile unsigned char Debug)
{

volatile unsigned char ret;
CAN_TxHeaderTypeDef TxHeader;
uint8_t TxData[8], iex_cmd, ii, pos, temp;
uint32_t TxMailbox;
HAL_StatusTypeDef RetVal;
long iex_NAD;
uint8_t TXbuffer[256];

iex_NAD = Id & 0x1fffff;
iex_cmd = Id>>21;

	TxHeader.ExtId = Id;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_EXT;
	TxHeader.DLC = MessageLen;
	TxHeader.TransmitGlobalTime = DISABLE;

	for (ii=0;ii<MessageLen;ii++) {
		TxData[ii] = MessageData[ii];
	}

	RetVal = HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);


	if ( RetVal == HAL_OK) {

		pos = sprintf(TXbuffer,"TX_CAN: EXT %#10lx | %12s (%x),   NAD: %5.0ld | %hu ",TxHeader.ExtId,parse_iex_command(iex_cmd),iex_cmd,iex_NAD,MessageLen );

	} else {

		pos = sprintf(TXbuffer,"TX_ERR[%d]: EXT %#10lx | %12s (%x),   NAD: %5.0ld | %hu ",RetVal,TxHeader.ExtId,parse_iex_command(iex_cmd),iex_cmd,iex_NAD,MessageLen );

    };
	CANBus_print_message (&TXbuffer[pos],TxData,MessageLen);

    APPDBGBF_PRINTF(CAN,4,iex_NAD,"%s", TXbuffer);

//	for (ii=0;ii<MessageLen;ii++) {
//		APPDBGBF_PRINTF(CAN,4,iex_NAD,"|%2x",TxData[ii]);
//	}
//
//	APPDBGBF_PRINTF(CAN,4,iex_NAD,"\r\n" );




return ret;
}


//*----------------------------------------------------------------------------
/*! \fn void  print_message ( unsigned char MData[],unsigned char MLen)
    \brief Prints CAN MEssage on debug channel.
    */
//*----------------------------------------------------------------------------
void CANBus_print_message (uint8_t TXbuffer[],  uint8_t MData[],uint8_t MLen)
{
	uint8_t pos=0,temp;

	unsigned char i;
	if (MLen > 8) {
		sprintf(TXbuffer,"ERR:CAN Message too long: %d\r\n",MLen);
		MLen=8;
	} else {

		for ( i = 0; i < MLen; i++ ) {
			  temp = sprintf(TXbuffer+pos,"|%02x",MData[i]);
			  pos += temp;
		}
		sprintf(TXbuffer+pos,"\r\n\r\n");

	}

}




//*----------------------------------------------------------------------------
/*! \fn char *parse_iex_command(volatile unsigned char cmd)
    \brief Returns pointer to text description of IEX2 protocol command.
    */
//*----------------------------------------------------------------------------
char * parse_iex_command(volatile unsigned char cmd)
{
volatile char *temp_pt, masked_cmd, masked_dir, masked_arg, temp;
  masked_cmd = cmd & 0xf0;
  masked_dir = cmd & 0x08;
  masked_arg = cmd & 0x07;


  if ((masked_cmd == IEX2_CMD_COMMAND_BIT_DATA) && (masked_dir == 0)) {
//   		TRACE_TPRINT ("PARSE IEX2 COMMAND | Got a match : %2x == %2x\r\n",cmd,IEX2_CMD_GOT_QX0_STATUS);
       if (masked_arg >= 4) {
       		sprintf(temp_str,"OUTSYSBITS %2d", masked_arg << 2);
       } else {
       		sprintf(temp_str,"OUTBITS %2d", masked_arg << 2);
       };
   } else if ((masked_cmd == IEX2_CMD_COMMAND_BIT_DATA) && (masked_dir)) {
//   		TRACE_TPRINT ("PARSE IEX2 COMMAND | Got a match : %2x == %2x\r\n",cmd,IEX2_CMD_SEND_IX0_STATUS);
       if (masked_arg == 4) {
       		sprintf(temp_str,"STATUSBITS %2d", masked_arg << 2);
       } else if (masked_arg > 4) {
       		sprintf(temp_str,"INPSYSBITS %2d", masked_arg << 2);
       } else {
       		sprintf(temp_str,"INPBITS  %2d", masked_arg << 2);
       };
   } else if ((masked_cmd == IEX2_CMD_COMMAND_WORD_DATA) && (masked_dir == 0)) {
//   		TRACE_TPRINT ("PARSE IEX2 COMMAND | Got a match : %2x == %2x\r\n",cmd,IEX2_CMD_SEND_ONBUS_STATUS);
       if (masked_arg >= 4) {
       		sprintf(temp_str,"OUTSYSWORDS %2d", masked_arg << 2);
       } else {
       		sprintf(temp_str,"OUTWORDS %2d", masked_arg << 2);
       };
   } else if ((masked_cmd == IEX2_CMD_COMMAND_WORD_DATA) && (masked_dir)) {
//   		TRACE_TPRINT ("PARSE IEX2 COMMAND | Got a match : %2x == %2x\r\n",cmd,IEX2_CMD_GOT_QW0_STATUS);
       sprintf(temp_str,"INPWORDS  %2d", masked_arg << 2);
   } else if ((masked_cmd == IEX2_CMD_COMMAND_READ_PLC) && (masked_dir))  {
//   		TRACE_TPRINT ("PARSE IEX2 COMMAND | Got a match : %2x == %2x\r\n",cmd,IEX2_CMD_GOT_QW16_STATUS);
       sprintf(temp_str,"READ_PLC %2d", masked_arg);
  } else if ((masked_cmd == IEX2_CMD_COMMAND_WRITE_PLC ))  {
//   		TRACE_TPRINT ("PARSE IEX2 COMMAND | Got a match : %2x == %2x\r\n",cmd,IEX2_CMD_SEND_IW0_STATUS );
       sprintf(temp_str,"WRITE_PLC %2d", masked_arg);
  } else if ((masked_cmd == IEX2_CMD_COMMAND_BOOTLOADER ))  {
//   		TRACE_TPRINT ("PARSE IEX2 COMMAND | Got a match : %2x == %2x\r\n",cmd,IEX2_CMD_SEND_IW0_STATUS );
       sprintf(temp_str,"BOOT_LOADER %2d", masked_arg);
   } else {
//   		TRACE_TPRINT ("PARSE IEX2 COMMAND | No match : %2x == %s\r\n",cmd,iex_got_unknown);
       sprintf(temp_str,"??? Unknown %2d", masked_arg);
   };

   return(&temp_str[0]);
}



//*----------------------------------------------------------------------------
/*! \fn char *parse_iex_direction(volatile unsigned char cmd)
    \brief Returns pointer to text description of direction of IEX2 command.
    */
//*----------------------------------------------------------------------------
char *parse_iex_direction(volatile unsigned char cmd)
{
volatile char *temp;
  if (cmd & 0x08) {
	   temp=iex_got_direction_from_iex;
   } else {
	   temp=iex_got_direction_from_plc;
   };
   return(temp);
}

