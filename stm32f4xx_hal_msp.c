#include "stm32f4xx_hal.h"

extern void _Error_Handler(char *, int);

void HAL_MspInit(void) {

	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);
	
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
	
	HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
	
	HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
	
	HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
	
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c) {

	GPIO_InitTypeDef GPIO_InitStruct;
	
	if(hi2c->Instance == I2C1) {
	
		/**I2C1 GPIO Konfigürasyonu    
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA 
    */
		
		GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
		
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
		
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		//Peripheral clock etkinlestirildi
		__HAL_RCC_I2C1_CLK_ENABLE();
	}

}


void HAL_I2C1_MspDeInit(I2C_HandleTypeDef *hi2c) {

	if(hi2c->Instance == I2C1) {
	
		__HAL_RCC_I2C1_CLK_DISABLE();
		
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6 | GPIO_PIN_7);
	
	
	}


}

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {

	GPIO_InitTypeDef GPIO_InitStruct;
  if(huart->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }

	if(huart->Instance==USART3)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

  if(huart->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
	
	if(huart->Instance==USART3)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10|GPIO_PIN_11);

  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }

}
