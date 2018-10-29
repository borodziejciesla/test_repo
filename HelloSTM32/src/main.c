/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f10x.h"
			
static void delay(int time);

int main(void)
{
	GPIO_InitTypeDef gpio;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* Configure port A */
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_5;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &gpio);

	/* Configure port C*/
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &gpio);

	for(;;)
	{
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_5);
		}
		else
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		}
	}
}


static void delay(int time)
{
	int i;
	for (i = 0; i < time * 400; i++)
	{
		/* Do nothing */
	}
}
