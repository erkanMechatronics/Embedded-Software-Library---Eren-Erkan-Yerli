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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "usbd_cdc.h"
#include "usbd_conf.h"
#include "usbd_desc.h"
#include "usbd_cdc_if.h"

#include "string.h"
#include "stdint.h"


#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"




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

osThreadId SenderTask1Handle;
osThreadId SenderTask2Handle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void StartSenderTask1(void const * argument);
void StartSenderTask2(void const * argument);

/* USER CODE BEGIN PFP */



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*
 *
 *
 *
 *
 *
 */


void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask3(void *pvParameters);
void vTask4(void *pvParameters);
void vHighTask(void *pvParameters);
void vMediumTask(void *pvParameters);
void vLowTask(void *pvParameters);

// Task Handles
TaskHandle_t xTask1Handle = NULL;
TaskHandle_t xTask2Handle = NULL;
TaskHandle_t xTask3Handle = NULL;
TaskHandle_t xTask4Handle = NULL;
TaskHandle_t xHighTaskHandle = NULL;
TaskHandle_t xMediumTaskHandle = NULL;
TaskHandle_t xLowTaskHandle = NULL;

// Semaphore Handles
SemaphoreHandle_t myBinarySemaphoreHandle;


// Initial state priority of task 1 is : 2

//void vTask1(void *pvParameters)
//{
//  	UBaseType_t uxPriority;
//
//  	uxPriority = uxTaskPriorityGet(xTask1Handle);
//
//  	for( ;; )
//  	{
//  		HAL_Delay(1);
//
//  		char *str1 = "Task 1 is running\n";
//  		CDC_Transmit_FS((uint8_t *)str1, strlen(str1));
//
//  		HAL_Delay(1);
//
//  		char *str2 = "About to raise the Task 2 priority\n";
//  		CDC_Transmit_FS((uint8_t *)str2, strlen(str2));
//
//  		vTaskPrioritySet(xTask2Handle, uxPriority + 1);
//
//  		vTaskDelay(pdMS_TO_TICKS(2000));
//  	}
//}
//
//// Initial state priority of task 2 is : 1
//
//void vTask2(void *pvParameters)
//{
//  	UBaseType_t uxPriority;
//
//  	uxPriority = uxTaskPriorityGet(xTask2Handle);
//
//  	for( ;; )
//  	{
//  		HAL_Delay(1);
//
//  		char *str1 = "Task 2 is running\n";
//  		CDC_Transmit_FS((uint8_t *)str1, strlen(str1));
//
//  		HAL_Delay(1);
//
//  		char *str2 = "About to lower the Task 2 priority\n";
//  		CDC_Transmit_FS((uint8_t *)str2, strlen(str2));
//
//  		vTaskPrioritySet(xTask2Handle, uxPriority - 2);
//
//  		vTaskDelay(pdMS_TO_TICKS(2000));
//  	}
//
//}
//
//void vTask3(void *pvParameters)
//{
//	/*
//	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);
//	vTaskDelay(1000);
//	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);
//	vTaskDelay(1000);
//	*/
//
//	 for(;;)
//	 {
//	  	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);
//		HAL_Delay(1000);
//		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);
//		HAL_Delay(1000);
//
//	 }
//}
//
//
//
//void vTask4(void *pvParameters)
//{
//	/*
//	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_SET);
//	vTaskDelay(1000);
//	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET);
//	vTaskDelay(1000);
//    */
//
//	 for(;;)
//	 {
//	  	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_SET);
//	  	  HAL_Delay(1000);
//	      HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET);
//	      HAL_Delay(1000);
//	 }
//}
//
//void vHighTask(void *pvParameters)
//{
//
//	for(;;)
//	{
//		HAL_Delay(1);
//
//		char *str1 = "Entered High Task and waiting for Semaphore.\n";
//		// CDC_Transmit_FS((uint8_t *)str1, strlen(str1));
//		HAL_UART_Transmit(&huart2, (uint8_t *)str1, strlen(str1), 1000);
//
//		xSemaphoreTake(myBinarySemaphoreHandle,portMAX_DELAY);
//
//		HAL_Delay(1);
//		char *str2 = "Semaphore acquired by High Task\n";
//		// CDC_Transmit_FS((uint8_t *)str2, strlen(str2));
//		HAL_UART_Transmit(&huart2, (uint8_t *)str2, strlen(str2), 1000);
//
//		HAL_Delay(1);
//		char *str3 = "Leaving High Task and releasing Semaphore\n\n";
//		// CDC_Transmit_FS((uint8_t *)str3, strlen(str3));
//		HAL_UART_Transmit(&huart2, (uint8_t *)str3, strlen(str3), 1000);
//
//		xSemaphoreGive(myBinarySemaphoreHandle);
//
//		vTaskDelay(pdMS_TO_TICKS(500));
//	}
//
//}
//
//
//void vMediumTask(void *pvParameters)
//{
//
//	for(;;)
//	{
//		HAL_Delay(100);
//
//		char *str1 = "Entered Medium Task\n";
//		// CDC_Transmit_FS((uint8_t *)str1, strlen(str1));
//		HAL_UART_Transmit(&huart2, (uint8_t *)str1, strlen(str1), 1000);
//
//
//		HAL_Delay(1);
//		char *str2 = "Entered Medium Task\n\n";
//		// CDC_Transmit_FS((uint8_t *)str2, strlen(str2));
//		HAL_UART_Transmit(&huart2, (uint8_t *)str2, strlen(str2), 1000);
//
//		vTaskDelay(pdMS_TO_TICKS(500));
//	}
//
//}
//
//void vLowTask(void *pvParameters)
//{
//
//	for(;;)
//	{
//		HAL_Delay(1);
//
//		char *str1 = "Entered Low Task and waiting for Semaphore.\n";
//		// CDC_Transmit_FS((uint8_t *)str1, strlen(str1));
//		HAL_UART_Transmit(&huart2, (uint8_t *)str1, strlen(str1), 1000);
//
//		xSemaphoreTake(myBinarySemaphoreHandle,portMAX_DELAY);
//
//		HAL_Delay(1);
//		char *str2 = "Semaphore acquired by Low Task\n";
//		// CDC_Transmit_FS((uint8_t *)str2, strlen(str2));
//		HAL_UART_Transmit(&huart2, (uint8_t *)str2, strlen(str2), 1000);
//
//		while(!(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)));
//
//		HAL_Delay(1);
//		char *str3 = "Leaving Low Task and releasing  Semaphore.\n\n";
//		// CDC_Transmit_FS((uint8_t *)str3, strlen(str3));
//		HAL_UART_Transmit(&huart2, (uint8_t *)str3, strlen(str3), 1000);
//
//		xSemaphoreGive(myBinarySemaphoreHandle);
//
//		vTaskDelay(pdMS_TO_TICKS(500));
//	}
//}

