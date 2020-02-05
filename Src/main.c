/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attentions
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "limits.h"
#include "_guiapp.h"
#include "_config.h"
#include "_database.h"
#include "_canbus.h"
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
CAN_HandleTypeDef hcan2;

CRC_HandleTypeDef hcrc;

IWDG_HandleTypeDef hiwdg;

RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart1;

osThreadId LcdTaskHandle;
osThreadId CanRxTaskHandle;
osThreadId SerialTaskHandle;
osTimerId TimerCANHandle;
osMutexId CanTxMutexHandle;
osMutexId SwvMutexHandle;
/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CRC_Init(void);
extern void GRAPHICS_HW_Init(void);
extern void GRAPHICS_Init(void);
extern void GRAPHICS_MainTask(void);
static void MX_CAN2_Init(void);
static void MX_RTC_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_IWDG_Init(void);
void StartLcdTask(void const *argument);
void StartCanRxTask(void const *argument);
void StartSerialTask(void const *argument);
void CallbackTimerCAN(void const *argument);

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
	MX_CRC_Init();
	MX_CAN2_Init();
	MX_USART1_UART_Init();
	MX_IWDG_Init();
	/* USER CODE BEGIN 2 */
	CAN_Init();
	/* USER CODE END 2 */

	/* Initialise the graphical hardware */
	GRAPHICS_HW_Init();

	/* Initialise the graphical stack engine */
	GRAPHICS_Init();

	/* Create the mutex(es) */
	/* definition and creation of CanTxMutex */
	osMutexDef(CanTxMutex);
	CanTxMutexHandle = osMutexCreate(osMutex(CanTxMutex));

	/* definition and creation of SwvMutex */
	osMutexDef(SwvMutex);
	SwvMutexHandle = osMutexCreate(osMutex(SwvMutex));

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* Create the timer(s) */
	/* definition and creation of TimerCAN */
	osTimerDef(TimerCAN, CallbackTimerCAN);
	TimerCANHandle = osTimerCreate(osTimer(TimerCAN), osTimerPeriodic, NULL);

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	osTimerStart(TimerCANHandle, TIMER_CAN_MS);
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of LcdTask */
	osThreadDef(LcdTask, StartLcdTask, osPriorityNormal, 0, 256);
	LcdTaskHandle = osThreadCreate(osThread(LcdTask), NULL);

	/* definition and creation of CanRxTask */
	osThreadDef(CanRxTask, StartCanRxTask, osPriorityAboveNormal, 0, 128);
	CanRxTaskHandle = osThreadCreate(osThread(CanRxTask), NULL);

	/* definition and creation of SerialTask */
	osThreadDef(SerialTask, StartSerialTask, osPriorityBelowNormal, 0, 128);
	SerialTaskHandle = osThreadCreate(osThread(SerialTask), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* Start scheduler */
	osKernelStart();

	/* We should never get here as control is now taken by the scheduler */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
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
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 180;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
			{
		Error_Handler();
	}
	/** Activate the Over-Drive mode
	 */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK)
			{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
			{
		Error_Handler();
	}
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC | RCC_PERIPHCLK_RTC;
	PeriphClkInitStruct.PLLSAI.PLLSAIN = 60;
	PeriphClkInitStruct.PLLSAI.PLLSAIR = 5;
	PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_4;
	PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
			{
		Error_Handler();
	}
}

/**
 * @brief CAN2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_CAN2_Init(void)
{

	/* USER CODE BEGIN CAN2_Init 0 */

	/* USER CODE END CAN2_Init 0 */

	/* USER CODE BEGIN CAN2_Init 1 */
	/* USER CODE END CAN2_Init 1 */
	hcan2.Instance = CAN2;
	hcan2.Init.Prescaler = 6;
	hcan2.Init.Mode = CAN_MODE_NORMAL;
	hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan2.Init.TimeSeg1 = CAN_BS1_12TQ;
	hcan2.Init.TimeSeg2 = CAN_BS2_2TQ;
	hcan2.Init.TimeTriggeredMode = DISABLE;
	hcan2.Init.AutoBusOff = ENABLE;
	hcan2.Init.AutoWakeUp = DISABLE;
	hcan2.Init.AutoRetransmission = DISABLE;
	hcan2.Init.ReceiveFifoLocked = DISABLE;
	hcan2.Init.TransmitFifoPriority = DISABLE;
	if (HAL_CAN_Init(&hcan2) != HAL_OK)
			{
		Error_Handler();
	}
	/* USER CODE BEGIN CAN2_Init 2 */
	/* USER CODE END CAN2_Init 2 */

}

/**
 * @brief CRC Initialization Function
 * @param None
 * @retval None
 */
static void MX_CRC_Init(void)
{

	/* USER CODE BEGIN CRC_Init 0 */

	/* USER CODE END CRC_Init 0 */

	/* USER CODE BEGIN CRC_Init 1 */

	/* USER CODE END CRC_Init 1 */
	hcrc.Instance = CRC;
	if (HAL_CRC_Init(&hcrc) != HAL_OK)
			{
		Error_Handler();
	}
	/* USER CODE BEGIN CRC_Init 2 */

	/* USER CODE END CRC_Init 2 */

}

/**
 * @brief IWDG Initialization Function
 * @param None
 * @retval None
 */
static void MX_IWDG_Init(void)
{

	/* USER CODE BEGIN IWDG_Init 0 */

	/* USER CODE END IWDG_Init 0 */

	/* USER CODE BEGIN IWDG_Init 1 */

	/* USER CODE END IWDG_Init 1 */
	hiwdg.Instance = IWDG;
	hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
	hiwdg.Init.Reload = 4095;
	if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
			{
		Error_Handler();
	}
	/* USER CODE BEGIN IWDG_Init 2 */

	/* USER CODE END IWDG_Init 2 */

}

