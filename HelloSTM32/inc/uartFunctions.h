#ifndef UARTFUNCTIONS_H_
#define UARTFUNCTIONS_H_

#include "initPWMState.h"

extern void send_string(char* s);

extern void sendMeasurement(const volatile float * const measurement);

#endif
