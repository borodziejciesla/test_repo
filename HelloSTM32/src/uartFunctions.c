#include "uartFunctions.h"

void send_string(char* s)
{
	HAL_UART_Transmit_IT(getUart(), (uint8_t*)s, strlen(s));
}

void sendMeasurement(uint32_t measurement)
{
	uint8_t T [1];
	T[0] = 66;
	HAL_UART_Transmit_IT(getUart(), (uint8_t*)T, 1);
}
