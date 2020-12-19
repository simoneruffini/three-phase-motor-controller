/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "dma.h"
#include "gpio.h"
#include "tim.h"
#include "usart.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "math.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define good_sampling_value 300
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t sin_samp_chn1[] = {
    5312,  5729,  6143,  6552,  6954,  7345,  7724,  8088,  8435,  8762,
    9069,  9352,  9610,  9842,  10045, 10220, 10364, 10478, 10559, 10608,
    10625, 10608, 10559, 10478, 10364, 10220, 10045, 9842,  9610,  9352,
    9069,  8762,  8435,  8088,  7724,  7345,  6954,  6552,  6143,  5729,
    5312,  4895,  4481,  4072,  3670,  3279,  2900,  2536,  2189,  1862,
    1555,  1272,  1014,  782,   579,   404,   260,   146,   65,    16,
    0,     16,    65,    146,   260,   404,   579,   782,   1014,  1272,
    1555,  1862,  2189,  2536,  2900,  3279,  3670,  4072,  4481,  4895};
uint32_t sin_samp_chn2[] = {
    9913,  9690,  9441,  9166,  8867,  8546,  8205,  7847,  7473,  7085,
    6687,  6280,  5867,  5451,  5034,  4619,  4207,  3803,  3408,  3025,
    2656,  2303,  1969,  1655,  1364,  1097,  857,   643,   459,   304,
    181,   88,    29,    1,     7,     45,    116,   218,   352,   517,
    711,   934,   1183,  1458,  1757,  2078,  2419,  2777,  3151,  3539,
    3937,  4344,  4757,  5173,  5590,  6005,  6417,  6821,  7216,  7599,
    7968,  8321,  8655,  8969,  9260,  9527,  9767,  9981,  10165, 10320,
    10443, 10536, 10595, 10623, 10617, 10579, 10508, 10406, 10272, 10107};
uint32_t sin_samp_chn3[] = {
    711,   517,   352,   218,   116,   45,    7,     1,     29,    88,
    181,   304,   459,   643,   857,   1097,  1364,  1655,  1969,  2303,
    2656,  3025,  3408,  3803,  4207,  4619,  5034,  5451,  5867,  6280,
    6687,  7085,  7473,  7847,  8205,  8546,  8867,  9166,  9441,  9690,
    9913,  10107, 10272, 10406, 10508, 10579, 10617, 10623, 10595, 10536,
    10443, 10320, 10165, 9981,  9767,  9527,  9260,  8969,  8655,  8321,
    7968,  7599,  7216,  6821,  6417,  6005,  5590,  5173,  4757,  4344,
    3937,  3539,  3151,  2777,  2419,  2078,  1757,  1458,  1183,  934};
uint8_t sin_samp_chnX_size = sizeof(sin_samp_chn1) / sizeof(sin_samp_chn1[0]);
uint8_t _position = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint32_t get_timer_period_hz(uint16_t);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick.
   */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_LPUART1_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  __HAL_TIM_SET_PRESCALER(&htim2, 3);
  __HAL_TIM_SET_AUTORELOAD(&htim2, 10625);
  //__HAL_TIM_ENABLE_OCxPRELOAD(&htim2, TIM_CHANNEL_1);
  if (HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, sin_samp_chn1,
                            sin_samp_chnX_size) != HAL_OK) {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, sin_samp_chn2,
                            sin_samp_chnX_size) != HAL_OK) {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_3, sin_samp_chn3,
                            sin_samp_chnX_size) != HAL_OK) {
    Error_Handler();
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
   */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the peripherals clocks
   */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1) {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line
number,
ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
