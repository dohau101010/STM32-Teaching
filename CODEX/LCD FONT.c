#include "main.h"
uint8_t count;
void delay_us(uint32_t us) 
{
  for (uint32_t i = 0; i < us; ++i);
}
void output_4bit(char  byte)
{
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (GPIO_PinState) (byte&128));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, (GPIO_PinState) (byte&64));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, (GPIO_PinState) (byte&32));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, (GPIO_PinState) (byte&16));
}
void lcd_command(char data)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	HAL_Delay(1);
	output_4bit(data);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	output_4bit(data<<4);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
}
void lcd_data(char data)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	delay_us(500);
	output_4bit(data);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	output_4bit(data<<4);
	delay_us(500);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
}
void lcd_goto(uint8_t x, uint8_t y)
{
   char lcd_pos[] ={0x80, 0xc0, 0x94, 0xd4};
   lcd_command(lcd_pos[x] + y);
}
void lcdstring_display(char* string)
{
   while(*string)
	{
		lcd_data(*string);
		string++;
	}
}


void SystemClock_Config(void);
static void MX_GPIO_Init(void);
const uint8_t  lcd_ma_8doan[] = {
   0x07,0x0f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,  //doan f - 0
   0x1f,0x1f,0x1f,0x00,0x00,0x00,0x00,0x00,  //doan a - 1
   0x1c,0x1e,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,  //doan b - 2
   0x00,0x00,0x00,0x00,0x00,0x1f,0x1f,0x1f,  //doan d - 3
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x0f,0x07,  //doan e - 4
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1e,0x1c,  //doan c - 5      
   0x1f,0x1f,0x1f,0x00,0x00,0x00,0x1f,0x1f,  //doan g+d-6 
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f}; //doan i  -7  
const uint8_t   lcd_so_to[10][6] ={
                  0,1,2,4,3,5,    // so 0
                  1,2,32,3,7,3,   // so 1
                  6,6,2,4,3,3,    // so 2
                  6,6,2,3,3,5,    // so 3
                  7,3,7,32,32,7,  // so 4
                  7,6,6,3,3,5,    // so 5                               
                  0,6,6,4,3,5,    // so 6
                  1,1,7,32,32,7,  // so 7
                  0,6,2,4,3,5,    // so 8
                  0,6,2,3,3,5};   // so 9
void lcd2x3_display(uint8_t  so, uint8_t x,uint8_t y) 
{                        
   uint8_t i;
   lcd_goto(x,y);
   for(i=0;i<6;i++)
   {                                                           
      if(i==3) lcd_goto(x+1,y);
      lcd_data(lcd_so_to[so][i]);
   }                        
}
const uint8_t LCD_SO_X1[11][12] ={   //Font 3x4 
0,1,2,7,32,7,7,32,7,5,3,4,   //0
1,2,32,32,7,32,32,7,32,3,7,3,   //1
1,1,2,3,3,7,7,32,32,5,3,3,   //2
0,1,2,32,3,4,32,32,2,5,3,4,   //3
7,32,7,5,3,7,32,32,7,32,32,7,   //4
7,1,1,7,3,3,32,32,7,5,3,4,   //5
0,1,2,7,3,3,7,32,7,5,3,4,   //6
1,1,7,32,32,4,32,0,32,32,7,32,   //7
0,1,2,5,3,4,0,32,2,5,3,4,   //8
0,1,2,5,3,7,32,32,7,5,3,4,   //9
32,32,32,32,32,32,32,32,32,32,32,32};//XOA
void lcd3x4_display(uint8_t  so, uint8_t y) 
{                        
   uint8_t i;
   lcd_goto(0,y);
   for(i=0;i<12;i++)
   {                                                           
      if(i==3)      lcd_goto(1,y);
        else if(i==6) lcd_goto(2,y);
        else if(i==9) lcd_goto(3,y);
       lcd_data(LCD_SO_X1[so][i]);
   }                        
}
void lcd_setup(void)
{	
	HAL_Delay(30);	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
	
	lcd_command(0x28);
	lcd_command(0x0c);
	lcd_command(0x06);
	lcd_command(0x01);
	
	uint8_t i; 
  lcd_command(0x40); for(i=0;i<64;i++) 
  lcd_data(lcd_ma_8doan[i]); 

}
uint8_t count;
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
	lcd_setup();
  while (1)
  {		 
		
	 count++; count%=21;
	 
	 lcd3x4_display(count/10,0);
	 lcd3x4_display(count%10,3);
	 ;
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
