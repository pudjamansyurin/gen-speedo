/*
 * VCU.c
 *
 *  Created on: May 11, 2020
 *      Author: pudja
 */

/* Includes ------------------------------------------------------------------*/
#include "Nodes/VCU.h"
#include "Nodes/HMI1.h"

/* External variables ---------------------------------------------------------*/
extern hmi1_t HMI1;

/* Public variables -----------------------------------------------------------*/
vcu_t VCU = {
		.d = { 0 }
};

/* Public functions implementation --------------------------------------------*/
void VCU_Init(void) {
	memset(&VCU, 0, sizeof(vcu_t));
}

/* ====================================== CAN RX =================================== */
void VCU_RX_SwitchControl(can_rx_t *Rx) {
	UNION64 *d = &(Rx->data);

	// read message
	HMI1.d.state.abs = (d->u8[0] >> 0) & 0x01;
	HMI1.d.state.mirroring = (d->u8[0] >> 1) & 0x01;
	HMI1.d.state.lamp = (d->u8[0] >> 2) & 0x01;
	HMI1.d.state.warning = (d->u8[0] >> 3) & 0x01;
	HMI1.d.state.overheat = (d->u8[0] >> 4) & 0x01;
	HMI1.d.state.unfinger = (d->u8[0] >> 5) & 0x01;
	HMI1.d.state.unremote = (d->u8[0] >> 6) & 0x01;
	HMI1.d.state.daylight = (d->u8[0] >> 7) & 0x01;

	// sein
	HMI1.d.sein.left = (d->u8[1] >> 0) & 0x01;
	HMI1.d.sein.right = (d->u8[1] >> 1) & 0x01;
	HMI1.hbar.reverse = (d->u8[1] >> 2) & 0x01;
	VCU.d.bms.run = (d->u8[1] >> 3) & 0x01;
	VCU.d.mcu.run = (d->u8[1] >> 4) & 0x01;
	HMI1.d.state.scanning = (d->u8[1] >> 5) & 0x03;

	// mode
	HMI1.hbar.d.mode[HBAR_M_DRIVE] = (d->u8[2] >> 0) & 0x03;
	HMI1.hbar.d.mode[HBAR_M_TRIP] = (d->u8[2] >> 2) & 0x03;
	HMI1.hbar.d.mode[HBAR_M_REPORT] = (d->u8[2] >> 4) & 0x01;
	HMI1.hbar.m = (d->u8[2] >> 5) & 0x03;
	HMI1.hbar.listening = (d->u8[2] >> 7) & 0x01;

	// others
	VCU.d.mcu.speed = d->u8[3];
	VCU.d.mcu.discur = d->u8[4];
	VCU.d.bms.soc = d->u8[5];
	VCU.d.signal = d->u8[6];
	VCU.d.state = d->u8[7];

	VCU.d.tick = _GetTickMS();
}

void VCU_RX_ModeData(can_rx_t *Rx) {
	UNION64 *d = &(Rx->data);

	switch (HMI1.hbar.d.mode[HBAR_M_TRIP]) {
		case HBAR_M_TRIP_A:
			HMI1.hbar.d.trip = d->u16[0];
			break;
		case HBAR_M_TRIP_B:
			HMI1.hbar.d.trip = d->u16[1];
			break;
		case HBAR_M_TRIP_ODO:
			HMI1.hbar.d.trip = d->u16[2];
			break;
		default:
			break;
	}

	switch (HMI1.hbar.d.mode[HBAR_M_REPORT]) {
		case HBAR_M_REPORT_RANGE:
			HMI1.hbar.d.report = d->u8[6];
			break;
		case HBAR_M_REPORT_AVERAGE:
			HMI1.hbar.d.report = d->u8[7];
			break;
		default:
			break;
	}

	VCU.d.tick = _GetTickMS();
}
