#include <Wire.h>

#define I2CArduSense_ADDR                 0x7A        // I2C Slave Address for I2CArduSense
#define I2CArduSense_SIGNATURE            0x4154      // AT for Andre Thomas in HEX :)

uint16_t  I2CArduSense_Interrupt_Reg = 0x00;

void setup() {
  Wire.begin(I2CArduSense_ADDR);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
  Serial.println("Begin");
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

void loop() {
}

void receiveEvent(int bytesReceived) {
}

void requestEvent() {
  if (Wire.available()) {
    uint8_t reg = Wire.read();
    Serial.print("Request: ");
    Serial.println(reg);
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

