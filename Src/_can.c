/*
 * _can.c
 *
 *  Created on: Oct 7, 2019
 *      Author: Puja Kusuma
 */

#include "_can.h"

extern osMailQId canRxMailHandle;
extern osMutexId CanTxMutexHandle;
extern CAN_HandleTypeDef hcan2;
CAN_HandleTypeDef *CanHandle = &hcan2;

void CAN_Init(void) {
	CAN_FilterTypeDef sFilterConfig;

	/* Configure the CAN Filter */
	sFilterConfig.FilterBank = 15;
	// give all filter to CAN2
	sFilterConfig.SlaveStartFilterBank = 15;
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
	if (HAL_CAN_ConfigFilter(CanHandle, &sFilterConfig) != HAL_OK) {
		/* Start Error */
		Error_Handler();
	}

	/* Start the CAN peripheral */
	if (HAL_CAN_Start(CanHandle) != HAL_OK) {
		/* Start Error */
		Error_Handler();
	}

	/* Activate CAN RX notification */
	if (HAL_CAN_ActivateNotification(CanHandle, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
		/* Notification Error */
		Error_Handler();
	}
}

void CAN_Set_Tx_Header(CAN_TxHeaderTypeDef *TxHeader, uint32_t StdId, uint32_t DLC) {
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
uint8_t CAN_Write(CAN_Tx *TxCan) {
	osMutexWait(CanTxMutexHandle, osWaitForever);

	uint32_t TxMailbox;
	HAL_StatusTypeDef status;
	// check tx mailbox is ready
	while (HAL_CAN_GetTxMailboxesFreeLevel(CanHandle) == 0)
		;
	/* Start the Transmission process */
	status = HAL_CAN_AddTxMessage(CanHandle, &(TxCan->TxHeader), (uint8_t*) &(TxCan->TxData), &TxMailbox);

	if (status != HAL_OK) {
		SWV_SendStrLn("HAL_CAN_AddTxMessage FAIL");
	} else {
		SWV_SendStrLn("HAL_CAN_AddTxMessage OK");
	}

	osMutexRelease(CanTxMutexHandle);
	return (status == HAL_OK);
}

/*----------------------------------------------------------------------------
 read a message from CAN peripheral and release it
 *----------------------------------------------------------------------------*/
uint8_t CAN_Read(CAN_Rx *RxCan) {
	HAL_StatusTypeDef status;

	/* Get RX message */
	status = HAL_CAN_GetRxMessage(CanHandle, CAN_RX_FIFO0, &(RxCan->RxHeader), RxCan->RxData);

	return (status == HAL_OK);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
	CAN_Rx *RxCan;

	SWV_SendStrLn("HAL_CAN_RxFifo0MsgPendingCallback");
	// Allocate memory
	RxCan = osMailAlloc(canRxMailHandle, 0);
	// check memory allocation result
	if (RxCan != NULL) {
		// read rx fifo
		if (CAN_Read(RxCan)) {
			// Send Message
			if (osMailPut(canRxMailHandle, RxCan) != osOK) {
				osMailFree(canRxMailHandle, RxCan);
			}
		} else {
			osMailFree(canRxMailHandle, RxCan);
		}
	}
}

