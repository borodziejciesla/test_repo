#include "uartFunctions.h"

void send_string(char* s)
{
	HAL_UART_Transmit_IT(getUart(), (uint8_t*)s, strlen(s));
}

void sendMeasurement(uint32_t measurement)
{
	char message[6];
	message[0] = 's';
	memcpy(message + 1, &measurement, sizeof(measurement));
	message[5] = 'n';

	HAL_UART_Transmit_IT(getUart(), message, 6);
}
