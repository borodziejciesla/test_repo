#include "stm32f10x.h"

static void send_char(char c);
static void send_string(const char * s);
static char recive_char(void);

int main(void)
{
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef uart;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_2;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_3;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio);

	USART_StructInit(&uart);
	uart.USART_BaudRate = 9600;
	USART_Init(USART2, &uart);

	USART_Cmd(USART2, ENABLE);

	while(1)
	{
		char c = recive_char();
		if (c != 0)
		{
			switch (c)
			{
				case 'a':
				{
					send_string("Hello world!\r\n");
					break;
				}
				case 'b':
				{
					send_string("Hello!\r\n");
					break;
				}
				default:
				{
					send_string("hgdfghdui!\r\n");
				}
			}
		}
	}

}


static void send_char(char c)
{
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){};
	USART_SendData(USART2, c);
}

static void send_string(const char * s)
{
	int i = 0;
	while(*s)
	{
		send_char(*s++);
	}
}

static char recive_char(void)
{
	char recived_char = 0;

	if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE))
	{
		recived_char = USART_ReceiveData(USART2);
	}
	else
	{
		/* Do nothing */
	}
}
