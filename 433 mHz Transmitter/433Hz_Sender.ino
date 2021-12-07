#include "Wire.h"
// SHT25 I2C address is 0x40(64)
#define Addr 0x40
#include <SPI.h>
#include <SD.h>
#include <RH_ASK.h>
#define DS3231_I2C_ADDRESS 0x68
RH_ASK rf_driver;

char msg[30];
char tempstr[20];
void setup() {
  rf_driver.init();
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}
void loop() {
  // display the real-time clock data on the Serial Monitor,
  // put your main code here, to run repeatedly:
  unsigned int data[2];
  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Send humidity measurement command, NO HOLD master
  Wire.write(0xF5);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(250);
  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);
  // Read 2 bytes of data
  // humidity msb, humidity lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    // Convert the data
    float humidity = (((data[0] * 256.0 + data[1]) * 125.0) / 65536.0) - 6;
    // Output data to Serial Monitor
    //Serial.print("RH ");
    //sprintf(msg, "%f", humidity);
    dtostrf(humidity, 4, 2, msg);
    //Serial.print(msg);
  }
// Start I2C transmission
  Wire.beginTransmission(Addr);
  // Send temperature measurement command, NO HOLD master
  Wire.write(0xF3);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(250);
  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);
  // Read 2 bytes of data
  // temp msb, temp lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    // Convert the data
    float cTemp = (((data[0] * 256.0 + data[1]) * 175.72) / 65536.0) - 46.85;
    float fTemp = (cTemp * 1.8) + 32;
    // Output data to Serial Monitor
    //Serial.print("TC ");
    //sprintf(tempstr, "%f", cTemp);
    dtostrf(cTemp, 4, 2, tempstr);
    //Serial.print(tempstr);
  }
  strcat(msg, ", ");
  strcat(msg,tempstr);
  //strcat(msg, "\n");
  Serial.println(msg);
  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();
  delay(500); // every second
}
