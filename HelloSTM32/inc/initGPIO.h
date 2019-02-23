/*
 * initGPIO.h
 *
 *  Created on: 06.01.2019
 *      Author: borodziej_cesla
 */

#ifndef INITGPIO_H_
#define INITGPIO_H_

#include "stm32f1xx.h"
#include "PWM_STATE.h"

extern void initButton(GPIO_InitTypeDef * const gpio);
extern void initLED(GPIO_InitTypeDef * const gpio);
extern void initPWM(GPIO_InitTypeDef * const gpio,
		TIM_HandleTypeDef * const tim,
		TIM_OC_InitTypeDef * const oc,
		const PWM_STATE_T * const pwm_state);
extern void initTimer(TIM_HandleTypeDef * const tim,
		float time);
extern void USARTInit(GPIO_InitTypeDef * const gpio,
		UART_HandleTypeDef * const uart);

#endif /* INITGPIO_H_ */
