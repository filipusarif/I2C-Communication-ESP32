#include "Wire.h"

#define I2C_DEV_ADDR 4

uint8_t error;
uint8_t bytesReceived;
int data[4][10];

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void piezo(int Index_Slave){
  for(int i=0; i<10; i++){
    // Write a request message to the slave
    Wire.beginTransmission(I2C_DEV_ADDR);
    Wire.write(Index_Slave); 
    error = Wire.endTransmission(true);
    // Serial.printf("endTransmission: %u\n", error);

    // Request 2 bytes from the slave (assuming piezoValue is 2 bytes)
    bytesReceived = Wire.requestFrom(I2C_DEV_ADDR, sizeof(int));

    if (bytesReceived == sizeof(int)) {
      int piezoValue;
      Wire.readBytes((char*)&piezoValue, sizeof(piezoValue));
      // Serial.printf("Piezo value received: %d\n", piezoValue);
      data[Index_Slave][i] = piezoValue;
    } else {
      Serial.println("Failed to receive piezo value");
    }
    delay(100);
  }
  printData(Index_Slave);
}

void printData(int slave){
  for(int i=0; i<10; i++){
    Serial.print(data[slave][i]);
    if(i<9)
    Serial.print(",");
    else
    Serial.println(";");
  }
}

void loop() {
  if (Serial.available() > 0) {
    String incomingString = Serial.readStringUntil('\n');

    if(incomingString == "get"){
      piezo(0);
    }
    
  }
}
