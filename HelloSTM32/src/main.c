/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f1xx.h"

typedef enum DIRECTION
{
	DIRECTION_LEFT = 0,
	DIRECTION_RIGHT = 1
} DIRECTION_T;

volatile DIRECTION_T direction = DIRECTION_RIGHT;
volatile uint32_t led = 0;


/**********************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_13)
	{
		HAL_GPIO_WritePin(GPIOC, 1 << led, GPIO_PIN_RESET);

		switch (direction)
		{
			case DIRECTION_RIGHT:
			{
				direction = DIRECTION_LEFT;
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

				break;
			}

			case DIRECTION_LEFT:
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
				direction = DIRECTION_RIGHT;
			}

			default:
			{
				// Do nothing
			}
		}

	}
	else
	{
		// Do nothing
	}
}

/**********************************************************************************/
int main(void)
{
	HAL_Init();

	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	// Output
	GPIO_InitTypeDef gpio;
	gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
			| GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &gpio);

	gpio.Pin = GPIO_PIN_5;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &gpio);

	// Input
	gpio.Mode = GPIO_MODE_IT_RISING;
	gpio.Pull = GPIO_PULLUP;
	gpio.Pin = GPIO_PIN_13;
	HAL_GPIO_Init(GPIOC, &gpio);

	// Infinite Loop
	for(;;)
	{
		HAL_GPIO_WritePin(GPIOC, 1 << led, GPIO_PIN_SET);
		HAL_Delay(150);
		HAL_GPIO_WritePin(GPIOC, 1 << led, GPIO_PIN_RESET);


		switch (direction)
		{
			case DIRECTION_RIGHT:
			{
				if (++led >= 10)
				{
					led = 0;
				}

				break;
			}

			case DIRECTION_LEFT:
			{
				if (--led <= 0)
				{
					led = 9;
				}

				break;
			}

			default:
			{
				// Do nothing
			}
		}
	}
}
