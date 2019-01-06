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


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_13)
	{
	    /* Signalizes interruption */
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

		PWM_STATE_T * pwm_state = getGlobalPWMState();

		if (pwm_state->is_started == false)
		{
			//start initialization
			pwm_state->is_started = true;
		}
		else
		{
			/* stop PWM */
			pwm_state->is_started = false;
		}
	}
	else
	{
		/* Do nothing */
	}
}
