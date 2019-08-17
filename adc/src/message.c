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

	message.end[0] = 'e';
	message.end[1] = 'n';
	message.end[2] = 'd';
	message.end[3] = 'm';
}

void SetMessageValue(const float angle)
{
	message.angle = angle;
}

Message* GetMessage(void)
{
	return &message;
}
