#include <Arduino.h>
#include <Wire.h>
#include "globals.h"


#define SERIAL_DEBUG    // Enable debugging output to serial

#define I2CArduSense_ADDR                 0x7A        // I2C Slave Address for I2CArduSense
#define I2CArduSense_SIGNATURE            0x4153      // AS for ArduSense in HEX :)


void setup() {
  Wire.begin(I2CArduSense_ADDR);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
#ifdef SERIAL_DEBUG  
  Serial.begin(115200);
  Serial.println("Begin");
#endif

  I2CArduSense_Interrupt_Reg = 0x0000;
  mclock = millis();
}

void I2cWrite16(uint16_t val) {
  uint8_t msb, lsb;
  msb = (val >> 8);
  lsb = (val & 0x00ff);
  Wire.write(msb);
  Wire.write(lsb);
}

void SendSignature(void) {
  I2cWrite16(I2CArduSense_SIGNATURE);
}

void SendInterruptRegister(void) {
  // Send interrupt register content
  I2cWrite16(I2CArduSense_Interrupt_Reg);
  // Reset interrupt register
  I2CArduSense_Interrupt_Reg=0;
}

/*
 * unsigned long m50;
unsigned long m100;
unsigned long m500;
unsigned long m1000;
 */

void loop() {
  mclock=millis();
  if (mclock > m50+50) {
    XsnsNextCall(FUNC_EVERY_50_MSECOND);
    m50=millis();
  }
  if (mclock > m100+100) {
    XsnsNextCall(FUNC_EVERY_100_MSECOND);
    m100=millis();
  }
  if (mclock > m500+500) {
    XsnsNextCall(FUNC_EVERY_500_MSECOND);
    m500=millis();
  }
  if (mclock > m1000+1000) {
    XsnsNextCall(FUNC_EVERY_SECOND);
    m1000=millis();
  }
}

void receiveEvent(int bytesReceived) {
}

void requestEvent() {
  if (Wire.available()) {
    uint8_t reg = Wire.read();
#ifdef SERIAL_DEBUG    
    Serial.print("Request: ");
    Serial.println(reg);
#endif    
    switch (reg) {
      case 0:
        SendSignature();
        break;
      case 1:
        SendInterruptRegister();
        break;
      default:
        break;
    }
  }
}


