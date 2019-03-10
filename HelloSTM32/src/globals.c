#include "globals.h"

static TIM_HandleTypeDef tim_global;
static TIM_OC_InitTypeDef oc_global;
static UART_HandleTypeDef uart;
static GPIO_InitTypeDef gpio;
static uint32_t last_counter = 0u;

TIM_HandleTypeDef* getGlobalTimer(void)
{
	return &tim_global;
}

TIM_OC_InitTypeDef* getGlobalOC(void)
{
	return &oc_global;
}

UART_HandleTypeDef* getUart(void)
{
	return &uart;
}

GPIO_InitTypeDef* getGPIO(void)
{
	return &gpio;
}

uint32_t getCounter(void)
{
	return last_counter;
}

void setCounter(uint32_t new_counter)
{
	last_counter = new_counter;
}

void updateCounter(uint32_t update_value)
{
	last_counter += update_value;
}

void incrementCounter(void)
{
	last_counter++;
}

