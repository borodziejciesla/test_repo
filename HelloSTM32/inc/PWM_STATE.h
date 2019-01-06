/*
 * PWM_STATE.h
 *
 *  Created on: 06.01.2019
 *      Author: borodziej_ciesla
 */

#ifndef PWM_STATE_H_
#define PWM_STATE_H_

#include "stdbool.h"

/* Structure for control PWM state */
typedef struct PWM_STATE
{
	bool is_started;			/* [-] true if ESC initialization procedure was started */
	bool is_initialized;		/* [-] true if ESC initialization procedure is finished */
	float max_pwm_value;		/* [-] maximum value of PWM  */
	float current_pwm_value;	/* [-] current PWM value */
	bool is_max_velocity;		/* [-] true if current_pwm_value reached max_pwm_value */
	float pwm_step;				/* [-] defines PWm value increment step */
} PWM_STATE_T;

#endif /* PWM_STATE_H_ */
