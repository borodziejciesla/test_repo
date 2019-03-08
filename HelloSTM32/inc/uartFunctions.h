#ifndef UARTFUNCTIONS_H_
#define UARTFUNCTIONS_H_

#include "initPWMState.h"

extern void send_string(char* s);
extern void sendMeasurement(uint32_t measurement);

#endif
