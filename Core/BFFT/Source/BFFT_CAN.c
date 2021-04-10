/*
 * BFFT_CAN.c
 *
 *  Created on: Apr 8, 2021
 *      Author: Nutzer
 */

#include "BFFT.h"

#define CAN_BUFFER_SIZE 4u
#define CAN_INDEX_MESSAGE_VALID 0u
#define CAN_INDEX_MESSAGE_INVALID 1u

static CAN_TxHeaderTypeDef xCANTxHeader;
static CAN_RxHeaderTypeDef xCANRxHeader;
static CAN_FilterTypeDef xCANFilter;
static uint32_t u32CANTxBufferNumber;
static const uint32_t cu32TxId = 0;
static volatile uint32_t au32CANDataValidationCounters[] = {0u, 0u};
static const uint8_t cau8TxData[CAN_BUFFER_SIZE] = {0xBAu, 0xDDu, 0xCAu, 0xFEu};
static uint8_t au8RxData[CAN_BUFFER_SIZE] = {0u, 0u, 0u, 0u};

static int8_t s8CANGeneralInit(void);
static int8_t s8CANTxInit(void);
static int8_t s8CANFilterInit(void);
static void vCANSetStatusLED(const int8_t cs8CANStatus);


int8_t s8CANInit(void)
{
   int8_t s8ErrorHandle = CAN_OKAY;

   if(CAN_ERROR == s8CANGeneralInit())
   {
      s8ErrorHandle = CAN_ERROR;
   }

   if(CAN_ERROR == s8CANTxInit())
   {
      s8ErrorHandle = CAN_ERROR;
   }

   if(CAN_ERROR == s8CANFilterInit())
   {
      s8ErrorHandle = CAN_ERROR;
   }

   vCANSetStatusLED(s8ErrorHandle);

   return s8ErrorHandle;
}


int8_t s8CANSendMessage(void)
{
   int8_t s8ErrorHandle = CAN_OKAY;

   if(HAL_OK != HAL_CAN_AddTxMessage(&hcan1, &xCANTxHeader, (uint8_t*) cau8TxData, &u32CANTxBufferNumber))
   {
      s8ErrorHandle = CAN_ERROR;
   }

   vCANSetStatusLED(s8ErrorHandle);

   return s8ErrorHandle;
}


int8_t s8CANReceiveMessage(uint8_t* const pu8Data)
{
   int8_t s8ErrorHandle = CAN_OKAY;
   uint8_t* pu8ReceiveBuffer = au8RxData;

   if(NULL != pu8Data)
   {
      pu8ReceiveBuffer = pu8Data;
   }

   if(HAL_OK != HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &xCANRxHeader, pu8ReceiveBuffer))
   {
      s8ErrorHandle = CAN_ERROR;
   }
   else
   {
      if(0u == memcmp(cau8TxData, pu8ReceiveBuffer, CAN_BUFFER_SIZE))
      {
         au32CANDataValidationCounters[CAN_INDEX_MESSAGE_VALID]++;
      }
      else
      {
         au32CANDataValidationCounters[CAN_INDEX_MESSAGE_INVALID]++;
         s8ErrorHandle = CAN_ERROR;
      }

      memset(au8RxData, 0u, CAN_BUFFER_SIZE);
   }

   vCANSetStatusLED(s8ErrorHandle);

   return s8ErrorHandle;
}


static int8_t s8CANGeneralInit(void)
{
   int8_t s8ErrorHandle = CAN_OKAY;

   if(HAL_OK != HAL_CAN_Start(&hcan1))
   {
      s8ErrorHandle = CAN_ERROR;
   }

   if(HAL_OK != HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING))
   {
      s8ErrorHandle = CAN_ERROR;
   }

   return s8ErrorHandle;
}

static int8_t s8CANTxInit(void)
{
   xCANTxHeader.IDE = CAN_ID_STD;
   xCANTxHeader.StdId = cu32TxId;
   xCANTxHeader.RTR = CAN_RTR_DATA;
   xCANTxHeader.DLC = CAN_BUFFER_SIZE;
   xCANTxHeader.TransmitGlobalTime = DISABLE;

   return CAN_OKAY;
}


static int8_t s8CANFilterInit(void)
{
   int8_t s8ErrorHandle = CAN_OKAY;

   xCANFilter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
   xCANFilter.FilterIdHigh = cu32TxId << 5u;
   xCANFilter.FilterIdLow = 0u;
   xCANFilter.FilterMaskIdHigh = 0u;
   xCANFilter.FilterMaskIdLow = 0u;
   xCANFilter.FilterScale = CAN_FILTERSCALE_32BIT;
   xCANFilter.FilterActivation = CAN_FILTER_ENABLE;

   if(HAL_OK != HAL_CAN_ConfigFilter(&hcan1, &xCANFilter))
   {
      s8ErrorHandle = CAN_ERROR;
   }

   return s8ErrorHandle;
}


static void vCANSetStatusLED(const int8_t cs8CANStatus)
{
   (CAN_OKAY == cs8CANStatus) ? vLEDStatusOkaySet() : vLEDStatusErrorSet();
}
