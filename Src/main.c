/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
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
#if (!USE_HMI_LEFT)
#include "_canbus.h"
#endif
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

osThreadId LcdTaskHandle;
osThreadId CanRxTaskHandle;
osThreadId SerialTaskHandle;
osTimerId Timer500Handle;
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
void StartLcdTask(void const *argument);
void StartCanRxTask(void const *argument);
void StartSerialTask(void const *argument);
void CallbackTimer500(void const *argument);

/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
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
	/* USER CODE BEGIN 2 */
#if (!USE_HMI_LEFT)
	CAN_Init();
#endif
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
#if (USE_HMI_LEFT)
	osMutexDelete(CanTxMutexHandle);
#endif
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* Create the timer(s) */
	/* definition and creation of Timer500 */
	osTimerDef(Timer500, CallbackTimer500);
	Timer500Handle = osTimerCreate(osTimer(Timer500), osTimerPeriodic, NULL);

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
#if (!USE_HMI_LEFT)
	osTimerStart(Timer500Handle, 500);
#endif
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of LcdTask */
	osThreadDef(LcdTask, StartLcdTask, osPriorityNormal, 0, 256);
	LcdTaskHandle = osThreadCreate(osThread(LcdTask), NULL);

	/* definition and creation of CanRxTask */
	osThreadDef(CanRxTask, StartCanRxTask, osPriorityNormal, 0, 128);
	CanRxTaskHandle = osThreadCreate(osThread(CanRxTask), NULL);

	/* definition and creation of SerialTask */
	osThreadDef(SerialTask, StartSerialTask, osPriorityNormal, 0, 128);
	SerialTaskHandle = osThreadCreate(osThread(SerialTask), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
#if (USE_HMI_LEFT)
	osThreadTerminate(CanRxTaskHandle);
#endif
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
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 180;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Activate the Over-Drive mode
	 */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	PeriphClkInitStruct.PLLSAI.PLLSAIN = 60;
	PeriphClkInitStruct.PLLSAI.PLLSAIR = 5;
	PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_4;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief CAN2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_CAN2_Init(void) {

	/* USER CODE BEGIN CAN2_Init 0 */

	/* USER CODE END CAN2_Init 0 */

	/* USER CODE BEGIN CAN2_Init 1 */
#if (!USE_HMI_LEFT)
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
	if (HAL_CAN_Init(&hcan2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN CAN2_Init 2 */
#endif
	/* USER CODE END CAN2_Init 2 */

}

/**
 * @brief CRC Initialization Function
 * @param None
 * @retval None
 */
static void MX_CRC_Init(void) {

	/* USER CODE BEGIN CRC_Init 0 */

	/* USER CODE END CRC_Init 0 */

	/* USER CODE BEGIN CRC_Init 1 */

	/* USER CODE END CRC_Init 1 */
	hcrc.Instance = CRC;
	if (HAL_CRC_Init(&hcrc) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN CRC_Init 2 */

	/* USER CODE END CRC_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
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
void StartLcdTask(void const *argument) {
	/* Graphic application */
	//  GRAPHICS_MainTask();
	/* USER CODE BEGIN 5 */
	// Turn on backlight
#if (!USE_HMI_LEFT)
	BSP_Set_Backlight(1);
#endif
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
void StartCanRxTask(void const *argument) {
	/* USER CODE BEGIN StartCanRxTask */
#if (!USE_HMI_LEFT)
	extern CAN_Rx RxCan;
	uint8_t i;
	uint32_t ulNotifiedValue;
	/* Infinite loop */
	for (;;) {
		// check if has new can message
		xTaskNotifyWait(0x00, ULONG_MAX, &ulNotifiedValue, portMAX_DELAY);
		// proceed event
		if ((ulNotifiedValue & EVENT_CAN_RX_IT)) {
			//			// handle message
			//			switch (RxCan->RxHeader.StdId) {
			//				case CAN_ADDR_MCU_DUMMY:
			//					// convert RPM to Speed
			//					DB_MCU_Speed = ((RxCan->RxData[1] << 8) | (RxCan->RxData[0])) * MCU_SPEED_MAX / MCU_RPM_MAX;
			//					// set volume
			//					osMessagePut(AudioVolQueueHandle, DB_MCU_Speed, osWaitForever);
			//					break;
			//				default:
			//					break;
			//			}

			// show this message
			SWV_SendStr("ID: ");
			SWV_SendHex32(RxCan.RxHeader.StdId);
			SWV_SendStr(", Data: ");
			for (i = 0; i < RxCan.RxHeader.DLC; i++) {
				SWV_SendHex8(RxCan.RxData[i]);
			}
			SWV_SendStrLn("");
		}
	}
#endif
	/* USER CODE END StartCanRxTask */
}

/* USER CODE BEGIN Header_StartSerialTask */
/**
 * @brief Function implementing the serialTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSerialTask */
void StartSerialTask(void const *argument) {
	/* USER CODE BEGIN StartSerialTask */
	/* Infinite loop */
	for (;;) {
		SWV_SendStrLn("Serial Task Running");

		BSP_Led_Toggle(1);
		osDelay(250);
	}
	/* USER CODE END StartSerialTask */
}

/* CallbackTimer500 function */
void CallbackTimer500(void const *argument) {
	/* USER CODE BEGIN CallbackTimer500 */
#if (!USE_HMI_LEFT)
	CANBUS_HMI_Heartbeat();
	BSP_Led_Toggle(2);
#endif
	/* USER CODE END CallbackTimer500 */
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM6 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
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
void Error_Handler(void) {
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
