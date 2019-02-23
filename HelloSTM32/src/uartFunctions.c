#include "uartFunctions.h"

void send_string(char* s)
{
	HAL_UART_Transmit_IT(getUart(), (uint8_t*)s, strlen(s));
}

void sendMeasurement(const volatile float * const measurement)
{
	HAL_UART_Transmit_IT(getUart(), (uint8_t*)measurement, sizeof(float));
}
