/*
 * iex.h
 *
 *  Created on: Jun 27, 2021
 *      Author: Robi
 */

#ifndef INC_IEX_H_
#define INC_IEX_H_

#include "main.h"
//#include "usart.h"
//#include "stm32f1xx_hal_uart.h"

typedef unsigned int uint_32 ;
typedef unsigned short int uint_16 ;
typedef unsigned char uint_8 ;

extern uint8_t printf_buf[];
// ------------------------------------------------------
//          IEX Modules configuration setup
// ------------------------------------------------------


// ------------------------------------------------------

#define CLASS_MASK 0xF0       /* mask for class - command        */
#define DIR_MASK   0x08       /* mask for direction bit  */
#define ARG_MASK   0x07       /* mask for argument       */
#define IX_STATUS  0x04      /* Status Message Argument */

#define IX_DATA 0x38        /* binary inputs  */
#define QX_DATA 0x30        /* binary outputs */
#define IW_DATA 0x78        /* analog inputs  */
#define QW_DATA 0x70        /* analog outputs */

#define BAUDSYNC 0xF0       /* baud sync message (for autobaud sync of modules) */

// ------------- DEBUG PRINTFS --------------------------------------

#define CFGAPP_DEBUG_ENABLE             //!< Global Enable of debug printfs...  Generic levels: 0..only fatal err, 1..common ERRs, 2..report

//#define CAN_STD_MSG_ENABLE             //!< Enable of debug printfs for CAN STD messages


//#define CAN_NADFilter_VALUE 3805
#define CAN_NADFilter_VALUE NAD_default

//#define CFGAPP_DEBUG_LEVEL_CAN       11 //!< 0..no print, 1..Warnings, 2..RX parsed, 4..TX parsed, 8..RX raw, 16..TX raw, 256..Status Msgs, 512..BaudSync Mesgs
#define CFGAPP_DEBUG_LEVEL_CAN       39 //!< 0..no print, 1..Warnings, 2..RX parsed, 4..TX parsed, 8..RX raw, 16..TX raw, 256..Status Msgs, 512..BaudSync Mesgs
typedef struct {
//        int      Modbus;
//        int      TCP;
//        int      FP;
//        int      GUI;
//        int      Settings;
//        int      Cmd;
//        int      FTP;
    int      CAN;
} APP_DEBUG;

extern volatile APP_DEBUG AppDebug;
extern uint_32 CAN_NADFilter;


#ifdef CFGAPP_DEBUG_ENABLE


#define  APPDBG_PRINTF(Type,Level,...) \
    do {  if (AppDebug.Type > Level ) {sprintf (printf_buf,__VA_ARGS__); CDC_Transmit_FS(printf_buf, strlen(printf_buf));  } while (0)

#define  APPDBGB_PRINTF(Type,Level,...) \
    do { \
		  if (AppDebug.Type & Level ) { \
				sprintf (printf_buf,__VA_ARGS__); \
				CDC_Transmit_FS(printf_buf, strlen(printf_buf)); \
		  }; \
	} while (0)

#define  APPDBGBF_PRINTF(Type,Level,Nad,...) \
    do {  \
		   if (  (AppDebug.Type & Level ) && ( CAN_NADFilter == 0 || ( CAN_NADFilter != 0 && CAN_NADFilter == Nad ) ) ) { \
			   	   sprintf (printf_buf,__VA_ARGS__); \
			   	   CDC_Transmit_FS(printf_buf, strlen(printf_buf)); \
		   };  \
    } while (0)

#else
    #define  APPDBG_PRINTF(Type,Level,...) {}
    #define  APPDBGB_PRINTF(Type,Level,...) {}
	#define  APPDBGBF_PRINTF(Type,Level,Nad,...) {}
#endif




uint_32 CANBus_Parse_RX_Message (uint_32 ID,uint_32 msg_size, unsigned char dptr []);
void IEX_Init (void) ;
char * parse_iex_command(volatile unsigned char cmd);
void CANBus_print_message (uint8_t TXbuffer[],  uint8_t MData[],uint8_t MLen);



#endif /* INC_IEX_H_ */
