/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"



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
UART_HandleTypeDef huart2;

//osThreadId Task1Handle;
osThreadId Task2Handle;
osMessageQId myQueue01Handle;
osSemaphoreId myBinarySem01Handle;
/* USER CODE BEGIN PV */

// void RTOSTask1(void* argument);
// void RTOSTask2(void* argument);

// xTaskHandle task1Handle;
// xTaskHandle task2Handle;

// xQueueHandle  queueHandle;

// xSemaphoreHandle semaphoreHandle;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
//void StartTask1(void const * argument);
void StartTask2(void const * argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// char receiveData;


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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of myBinarySem01 */
  osSemaphoreDef(myBinarySem01);
  myBinarySem01Handle = osSemaphoreCreate(osSemaphore(myBinarySem01), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of myQueue01 */
  osMessageQDef(myQueue01, 5, uint8_t);
  myQueue01Handle = osMessageCreate(osMessageQ(myQueue01), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Task1 */
//  osThreadDef(Task1, StartTask1, osPriorityNormal, 0, 128);
//  Task1Handle = osThreadCreate(osThread(Task1), NULL);

  /* definition and creation of Task2 */
  osThreadDef(Task2, StartTask2, osPriorityNormal, 0, 128);
  Task2Handle = osThreadCreate(osThread(Task2), NULL);

  /* USER CODE BEGIN RTOS_THREADS */

  /*
  xTaskCreate(RTOSTask1, "task1", 128, NULL, 1, &task1Handle);
  xTaskCreate(RTOSTask2, "task2", 128, NULL, 1, &task2Handle);

  queueHandle = xQueueCreate(5,sizeof(int));

  if (queueHandle == 0)  // Queue not created
  {
	  char *str = "Unable to create Integer Queue\n\n";
	  HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen (str), HAL_MAX_DELAY);
  }
  else	// Queue is created successfully
  {
	  char *str = "Integer Queue Created successfully\n\n";
	  HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen (str), HAL_MAX_DELAY);
  }

  vTaskStartScheduler();
  */

  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/*
void RTOSTask1(void* argument)
{
	int receivedValue = 0;
	uint32_t TickDelay = pdMS_TO_TICKS(20);
	// int transmitValue = 555;

	while(1)
	{
		if(xSemaphoreTake(semaphoreHandle,portMAX_DELAY) == pdTRUE)
		{
			// char *ptx1 = "Task 1 is executed";
			// HAL_UART_Transmit(&huart2, (uint8_t *)ptx1, 18, 500);

			xQueueReceive(queueHandle, &receivedValue, portMAX_DELAY);

			// xQueueSend(queueHandle,&transmitValue,portMAX_DELAY);

			// char *ptx3 = NULL;
			// sprintf(ptx3,"Successfully received the number %d to the queue.\nLeaving Task 1\n\n\n",receivedValue);
		    // HAL_UART_Transmit(&huart2, (uint8_t *)ptx3, 67, 500);
		}

		vTaskDelay(TickDelay);
	}

}


void RTOSTask2(void* argument)
{
	int i = 222;
	uint32_t TickDelay = pdMS_TO_TICKS(1000);

	while(1)
	{
//		if(xQueueSend(queueHandle,(void *)&i,portMAX_DELAY) == pdPASS)
//		{
//			// char *ptx2 = "Data is sent successfully by task 2.\nLeaving task 2.\n\n\n";
//			// HAL_UART_Transmit(&huart2, (uint8_t *)ptx2,55 , 500);
//		}

		xQueueSend(queueHandle,(void *)&i,portMAX_DELAY);
		vTaskDelay(TickDelay);
	}
}
*/
// Interrupt Service Routine Number 1
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{


	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	// Assuming xSemaphore is your semaphore handle
	xSemaphoreGiveFromISR(myBinarySem01Handle, &xHigherPriorityTaskWoken);

	// If xHigherPriorityTaskWoken was set to true, a context switch should be requested
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

// Interrupt Service Routine Number 2
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//HAL_UART_Receive_IT(&huart2,(uint8_t *)&receiveData, 1);


//	int sendDatabyUART = 111;
//	if(receiveData == 'r')
//	{
//		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
//
//		if (xQueueSendToFrontFromISR(myQueue01Handle, &sendDatabyUART, &xHigherPriorityTaskWoken) == pdPASS)
//		{
//			HAL_UART_Transmit(huart, (uint8_t *)"\n\nSent from ISR\n\n", 17, 500);
//		}
//
//		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
//	}

}



/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartTask1 */
/**
  * @brief  Function implementing the Task1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTask1 */
//void StartTask1(void const * argument)
//{
//  /* USER CODE BEGIN 5 */
//////  /* Infinite loop */
//
//	int receivedValue = 0;
//	uint32_t TickDelay = pdMS_TO_TICKS(20);
//		// int transmitValue = 555;
//
//	while(1)
//	{
//		if(xSemaphoreTake(myBinarySem01Handle,) == pdTRUE)
//		{
//			// char *ptx1 = "Task 1 is executed";
//			// HAL_UART_Transmit(&huart2, (uint8_t *)ptx1, 18, 500);
//
//			xQueueReceive(myQueue01Handle, &receivedValue, portMAX_DELAY);
//
//			// xQueueSend(queueHandle,&transmitValue,portMAX_DELAY);
//
//			// char *ptx3 = NULL;
//			// sprintf(ptx3,"Successfully received the number %d to the queue.\nLeaving Task 1\n\n\n",receivedValue);
//			// HAL_UART_Transmit(&huart2, (uint8_t *)ptx3, 67, 500);
//		}
//
//		vTaskDelay(TickDelay);
//	}
//  /* USER CODE END 5 */
//}

/* USER CODE BEGIN Header_StartTask2 */
/**
* @brief Function implementing the Task2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask2 */
void StartTask2(void const * argument)
{
  /* USER CODE BEGIN StartTask2 */
////  /* Infinite loop */
//	int i = 222;
	uint32_t TickDelay = pdMS_TO_TICKS(1);

	while(1)
	{
	//		if(xQueueSend(queueHandle,(void *)&i,portMAX_DELAY) == pdPASS)
	//		{
	//			// char *ptx2 = "Data is sent successfully by task 2.\nLeaving task 2.\n\n\n";
	//			// HAL_UART_Transmit(&huart2, (uint8_t *)ptx2,55 , 500);
	//		}
		if(xSemaphoreTake(myBinarySem01Handle,0) == pdTRUE)
		{
			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
		}
		// xQueueSend(myQueue01Handle,(void *)&i,portMAX_DELAY);
		vTaskDelay(TickDelay);
	}
  /* USER CODE END StartTask2 */
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
  __disable_irq();
  while (1)
  {
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