void Task1(void *pvParameters);
void Task2(void *pvParameters);
void Task3(void *pvParameters);
void Task4(void *pvParameters);

void Task1(void *pvParameters)
{
	UBaseType_t priority1;
	TickType_t delay;
	delay = pdMS_TO_TICKS(4000);

	priority1 = uxTaskPriorityGet(xTask1Handle);

	for(;;)
	{
		HAL_Delay(1);
		char *str1 = "Entered and running Task 1\n";
		CDC_Transmit_FS((uint8_t *)str1, strlen(str1));
		HAL_Delay(1);

		//HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);

		vTaskPrioritySet(xTask2Handle,priority1 + 1);
		vTaskDelay(delay);
	}

}

void Task2(void *pvParameters)
{
	UBaseType_t priority2;
	TickType_t delay;
	delay = pdMS_TO_TICKS(4000);

	priority2 = uxTaskPriorityGet(xTask2Handle);

	for(;;)
	{
		HAL_Delay(1);
		char *str1 = "Entered and running Task 2\n";
		CDC_Transmit_FS((uint8_t *)str1, strlen(str1));
		HAL_Delay(1);

		// vTaskPrioritySet(xTask2Handle,priority2 - 2);
		vTaskPrioritySet(xTask2Handle,priority2 - 2);
		vTaskDelay(delay);
	}


}

void Task3(void *pvParameters)
{
	volatile uint8_t count_value = 0;
	TickType_t delay;

	delay = pdMS_TO_TICKS(4000);

	for(;;)
	{
		HAL_Delay(1);
		char *str1 = "Entered and running Task 3\n";
		CDC_Transmit_FS((uint8_t *)str1, strlen(str1));
		HAL_Delay(1);

		if(count_value == 3)
		{
			// xTaskNotifyGive(xTask4Handle);
			// ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
			xSemaphoreGive(myBinarySemaphoreHandle);

			vTaskDelete(xTask3Handle);
		}
		else
		{
			count_value++;
		}

		vTaskDelay(delay);
	}

}

void Task4(void *pvParameters)
{
	// ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

	for(;;)
	{

		if(xSemaphoreTake(myBinarySemaphoreHandle,portMAX_DELAY))
		{

			// char *str2 = "Deleting the Task 3 from Task 4\n";
			// CDC_Transmit_FS((uint8_t *)str2, strlen(str2));
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12, GPIO_PIN_SET);




		}

	}

	// xTaskNotifyGive(xTask3Handle);
}




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

  MX_USB_DEVICE_Init();


  // xTaskCreate(vTask1, "Task 1", 1000, NULL, 2, &xTask1Handle);
  // xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, &xTask2Handle);
  // xTaskCreate(vTask3, "Task 3", 1000, NULL, 2, &xTask3Handle);
  // xTaskCreate(vTask4, "Task 4", 1000, NULL, 1, &xTask4Handle);

  myBinarySemaphoreHandle = xSemaphoreCreateBinary();

  // xTaskCreate(vHighTask, "High Task", 1000, NULL, 3, &xHighTaskHandle);
  // xTaskCreate(vMediumTask, "Medium Task", 1000, NULL, 2, &xMediumTaskHandle);
  // xTaskCreate(vLowTask, "Low Task", 1000, NULL, 1, &xLowTaskHandle);

  xTaskCreate(Task1,"Task 1",1000,NULL,3,&xTask1Handle);
  xTaskCreate(Task2,"Task 2",1000,NULL,2,&xTask2Handle);
  xTaskCreate(Task3,"Task 3",1000,NULL,1,&xTask3Handle);
  xTaskCreate(Task4,"Task 4",1000,NULL,5,&xTask4Handle);

  // xSemaphoreGive(myBinarySemaphoreHandle);

  vTaskStartScheduler();


  /* USER CODE END 2 */

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
  /* definition and creation of SenderTask1 */
  //osThreadDef(SenderTask1, StartSenderTask1, osPriorityNormal, 0, 128);
  //SenderTask1Handle = osThreadCreate(osThread(SenderTask1), NULL);

  /* definition and creation of SenderTask2 */
  //osThreadDef(SenderTask2, StartSenderTask2, osPriorityNormal, 0, 128);
  //SenderTask2Handle = osThreadCreate(osThread(SenderTask2), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  //osKernelStart();

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartSenderTask1 */
/**
  * @brief  Function implementing the SenderTask1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartSenderTask1 */

/* USER CODE BEGIN Header_StartSenderTask2 */
/**
* @brief Function implementing the SenderTask2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSenderTask2 */


/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM2) {
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
