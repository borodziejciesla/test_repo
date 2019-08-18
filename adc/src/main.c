#include "globals.h"
#include "message.h"
#include "interruptions.h"

int main(void)
{
	SystemCoreClock = 8000000; // taktowanie 8Mhz
	HAL_Init();

	InitUART();
	InitADC();
	InitGPIO();
	InitTimer();

	InitMessage();

	while (true)
	{}
}
