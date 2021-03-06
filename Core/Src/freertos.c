/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for ThreadCANSendMe */
osThreadId_t ThreadCANSendMeHandle;
const osThreadAttr_t ThreadCANSendMe_attributes = {
  .name = "ThreadCANSendMe",
  .priority = (osPriority_t) osPriorityBelowNormal,
  .stack_size = 128 * 4
};
/* Definitions for ThreadLEDSystem */
osThreadId_t ThreadLEDSystemHandle;
const osThreadAttr_t ThreadLEDSystem_attributes = {
  .name = "ThreadLEDSystem",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void vThreadCANSendMessage(void *argument);
void vThreadLEDSystemAlive(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of ThreadCANSendMe */
  ThreadCANSendMeHandle = osThreadNew(vThreadCANSendMessage, NULL, &ThreadCANSendMe_attributes);

  /* creation of ThreadLEDSystem */
  ThreadLEDSystemHandle = osThreadNew(vThreadLEDSystemAlive, NULL, &ThreadLEDSystem_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_vThreadCANSendMessage */
/**
* @brief Function implementing the ThreadCANSendMe thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_vThreadCANSendMessage */
void vThreadCANSendMessage(void *argument)
{
  /* USER CODE BEGIN vThreadCANSendMessage */
  /* Infinite loop */
   TickType_t xPreviousWakeTime = xTaskGetTickCount();

   while(1)
   {
      s8CANSendMessage();
      vTaskDelayUntil(&xPreviousWakeTime, 5u/portTICK_RATE_MS);
   }
  /* USER CODE END vThreadCANSendMessage */
}

/* USER CODE BEGIN Header_vThreadLEDSystemAlive */
/**
* @brief Function implementing the ThreadLEDSystem thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_vThreadLEDSystemAlive */
void vThreadLEDSystemAlive(void *argument)
{
  /* USER CODE BEGIN vThreadLEDSystemAlive */
  /* Infinite loop */
   TickType_t xPreviousWakeTime = xTaskGetTickCount();

   while(1)
   {
      vLEDSystemAliveToggle();
      vTaskDelayUntil(&xPreviousWakeTime, 250u/portTICK_RATE_MS);
   }
  /* USER CODE END vThreadLEDSystemAlive */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
