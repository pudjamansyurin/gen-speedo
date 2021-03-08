/*
 * _can.c
 *
 *  Created on: Oct 7, 2019
 *      Author: Puja Kusuma
 */

/* Includes ------------------------------------------------------------------*/
#include "Drivers/_canbus.h"

/* External variables ----------------------------------------------------------*/
#if (RTOS_ENABLE)
extern osMessageQueueId_t CanRxQueueHandle;
extern osMutexId_t CanTxMutexHandle;
#endif
extern CAN_HandleTypeDef hcan2;

/* Private variables ----------------------------------------------------------*/
static can_t can = {
		.active = 0,
		.pcan = &hcan2
};

/* Private functions declaration ----------------------------------------------*/
static void lock(void);
static void unlock(void);
static uint8_t Activated(void);
static void Header(CAN_TxHeaderTypeDef *TxHeader, uint32_t address, uint32_t DLC);
static void TxDebugger(CAN_TxHeaderTypeDef *TxHeader, CAN_DATA *TxData);
static void RxDebugger(CAN_RxHeaderTypeDef *RxHeader, CAN_DATA *RxData);

/* Public functions implementation ---------------------------------------------*/
void CANBUS_Init(void) {
	uint8_t e;

	e = (!CANBUS_Filter());

	if (!e)
		e = (HAL_CAN_Start(can.pcan) != HAL_OK);

#if (RTOS_ENABLE)
	if (!e)
		e = (HAL_CAN_ActivateNotification(can.pcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK);
#endif

	if (e)
		printf("CAN: Initiate error.\n");

	can.active = !e;
}

void CANBUS_DeInit(void) {
	HAL_CAN_DeactivateNotification(can.pcan, CAN_IT_RX_FIFO0_MSG_PENDING);
	HAL_CAN_Stop(can.pcan);
	HAL_CAN_DeInit(can.pcan);
}


uint8_t CANBUS_Filter(void) {
	CAN_FilterTypeDef sFilterConfig;

	/* Configure the CAN Filter */
	sFilterConfig.FilterBank = 0;
	// set filter to mask mode (not id_list mode)
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	// set 32-bit scale configuration
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	// assign filter to FIFO 0
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	// activate filter
	sFilterConfig.FilterActivation = ENABLE;
	// give all filter to CAN2
	sFilterConfig.SlaveStartFilterBank = 0;

	return (HAL_CAN_ConfigFilter(can.pcan, &sFilterConfig) == HAL_OK);
}

/*----------------------------------------------------------------------------
 wite a message to CAN peripheral and transmit it
 *----------------------------------------------------------------------------*/
uint8_t CANBUS_Write(uint32_t address, CAN_DATA *TxData, uint32_t DLC) {
	CAN_TxHeaderTypeDef TxHeader;
	HAL_StatusTypeDef status;

	if (!Activated())
		return 0;

	lock();
	Header(&TxHeader, address, DLC);
	while (HAL_CAN_GetTxMailboxesFreeLevel(can.pcan) == 0);

	status = HAL_CAN_AddTxMessage(can.pcan, &TxHeader, TxData->u8, NULL);

	//  if (status == HAL_OK)
	//    TxDebugger(&TxHeader, TxData);

	unlock();
	return (status == HAL_OK);
}

/*----------------------------------------------------------------------------
 read a message from CAN peripheral and release it
 *----------------------------------------------------------------------------*/
uint8_t CANBUS_Read(can_rx_t *Rx) {
	HAL_StatusTypeDef status = HAL_ERROR;

	if (!Activated())
		return 0;

	lock();
	if (HAL_CAN_GetRxFifoFillLevel(can.pcan, CAN_RX_FIFO0)) {
		status = HAL_CAN_GetRxMessage(can.pcan, CAN_RX_FIFO0, &(Rx->header), Rx->data.u8);

		//    if (status == HAL_OK)
		//      RxDebugger(&(Rx->header), &(Rx->data));

	}
	unlock();

	return (status == HAL_OK);
}

uint32_t CANBUS_ReadID(CAN_RxHeaderTypeDef *RxHeader) {
	if (RxHeader->IDE == CAN_ID_STD)
		return RxHeader->StdId;
	return RxHeader->ExtId;
}

#if (RTOS_ENABLE)
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
	can_rx_t Rx;
	// signal only when RTOS started
	if (CANBUS_Read(&Rx))
		if (osKernelGetState() == osKernelRunning)
			osMessageQueuePut(CanRxQueueHandle, &Rx, 0U, 0U);


}
#endif

/* Private functions implementation --------------------------------------------*/
static void lock(void) {
#if (RTOS_ENABLE)
	osMutexAcquire(CanTxMutexHandle, osWaitForever);
#endif
}

static void unlock(void) {
#if (RTOS_ENABLE)
	osMutexRelease(CanTxMutexHandle);
#endif
}

static void Header(CAN_TxHeaderTypeDef *TxHeader, uint32_t address, uint32_t DLC) {
	/* Configure Transmission process */
	if (address > 0x7FF) {
		TxHeader->IDE = CAN_ID_EXT;
		TxHeader->ExtId = address;
	} else {
		TxHeader->IDE = CAN_ID_STD;
		TxHeader->StdId = address;
	}
	TxHeader->RTR = (DLC ? CAN_RTR_DATA : CAN_RTR_REMOTE);
	TxHeader->DLC = DLC;
	TxHeader->TransmitGlobalTime = DISABLE;
}

static uint8_t Activated(void) {
	if (!can.active) {
		CANBUS_DeInit();
		CANBUS_Init();
	}
	return can.active;
}

static void TxDebugger(CAN_TxHeaderTypeDef *TxHeader, CAN_DATA *TxData) {
	printf("CAN:[TX] 0x%08X => %.*s\n",
			(unsigned int) ((TxHeader->IDE == CAN_ID_STD) ? TxHeader->StdId : TxHeader->ExtId),
			(TxHeader->RTR == CAN_RTR_DATA) ? (int) TxHeader->DLC : strlen("RTR"),
					(TxHeader->RTR == CAN_RTR_DATA) ? TxData->CHAR : "RTR"
	);
}

static void RxDebugger(CAN_RxHeaderTypeDef *RxHeader, CAN_DATA *RxData) {
	printf("CAN:[RX] 0x%08X <=  %.*s\n",
			(unsigned int) CANBUS_ReadID(RxHeader),
			(RxHeader->RTR == CAN_RTR_DATA) ? (int) RxHeader->DLC : strlen("RTR"),
					(RxHeader->RTR == CAN_RTR_DATA) ? RxData->CHAR : "RTR"
	);
}

