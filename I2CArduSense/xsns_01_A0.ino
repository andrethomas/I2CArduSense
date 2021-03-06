/*
 * Example template
 * 
 * TODO: Add JSON generation code for sample template reading A0
 */

#include <Arduino.h>
#include "globals.h"

#define XSNS_01 1

void A0_MakeJSON(void) {
  sprintf(jsonresult,"{\"A0\":%i}",analogRead(A0));
}

/***************************************\
 Interface
\***************************************/

boolean Xsns01(byte function) {
  boolean result = false;
  switch (function) {
    case FUNC_EVERY_50_MSECOND:
      break;
    case FUNC_EVERY_100_MSECOND:
      break;
    case FUNC_EVERY_500_MSECOND:
      break;
    case FUNC_EVERY_SECOND:
      break;
    case FUNC_JSON:
      A0_MakeJSON();
      result=true;
      break;
    default:
      break;
  }
  return result;
}

