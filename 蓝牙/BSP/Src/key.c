#include "key.h"


 	    
void KEY_Init(void)
{
/*	
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  // GPIO Ports Clock Enable 
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();	
	  //Configure GPIO pin : PA0 
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  //Configure GPIO pins : PB0 PB1 PB2 
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);*/
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值：

//
//长按按键 ：    1s 内 检测到同一按键且不发生改变
unsigned char KEY_Scan(unsigned char mode)
{	 
	static unsigned char key_up=1;
	if(mode)key_up=1;  	  
	if(key_up && (KEY1 == GPIO_PIN_RESET || KEY2==GPIO_PIN_RESET || KEY3==GPIO_PIN_RESET || KEY4==GPIO_PIN_RESET))
	{
		key_up=0;
		if(KEY1==GPIO_PIN_RESET)return KEY1_PRES;
		if(KEY2==GPIO_PIN_RESET)return KEY2_PRES;	
    if(KEY3==GPIO_PIN_RESET)return KEY3_PRES;
    if(KEY4==GPIO_PIN_RESET)return KEY4_PRES;		
	}
	else if(KEY1==GPIO_PIN_SET && KEY2==GPIO_PIN_SET && KEY3==GPIO_PIN_SET && KEY4==GPIO_PIN_SET)key_up=1; 	     
	return 0;
}
