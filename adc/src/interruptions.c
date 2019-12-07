/*
 * interruptions.c
 *
 *  Created on: 18.08.2019
 *      Author: user
 */

#include "interruptions.h"

#include <math.h>

#include "globals.h"
#include "message.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static const float scaling_factor = 3.3F / 4096.0F;	// [V]
	static const float maximum_range = 5.0F;			// [m]
	static const float maximum_output_voltage = 10.0F;	// [V]
	static const float height = 0.54F;					// [m]
	static const float offset = 0.268F;					// [m]

	uint32_t raw_value = HAL_ADC_GetValue(GetADC());
	const float voltage = ((float)raw_value) * scaling_factor;
	const float delta = (voltage / maximum_output_voltage) * maximum_range - offset;
	const float angle = atan2(delta, height);

	SetMessageValue(angle);

	HAL_UART_Transmit(GetUART(), (uint8_t*)GetMessage(), sizeof(Message), 1000);
}
