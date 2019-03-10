/*
 * interruptions.c
 *
 *  Created on: 06.01.2019
 *      Author: borodziej_ciesla
 */

#include "stm32f1xx.h"
#include "interruptions.h"
#include "PWM_STATE.h"
#include "initPWMState.h"
#include "initGPIO.h"
#include "uartFunctions.h"
#include "globals.h"

#define COMPARATOR 		GPIO_PIN_15

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/*****************************************************************************************/
/*
 * Set interrupt
 */
void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(getGlobalTimer());
}

/*****************************************************************************************/
/*
 * Comparator interruption
 */
void comparatorInterruption(void)
{
	incrementCounter();
}

/*****************************************************************************************/
/* EXTI */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == COMPARATOR)
	{
		comparatorInterruption();
	}
	else
	{
		/* Do nothing */
	}
}

/*****************************************************************************************/
/*
 * Timer interruption
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	auto uint32_t tmp = getCounter();

	sendMeasurement(tmp);
	setCounter(0u);
}

/*****************************************************************************************/
/* USART Transmit Interruption */
void USART2_IRQHandler(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_UART_IRQHandler(getUart());
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
}
