#ifndef __LED_H
#define __LED_H
#include "main.h"
#define LED1 0x01
#define LED2 0x02
#define LED3 0x04
#define LED4 0x08
#define LED5 0x10
#define LED6 0x20
#define LED7 0x40
#define LED8 0x80
void LED_Init(void);
void LED1_ON(void);
void LED2_ON(void);
void LED3_ON(void);
void LED4_ON(void);
void LED5_ON(void);
void LED6_ON(void);
void LED7_ON(void);
void LED8_ON(void);
void LED1_OFF(void);
void LED2_OFF(void);
void LED3_OFF(void);
void LED4_OFF(void);
void LED5_OFF(void);
void LED6_OFF(void);
void LED7_OFF(void);
void LED8_OFF(void);
void LED1_TOG(void);
void LED2_TOG(void);
void LED3_TOG(void);
void LED4_TOG(void);
void LED5_TOG(void);
void LED6_TOG(void);
void LED7_TOG(void);
void LED8_TOG(void);
void LED_ALL_OFF(void);
void LED_ALL_ON(void);
void LED_ALL_TOG(void);
void LED_Light(uint8_t state);
#endif