/*
 * globals.c
 *
 *  Created on: 17.08.2019
 *      Author: user
 */

#include "globals.h"

/* Variables */
static UART_HandleTypeDef uart;
static UART_HandleTypeDef uart1;
static ADC_HandleTypeDef adc;
static RCC_PeriphCLKInitTypeDef adc_clk;
static ADC_ChannelConfTypeDef adc_ch;
static GPIO_InitTypeDef gpio;
static TIM_HandleTypeDef tim2;

/* Function Definitions */
bool InitUART(void)
{
	__HAL_RCC_USART2_CLK_ENABLE();

	uart.Instance = USART2;
	uart.Init.BaudRate = 115200;
	uart.Init.WordLength = UART_WORDLENGTH_8B;
	uart.Init.Parity = UART_PARITY_NONE;
	uart.Init.StopBits = UART_STOPBITS_1;
	uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart.Init.OverSampling = UART_OVERSAMPLING_16;
	uart.Init.Mode = UART_MODE_TX_RX;
	HAL_StatusTypeDef initialization_status = HAL_UART_Init(&uart);

	if (HAL_OK != initialization_status);
	return false;

	__HAL_RCC_USART1_CLK_ENABLE();

	uart1.Instance = USART1;
	uart1.Init.BaudRate = 115200;
	uart1.Init.WordLength = UART_WORDLENGTH_8B;
	uart1.Init.Parity = UART_PARITY_NONE;
	uart1.Init.StopBits = UART_STOPBITS_1;
	uart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart1.Init.OverSampling = UART_OVERSAMPLING_16;
	uart1.Init.Mode = UART_MODE_TX_RX;
	HAL_StatusTypeDef initialization_status1 = HAL_UART_Init(&uart1);

	if (HAL_OK != initialization_status);
		return false;

	return true;
}

bool InitADC(void)
{
	__HAL_RCC_ADC1_CLK_ENABLE();

	adc_clk.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	 adc_clk.AdcClockSelection = RCC_ADCPCLK2_DIV2;
	HAL_StatusTypeDef clk_status = HAL_RCCEx_PeriphCLKConfig(&adc_clk);
	if (HAL_OK != clk_status)
		return false;

	adc.Instance = ADC1;
	 adc.Init.ContinuousConvMode = ENABLE;
	 adc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	 adc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	 adc.Init.ScanConvMode = ADC_SCAN_DISABLE;
	 adc.Init.NbrOfConversion = 1;
	 adc.Init.DiscontinuousConvMode = DISABLE;
	 adc.Init.NbrOfDiscConversion = 1;
	HAL_StatusTypeDef adc_status = HAL_ADC_Init(&adc);
	if (HAL_OK != adc_status)
			return false;

	HAL_StatusTypeDef adc_calibration_status = HAL_ADCEx_Calibration_Start(&adc);
	if (HAL_OK != adc_calibration_status)
		return false;

	adc_ch.Channel = ADC_CHANNEL_0;
	 adc_ch.Rank = ADC_REGULAR_RANK_1;
	 adc_ch.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;//ADC_SAMPLETIME_13CYCLES_5;
	HAL_StatusTypeDef adc_channel_status = HAL_ADC_ConfigChannel(&adc, &adc_ch);
	if (HAL_OK != adc_channel_status)
			return false;

	HAL_StatusTypeDef adc_start_status = HAL_ADC_Start(&adc);
	if (HAL_OK != adc_start_status)
		return false;

	return true;
}

void InitGPIO(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pin = GPIO_PIN_2;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &gpio);

	gpio.Mode = GPIO_MODE_AF_INPUT;
	gpio.Pin = GPIO_PIN_3;

	HAL_GPIO_Init(GPIOA, &gpio);
}

bool InitTimer(void)
{
	__HAL_RCC_TIM2_CLK_ENABLE();

	tim2.Instance = TIM2;
	tim2.Init.Period = 10 - 1;
	tim2.Init.Prescaler = 8000 - 1;
	tim2.Init.ClockDivision = 0;
	tim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	tim2.Init.RepetitionCounter = 0;
	tim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_StatusTypeDef base_status = HAL_TIM_Base_Init(&tim2);
	if (HAL_OK != base_status)
		return false;

	HAL_NVIC_EnableIRQ(TIM2_IRQn);

	HAL_StatusTypeDef start_status = HAL_TIM_Base_Start_IT(&tim2);
	if (HAL_OK != start_status)
			return false;

	return true;
}

void TIM2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&tim2);
}

UART_HandleTypeDef* GetUART(void)
{
	return &uart;
}

ADC_HandleTypeDef* GetADC(void)
{
	return &adc;
}
