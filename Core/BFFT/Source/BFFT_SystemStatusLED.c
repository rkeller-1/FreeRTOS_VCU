/*
 * BFFT_SystemStatusLED.c
 *
 *  Created on: Apr 8, 2021
 *      Author: Nutzer
 */

#include "BFFT.h"


void vLEDStatusOkaySet(void)
{
   HAL_GPIO_WritePin(LED_StatusOkay_GPIO_Port, LED_StatusOkay_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(LED_StatusError_GPIO_Port, LED_StatusError_Pin, GPIO_PIN_RESET);
}

void vLEDStatusErrorSet(void)
{
   HAL_GPIO_WritePin(LED_StatusOkay_GPIO_Port, LED_StatusOkay_Pin, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(LED_StatusError_GPIO_Port, LED_StatusError_Pin, GPIO_PIN_SET);
}

void vLEDSystemAliveToggle(void)
{
   HAL_GPIO_TogglePin(LED_SystemAlive_GPIO_Port, LED_SystemAlive_Pin);
}
