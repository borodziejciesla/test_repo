#ifndef I2C_HAL_INC_MESSAGE_H_
#define I2C_HAL_INC_MESSAGE_H_

#define MESSAGE_HEADER_LENGTH	(3U)
#define MESSAGE_END_LENGTH		(3U)

typedef struct Mesage
{
	char header[MESSAGE_HEADER_LENGTH];
	float angle;
	char end[MESSAGE_END_LENGTH];
} MessageT;

#endif
