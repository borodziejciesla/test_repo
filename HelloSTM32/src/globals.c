#include "globals.h"

static PWM_STATE_T pwm_state_global;
static TIM_HandleTypeDef tim_global;
static TIM_OC_InitTypeDef oc_global;
static TIM_HandleTypeDef pwm_global;
static TIM_HandleTypeDef timer_comparator;
static UART_HandleTypeDef uart;
static GPIO_InitTypeDef gpio;
static volatile float speed;
static uint64_t last_counter;

PWM_STATE_T* getGlobalPWMState(void)
{
	return &pwm_state_global;
}

TIM_HandleTypeDef* getGlobalTimer(void)
{
	return &tim_global;
}

TIM_OC_InitTypeDef* getGlobalOC(void)
{
	return &oc_global;
}

TIM_HandleTypeDef* getGlobalPWM(void)
{
	return &pwm_global;
}

UART_HandleTypeDef* getUart(void)
{
	return &uart;
}

GPIO_InitTypeDef* getGPIO(void)
{
	return &gpio;
}

const float* getSpeed(void)
{
	return &speed;
}

void setSpeed(float new_speed)
{
	speed = new_speed;
}

TIM_HandleTypeDef* getTimerComparator(void)
{
	return &timer_comparator;
}

uint64_t* getCounter(void)
{
	return &last_counter;
}

void setCounter(uint32_t new_counter)
{
	last_counter = (uint64_t)new_counter;
}

