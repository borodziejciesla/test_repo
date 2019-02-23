#include "stm32f1xx.h"
#include "PWM_STATE.h"
#include "initPWMState.h"
#include "initGPIO.h"

#include <string.h>

/************************************************************************************************/
int main(void)
{
	SystemCoreClock = 8000000; // 8Mhz

	/* Initialize HAl and clock */
	HAL_Init();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_TIM4_CLK_ENABLE();
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();

	/* Initialize PWM structure */
	float pwm_max_value = 0.5f;
	float pwm_step_time = 3.0f;
	float pwm_step = 0.002f;
	uint32_t pwm_resolution = 1000;
	float pwm_frequency = 300.0f;

	initPWMState(getGlobalPWMState(), pwm_max_value, pwm_step_time, pwm_step, pwm_resolution, pwm_frequency);

	/* Initialize peripherals */
	initButton(getGPIO());
	initLED(getGPIO());
	initPWM(getGPIO(), getGlobalPWM(), getGlobalOC(), getGlobalPWMState());
	initTimer(getGlobalTimer(), getGlobalPWMState()->pwm_step_time);
	USARTInit(getGPIO(), getUart());

	getGPIO()->Mode = GPIO_MODE_IT_RISING;
	getGPIO()->Pull = GPIO_PULLDOWN;
	getGPIO()->Pin = GPIO_PIN_14;
	HAL_GPIO_Init(GPIOC, getGPIO());

	HAL_TIM_Base_Start_IT(getGlobalTimer());
	__HAL_TIM_ENABLE_IT(getGlobalTimer(), TIM_IT_CC1);

	/* Initialize interruptions */
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	HAL_NVIC_EnableIRQ(USART2_IRQn);

	volatile float f = 16.0f;

	while (1) {
	}
}
