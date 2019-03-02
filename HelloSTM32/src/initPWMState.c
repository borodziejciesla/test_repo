/*
 * initPWMState.c
 *
 *  Created on: 06.01.2019
 *      Author: borodziej_ciesla
 */

#include "initPWMState.h"

void initPWMState(PWM_STATE_T * const pwm_state,
		float max_pwm_value,
		float pwm_step_time,
		float pwm_step,
		uint32_t pwm_resolution,
		float pwm_frequency)
{
	pwm_state->is_started = false;
	pwm_state->is_initialized = false;
	pwm_state->max_pwm_value = max_pwm_value;
	pwm_state->current_pwm_value = INITIAL_PWM_VALUE;
	pwm_state->is_max_velocity = false;
	pwm_state->pwm_step = pwm_step;
	pwm_state->resolution = pwm_resolution;
	pwm_state->frequency = pwm_frequency;
	pwm_state->pwm_step_time = pwm_step_time;
}
