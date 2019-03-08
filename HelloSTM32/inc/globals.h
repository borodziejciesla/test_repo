#ifndef GLOBALS_H
#define GLOBALS_H

#include "PWM_STATE.h"
#include "stm32f1xx.h"

extern PWM_STATE_T* getGlobalPWMState(void);
extern TIM_HandleTypeDef* getGlobalPWM(void);
extern TIM_HandleTypeDef* getGlobalTimer(void);
extern TIM_OC_InitTypeDef* getGlobalOC(void);
extern UART_HandleTypeDef* getUart(void);
extern GPIO_InitTypeDef* getGPIO(void);
extern TIM_HandleTypeDef* getTimerComparator(void);
extern uint32_t getCounter(void);
extern void setCounter(uint32_t new_counter);
extern void updateCounter(uint32_t update_value);
extern void incrementCounter(void);

#endif
