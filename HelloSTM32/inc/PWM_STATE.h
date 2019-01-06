/*
 * PWM_STATE.h
 *
 *  Created on: 06.01.2019
 *      Author: borodziej_ciesla
 */

#ifndef PWM_STATE_H_
#define PWM_STATE_H_

#include "stdbool.h"
#include "stdint.h"

/* Structure for control PWM state */
typedef struct PWM_STATE
{
	bool is_started;			/* [-] true if ESC initialization procedure was started */
	bool is_initialized;		/* [-] true if ESC initialization procedure is finished */
	float max_pwm_value;		/* [-] maximum value of PWM  */
	float current_pwm_value;	/* [-] current PWM value */
	bool is_max_velocity;		/* [-] true if current_pwm_value reached max_pwm_value */
	float pwm_step;				/* [-] defines PWM value increment step */
	float pwm_step_time;		/* [-] defines time of  PWM value increment step */
	uint32_t resolution;		/* [-] number of steps in PWM cycle */
	float frequency;			/* [Hz] PWM frequency */
} PWM_STATE_T;

#endif /* PWM_STATE_H_ */
