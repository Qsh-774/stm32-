#ifndef __KEY_H__
#define __KEY_H__	 
#include "main.h"
 	 


//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)	 
 

#define KEY1  HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)//��ȡ����1
#define KEY2  HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)//��ȡ����2
#define KEY3  HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)//��ȡ����3
#define KEY4  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)//��ȡ����4



#define KEY1_PRES	1		//KEY1  
#define KEY2_PRES	2		//KEY2 
#define KEY3_PRES	3		//KEY3  
#define KEY4_PRES	4		//KEY4 


void KEY_Init(void);//IO��ʼ��
unsigned char KEY_Scan(unsigned char mode);  	//����ɨ�躯��	

#endif
