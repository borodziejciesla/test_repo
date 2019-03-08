/*
 * interruptions.h
 *
 *  Created on: 06.01.2019
 *      Author: borodziej_ciesla
 */

#ifndef INTERRUPTIONS_H_
#define INTERRUPTIONS_H_

#include "stm32f1xx.h"

extern void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
extern void TIM2_IRQHandler(void);
extern void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
extern void USART2_IRQHandler(void);

#endif /* INTERRUPTIONS_H_ */
