#ifndef __MEMS_H
#define __MEMS_H

#include "main.h"

#define CTRL_REG1 			0x20
#define CTRL_REG2 			0x21
#define CTRL_REG3 			0x22
#define FF_WU_THS_1 		0x32
#define FF_WU_DURATION_1 	0x33
#define FF_WU_CFG_1 		0x30
#define STATUS_REG 			0x27


uint8_t LIS302DL_Check(void);
void LIS302DL_Config(void);
char  *Lis302DL_Output(void);

#endif

