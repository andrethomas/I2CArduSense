/*
 * Support functions for sensors
 */

#include <Arduino.h>
#include "globals.h"

void xsns_si(uint8_t intid) {
  I2CArduSense_Interrupt_Reg |= (1 << intid);
}

void xsns_ci(uint8_t intid) {
  I2CArduSense_Interrupt_Reg &= ~(1 << intid);
}

void xsns_ci_all(void) {
  I2CArduSense_Interrupt_Reg = 0;
}

