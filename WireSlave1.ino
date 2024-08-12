#include "Wire.h"

#define I2C_DEV_ADDR 4
// #define PIEZO_PIN  

void onRequest() {
  // int piezoValue = analogRead(PIEZO_PIN);  
   int piezoValue = random(200, 401);
  Wire.write((uint8_t*)&piezoValue, sizeof(piezoValue));  
  Serial.println("Piezo value sent to master");
}

void onReceive(int len) {
  Serial.printf("onReceive[%d]: ", len);
  while (Wire.available()) {
    Serial.write(Wire.read());
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  Wire.begin(I2C_DEV_ADDR);
  // pinMode(PIEZO_PIN, INPUT);
}

void loop() {
  
}
