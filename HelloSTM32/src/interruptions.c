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

#define MIN(a, b) (((a) < (b)) ? (a) : (b))


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_13)
	{
	    /* Signalizes interruption */
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

		PWM_STATE_T * pwm_state = getGlobalPWMState();

		if (pwm_state->is_started == false)
		{
			TIM_HandleTypeDef * tim = getGlobalTimer();
			initTimer(tim, 3.0f);
			HAL_TIM_Base_Start_IT(tim);
			__HAL_TIM_ENABLE_IT(tim, TIM_IT_CC1);
			__HAL_TIM_SET_COMPARE(getGlobalPWM(), TIM_CHANNEL_2, (float)(pwm_state->max_pwm_value * pwm_state->resolution));

			pwm_state->is_started = true;
		}
		else
		{
			/* stop PWM */
			pwm_state->is_started = false;
			pwm_state->is_initialized = false;
			pwm_state->current_pwm_value = 0.0f;
			__HAL_TIM_SET_COMPARE(getGlobalPWM(), TIM_CHANNEL_2, 0.0f);
		}
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

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	PWM_STATE_T * pwm_state = getGlobalPWMState();

	if ((pwm_state->is_started == true) && (pwm_state->is_initialized == false))
	{
		pwm_state->is_initialized = true;
		__HAL_TIM_SET_COMPARE(getGlobalPWM(), TIM_CHANNEL_2, 0.0f);
	}
	else if ((pwm_state->is_started == true) && (pwm_state->is_initialized == true))
	{
		TIM_HandleTypeDef * tim = getGlobalTimer();
		initTimer(tim, pwm_state->pwm_step_time);

		if (pwm_state->current_pwm_value < pwm_state->max_pwm_value)
		{
			pwm_state->current_pwm_value += pwm_state->pwm_step;
		}
		else
		{
			/* Do nothing */
		}

		float pwm_value = pwm_state->resolution * MIN(pwm_state->max_pwm_value, pwm_state->current_pwm_value);

		__HAL_TIM_SET_COMPARE(getGlobalPWM(), TIM_CHANNEL_2, (float)(pwm_value * pwm_state->resolution));
	}
	else
	{
		/* Do nothing */
	}

	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_RESET)
	 {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	 }
	 else
	 {
		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	 }
}
