/*
 * initPWMState.h
 *
 *  Created on: 06.01.2019
 *      Author: borodziej_ciesla
 */

#ifndef INITPWMSTATE_H_
#define INITPWMSTATE_H_

#include "PWM_STATE.h"

extern PWM_STATE_T* getGlobalPWMState(void);
extern void initPWMState(PWM_STATE_T * const pwm_state, float max_pwm_value, float pwm_step);

#endif /* INITPWMSTATE_H_ */
