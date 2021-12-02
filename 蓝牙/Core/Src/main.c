/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "manager.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t UartRe,UartRe_Buf[255],UARTReED=0;
uint8_t ID[100][5],ID_num=0;
uint8_t Open=0,Flag=0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void MainEventHandler(uint16_t event)
{
		char Del[30]="",Dell[30]="";
		char Car[5]="",flag=0;
	switch(event)
	{
		case EVENT_DEL:
			for(uint8_t i=0;i<100;++i)
			if(!strcmp((char *)ID[i],(char *)UartRe_Buf))
			{
					strcpy((char *)ID[i],"");
					flag=1;
					ID_num--;
					break;				
			}			
			if(!flag) 		
					HAL_UART_Transmit_IT(&huart1,(uint8_t*)"DEL unsuccessful!",16);
			else
					HAL_UART_Transmit_IT(&huart1,(uint8_t*)"DEL succesful!",14);			
		break;
			
		case EVENT_ADD:
			
			for(uint8_t i=0;i<100;++i)
			{
				if(!strcmp((char *)ID[i],""))
				{
					strcpy((char *)ID[i],(char *)UartRe_Buf);
					flag=1;
					ID_num++;
					break;				
				}
				if(!strcmp((char *)ID[i],(char *)UartRe_Buf))
				{
					flag=1;
					break;
				}
			}			
			if(!flag) 		
					HAL_UART_Transmit_IT(&huart1,(uint8_t*)"ADD unsuccessful!",16);
			else
					HAL_UART_Transmit_IT(&huart1,(uint8_t*)"ADD succesful!",14);				
		break;
			
		case EVENT_OPEN:
			for(uint8_t i=0;i<100;++i)
			if(strcmp((char *)ID[i],"") && !strcmp((char *)ID[i],(char *)UartRe_Buf))
			{

				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  //HAL_Delay(1000);
	
					htim2.Instance->CCR1=55;
					HAL_Delay(1500);
					htim2.Instance->CCR1=230;   
					HAL_Delay(1500);
				
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);								
//					HAL_UART_Transmit_IT(&huart1, (uint8_t *)"AT+DISC",7);				
					flag=1;
					break;				
			}
			if(!flag) 		
					HAL_UART_Transmit_IT(&huart1,(uint8_t*)"Your ID is Error!",17);
			else
					HAL_UART_Transmit_IT(&huart1,(uint8_t*)"Welcom!",7);				  
		break;		
			
		case EVENT_USART:

				if(!strcmp((char *)UartRe_Buf,"Open") && Flag)
				{
					Flag=0;					
					HAL_UART_Transmit_IT(&huart1,(uint8_t*)"Please Enter your ID",20);
					HAL_Delay(200);
					PushEvent(EVENT_OPEN);
					break;
				}		

			
				if(!strcmp((char *)UartRe_Buf,"Addn") && Flag)
				{
					Flag=0;					
					HAL_UART_Transmit_IT(&huart1,(uint8_t*)"Please Enter your ID",20);
					HAL_Delay(200);					
					PushEvent(EVENT_ADD);
					break;					
				}
				
				if(!strcmp((char *)UartRe_Buf,"Delt") && Flag)
				{
					Flag=0;
					HAL_UART_Transmit_IT(&huart1,(uint8_t*)"Please Enter your ID",20);
					HAL_Delay(200);					
					PushEvent(EVENT_DEL);
					break;					
				}
				
				if(!strcmp((char *)UartRe_Buf,"0113"))
				{
					Flag=1;
					HAL_UART_Transmit_IT(&huart1,(uint8_t*)"Welcome Admin!",14);
					break;					
				}	
				HAL_UART_Transmit_IT(&huart1,(uint8_t*)"PIN Error!",10);	
		break;
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
	UNUSED(huart1);
	UartRe_Buf[UARTReED]=UartRe;
	if(UARTReED<4)UARTReED++;
	if(UartRe=='R')
	{
		UARTReED=0;	
	}
	if(UARTReED == 4)
	{
		PushEvent(EVENT_USART);		
		UARTReED=0;
	}
	HAL_UART_Receive_IT(&huart1,(uint8_t*)&UartRe,1);
	
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
  MX_TIM2_Init();
  MX_USART1_UART_Init();
//  /* USER CODE BEGIN 2 */

	HAL_UART_Receive_IT(&huart1, (uint8_t*)&UartRe, 1);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		uint8_t event = PopEvent();

		/*事件处理*/
		if(event) MainEventHandler(event);		
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */
  //64/ 640 /2000 = 50HZ = 20ms   舵机 0.5 - 2.5ms
  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 640-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 2000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
	//250关   60 开
  sConfigOC.Pulse = 250;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
