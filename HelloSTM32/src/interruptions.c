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

#define BUTTON			GPIO_PIN_13
#define COMPARATOR 		GPIO_PIN_15

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/*****************************************************************************************/
/*
 * Button interruption
 */
void buttonInterruption(void)
{
	static float last_time = 0.0f;

	/* Signalizes interruption */
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	PWM_STATE_T * pwm_state = getGlobalPWMState();

	if (pwm_state->is_started == false)
	{
		pwm_state->is_started = true;
	}
	else
	{
		/* stop PWM */
		pwm_state->is_started = false;
		pwm_state->is_initialized = false;
		pwm_state->current_pwm_value = INITIAL_PWM_VALUE;
		__HAL_TIM_SET_COMPARE(getGlobalPWM(), TIM_CHANNEL_2, 0.0f);
	}

	uint32_t t = HAL_GetTick();
	float time = (float)t;
	setSpeed(1.0f / ((time - last_time) / 1000.0f));
	sendMeasurement(getSpeed());

	last_time = time;
}

/*
 * Comparator interruption
 */
void comparatorInterruption(void)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	uint32_t timer_counter = *getCounter() + getTimer3()->Instance->CNT;
	getTimer3()->Instance->CNT = 0u;
	setCounter(0u);

	float speed = (float)(1.0f / (timer_counter / 0.000001f));
	setSpeed(speed);
}

/*****************************************************************************************/
/* EXTI */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == BUTTON)
	{
		buttonInterruption();
	}
	else if (GPIO_Pin == COMPARATOR)
	{
		comparatorInterruption();
	}
	else
	{
		/* Do nothing */
	}
}

void TIM2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(getGlobalTimer());
}

void TIM3_IRQHandler(void)
{
	setCounter(getTimer3()->Instance->CNT);
	HAL_TIM_IRQHandler(getTimer3());
}

/*****************************************************************************************/
/*
 * Timer interruption
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	sendMeasurement(getSpeed());
}

/*****************************************************************************************/
/* USART Transmit Interruption */
void USART2_IRQHandler(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_UART_IRQHandler(getUart());
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
}
