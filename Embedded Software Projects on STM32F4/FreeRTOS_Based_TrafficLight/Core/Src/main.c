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

#include "usbd_conf.h"
#include "usbd_cdc_if.h"
#include "usbd_desc.h"
#include "string.h"
#include "stdint.h"

volatile uint8_t control = 0;

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
osThreadId TrafficLight1Handle;
osThreadId TrafficLight2Handle;
osThreadId pedestrianTaskHandle;
osSemaphoreId myBinarySem01Handle;
osSemaphoreId myBinarySem02Handle;
osSemaphoreId myBinarySem03Handle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void StartTrafficLight1(void const * argument);
void StartTrafficLight2(void const * argument);
void StartpedestrianTask(void const * argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of myBinarySem01 */
  osSemaphoreDef(myBinarySem01);
  myBinarySem01Handle = osSemaphoreCreate(osSemaphore(myBinarySem01), 1);

  /* definition and creation of myBinarySem02 */
  osSemaphoreDef(myBinarySem02);
  myBinarySem02Handle = osSemaphoreCreate(osSemaphore(myBinarySem02), 1);

  /* definition and creation of myBinarySem03 */
  osSemaphoreDef(myBinarySem03);
  myBinarySem03Handle = osSemaphoreCreate(osSemaphore(myBinarySem03), 1);

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
  /* definition and creation of TrafficLight1 */
  osThreadDef(TrafficLight1, StartTrafficLight1, osPriorityNormal, 0, 128);
  TrafficLight1Handle = osThreadCreate(osThread(TrafficLight1), NULL);

  /* definition and creation of TrafficLight2 */
  osThreadDef(TrafficLight2, StartTrafficLight2, osPriorityNormal, 0, 128);
  TrafficLight2Handle = osThreadCreate(osThread(TrafficLight2), NULL);

  /* definition and creation of pedestrianTask */
  osThreadDef(pedestrianTask, StartpedestrianTask, osPriorityAboveNormal, 0, 128);
  pedestrianTaskHandle = osThreadCreate(osThread(pedestrianTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
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
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
  HAL_GPIO_WritePin(GPIOD, GREEN2_Pin|ORANGE2_Pin|BLUE_Pin|RED2_Pin
                          |GREEN1_Pin|ORANGE1_Pin|RED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : GREEN2_Pin ORANGE2_Pin BLUE_Pin RED2_Pin
                           GREEN1_Pin ORANGE1_Pin RED1_Pin */
  GPIO_InitStruct.Pin = GREEN2_Pin|ORANGE2_Pin|BLUE_Pin|RED2_Pin
                          |GREEN1_Pin|ORANGE1_Pin|RED1_Pin;
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

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if (GPIO_Pin == GPIO_PIN_0)
	{
		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0));

		// xSemaphoreGiveFromISR(myBinarySem02Handle,portMAX_DELAY);

		// portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

		control = 1;
	}
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartTrafficLight1 */
/**
  * @brief  Function implementing the TrafficLight1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTrafficLight1 */
void StartTrafficLight1(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 5 */

	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET); // Kirmizi 1

  /* Infinite loop */
  for(;;)
  {
	  if(xSemaphoreTake(myBinarySem01Handle,portMAX_DELAY) == pdTRUE)
	  {
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_SET);   // Turuncu 1
		  HAL_Delay(1000);

		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_RESET);  // Turuncu 1
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_RESET);  // Kirmizi 1

		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_SET);  //  Yesil 1
		  char *str1 = "1. Trafik isigi yesil yaniyor.\n\n\r";
		  CDC_Transmit_FS((uint8_t *)str1,strlen(str1));

		  HAL_Delay(5000);

		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET); // Yesil 1
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_SET);   // Turuncu 1

		  HAL_Delay(1000);

		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_RESET);   // Turuncu 1
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET);   // Kirmizi 1
		  char *str2 = "1. Trafik isigi kirmizi yaniyor.\n\n\r";
		  CDC_Transmit_FS((uint8_t *)str2,strlen(str2));

		  HAL_Delay(4000);

		  if(control == 1)
		  {
			  xSemaphoreGive(myBinarySem02Handle);
		  }


		  xSemaphoreGive(myBinarySem01Handle);


	  }

	  vTaskDelay(pdMS_TO_TICKS(1));
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTrafficLight2 */
/**
* @brief Function implementing the TrafficLight2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTrafficLight2 */
void StartTrafficLight2(void const * argument)
{
  /* USER CODE BEGIN StartTrafficLight2 */

	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET); // Kirmizi 2
  /* Infinite loop */
  for(;;)
  {
	  if(xSemaphoreTake(myBinarySem01Handle,portMAX_DELAY) == pdTRUE)
	  {
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_SET);   // Turuncu 2
		  HAL_Delay(1000);

		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_RESET);  // Turuncu 2
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);  // Kirmizi 2

		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_SET);  //  Yesil 2
		  char *str1 = "1. Trafik isigi yesil yaniyor.\n\n\r";
		  CDC_Transmit_FS((uint8_t *)str1,strlen(str1));

		  HAL_Delay(5000);

		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_RESET); // Yesil 2
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_SET);   // Turuncu 2

		  HAL_Delay(1000);

		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_RESET);   // Turuncu 2
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);   // Kirmizi 2
		  char *str2 = "1. Trafik isigi kirmizi yaniyor.\n\n\r";
		  CDC_Transmit_FS((uint8_t *)str2,strlen(str2));

		  HAL_Delay(4000);

		  if(control == 1)
		  {
			  xSemaphoreGive(myBinarySem02Handle);
		  }

		  xSemaphoreGive(myBinarySem01Handle);
	  }

	  vTaskDelay(pdMS_TO_TICKS(1));
  }
  /* USER CODE END StartTrafficLight2 */
}

/* USER CODE BEGIN Header_StartpedestrianTask */
/**
* @brief Function implementing the pedestrianTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartpedestrianTask */
void StartpedestrianTask(void const * argument)
{
  /* USER CODE BEGIN StartpedestrianTask */
  /* Infinite loop */
  for(;;)
  {
	  if(xSemaphoreTake(myBinarySem02Handle,portMAX_DELAY) == pdTRUE)
	  {
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET); // Yesil 1
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_RESET); // Turuncu 1
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET);   // Kirmizi 1

		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_RESET);  // Yesil 2
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_RESET); // Turuncu 2
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);   // Kirmizi 2

		  HAL_Delay(500);

		  vTaskSuspend(TrafficLight1Handle);
		  vTaskSuspend(TrafficLight2Handle);

		  char *str1 = "1. ve 2. trafik isigi kirmizi yaniyor.\n\n\r";
		  CDC_Transmit_FS((uint8_t *)str1, strlen(str1));
		  // HAL_Delay(2000);

		  char *str2 = "Yayalar geciyor.\n\n\r";
		  CDC_Transmit_FS((uint8_t *)str2, strlen(str2));
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);

		  HAL_Delay(4000);

		  for(int i = 0;i < 5;i++)
		  {
			  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
			  HAL_Delay(250);
			  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
			  HAL_Delay(250);
		  }

		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);

		  char *str3 = "Yayalar gecti.\n\n\r";
		  CDC_Transmit_FS((uint8_t *)str3, strlen(str3));
		  HAL_Delay(2000);

		  control = 0;

		  vTaskResume(TrafficLight1Handle);
		  vTaskResume(TrafficLight2Handle);


	  }
	  vTaskDelay(pdMS_TO_TICKS(1));
  }
  /* USER CODE END StartpedestrianTask */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
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
