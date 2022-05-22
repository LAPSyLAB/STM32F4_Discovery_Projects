/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

#define NAD_default (long)750				// Defines Node V1 NAD for IEX

// These are IDs that are reported to IEX master for module identification (read appropriate .cym files)
#define IEX2_CYM_ID_V1     250   // 255 is max, select unique ID, also specified in .cym file


#define IEX2_DIRECTION_NODE2RC  0x1000000
#define IEX2_DIRECTION_RC2NODE  0x0000000

#define IEX2_COMMAND_BIT_DATA   0x6000000
#define IEX2_COMMAND_WORD_DATA  0xe000000

#define IEX2_ARGUMENT_IO_DATA0   0x000000
#define IEX2_ARGUMENT_IO_DATA4   0x200000
#define IEX2_ARGUMENT_SYS_DATA16 0x800000

//const unsigned long status_id=NAD + 0x7800000 ;
#define IEX2_ID_SEND_ONBUS_STATUS  (IEX2_COMMAND_BIT_DATA | IEX2_DIRECTION_NODE2RC | IEX2_ARGUMENT_SYS_DATA16)

// IX_id=NAD_v1+0x7000000 ; IX_data command id for sending input bits IX
#define IEX2_ID_SEND_IX0_STATUS    (IEX2_COMMAND_BIT_DATA | IEX2_DIRECTION_NODE2RC | IEX2_ARGUMENT_IO_DATA0)

// IW_id=NAD_v1+0xf000000 ; IW_data command id for sending input words IW
#define IEX2_ID_SEND_IW0_STATUS    (IEX2_COMMAND_WORD_DATA | IEX2_DIRECTION_NODE2RC | IEX2_ARGUMENT_IO_DATA0)

// IW_id2=NAD_v1+0xf200000 ; IW_data command id for sending input words IW 4..7
#define IEX2_ID_SEND_IW4_STATUS    (IEX2_COMMAND_WORD_DATA | IEX2_DIRECTION_NODE2RC | IEX2_ARGUMENT_IO_DATA4)

#define IEX2_CMD_DIRECTION_NODE2RC  0x08
#define IEX2_CMD_DIRECTION_RC2NODE  0x00

#define IEX2_CMD_COMMAND_BIT_DATA   0x30
#define IEX2_CMD_COMMAND_WORD_DATA  0x70
#define IEX2_CMD_COMMAND_READ_PLC   0x80
#define IEX2_CMD_COMMAND_WRITE_PLC  0x90
#define IEX2_CMD_COMMAND_BOOTLOADER 0xc0

#define IEX2_CMD_ARGUMENT_IO_DATA0   0x00
#define IEX2_CMD_ARGUMENT_IO_DATA4   0x01
#define IEX2_CMD_ARGUMENT_SYS_DATA16 0x04


// IEX2 Received Commands (after rotation)
//
// (command == 0x30) command id for receiveing output bits QX
#define IEX2_CMD_GOT_QX0_STATUS  (IEX2_CMD_COMMAND_BIT_DATA | IEX2_CMD_DIRECTION_RC2NODE | IEX2_CMD_ARGUMENT_IO_DATA0)

// (command == 0x70) command id for receiveing output words QW
#define IEX2_CMD_GOT_QW0_STATUS    (IEX2_CMD_COMMAND_WORD_DATA | IEX2_CMD_DIRECTION_RC2NODE  | IEX2_CMD_ARGUMENT_IO_DATA0)

// (command == 0x71) command id for receiveing output words QW
#define IEX2_CMD_GOT_QW4_STATUS    (IEX2_CMD_COMMAND_WORD_DATA | IEX2_CMD_DIRECTION_RC2NODE  | IEX2_CMD_ARGUMENT_IO_DATA4)

// (command == 0x74) command id for receiveing output system words QW
#define IEX2_CMD_GOT_QW16_STATUS    (IEX2_CMD_COMMAND_WORD_DATA | IEX2_CMD_DIRECTION_RC2NODE  | IEX2_CMD_ARGUMENT_SYS_DATA16)

// (command == 0x38) command id for sending input bits IX
#define IEX2_CMD_SEND_IX0_STATUS  (IEX2_CMD_COMMAND_BIT_DATA | IEX2_CMD_DIRECTION_NODE2RC | IEX2_CMD_ARGUMENT_IO_DATA0)

