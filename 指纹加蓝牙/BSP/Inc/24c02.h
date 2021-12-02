#ifndef __24C02_H
#define __24C02_H
#include "i2c.h"
uint8_t x24c02_read(uint8_t address);
void x24c02_write(unsigned char address,unsigned char info);
#endif