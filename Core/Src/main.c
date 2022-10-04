/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define OFF 0
#define RED 1
#define GREEN 2

#define NUM_LEDS 7

#define LED1(state) HAL_GPIO_WritePin(LED12_GPIO_Port, LED12_Pin, state&1); HAL_GPIO_WritePin(LED11_GPIO_Port, LED11_Pin, state&2);
#define LED2(state) HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, state&1); HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, state&2);
#define LED3(state) HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, state&1); HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, state&2);
#define LED4(state) HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, state&1); HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, state&2);
#define LED5(state) HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, state&1); HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, state&2);
#define LED6(state) HAL_GPIO_WritePin(LED10_GPIO_Port, LED10_Pin, state&1); HAL_GPIO_WritePin(LED9_GPIO_Port, LED9_Pin, state&2);
#define LED7(state) HAL_GPIO_WritePin(LED14_GPIO_Port, LED14_Pin, state&1); HAL_GPIO_WritePin(LED13_GPIO_Port, LED13_Pin, state&2);


#define BUT_LEFT HAL_GPIO_ReadPin(SWITCH_L_GPIO_Port,SWITCH_L_Pin)
#define BUT_RIGHT HAL_GPIO_ReadPin(SWITCH_R_GPIO_Port,SWITCH_R_Pin)


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

void set_LEDs(int state[], int del){

	  LED1(state[0]);
	  HAL_Delay(del);
	  LED2(state[1]);
	  HAL_Delay(del);
	  LED3(state[2]);
	  HAL_Delay(del);
	  LED4(state[3]);
	  HAL_Delay(del);
	  LED5(state[4]);
	  HAL_Delay(del);
	  LED6(state[5]);
	  HAL_Delay(del);
	  LED7(state[6]);
	  HAL_Delay(del);
}

void rot_R(int state[]){
	int state_last = state[NUM_LEDS-1];
	for(int i=NUM_LEDS-1;i>0;i--){
		state[i] = state[i-1];
	}
	state[0] = state_last;
}

void rot_L(int state[]){
	int state_first = state[0];
	for(int i=0;i<NUM_LEDS-1;i++){
		state[i] = state[i+1];
	}
	state[NUM_LEDS-1] = state_first;
}

void set_all(int colour){
	int tmp_state[] = {colour, colour, colour, colour, colour, colour, colour};
	set_LEDs(tmp_state, 0);
}

void flash(int colour, int del){
	set_all(OFF);
	HAL_Delay(del);
	set_all(colour);
	HAL_Delay(del);
	set_all(OFF);

}

//void flash

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

  int state[7] = {GREEN,0,0,0,0,0,0};
  int dir = 1;
  int game_over = 1;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

//	  while (game_over){
//		  set_LEDs(state, 0);
//
//	  }

	  set_LEDs(state, 0);

	  HAL_Delay(100);


	  if (BUT_LEFT){
//		  if (state[0] != OFF)
		  flash(GREEN, 100);
	  } else if(BUT_RIGHT){
		  for(int i=0;i<NUM_LEDS-1;i++){
			  if (state[i] == RED){
				  state[i] = GREEN;
			  } else if (state[i] == GREEN){
				  state[i] = RED;
			  }
		  }
	  }

	  if (state[0] != OFF){
		  dir = 1;
	  } else if (state[NUM_LEDS-1] != OFF){
		  dir = 0;
	  }

	  if (dir){
		  rot_R(state);
	  } else {
		  rot_L(state);
	  }





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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED12_Pin|LED11_Pin|LED13_Pin|LED14_Pin
                          |LED9_Pin|LED10_Pin|LED1_Pin|LED2_Pin
                          |LED4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED6_Pin|LED5_Pin|LED3_Pin|LED8_Pin
                          |LED7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED12_Pin LED11_Pin LED13_Pin LED14_Pin
                           LED9_Pin LED10_Pin LED1_Pin LED2_Pin
                           LED4_Pin */
  GPIO_InitStruct.Pin = LED12_Pin|LED11_Pin|LED13_Pin|LED14_Pin
                          |LED9_Pin|LED10_Pin|LED1_Pin|LED2_Pin
                          |LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SWITCH_L_Pin SWITCH_R_Pin */
  GPIO_InitStruct.Pin = SWITCH_L_Pin|SWITCH_R_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED6_Pin LED5_Pin LED3_Pin LED8_Pin
                           LED7_Pin */
  GPIO_InitStruct.Pin = LED6_Pin|LED5_Pin|LED3_Pin|LED8_Pin
                          |LED7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
