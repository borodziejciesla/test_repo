/*
 * initGPIO.h
 *
 *  Created on: 06.01.2019
 *      Author: borodziej_cesla
 */

#ifndef INITGPIO_H_
#define INITGPIO_H_

#include "stm32f1xx.h"

extern void initButton(GPIO_InitTypeDef * const gpio);
extern void initLED(GPIO_InitTypeDef * const gpio);
extern void initPWM(GPIO_InitTypeDef * const gpio,
		TIM_HandleTypeDef * const tim,
		float frequency_hz,
		uint16_t steps);

#endif /* INITGPIO_H_ */
