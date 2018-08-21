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
}

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

void I2cSendJSON(void) {
  
}

void requestEvent() {
  if (Wire.available()) {
    uint8_t reg = Wire.read();
#ifdef SERIAL_DEBUG    
    Serial.print("Request: ");
    Serial.println(reg);
#endif    
    switch (reg) {
      case 0x00:
        SendSignature();
        break;
      case 0x01:
#ifdef XSNS_01
       if(Xsns01(FUNC_JSON)) I2cSendJSON();
       xsns_ci(0);
#endif            
        break;
      case 0x02:
#ifdef XSNS_02
        if(Xsns02(FUNC_JSON)) I2cSendJSON();
        xsns_ci(1);
#endif            
        break;
      case 0x03:
#ifdef XSNS_03
        if(Xsns03(FUNC_JSON)) I2cSendJSON();
        xsns_ci(2);
#endif            
        break;
      case 0x04:
#ifdef XSNS_04
        if(Xsns04(FUNC_JSON)) I2cSendJSON();
        xsns_ci(3);
#endif            
        break;
      case 0x05:
#ifdef XSNS_05
        if(Xsns05(FUNC_JSON)) I2cSendJSON();
        xsns_ci(4);
#endif            
        break;
      case 0x06:
#ifdef XSNS_06
        if(Xsns06(FUNC_JSON)) I2cSendJSON();
        xsns_ci(5);
#endif            
        break;
      case 0x07:
#ifdef XSNS_07
        if(Xsns07(FUNC_JSON)) I2cSendJSON();
        xsns_ci(6);
#endif            
        break;
      case 0x08:
#ifdef XSNS_08
        if(Xsns08(FUNC_JSON)) I2cSendJSON();
        xsns_ci(7);
#endif            
        break;
      case 0x09:
#ifdef XSNS_09
        if(Xsns09(FUNC_JSON)) I2cSendJSON();
        xsns_ci(8);
#endif            
        break;
      case 0x0A:
#ifdef XSNS_10
        if(Xsns10(FUNC_JSON)) I2cSendJSON();
        xsns_ci(9);
#endif            
        break;
      case 0x0B:
#ifdef XSNS_11
        if(Xsns11(FUNC_JSON)) I2cSendJSON();
        xsns_ci(10);
#endif            
        break;
      case 0x0C:
#ifdef XSNS_12
        if(Xsns12(FUNC_JSON)) I2cSendJSON();
        xsns_ci(11);
#endif            
        break;
      case 0x0D:
#ifdef XSNS_13
        if(Xsns13(FUNC_JSON)) I2cSendJSON();
        xsns_ci(12);
#endif            
        break;
      case 0x0E:
#ifdef XSNS_14
        if(Xsns14(FUNC_JSON)) I2cSendJSON();
        xsns_ci(13);
#endif            
        break;
      case 0x0F:
#ifdef XSNS_15
        if(Xsns15(FUNC_JSON)) I2cSendJSON();
        xsns_ci(14);
#endif            
        break;
      case 0xA0:
#ifdef XSNS_16
        if(Xsns16(FUNC_JSON)) I2cSendJSON();
        xsns_ci(15);
#endif            
        break;
      case 0x7F:
        SendInterruptRegister();
        break;
      default:
        break;
    }
  }
}


