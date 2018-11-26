#include <stdio.h>
#include <stdint.h>
#include "stm32f10x.h"

#define FRAME_LENGTH (10)

void send_char(char c)
{
	 while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	 USART_SendData(USART2, c);
}

int __io_putchar(int c)
{
	 ///if (c=='\n')
	 //send_char('\r');
	 send_char(c);
	 return c;
}

void sendFrame(char frame[FRAME_LENGTH])
{
	uint8_t i = 0;

	for(i = 0; i < FRAME_LENGTH; i++)
	{
		send_char(frame[i]);
	}
}

int adc_read(int channel)
{
	 ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5);
	 ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	 while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET);

	 return ADC_GetConversionValue(ADC1);
}

static void create_frame(uint16_t u_1, uint16_t u_2, char * frame);

int main(void)
{
	 GPIO_InitTypeDef gpio;
	 USART_InitTypeDef uart;
	 ADC_InitTypeDef adc;

	 char frame[FRAME_LENGTH];
	 uint16_t u_1;
	 uint16_t u_2;

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	 RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	 GPIO_StructInit(&gpio);
	 gpio.GPIO_Pin = GPIO_Pin_2;
	 gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	 GPIO_Init(GPIOA, &gpio);

	 gpio.GPIO_Pin = GPIO_Pin_3;
	 gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 GPIO_Init(GPIOA, &gpio);

	 USART_StructInit(&uart);
	 uart.USART_BaudRate = 115200;
	 USART_Init(USART2, &uart);
	 USART_Cmd(USART2, ENABLE);

	 gpio.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	 gpio.GPIO_Mode = GPIO_Mode_AIN;
	 GPIO_Init(GPIOA, &gpio);

	 ADC_StructInit(&adc);
	 adc.ADC_ContinuousConvMode = DISABLE;
	 adc.ADC_NbrOfChannel = 1;
	 adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	 ADC_Init(ADC1, &adc);
	 ADC_Cmd(ADC1, ENABLE);

	 ADC_ResetCalibration(ADC1);
	 while (ADC_GetResetCalibrationStatus(ADC1));

	 ADC_StartCalibration(ADC1);
	 while (ADC_GetCalibrationStatus(ADC1));



	 while (1)
	 {
		 /* Read DAC data */
		 u_1 = adc_read(ADC_Channel_0);
		 u_2 = adc_read(ADC_Channel_1);

		 /* Create frame */
		 create_frame(u_1, u_2, frame);

		 /* Send Date */
		 sendFrame(frame);
	 }
}

/* ****************************************************************************************** */
static void create_frame(uint16_t u_1, uint16_t u_2, char frame[FRAME_LENGTH])
{
	char * tmp;

	// Header
	frame[0] = 's';
	frame[1] = 't';
	frame[2] = 'r';
	// Data
	tmp = (char*)(&u_1);
	frame[3] = tmp[0];
	frame[4] = tmp[1];
	tmp = (char*)(&u_2);
	frame[5] = tmp[0];
	frame[6] = tmp[1];
	// end
	frame[7] = 'e';
	frame[8] = 'n';
	frame[9] = 'd';
}
