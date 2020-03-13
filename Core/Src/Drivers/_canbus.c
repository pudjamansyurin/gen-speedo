/*
 * _can.c
 *
 *  Created on: Oct 7, 2019
 *      Author: Puja Kusuma
 */

#include "_canbus.h"

extern osThreadId CanRxTaskHandle;
extern osMutexId CanTxMutexHandle;
extern CAN_HandleTypeDef hcan2;
canbus_t CB;

void CANBUS_Init(void) {
	CAN_FilterTypeDef sFilterConfig;

	/* Configure the CAN Filter */
	sFilterConfig.FilterBank = 0;
	// give all filter to CAN2
	sFilterConfig.SlaveStartFilterBank = 0;
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

	/* Configure the CAN Filter */
	if (HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig) != HAL_OK) {
		/* Start Error */
		Error_Handler();
	}

	/* Start the CAN peripheral */
	if (HAL_CAN_Start(&hcan2) != HAL_OK) {
		/* Start Error */
		Error_Handler();
	}

	/* Activate CAN RX notification */
	if (HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
		/* Notification Error */
		Error_Handler();
	}
}

/**
 * Function to set global TxHeader variable.
 * @param TxHeader
 * @param StdId
 * @param DLC
 */
void CANBUS_Header(CAN_TxHeaderTypeDef *TxHeader, uint32_t StdId, uint32_t DLC) {
	/* Configure Global Transmission process */
	TxHeader->RTR = CAN_RTR_DATA;
	TxHeader->IDE = CAN_ID_STD;
	TxHeader->TransmitGlobalTime = DISABLE;
	TxHeader->StdId = StdId;
	TxHeader->DLC = DLC;
}

/*----------------------------------------------------------------------------
 wite a message to CAN peripheral and transmit it
 *----------------------------------------------------------------------------*/
uint8_t  CANBUS_Write(canbus_tx_t *tx) {
	osMutexWait(CanTxMutexHandle, osWaitForever);

	uint32_t TxMailbox;
	HAL_StatusTypeDef status;
	// check tx mailbox is ready
	while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan2) == 0)
		;
	/* Start the Transmission process */
	status = HAL_CAN_AddTxMessage(&hcan2, &(tx->header), (uint8_t*) &(tx->data), &TxMailbox);

	osMutexRelease(CanTxMutexHandle);
	return (status == HAL_OK);
}

/*----------------------------------------------------------------------------
 read a message from CAN peripheral and release it
 *----------------------------------------------------------------------------*/
uint8_t CANBUS_Read(canbus_rx_t *rx) {
	HAL_StatusTypeDef status;

	/* Get RX message */
	status = HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &(rx->header), rx->data);

	return (status == HAL_OK);
}

uint32_t CANBUS_ReadID(void) {
  return CB.rx.header.StdId;
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	// read rx fifo
	if (CANBUS_Read(&(CB.rx))) {
		// signal only when RTOS started
		if (osKernelRunning()) {
			xTaskNotifyFromISR(CanRxTaskHandle, EVENT_CAN_RX_IT, eSetBits, &xHigherPriorityTaskWoken);
		}
	}

	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
