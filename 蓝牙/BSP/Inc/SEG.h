#ifndef __SEG_H
#define __SEG_H
#include "main.h"

#define RCLK_PIN    GPIO_PIN_2
#define RCLK_PORT   GPIOA
#define SER_PIN   	GPIO_PIN_1
#define SER_PORT    GPIOA
#define SCK_PIN   	GPIO_PIN_3
#define SCK_PORT    GPIOA


#define RCLK_H			HAL_GPIO_WritePin(RCLK_PORT, RCLK_PIN, GPIO_PIN_SET)
#define RCLK_L			HAL_GPIO_WritePin(RCLK_PORT, RCLK_PIN, GPIO_PIN_RESET)

#define SER_H				HAL_GPIO_WritePin(SER_PORT, SER_PIN, GPIO_PIN_SET)
#define SER_L				HAL_GPIO_WritePin(SER_PORT, SER_PIN, GPIO_PIN_RESET)

#define SCK_H				HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_SET)
#define SCK_L				HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET)

void SEG_Init(void);
void SEG_DisplayValue(uint8_t Bit1, uint8_t Bit2, uint8_t Bit3);

#endif
