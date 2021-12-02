#include "LED.h"
uint8_t LED=0;
void LED_Init()
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
		
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
  /*Configure GPIO pin Output Level */		
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
																			|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);		
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);		
		
  /*Configure GPIO pins : PC8 PC9 PC10 PC11 PC12 PC13 PC14 PC15 */		
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
																		|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);	

  /*Configure GPIO pin : PD2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);		
}

/*
void LED1_ON()
{
			LED |= LED1;
			LED_Light(LED);
}
void LED1_OFF()
{
			LED &= 0xFF ^ LED1;
			LED_Light(LED);		
}
void LED2_ON()
{
			LED |= LED2;
			LED_Light(LED);
}
void LED2_OFF()
{
			LED &= 0xFF ^ LED2;
			LED_Light(LED);	
}
void LED3_ON()
{
			LED |= LED3;
			LED_Light(LED);
}
void LED3_OFF()
{
			LED &= 0xFF ^ LED3;
			LED_Light(LED);	
}
void LED4_ON()
{
			LED |= LED4;
			LED_Light(LED);	
}
void LED4_OFF()
{
			LED &= 0xFF ^ LED4;
			LED_Light(LED);	
}
void LED5_ON()
{
			LED |= LED5;
			LED_Light(LED);
}
void LED5_OFF()
{
			LED &= 0xFF ^ LED5;
			LED_Light(LED);	
}
void LED6_ON()
{
			LED |= LED6;
			LED_Light(LED);
}
void LED6_OFF()
{
			LED &= 0xFF ^ LED6;
			LED_Light(LED);	
}
void LED7_ON()
{
			LED |= LED7;
			LED_Light(LED);
}
void LED7_OFF()
{
			LED &= 0xFF ^ LED7;
			LED_Light(LED);	
}
void LED8_ON()
{
			LED |= LED8;
			LED_Light(LED);
}
void LED8_OFF()
{
			LED &= 0xFF ^ LED8;
			LED_Light(LED);	
}
void LED1_TOG()
{
			LED ^= LED1;
			LED_Light(LED);	
}
void LED2_TOG()
{
			LED ^= LED2;
			LED_Light(LED);	
}
void LED3_TOG()
{
			LED ^= LED3;
			LED_Light(LED);	
}
void LED4_TOG()
{
			LED ^= LED4;
			LED_Light(LED);	
}
void LED5_TOG()
{
			LED ^= LED5;
			LED_Light(LED);	
}
void LED6_TOG()
{
			LED ^= LED6;
			LED_Light(LED);	
}
void LED7_TOG()
{
			LED ^= LED7;
			LED_Light(LED);	
}
void LED8_TOG()
{
			LED ^= LED8;
			LED_Light(LED);	
}
*/
void LED_ALL_OFF()
{
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
																			|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);		
}
void LED_ALL_ON()
{
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
																			|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);		
}
void LED_ALL_TOG()
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
																			|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);	
}
void LED_Light(uint8_t state)//0为灭 1为亮  二进制的state表示8个灯的状态
{
	LED = state;
	uint32_t q[8]={GPIO_PIN_8,GPIO_PIN_9,GPIO_PIN_10,GPIO_PIN_11
																			,GPIO_PIN_12,GPIO_PIN_13,GPIO_PIN_14,GPIO_PIN_15};
	for(uint8_t i=0;i<8;i++)
			HAL_GPIO_WritePin(GPIOC, q[i], !(state&(1<<i)));																	
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);		
}