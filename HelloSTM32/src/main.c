#include <string.h>

#include "stm32f1xx.h"
#include "initGPIO.h"
#include "globals.h"

/************************************************************************************************/
int main(void)
{
	SystemCoreClock = 8000000; // 8Mhz

	float measurement_step_time = 0.005f;

	/* Initialize HAl and clock */
	HAL_Init();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_ADC1_CLK_ENABLE();

	/* Initialize peripherals */
	initLED(getGPIO());
	initTimerComparator(getGlobalTimer(), measurement_step_time);
	USARTInit(getGPIO(), getUart());
	initComparatorInput(getGPIO());\
	initADC(getADC());

	/* Initialize interruptions */
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	HAL_NVIC_EnableIRQ(USART2_IRQn);

	/* Start modules */
	HAL_TIM_Base_Start_IT(getGlobalTimer());
	HAL_ADC_Start(getADC());

	while (1) {}
}
