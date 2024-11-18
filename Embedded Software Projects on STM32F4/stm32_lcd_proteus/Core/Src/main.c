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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "LCD.h"
#include "string.h"
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"

void motor_forward(void);
void motor_backward(void);
void motor_stop(void);



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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


void motor_forward(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
}



void motor_backward(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
}

void motor_stop(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
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
  /* USER CODE BEGIN 2 */

  lcd_init(_LCD_4BIT, _LCD_FONT_5x8, _LCD_2LINE);
  lcd_cmd(_LCD_INIT);
  lcd_print(1, 1, "Enter Password.");


  int i = 1;

  char entered_password[5];
  char real_password[5] = "12345";


  // char yazi[32] = " ";
  HAL_Delay(10);
  // lcd_clear();

  // int i = 0;
  // char tuslar[4][3] = {
  //	  {'1','2','3'},
  //		  {'4','5','6'},
  //		  {'7','8','9'},
  //		  {'*','0','#'}
  //};


  // char sifre[5];



//  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
//  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
//  HAL_Delay(5000);
//
//  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
//  HAL_Delay(5000);

  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);


  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);

	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14))
	{
		while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14));
		lcd_print(2,i,"1");
		entered_password[i - 1] = '1';
		i++;

	}
	else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13))
	{
		while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13));
		lcd_print(2,i,"4");
		entered_password[i - 1] = '4';
		i++;
	}
	else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12))
	{
		while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12));
		lcd_print(2,i,"7");
		entered_password[i - 1] = '7';
		i++;
	}
	else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11))
	{
		while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11));
		lcd_print(2,i,"*");
		entered_password[i - 1] = '*';
		i++;
	}

	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);

	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14))
	{
		while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14));
		lcd_print(2,i,"2");
		entered_password[i - 1] = '2';
		i++;
	}
	else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13))
	{
		while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13));
		lcd_print(2,i,"5");
		entered_password[i - 1] = '5';
		i++;
	}
	else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12))
	{
		while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12));
		lcd_print(2,i,"8");
		entered_password[i - 1] = '8';
		i++;

	}
	else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11))
	{
		while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11));
		lcd_print(2,i,"0");
		entered_password[i - 1] = '0';
		i++;
	}

	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);

	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14))
	{
		while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14));
		lcd_print(2,i,"3");
		entered_password[i - 1] = '3';
		i++;
	}
	else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13))
	{
		while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13));
		lcd_print(2,i,"6");
		entered_password[i - 1] = '6';
		i++;
	}
	else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12))
	{
		while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12));
		lcd_print(2,i,"9");
		entered_password[i - 1] = '9';
		i++;
	}
	else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11))
	{
		while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11));
		lcd_print(2,i,"#");
		entered_password[i - 1] = '#';
		i++;
	}


	if (i == 6)
	{
		for(int j = 0;j < 5;j++)
		{
			if(entered_password[j] != real_password[j])
			{
				lcd_clear();
				lcd_print(1, 1, "Wrong Password!");
				lcd_print(2, 1, "Try again.");
				HAL_Delay(3000);

				lcd_clear();
				lcd_print(1,1,"Enter Password.");

				i = 1;
				break;
			}

			if(j == 4)
			{
				lcd_clear();
				lcd_print(1,1,"Correct Password!");
				HAL_Delay(1000);
				lcd_print(2,1,"Enter Please!");
				motor_forward();
				HAL_Delay(3000);

				motor_stop();
				HAL_Delay(1000);

				motor_backward();
				HAL_Delay(3000);
				motor_stop();

				for(int a = 0;a < 5;a++)
				{
					entered_password[a] = 0;
				}

				lcd_clear();
				lcd_print(1,1,"Enter Password.");




				i = 1;
			}
		}
	}
  }
  /* USER CODE END 3 */
}

/*



for(int i = 0;i < 5;i++)
{
	hangi tuşa denk geliyorsa yazdır. o ilgili değeri bir diziye ata.
	ondan sonra bir sonraki sütuna yazdır. yine diziye ata.

	en sonda dizinin elemanları sırasıyla "12345" sifresine esitse,
	sifre dogrudur dolayısıyla kapıyı açabilirsin.
}





 */







/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_EN_Pin|LCD_RS_Pin|LCD_D4_Pin|LCD_D5_Pin
                          |LCD_D6_Pin|LCD_D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pins : LCD_EN_Pin LCD_RS_Pin LCD_D4_Pin LCD_D5_Pin
                           LCD_D6_Pin LCD_D7_Pin */
  GPIO_InitStruct.Pin = LCD_EN_Pin|LCD_RS_Pin|LCD_D4_Pin|LCD_D5_Pin
                          |LCD_D6_Pin|LCD_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB6 PB7
                           PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB11 PB12 PB13 PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
