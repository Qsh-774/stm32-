#include "manager.h"
//#include "lcd.h"
//#include "key.h"
uint16_t EventList[10]={0};
uint16_t EventListED=0;

void PushEvent(uint16_t event)
{
	if(EventListED<10)
	{
		EventList[EventListED]=event;
		EventListED++;
	}
}

uint16_t PopEvent(void)
{
	if(EventListED>0)
	{
		EventListED--;
		return EventList[EventListED];
	}
	return NO_EVENT;
	
}
//int16_t KeyTime[5]={0};
//int16_t KeyState[4]={0};
//int16_t KeyNumList[10];
//int16_t KeyStateList[10];
//uint16_t KeyListWP=0;
//uint16_t KeyListLock=0;



//uint16_t PopKey(int16_t k)
//{

//	KeyTime[1]=0;
//	KeyTime[2]=0;
//	KeyTime[3]=0;	
//	KeyTime[4]=0;
//	
//	key=k;
//	while(KeyListWP>0)
//	{

//		KeyListWP--;
//	}

//	return 0;
//}


void TimerTickProcess(void)//1ms  
{
//	static uint32_t ticks=0;
//	ticks++;
//	static uint8_t KEY=0,KEY_PRE=0;
//	if(ticks%20==0)//10ms 相当于去抖
//	{

//			KEY=KEY_Scan(1);			
//		if(KEY && KeyTime[KEY]<10) KeyTime[KEY]++,KEY_PRE=KEY;
//		if(!KEY && KeyTime[KEY_PRE]>=2)PopKey(KEY_PRE),PushEvent(EVENT_KEY);//短按键事件
//	}
//	if(ticks%2000==0)
//	{
//		PushEvent(EVENT_TICK_2S);
//	}
//	if(ticks%200==0)
//	{
//		PushEvent(EVENT_LED);
//	}
//	if(ticks%1000==0)
//	{
//		PushEvent(EVENT_TICK_1S);
//	}
}
//void LCDRefreshAll(char *in)//相当于 对整个屏刷新一遍
//{
//	uint_fast16_t i,j;
//	for(j=0;j<10;j++)
//	{
//		for(i=0;i<20;i++)
//		{
//			if(*in==0)
//			{
//				LCD_DisplayChar(24*j,319-16*i,' ');
//			}else
//				LCD_DisplayChar(24*j,319-16*i,*in);
//			in++;
//		}	
//	}
//}
//void LCDRefreshALine(char *in,uint16_t pos,uint16_t len)//刷新某一行任意一列开始 POS是位置
//{
//	uint16_t line,column;
//	line=pos/20;column=pos%20;
//	uint_fast16_t i;
//	//in+=line*20+column;
//	in+=pos;
//	len+=column;
//	if(len>=20)len=19;//只输出一行
//	for(i=column;i<column+len;i++)
//	{
//		if(*in==0)
//		{
//			LCD_DisplayChar(Line1*line,319-16*i,' ');
//			return;		
//		}
//		LCD_DisplayChar(Line1*line,319-16*i,*in);
//		in++;
//	}		
//}

