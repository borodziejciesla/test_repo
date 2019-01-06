/*
 * initPWMState.c
 *
 *  Created on: 06.01.2019
 *      Author: borodziej_ciesla
 */

#include "initPWMState.h"

static PWM_STATE_T pwm_state_global;

PWM_STATE_T* getGlobalPWMState(void)
{
	return &pwm_state_global;
}

void initPWMState(PWM_STATE_T * const pwm_state, float max_pwm_value, float pwm_step)
{
	pwm_state->is_started = false;
	pwm_state->is_initialized = false;
	pwm_state->max_pwm_value = max_pwm_value;
	pwm_state->current_pwm_value = 0.0f;
	pwm_state->is_max_velocity = false;
	pwm_state->pwm_step = pwm_step;
}
