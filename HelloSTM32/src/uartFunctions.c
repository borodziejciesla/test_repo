#include "uartFunctions.h"

void send_string(char* s)
{
	HAL_UART_Transmit_IT(getUart(), (uint8_t*)s, strlen(s));
}

void sendMeasurement(uint32_t measurement)
{
	uint32_t tmp = measurement;
	HAL_UART_Transmit_IT(getUart(), &tmp, sizeof(measurement));
}