/**
 * @brief RTC Initialization Function
 * @param None
 * @retval None
 */
static void MX_RTC_Init(void)
{

	/* USER CODE BEGIN RTC_Init 0 */

	/* USER CODE END RTC_Init 0 */

	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };

	/* USER CODE BEGIN RTC_Init 1 */

	/* USER CODE END RTC_Init 1 */
	/** Initialize RTC Only
	 */
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if (HAL_RTC_Init(&hrtc) != HAL_OK)
			{
		Error_Handler();
	}

	/* USER CODE BEGIN Check_RTC_BKUP */

	/* USER CODE END Check_RTC_BKUP */

	/** Initialize RTC and set the Time and Date
	 */
	sTime.Hours = 0x0;
	sTime.Minutes = 0x0;
	sTime.Seconds = 0x0;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
			{
		Error_Handler();
	}
	sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	sDate.Month = RTC_MONTH_JANUARY;
	sDate.Date = 0x1;
	sDate.Year = 0x0;

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
			{
		Error_Handler();
	}
	/* USER CODE BEGIN RTC_Init 2 */

	/* USER CODE END RTC_Init 2 */

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void)
{

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
			{
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE, LEFT_LD1_Pin | LEFT_LD2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(RIGHT_BACKLIGHT_GPIO_Port, RIGHT_BACKLIGHT_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOG, RIGHT_LD1_Pin | RIGHT_LD2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : LEFT_LD1_Pin LEFT_LD2_Pin */
	GPIO_InitStruct.Pin = LEFT_LD1_Pin | LEFT_LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pin : RIGHT_BACKLIGHT_Pin */
	GPIO_InitStruct.Pin = RIGHT_BACKLIGHT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RIGHT_BACKLIGHT_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : RIGHT_LD1_Pin RIGHT_LD2_Pin */
	GPIO_InitStruct.Pin = RIGHT_LD1_Pin | RIGHT_LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartLcdTask */
/**
 * @brief  Function implementing the lcdTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartLcdTask */
void StartLcdTask(void const *argument)
{
	/* Graphic application */
	//  GRAPHICS_MainTask();
	/* USER CODE BEGIN 5 */
	//#if !USE_HMI_LEFT
	//	// Control backlight
	//	BSP_Set_Backlight(1);
	//#endif
	// run main task
	GUI_MainTask();
	/* Infinite loop */
	for (;;) {
		osDelay(1);
	}
	/* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartCanRxTask */
/**
 * @brief Function implementing the CanRxTask thread.
 * @param argument: Not used
 * @retval None
 */

/* USER CODE END Header_StartCanRxTask */
void StartCanRxTask(void const *argument)
{
	/* USER CODE BEGIN StartCanRxTask */
#if !USE_HMI_LEFT
	extern status_t DB_HMI_Status;
#endif
	extern CAN_Rx RxCan;
	uint32_t ulNotifiedValue;
	uint8_t RelatedCAN;
	/* Infinite loop */
	for (;;) {
		// check if has new can message
		xTaskNotifyWait(0x00, ULONG_MAX, &ulNotifiedValue, portMAX_DELAY);

		// proceed event
		RelatedCAN = 1;
		if ((ulNotifiedValue & EVENT_CAN_RX_IT)) {
			// handle message
			switch (RxCan.RxHeader.StdId) {
			case CAN_ADDR_ECU_SWITCH:
				CANBUS_ECU_Switch_Read();
#if !USE_HMI_LEFT
				// Control back-light
				BSP_Set_Backlight(DB_HMI_Status.daylight);
#endif
				break;
			case CAN_ADDR_ECU_SELECT_SET:
				CANBUS_ECU_Select_Set_Read();
				break;
			case CAN_ADDR_ECU_TRIP_MODE:
				CANBUS_ECU_Trip_Mode_Read();
				break;
			case CAN_ADDR_MCU_DUMMY:
				CANBUS_MCU_Dummy_Read();
				break;
			case CAN_ADDR_BMS_DUMMY:
				CANBUS_BMS_Dummy_Read();
				break;
			default:
				RelatedCAN = 0;
				break;
			}

			// notify GUI thread
			if (RelatedCAN) {
				xTaskNotify(LcdTaskHandle, 0x01, eSetBits);
			}

			//			// show this message
			//			SWV_SendStr("ID: ");
			//			SWV_SendHex32(RxCan.RxHeader.StdId);
			//			SWV_SendStr(", Data: ");
			//			for (i = 0; i < RxCan.RxHeader.DLC; i++) {
			//				SWV_SendHex8(RxCan.RxData[i]);
			//			}
			//			SWV_SendStrLn("");
		}
	}
	/* USER CODE END StartCanRxTask */
}

/* USER CODE BEGIN Header_StartSerialTask */
/**
 * @brief Function implementing the serialTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSerialTask */
void StartSerialTask(void const *argument)
{
	/* USER CODE BEGIN StartSerialTask */
	/* Infinite loop */
	for (;;) {
		SWV_SendStrLn("Serial Task Running");

		osDelay(250);
	}
	/* USER CODE END StartSerialTask */
}

/* CallbackTimerCAN function */
void CallbackTimerCAN(void const *argument)
{
	/* USER CODE BEGIN CallbackTimerCAN */
	CANBUS_HMI_Heartbeat();

	BSP_Led_Toggle(2);
	/* USER CODE END CallbackTimerCAN */
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM6 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM6) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while (1) {
		// error state
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
