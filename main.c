/******TMP102 Sensor Hal Driver****************/
/*****This project developed with using HAL libraries*****/

#include "stm32f4xx_hal.h"
#include "main.h"
#include "tmp_102.h"
#include "my_printf.h"

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);

uint8_t tmp102_conf_reg[2];
double temper_res;

int main(void) {

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
 
  /* Configure the system clock */
  SystemClock_Config();
 
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  //MX_USART2_UART_Init();
  MX_USART3_UART_Init();
	
	tmp102_init(&hi2c1);
	
	while(1) {
	
		temper_res = tmp102_temperature_read(&hi2c1);
	
		//my_printf(&huart2, "Current te¦mperature: %f\n", temper_res);
		my_printf(&huart3, "Current temperature");	
		HAL_Delay(10);
	}

}

static void MX_I2C1_Init(void) {
 
  hi2c1.Instance = I2C1;
	
  hi2c1.Init.ClockSpeed = 400000;
	
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	
  hi2c1.Init.OwnAddress1 = 0;
	
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	
  hi2c1.Init.OwnAddress2 = 0;
	
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
 
}

static void   MX_USART2_UART_Init() {
	
	huart2.Instance = USART2;
	
	huart2.Init.BaudRate = 115200;
	
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	
	huart2.Init.StopBits = UART_STOPBITS_1;
	
	huart2.Init.Parity = UART_PARITY_NONE;
	
	huart2.Init.Mode = UART_MODE_TX_RX;
	
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	
	if(HAL_UART_Init(&huart2) != HAL_OK) {
	
		_Error_Handler(__FILE__, __LINE__);
	
	}

}

static void  MX_USART3_UART_Init() {
	
	huart3.Instance = USART3;
	
	huart3.Init.BaudRate = 115200;
	
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	
	huart3.Init.StopBits = UART_STOPBITS_1;
	
	huart3.Init.Parity = UART_PARITY_NONE;
	
	huart3.Init.Mode = UART_MODE_TX_RX;
	
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	
	if(HAL_UART_Init(&huart3) != HAL_OK) {
	
		_Error_Handler(__FILE__, __LINE__);
	
	}

}

void SystemClock_Config(void) {

	RCC_OscInitTypeDef RCC_OscInitStruct;
	
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	
	/**Ana dahili regulatör çikis gerilimini konfigüre et
    */

	__HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	/**CPU, AHB ve APB buslarinin clocklari set edilir
    */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	
	RCC_OscInitStruct.HSICalibrationValue = 16;
	
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	
	RCC_OscInitStruct.PLL.PLLM = 16;
	
	RCC_OscInitStruct.PLL.PLLN = 336;
	
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	
	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
	
		_Error_Handler(__FILE__,__LINE__);
		
	}
	
	/**CPU, AHB ve APB buslarinin clocklari ilklendirilir
    */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
																|RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	
	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
	
		_Error_Handler(__FILE__, __LINE__);
	
	}
	
	//Systick Interrupt Time'i konfigüre et
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
	
	//Systick'i konfigüre et
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	
	//Systick_IRQn interrupt'i konfigüre et
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
	
}
	
static void MX_GPIO_Init(void) {

	GPIO_InitTypeDef GPIO_InitStruct;
	
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	__HAL_RCC_GPIOH_CLK_ENABLE();
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
	
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
	
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);
	
}

	/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line) {
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}
