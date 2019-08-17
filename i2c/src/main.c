#include "stm32f10x.h"

int main(void)
{
 GPIO_InitTypeDef gpio;
 I2C_InitTypeDef i2c;

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

 GPIO_StructInit(&gpio);
 gpio.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; // SCL, SDA
 gpio.GPIO_Mode = GPIO_Mode_AF_OD;
 gpio.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOB, &gpio);

 I2C_StructInit(&i2c);
 i2c.I2C_Mode = I2C_Mode_I2C;
 i2c.I2C_Ack = I2C_Ack_Enable;
 i2c.I2C_ClockSpeed = 100000;
 I2C_Init(I2C1, &i2c);
 I2C_Cmd(I2C1, ENABLE);

 I2C_GenerateSTART(I2C1, ENABLE);
 while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);

 I2C_Send7bitAddress(I2C1, 0xa0, I2C_Direction_Transmitter);
 while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);

 I2C_SendData(I2C1, 0x00);
 while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);

 I2C_GenerateSTART(I2C1, ENABLE);
 while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);

 I2C_AcknowledgeConfig(I2C1, ENABLE);
 I2C_Send7bitAddress(I2C1, 0xa0, I2C_Direction_Receiver);
 while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);

    while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
    uint8_t data1 = I2C_ReceiveData(I2C1);

 I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);
    while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
    uint8_t data2 = I2C_ReceiveData(I2C1);

 while (1)
 ;
}
