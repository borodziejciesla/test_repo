#include "uartFunctions.h"

void send_string(char* s)
{
	HAL_UART_Transmit_IT(getUart(), (uint8_t*)s, strlen(s));
}

void sendMeasurement(uint32_t measurement)
{
	static char message[7] = {'s', 't', 'a'};
	memcpy(message + 3, (uint8_t*)&measurement, sizeof(measurement));

	HAL_UART_Transmit_IT(getUart(), message, 7);
}