// (command == 0x78) command id for sending input words IW
#define IEX2_CMD_SEND_IW0_STATUS  (IEX2_CMD_COMMAND_WORD_DATA | IEX2_CMD_DIRECTION_NODE2RC | IEX2_CMD_ARGUMENT_IO_DATA0)

// (command == 0x79) command id for sending input words IW
#define IEX2_CMD_SEND_IW4_STATUS  (IEX2_CMD_COMMAND_WORD_DATA | IEX2_CMD_DIRECTION_NODE2RC | IEX2_CMD_ARGUMENT_IO_DATA4)

// (command == 0x3c) command id for sending status bits IX
#define IEX2_CMD_SEND_ONBUS_STATUS  (IEX2_CMD_COMMAND_BIT_DATA | IEX2_CMD_DIRECTION_NODE2RC | IEX2_CMD_ARGUMENT_SYS_DATA16 )






extern volatile unsigned long  NAD_v1;

//IX_system_data command id for sending onbus status
extern volatile unsigned long status_id ;
extern volatile unsigned char status_data[];

// IX_data command id for sending input bits IX
extern volatile unsigned long IX_id ;
extern volatile unsigned char IX_data[];


/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CS_I2C_SPI_Pin GPIO_PIN_3
#define CS_I2C_SPI_GPIO_Port GPIOE
#define PC14_OSC32_IN_Pin GPIO_PIN_14
#define PC14_OSC32_IN_GPIO_Port GPIOC
#define PC15_OSC32_OUT_Pin GPIO_PIN_15
#define PC15_OSC32_OUT_GPIO_Port GPIOC
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define OTG_FS_PowerSwitchOn_Pin GPIO_PIN_0
#define OTG_FS_PowerSwitchOn_GPIO_Port GPIOC
#define PDM_OUT_Pin GPIO_PIN_3
#define PDM_OUT_GPIO_Port GPIOC
#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define I2S3_WS_Pin GPIO_PIN_4
#define I2S3_WS_GPIO_Port GPIOA
#define SPI1_SCK_Pin GPIO_PIN_5
#define SPI1_SCK_GPIO_Port GPIOA
#define SPI1_MISO_Pin GPIO_PIN_6
#define SPI1_MISO_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define CLK_IN_Pin GPIO_PIN_10
#define CLK_IN_GPIO_Port GPIOB
#define LD4_Pin GPIO_PIN_12
#define LD4_GPIO_Port GPIOD
#define LD3_Pin GPIO_PIN_13
#define LD3_GPIO_Port GPIOD
#define LD5_Pin GPIO_PIN_14
#define LD5_GPIO_Port GPIOD
#define LD6_Pin GPIO_PIN_15
#define LD6_GPIO_Port GPIOD
#define I2S3_MCK_Pin GPIO_PIN_7
#define I2S3_MCK_GPIO_Port GPIOC
#define VBUS_FS_Pin GPIO_PIN_9
#define VBUS_FS_GPIO_Port GPIOA
#define OTG_FS_ID_Pin GPIO_PIN_10
#define OTG_FS_ID_GPIO_Port GPIOA
#define OTG_FS_DM_Pin GPIO_PIN_11
#define OTG_FS_DM_GPIO_Port GPIOA
#define OTG_FS_DP_Pin GPIO_PIN_12
#define OTG_FS_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define I2S3_SCK_Pin GPIO_PIN_10
#define I2S3_SCK_GPIO_Port GPIOC
#define I2S3_SD_Pin GPIO_PIN_12
#define I2S3_SD_GPIO_Port GPIOC
#define Audio_RST_Pin GPIO_PIN_4
#define Audio_RST_GPIO_Port GPIOD
#define OTG_FS_OverCurrent_Pin GPIO_PIN_5
#define OTG_FS_OverCurrent_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define Audio_SCL_Pin GPIO_PIN_6
#define Audio_SCL_GPIO_Port GPIOB
#define Audio_SDA_Pin GPIO_PIN_9
#define Audio_SDA_GPIO_Port GPIOB
#define MEMS_INT2_Pin GPIO_PIN_1
#define MEMS_INT2_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
