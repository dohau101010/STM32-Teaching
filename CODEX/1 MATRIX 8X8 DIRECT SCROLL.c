#include "main.h"
#include "stdio.h"
#include "string.h"
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
uint8_t dich = 0;
 uint8_t  character[][8] = {
{0xFF,0x03,0x01,0xED,0xED,0x01,0x03,0xFF},
{0xFF,0x01,0x01,0x6D,0x6D,0x01,0x93,0xFF},//B 
{0xFF,0x83,0x01,0x7D,0x7D,0x39,0xBB,0xFF},//C 
{0xFF,0x01,0x01,0x7D,0x7D,0x01,0x83,0xFF},//D 
{0xFF,0x01,0x01,0x6D,0x6D,0x6D,0x7D,0xFF},//E 
{0xFF,0x01,0x01,0xED,0xED,0xED,0xFD,0xFF},//F 
{0xFF,0x83,0x01,0x7D,0x5D,0x19,0x9B,0xFF},//G 
{0xFF,0x01,0x01,0xEF,0xEF,0x01,0x01,0xFF},//H 
{0xFF,0xFF,0x7D,0x01,0x01,0x7D,0xFF,0xFF},//I 
{0xFF,0x9F,0x9F,0x7D,0x01,0x81,0xFD,0xFF},//J 
{0xFF,0x01,0x01,0xC7,0x93,0x39,0x7D,0xFF},//K 
{0xFF,0x01,0x01,0x7F,0x7F,0x7F,0x7F,0xFF},//L 
{0xFF,0x01,0x01,0xF3,0xE7,0xF3,0x01,0x01},//M 
{0xFF,0x01,0x01,0xF3,0xE7,0xCF,0x01,0x01},//N
{0xFF,0x83,0x01,0x7D,0x7D,0x01,0x83,0xFF},//O
{0xFF,0x01,0x01,0xDD,0xDD,0xC1,0xE3,0xFF},//P
{0xFF,0xC3,0x81,0xBD,0x9D,0x01,0x43,0xFF},//Q  
{0xFF,0x01,0x01,0xCD,0x8D,0x21,0x73,0xFF},//R  
{0xFF,0xB3,0x21,0x6D,0x6D,0x09,0x9B,0xFF},//S  
{0xFF,0xF9,0xFD,0x01,0x01,0xFD,0xF9,0xFF},//T      
{0xFF,0x81,0x01,0x7F,0x7F,0x01,0x01,0xFF},//U  
{0xFF,0xC1,0x81,0x3F,0x3F,0x81,0xC1,0xFF},//V  
{0xFF,0x01,0x01,0x9F,0xCF,0x9F,0x01,0x01},//W  
{0xFF,0x39,0x11,0xC7,0xEF,0xC7,0x11,0x39},//X  
{0xFF,0xF1,0xE1,0x0F,0x0F,0xE1,0xF1,0xFF},//Y  
{0xFF,0x3D,0x1D,0x4D,0x65,0x71,0x79,0xFF},//Z
{0xFF,0x7F,0x77,0x01,0x01,0x7F,0x7F,0xFF},//1
{0xFF,0x3B,0x19,0x5D,0x6D,0x61,0x73,0xFF},//2
{0xFF,0xBB,0x39,0x6D,0x6D,0x01,0x93,0xFF},//3
{0xFF,0xCF,0xD7,0xDB,0x01,0x01,0xDF,0xFF},//4
{0xFF,0xB1,0x31,0x75,0x75,0x05,0x8D,0xFF},//5
{0xFF,0x83,0x01,0x6D,0x6D,0x09,0x9B,0xFF},//6
{0xFF,0xF9,0xF9,0x1D,0x05,0xE1,0xF9,0xFF},//7
{0xFF,0x93,0x01,0x6D,0x6D,0x01,0x93,0xFF},//8
{0xFF,0xB3,0x21,0x6D,0x6D,0x01,0x83,0xFF},//9
{0xFF,0x83,0x01,0x6D,0x75,0x01,0x83,0xFF},//0
{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},//space
 };

void output_h(uint8_t byte)
{
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, (GPIO_PinState) (byte&128));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, (GPIO_PinState) (byte&64));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, (GPIO_PinState) (byte&32));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, (GPIO_PinState) (byte&16));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, (GPIO_PinState) (byte&8));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (GPIO_PinState) (byte&4));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, (GPIO_PinState) (byte&2));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (GPIO_PinState) (byte&1));
}
void output_c(uint8_t byte)
{
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (GPIO_PinState) (byte&128));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (GPIO_PinState) (byte&64));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (GPIO_PinState) (byte&32));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (GPIO_PinState) (byte&16));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (GPIO_PinState) (byte&8));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, (GPIO_PinState) (byte&4));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, (GPIO_PinState) (byte&2));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, (GPIO_PinState) (byte&1));
}
void matrix_display(uint8_t in)
{
		for(uint8_t i=0; i<8; i++)
	{
			dich = 0x80>>i;
			output_c(dich);
			output_h(character[in][i]);
			HAL_Delay(1);
			output_c(0);
	}
}
void matrix_display_scroll(uint8_t in, uint8_t speed)
{
	uint8_t scroll = 0x80;
	for(uint8_t p=0; p<8; p++)
	{
	  scroll = 0x80 >> p;
		for(uint8_t k = 0; k < speed; k++)
		for(uint8_t i=0; i<8; i++)
	{
			dich = scroll>>i;
			output_c(dich);
			output_h(character[in][i]);
			HAL_Delay(1);
			output_c(0);
	}
}
}
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
	output_h(0);
  while (1)
  {		 
   matrix_display_scroll(5, 20);
	
  }
}


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
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7
                           PA8 PA9 PA10 PA11
                           PA12 PA13 PA14 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB12 PB13 PB14
                           PB15 PB3 PB4 PB5
                           PB6 PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/