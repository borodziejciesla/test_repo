#include "stm32f10x.h"

void send_char(char c)
{
 while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
 USART_SendData(USART2, c);
}

int __io_putchar(int c)
{
 if (c=='\n')
 send_char('\r');
 send_char(c);
 return c;
}

void USART2_IRQHandler(void)
{
	if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE))
	{
		char c = USART_ReceiveData(USART2);
		switch (c)
		{
			case 'a':
				printf("Odebrano komunikat %5d!\n", 5);
				break;
			case 'b':
				printf("Odebrano komunikat B!\n");
				break;
			default:
				printf("Nieznany komunikat:(\n");
		}
	}
}

int main(void)
{
 GPIO_InitTypeDef gpio;
 USART_InitTypeDef uart;
 NVIC_InitTypeDef nvic;

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

 nvic.NVIC_IRQChannel = USART2_IRQn;
 nvic.NVIC_IRQChannelPreemptionPriority = 0;
 nvic.NVIC_IRQChannelSubPriority = 0;
 nvic.NVIC_IRQChannelCmd = ENABLE;
 NVIC_Init(&nvic);

 USART_StructInit(&uart);
 uart.USART_BaudRate = 115200;
 USART_Init(USART2, &uart);

 USART_Cmd(USART2, ENABLE);

 USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

 while (1)
 {
	 // Do nothing
 }
}
