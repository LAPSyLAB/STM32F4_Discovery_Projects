/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "i2c.h"
#include "i2s.h"
#include "spi.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include "iex.h"

#include "stm32f4xx_hal_can.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t TXbuffer[256]="\nHello World!\0";
uint8_t RXbuffer[256];
volatile uint8_t RXbufferStrLen=0;
uint8_t Cmdbuffer[256];
uint8_t CmdbufferPos=0;

uint32_t CanMsgCnt = 0;


uint8_t printf_buf[256];

extern volatile APP_DEBUG AppDebug;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    uint8_t CAN_Rx_Msg[8];
    CAN_RxHeaderTypeDef RxHeader;
    int ii, jj, pos, tempint;
    int8_t RetVal;
    char RXChar;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2S3_Init();
  MX_SPI1_Init();
  MX_USB_DEVICE_Init();
  MX_CAN1_Init();
  /* USER CODE BEGIN 2 */

  CAN_SetAllFilter(&hcan1);

  HAL_CAN_Start(&hcan1);

  IEX_Init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  CDC_Transmit_FS(buffer,sizeof(buffer));
//	  HAL_Delay(1000);
	  if (RXbufferStrLen > 0) {

		  for (ii=0;ii<RXbufferStrLen;ii++) {
			  RXChar = RXbuffer[ii];

			  if (RXChar == 13) {
				  Cmdbuffer[CmdbufferPos] = 0;

				  if ((Cmdbuffer[0]=='r') || (Cmdbuffer[0]=='R')) {
					  IEX_Init ();

	  			  } else if ( (Cmdbuffer[0]=='d') || (Cmdbuffer[0]=='D')) {
	  				AppDebug.CAN = atoi( &(Cmdbuffer[1]) );

	  			  } else if ( (Cmdbuffer[0]=='n') || (Cmdbuffer[0]=='N')) {
	  				CAN_NADFilter= atoi( &(Cmdbuffer[1]) );

	  			  } else if ( (Cmdbuffer[0]=='h') || (Cmdbuffer[0]=='H')) {
	  				pos = snprintf(TXbuffer,256,"CAN Sniffer Settings Debug:%d | NADFilt:%d \r\n d ... debug\r\n N ... NAD filter\r\n\ r ... reset\r\n h ... help\r\nExamples: d11, N10619, r, h.\r\n\r\n\0",AppDebug.CAN,CAN_NADFilter);
	  				CDC_Transmit_FS(TXbuffer,pos+1);

				  }
				  CmdbufferPos = 0;

			  } else {
				  Cmdbuffer[CmdbufferPos++] = RXChar;
			  }

		  }

//		  pos = snprintf(TXbuffer,256,"USB Msg Received: %s \r\n\0",RXbuffer);
//		  CDC_Transmit_FS(TXbuffer,pos+1);
		  RXbufferStrLen = 0;
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      if(HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) != 0)
      {
          HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, CAN_Rx_Msg);
		  CanMsgCnt++;

          if (RxHeader.IDE) {
              CANBus_Parse_RX_Message (RxHeader.ExtId,RxHeader.DLC, CAN_Rx_Msg);

//          } else {
//              CANBus_Parse_RX_Message (RxHeader.StdId,RxHeader.DLC, CAN_Rx_Msg);

          }


          if  ( ( AppDebug.CAN & 8 )  && (RxHeader.DLC > 0) &&   // only non-zero length messages (disregard baudsync messages)
        		  	  ( CAN_NADFilter == 0 ||
        		  			  	  ( CAN_NADFilter != 0 && (CAN_NADFilter == (RxHeader.ExtId & 0x1FFFFF) && RxHeader.IDE) || (CAN_NADFilter == (RxHeader.StdId & 0x7FF) && !RxHeader.IDE))  )
			   ) { // Debug RAW RX messages
				if (RxHeader.IDE)  {
				  pos = sprintf(TXbuffer,"Can Msg EXT[%d]: Cmd:0x%02x NAD:%7d [CAN_ID=0x%08x]: LEN=%d ",CanMsgCnt,(RxHeader.ExtId>>21),(RxHeader.ExtId & 0x1FFFFF), RxHeader.ExtId, RxHeader.DLC);

				} else {
				  pos = sprintf(TXbuffer,"Can Msg STD[%d]: ID=%4d [0x%3x] : LEN=%d ",CanMsgCnt,RxHeader.StdId, RxHeader.StdId, RxHeader.DLC);
				}

				for (ii=0;ii<RxHeader.DLC;ii++) {
					  tempint = sprintf(TXbuffer+pos,"|%02x",CAN_Rx_Msg[ii]);
					  pos += tempint;
				}
				sprintf(TXbuffer+pos,"\r\n\r\n");
				CDC_Transmit_FS(TXbuffer,strlen(TXbuffer));
          }



      }


  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
