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
	static float last_time = 0.0f;

	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	uint32_t t = HAL_GetTick();
	float time = (float)t;
	setSpeed(1.0f / ((time - last_time) / 1000.0f));
	sendMeasurement(getSpeed());
	last_time = time;
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

/*****************************************************************************************/
/*
 * Timer interruption
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	PWM_STATE_T * pwm_state = getGlobalPWMState();

	if ((pwm_state->is_started == false) && (pwm_state->is_initialized == false))
	{
		__HAL_TIM_SET_COMPARE(getGlobalPWM(), TIM_CHANNEL_2, 0.0f);
	}
	else if ((pwm_state->is_started == true) && (pwm_state->is_initialized == false))
	{
		__HAL_TIM_SET_COMPARE(getGlobalPWM(), TIM_CHANNEL_2, (float)(pwm_state->resolution));
		pwm_state->is_initialized = true;
	}
	else if ((pwm_state->is_started == true) && (pwm_state->is_initialized == true))
	{
		if (pwm_state->current_pwm_value < pwm_state->max_pwm_value)
		{
			pwm_state->current_pwm_value += pwm_state->pwm_step;
		}
		else
		{
			/* Do nothing */
		}

		float pwm_value = pwm_state->resolution * MIN(pwm_state->max_pwm_value, pwm_state->current_pwm_value);
		__HAL_TIM_SET_COMPARE(getGlobalPWM(), TIM_CHANNEL_2, pwm_value);
	}
	else
	{
		/* Do nothing */
	}
}

/*****************************************************************************************/
/* USART Transmit Interruption */
void USART2_IRQHandler(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_UART_IRQHandler(getUart());
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
}
