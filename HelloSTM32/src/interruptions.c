/*
 * interruptions.c
 *
 *  Created on: 06.01.2019
 *      Author: borodziej_ciesla
 */

#include "stm32f1xx.h"
#include "interruptions.h"
#include "PWM_STATE.h"
#include "initPWMState.h"
#include "initGPIO.h"
#include "uartFunctions.h"
#include "globals.h"

#define COMPARATOR 		GPIO_PIN_15

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/*****************************************************************************************/
/*
 * Set interrupt
 */
void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(getGlobalTimer());
}

/*****************************************************************************************/
/*
 * Comparator interruption
 */
void comparatorInterruption(void)
{
	incrementCounter();
}

/*****************************************************************************************/
/* EXTI */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == COMPARATOR)
		comparatorInterruption();
}

/*****************************************************************************************/
/*
 * Timer interruption
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static unsigned char ADSwrite[6];
	static const char ADS1015_ADDRESS = 0x48;

	ADSwrite[0] = 0x01;
	ADSwrite[1] = 0xC1;
	ADSwrite[2] = 0x83;

	HAL_I2C_Master_Transmit(getI2C(), ADS1015_ADDRESS << 1, ADSwrite, 3, 100);
	ADSwrite[0] = 0x00;
	HAL_I2C_Master_Transmit(getI2C(), ADS1015_ADDRESS << 1, ADSwrite, 1, 100);
	HAL_Delay(20);
	HAL_I2C_Master_Receive(getI2C(), ADS1015_ADDRESS << 1, ADSwrite, 2, 100);
	int16_t reading = (ADSwrite[0] << 8 | ADSwrite[1]);
	if(reading < 0 )
		reading = 0;
	setVoltage(reading * getVoltageStep());
}

/*****************************************************************************************/
/* USART Transmit Interruption */
void USART2_IRQHandler(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_UART_IRQHandler(getUart());
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
}
