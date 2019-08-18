/*
 * message.c
 *
 *  Created on: 17.08.2019
 *      Author: user
 */

#include "message.h"

static Message message;

void InitMessage(void)
{
	message.start[0] = 's';
	message.start[1] = 't';
	message.start[2] = 'a';
	message.start[3] = 'r';

	message.angle = 0.0F;
}

void SetMessageValue(const float angle)
{
	message.angle = angle;
}

Message* GetMessage(void)
{
	return &message;
}
