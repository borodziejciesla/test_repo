/*
 * globals.h
 *
 *  Created on: 17.08.2019
 *      Author: user
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdbool.h>

#include "stm32f1xx.h"

extern bool InitUART(void);
extern bool InitADC(void);
extern void InitGPIO(void);

extern UART_HandleTypeDef* GetUART(void);
extern ADC_HandleTypeDef* GetADC(void);

#endif /* GLOBALS_H_ */
