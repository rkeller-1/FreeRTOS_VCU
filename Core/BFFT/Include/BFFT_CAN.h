/*
 * BFFT_CAN.h
 *
 *  Created on: Apr 8, 2021
 *      Author: Nutzer
 */

#ifndef BFFT_INCLUDE_BFFT_CAN_H_
#define BFFT_INCLUDE_BFFT_CAN_H_

#define CAN_OKAY   0
#define CAN_ERROR -1

int8_t s8CANInit(void);
int8_t s8CANSendMessage(void);
int8_t s8CANReceiveMessage(uint8_t* const pu8Data);

#endif /* BFFT_INCLUDE_BFFT_CAN_H_ */
