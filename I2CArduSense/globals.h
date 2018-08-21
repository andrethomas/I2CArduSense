#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <Arduino.h>

#define FUNC_JSON                 0x00
#define FUNC_EVERY_SECOND         0x01
#define FUNC_EVERY_500_MSECOND    0x02
#define FUNC_EVERY_100_MSECOND    0x03
#define FUNC_EVERY_50_MSECOND     0x04

uint16_t  I2CArduSense_Interrupt_Reg = 0x0000;

char jsonresult[1000];

unsigned long mclock;
unsigned long m50;
unsigned long m100;
unsigned long m500;
unsigned long m1000;

#endif // __GLOBALS_H__
