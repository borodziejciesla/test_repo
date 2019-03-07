/*
 * initGPIO.c
 *
 *  Created on: 06.01.2019
 *      Author: borodziej_cesla
 */

#include "initGPIO.h"

#include "stm32f1xx.h"

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

void initPWM(GPIO_InitTypeDef * const gpio,
		TIM_HandleTypeDef * const tim,
		TIM_OC_InitTypeDef * const oc,
		const PWM_STATE_T * const pwm_state)
{
	gpio->Mode = GPIO_MODE_AF_PP;
	gpio->Pin = GPIO_PIN_7;
	gpio->Pull = GPIO_NOPULL;
	gpio->Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, gpio);

	float t_sys = (float)pwm_state->resolution * 1.0f / ((float)SystemCoreClock);
	float t = 1.0f / pwm_state->frequency;

	tim->Instance = TIM4;
	tim->Init.Period = pwm_state->resolution - 1u;
	tim->Init.Prescaler = ((uint32_t)(t / t_sys)) - 1u;
	tim->Init.ClockDivision = 0u;
	tim->Init.CounterMode = TIM_COUNTERMODE_UP;
	tim->Init.RepetitionCounter = 0u;
	tim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	HAL_TIM_PWM_Init(tim);

	oc->OCMode = TIM_OCMODE_PWM1;
	oc->Pulse = 0u;
	oc->OCPolarity = TIM_OCPOLARITY_HIGH;
	oc->OCNPolarity = TIM_OCNPOLARITY_LOW;
	oc->OCFastMode = TIM_OCFAST_ENABLE;
	oc->OCIdleState = TIM_OCIDLESTATE_SET;
	oc->OCNIdleState = TIM_OCNIDLESTATE_RESET;
	HAL_TIM_PWM_ConfigChannel(tim, oc, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(tim, TIM_CHANNEL_2);
}

void initTimer(TIM_HandleTypeDef * const tim, float time)
{
	tim->Instance = TIM2;
	tim->Init.Period = ((uint32_t)(time / 0.001f)) - 1u;
	tim->Init.Prescaler = 8000u - 1u;
	tim->Init.ClockDivision = 0u;
	tim->Init.CounterMode = TIM_COUNTERMODE_UP;
	tim->Init.RepetitionCounter = 0u;
	tim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(tim);
}

void USARTInit(GPIO_InitTypeDef * const gpio, UART_HandleTypeDef * const uart)
{
	/* Configure pins */
	gpio->Mode = GPIO_MODE_AF_PP;
	gpio->Pin = GPIO_PIN_2;
	gpio->Pull = GPIO_NOPULL;
	gpio->Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, gpio);

	gpio->Mode = GPIO_MODE_AF_INPUT;
	gpio->Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, gpio);

	/* Configure USART */
	uart->Instance = USART2;
	uart->Init.BaudRate = 115200u;
	uart->Init.WordLength = UART_WORDLENGTH_8B;
	uart->Init.Parity = UART_PARITY_NONE;
	uart->Init.StopBits = UART_STOPBITS_1;
	uart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart->Init.OverSampling = UART_OVERSAMPLING_16;
	uart->Init.Mode = UART_MODE_TX_RX;
	HAL_UART_Init(uart);
}

void initComparatorInput(GPIO_InitTypeDef * const gpio)
{
	gpio->Mode = GPIO_MODE_IT_RISING_FALLING;
	gpio->Pull = GPIO_PULLUP;
	gpio->Pin = GPIO_PIN_15;
	HAL_GPIO_Init(GPIOB, gpio);
}

void initTimerComparator(TIM_HandleTypeDef * const timer,
		float period)
{
	timer->Instance = TIM3;
	timer->Init.Period = 100000u - 1u;
	timer->Init.Prescaler = 80u - 1u;
	timer->Init.ClockDivision = 0u;
	timer->Init.CounterMode = TIM_COUNTERMODE_UP;
	timer->Init.RepetitionCounter = 0u;
	timer->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(timer);
}
