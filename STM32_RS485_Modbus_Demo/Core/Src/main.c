/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#include "i2c.h"
#include "i2s.h"
#include "spi.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mb.h"
#include "mbframe.h"
#include "mb_m.h"
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
#define BUFSIZE 256
char	SendBuffer[BUFSIZE];
int	Counter;
int KeyState=0;

uint8_t RXbuffer[BUFSIZE];
volatile uint8_t RXbufferStrLen=0;

uint8_t MBbuffer[BUFSIZE];
Modbus_Master_SM_State MB_MasterState=MBUS_READY;
uint8_t MBCnt = 0;
eMBMasterReqErrCode    errorCode = MB_MRE_NO_ERR;
uint16_t errorCount = 0;
uint16_t succCount = 0;
uint8_t MBErrorCode = 0;
USHORT  usModbusUserData[MB_PDU_SIZE_MAX];

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
	uint32_t lastRun = 0U;
	uint32_t nowTime;

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
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

//  eMBMasterInit( MB_RTU, &huart1, 115200, &htim2 );
//   eMBMasterEnable( );
//   eMBMasterReqReadInputRegister(0xA, 0, 2, 2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	 nowTime = HAL_GetTick();

	 if ((nowTime - lastRun) >= 1000) {
		 HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
		 HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
		 HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);

		 MB_MasterState=MBUS_REQSENT;
// -------------------------------------------------------------------
//       Checked tests
//       ModRSSim2 Modbus slave simulator running on PC
//		 and connected to USB Virtual COM port
// -------------------------------------------------------------------

//		 ---   Slave ID=1, Read state of 8 coils from address 0
//		 eMBMasterReqReadCoils( 1, 0, 8 ,1 );  //RXbuffer[3];

//		 ---   Slave ID=1, Write ON state to one coil on addresses 0-7
//		 errorCode = eMBMasterReqWriteCoil(1,MBCnt,0xFF00,1);
//		 MBCnt= (MBCnt + 1) % 8;

//		 ---   Slave ID=1, Write ON state to all coils on addresses 0-7
//		 errorCode = eMBMasterReqWriteMultipleCoils(1,0,8, &MBCnt,1);
//		 MBCnt++;

//		 ---   Slave ID=1, Read from 8 discrete inputs on addresses 0-7
//		 errorCode = eMBMasterReqReadDiscreteInputs(1,0,8,1);   //result in RXbuffer[3];


//		 ---   Slave ID=1, Read from 2 analog input registers from addresses 0-1
//        errorCode = eMBMasterReqReadInputRegister(1,0,2,1); //results in RXbuffer[3-6];

//		 ---   Slave ID=1, Read state of 2 analog output registers from addresses 0-1
//		  errorCode = eMBMasterReqReadHoldingRegister(1,0,2,1); //results in RXbuffer[3-6];

//		 ---   Slave ID=1, Write state 511 of 1 analog output register on addresses 0-15
//		  errorCode = eMBMasterReqWriteHoldingRegister(1,MBCnt,511,1);
//		  MBCnt= (MBCnt + 1) % 16;

//		 ---   Slave ID=1, Write state 511 of 1 analog output register on addresses 0-15
		 usModbusUserData[0]= usModbusUserData[1]= usModbusUserData[2]= usModbusUserData[3]=MBCnt;
		 errorCode = eMBMasterReqWriteMultipleHoldingRegister(1,MBCnt,2,usModbusUserData,1);
		 MBCnt= (MBCnt + 1) % 16;

		 // -------------------------------------
		 //       UNChecked tests - TODO
		 // -------------------------------------

		 //		errorCode = eMBMasterReqReadWriteMultipleHoldingRegister(1,3,2,usModbusUserData,5,2,WAIT_FOREVER);

	     lastRun = nowTime;
	 }


	 KeyState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, KeyState);


      // Receive over USB Virtual ComPort
	  if (RXbufferStrLen > 0) {

		  if ((RXbuffer[0] == MBbuffer[0]) && (RXbuffer[1] == MBbuffer[1]) ) {
			  succCount++;
		  } else {
			  errorCount++;
			  MBErrorCode = RXbuffer[2];
		  }

		  snprintf(SendBuffer,BUFSIZE,"Modbus Msg Received: Addr:%d FC:%02x Bytes:%d | %02x %02x %04x\r\n\0",RXbuffer[0],RXbuffer[1],RXbuffer[2],RXbuffer[3],RXbuffer[4],RXbuffer[3]*256+RXbuffer[4]);
          // Not sending on USB not to interfere with MODBUS communication !

		  MB_MasterState=MBUS_READY;
		  RXbufferStrLen = 0;

	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
