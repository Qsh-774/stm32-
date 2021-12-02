#ifndef __MANAGER_H
#define __MANAGER_H
#include "main.h"
#define NO_EVENT 0
#define EVENT_KEY 1
#define EVENT_DEL 2
#define EVENT_OPEN 3
#define EVENT_TICK_2S 4
#define EVENT_TICK_200MS 5
#define EVENT_TICK_1S 6
#define EVENT_USART 7
#define EVENT_PWM 8
#define EVENT_ADD 9

#define KEY_NONE 0
#define KEY_RELEASE 1
#define KEY_SHORT 2
#define KEY_LONG_START 3
#define KEY_LONG_TICK 4
void TimerTickProcess(void);
void PushEvent(uint16_t event);
uint16_t PopEvent(void);
void LCDRefreshAll(char *in);
void LCDRefreshALine(char *in,uint16_t pos,uint16_t len);

void PushKey(int16_t k);
uint16_t PopKey(int16_t k);
int16_t KeyProcess(int16_t number,uint8_t state);

#endif
