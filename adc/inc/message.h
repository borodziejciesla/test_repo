/*
 * message.h
 *
 *  Created on: 17.08.2019
 *      Author: user
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

/* Message Definition */
#define MESSAGE_HEADER_LENGTH	(4U)

typedef struct Message
{
	char start[MESSAGE_HEADER_LENGTH];
	float angle;;
} Message;

/* Methods */
extern void InitMessage(void);
extern void SetMessageValue(const float angle);
extern Message* GetMessage(void);

#endif /* MESSAGE_H_ */
