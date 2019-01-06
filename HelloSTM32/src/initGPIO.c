/*
 * initGPIO.c
 *
 *  Created on: 06.01.2019
 *      Author: borodziej_cesla
 */

#include "initGPIO.h"

void initButton(GPIO_InitTypeDef * const gpio)
{
	gpio->Mode = GPIO_MODE_IT_RISING;
	gpio->Pull = GPIO_PULLUP;
	gpio->Pin = GPIO_PIN_13;
	HAL_GPIO_Init(GPIOC, gpio);
}

void initLED(GPIO_InitTypeDef * const gpio)
{
	gpio->Mode = GPIO_MODE_OUTPUT_PP;
	gpio->Pull = GPIO_NOPULL;
	gpio->Pin = GPIO_PIN_5;
	gpio->Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, gpio);
}

extern void initPWM(GPIO_InitTypeDef * const gpio,
		TIM_HandleTypeDef * const tim,
		float frequency_hz,
		uint16_t steps)
{
	gpio->Mode = GPIO_MODE_AF_PP;
	gpio->Pin = GPIO_PIN_7;
	gpio->Pull = GPIO_NOPULL;
	gpio->Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, gpio);

	float t_sys = (float)steps * 1.0f / ((float)SystemCoreClock);
	float t = 1.0f / frequency_hz;

	tim->Instance = TIM4;
	tim->Init.Period = (uint32_t)steps - 1;
	tim->Init.Prescaler = ((uint32_t)(t / t_sys)) - 1;
	tim->Init.ClockDivision = 0;
	tim->Init.CounterMode = TIM_COUNTERMODE_UP;
	tim->Init.RepetitionCounter = 0;
	tim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	HAL_TIM_PWM_Init(tim);

	TIM_OC_InitTypeDef oc;
	oc.OCMode = TIM_OCMODE_PWM1;
	oc.Pulse = 100;
	oc.OCPolarity = TIM_OCPOLARITY_HIGH;
	oc.OCNPolarity = TIM_OCNPOLARITY_LOW;
	oc.OCFastMode = TIM_OCFAST_ENABLE;
	oc.OCIdleState = TIM_OCIDLESTATE_SET;
	oc.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	HAL_TIM_PWM_ConfigChannel(tim, &oc, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(tim, TIM_CHANNEL_2);
}
