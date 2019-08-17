#include "globals.h"

static TIM_HandleTypeDef tim_global;
static TIM_OC_InitTypeDef oc_global;
static UART_HandleTypeDef uart;
static GPIO_InitTypeDef gpio;
static I2C_HandleTypeDef i2c;

static uint32_t last_counter = 0u;
static float voltage = 0.0f;

static const float voltageConv = 6.114 / 32768.0;

TIM_HandleTypeDef* getGlobalTimer(void)
{
	return &tim_global;
}

TIM_OC_InitTypeDef* getGlobalOC(void)
{
	return &oc_global;
}

UART_HandleTypeDef* getUart(void)
{
	return &uart;
}

GPIO_InitTypeDef* getGPIO(void)
{
	return &gpio;
}

uint32_t getCounter(void)
{
	return last_counter;
}

void setCounter(uint32_t new_counter)
{
	last_counter = new_counter;
}

void updateCounter(uint32_t update_value)
{
	last_counter += update_value;
}

void incrementCounter(void)
{
	last_counter++;
}

extern void setVoltage(float new_voltage)
{
	voltage = new_voltage;
}

extern float getVoltage(void)
{
	return voltage;
}

extern float getVoltageStep(void)
{
	return voltageConv;
}

extern I2C_HandleTypeDef* getI2C(void)
{
	return &i2c;
}
