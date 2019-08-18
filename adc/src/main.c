#include <math.h>

#include "stm32f1xx.h"

#include "globals.h"
#include "message.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static const float scaling_factor = 3.3F / 4096.0F;	// [V]
	static const float maximum_range = 5.0F;			// [m]
	static const float maximum_output_voltage = 10.0F;	// [V]
	static const float height = 0.5F;					// [m]
	static const float offset = 0.3F;					// [m]

	uint32_t raw_value = HAL_ADC_GetValue(GetADC());
	const float voltage = ((float)raw_value) * scaling_factor;
	const float delta = (voltage / maximum_output_voltage) * maximum_range - offset;
	const float angle = atan2(height, delta);

	SetMessageValue(angle);

	HAL_UART_Transmit(GetUART(), (uint8_t*)GetMessage(), sizeof(Message), 1000);
}

void send_char(char c)
{
	HAL_UART_Transmit(GetUART(), (uint8_t*)&c, 1, 1000);
}

int __io_putchar(int ch)
{
	if (ch == '\n')
		send_char('\r');
	send_char(ch);
	return ch;
}

int main(void)
{
	SystemCoreClock = 8000000; // taktowanie 8Mhz
	HAL_Init();

	InitUART();
	InitADC();
	InitGPIO();
	InitTimer();

	InitMessage();

	while (true)
	{}
}
