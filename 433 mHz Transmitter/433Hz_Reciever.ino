#include "Wire.h"
// SHT25 I2C address is 0x40(64)
#define Addr 0x40
#include <SPI.h>
#include <SD.h>
#include <RH_ASK.h>
#define DS3231_I2C_ADDRESS 0x68

File myFile;
RH_ASK rf_driver(2000, 9, 12, 10, false);

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val) {
  return ( (val / 10 * 16) + (val % 10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val) {
  return ( (val / 16 * 10) + (val % 16) );
}
void setup() {
  rf_driver.init();
  Wire.begin();
  Serial.begin(9600);
  // set the initial time here:
  // DS3231 seconds, minutes, hours, day, date, month, year
  //setDS3231time(30, 42, 16, 5, 13, 10, 16);
  // Open serial communications and wait for port to open:
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}
/*void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
                   dayOfMonth, byte month, byte year) {
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
  }*/
void readDS3231time(byte *second,
                    byte *minute,
                    byte *hour,
                    byte *dayOfWeek,
                    byte *dayOfMonth,
                    byte *month,
                    byte *year) {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
void displayTime() {
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
                 &year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  myFile.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  myFile.print(":");
  if (minute < 10) {
    Serial.print("0");
    myFile.print("0");
  }
  Serial.print(minute, DEC);
  myFile.print(minute, DEC);
  Serial.print(":");
  myFile.print(":");
  if (second < 10) {
    Serial.print("0");
    myFile.print("0");
  }
  Serial.print(second, DEC);
  myFile.print(second, DEC);
  Serial.print(" ");
  myFile.print(" ");
  Serial.print(dayOfMonth, DEC);
  myFile.print(dayOfMonth, DEC);
  Serial.print("/");
  myFile.print("/");
  Serial.print(month, DEC);
  myFile.print(month, DEC);
  Serial.print("/");
  myFile.print("/");
  Serial.print(year, DEC);
  myFile.print(year, DEC);
  /*Serial.print(" Day of week: ");
    switch (dayOfWeek) {
    case 1:
      Serial.println("Sunday");
      break;
    case 2:
      Serial.println("Monday");
      break;
    case 3:
      Serial.println("Tuesday");
      break;
    case 4:
      Serial.println("Wednesday");
      break;
    case 5:
      Serial.println("Thursday");
      break;
    case 6:
      Serial.println("Friday");
      break;
    case 7:
      Serial.println("Saturday");
      break;
    }*/
}
void loop() {
  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);
  myFile = SD.open("TCRH.txt", FILE_WRITE);
  if (rf_driver.recv(buf, &buflen)) // Non-blocking
  {
    // Message with a good checksum received, dump it.
    if (myFile) {
      displayTime();
      Serial.print(" ");
      Serial.println((char*)buf);

      myFile.print(", ");
      myFile.println((char*)buf);
      myFile.close();
    } else {
      Serial.println("Failed to open TCRH.txt");
    }
  }


/*// display the real-time clock data on the Serial Monitor,
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
  //Serial.print("RH ");*/
/*myFile = SD.open("TCRH.txt", FILE_WRITE);
if (myFile) {
  displayTime();
  Serial.print(" ");
  Serial.print(humidity);
  Serial.print(", ");

  myFile.print(", ");
  myFile.print(humidity);
  myFile.print(", ");
  myFile.close();
} else {
  Serial.println("Failed to open TCRH.txt");
}
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
myFile = SD.open("TCRH.txt", FILE_WRITE);
if (myFile) {
  Serial.print(cTemp);
  Serial.print("\n");
  myFile.print(cTemp);
  myFile.print("\n");
  myFile.close();
} else {
  Serial.println("Failed to open TCRH.txt");
}
}*/
delay(500); // every second
}
