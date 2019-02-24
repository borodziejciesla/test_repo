/*
 * initPWMState.h
 *
 *  Created on: 06.01.2019
 *      Author: borodziej_ciesla
 */

#ifndef INITPWMSTATE_H_
#define INITPWMSTATE_H_

#include "PWM_STATE.h"
#include "stm32f1xx.h"

#define INITIAL_PWM_VALUE (0.3f)

extern PWM_STATE_T* getGlobalPWMState(void);
extern TIM_HandleTypeDef* getGlobalPWM(void);
extern TIM_HandleTypeDef* getGlobalTimer(void);
extern TIM_OC_InitTypeDef* getGlobalOC(void);
extern void initPWMState(PWM_STATE_T * const pwm_state,
		float max_pwm_value,
		float pwm_step_time,
		float pwm_step,
		uint32_t pwm_resolution,
		float pwm_frequency);
extern UART_HandleTypeDef* getUart(void);
extern GPIO_InitTypeDef* getGPIO(void);
extern const float* getSpeed(void);
extern void setSpeed(float new_speed);
extern TIM_HandleTypeDef* getTimer3(void);
extern uint32_t* getCounter(void);
extern void setCounter(uint32_t new);

#endif /* INITPWMSTATE_H_ */
