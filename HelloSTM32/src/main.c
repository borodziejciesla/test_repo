#include "stm32f1xx.h"
#include "PWM_STATE.h"
#include "initPWMState.h"
#include "initGPIO.h"

/* Global variables for file */
TIM_HandleTypeDef tim;
GPIO_InitTypeDef gpio;

/************************************************************************************************/
int main(void)
{
	SystemCoreClock = 8000000; // 8Mhz

	/* Initialize HAl and clock */
	HAL_Init();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_TIM4_CLK_ENABLE();

	/* Initialize PWM structure */
	initPWMState(getGlobalPWMState(), 0.5f, 0.02f);

	/* Initialize peripherals */
	initButton(&gpio);
	initLED(&gpio);
	initPWM(&gpio, &tim, 300.0f, 1000);

	/* Initialize interruptions */
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	while (1) {
	}
}
