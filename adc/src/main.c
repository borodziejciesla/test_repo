#include <string.h>

#include "stm32f1xx.h"

#include "globals.h"
#include "message.h"

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

 InitMessage();

 while (true)
 {
	 uint32_t value = HAL_ADC_GetValue(GetADC());
	 SetMessageValue((float)value);

	 HAL_UART_Transmit(GetUART(), (uint8_t*)GetMessage(), sizeof(Message), 1000);
	 printf("*****************Adc = %ld (%.3fV)\r\n", value, value * 3.3f / 4096.0f);
 }
}
