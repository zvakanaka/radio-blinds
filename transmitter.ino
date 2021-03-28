// THANK YOU: https://create.arduino.cc/projecthub/muhammad-aqib/nrf24l01-interfacing-with-arduino-wireless-communication-0c13d4
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.

void setup() {
  Serial.begin(9600);
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
  Serial.println("RF set up");
}

void loop() {
  if (Serial.available()) {  // check for incoming serial data
    String command = Serial.readString();  // read command from serial port

    if (command.indexOf("open") > -1) {
      Serial.println("Sending blinds_open");
      const char text[] = "blinds_open";
      radio.write(&text, sizeof(text)); // send message to receiver
    } else if (command.indexOf("shut") > -1) {
      Serial.println("Sending blinds_shut");
      const char text[] = "blinds_shut";
      radio.write(&text, sizeof(text)); // send message to receiver
    } else {
      Serial.print("Received unknown serial command:");// THANK YOU: https://create.arduino.cc/projecthub/muhammad-aqib/nrf24l01-interfacing-with-arduino-wireless-communication-0c13d4
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.

void setup() {
  Serial.begin(9600);
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
  Serial.println("RF set up");
}

void loop() {
  if (Serial.available()) {  // check for incoming serial data
    String command = Serial.readString();  // read command from serial port

    if (command.indexOf("open") > -1) {
      Serial.println("Sending blinds_open");
      const char text[] = "blinds_open";
      radio.write(&text, sizeof(text)); // send message to receiver
    } else if (command.indexOf("shut") > -1) {
      Serial.println("Sending blinds_shut");
      const char text[] = "blinds_shut";
      radio.write(&text, sizeof(text)); // send message to receiver
    } else {
      Serial.print("Received unknown serial command:");
      Serial.println(command);
    }
  }
}// THANK YOU: https://create.arduino.cc/projecthub/muhammad-aqib/nrf24l01-interfacing-with-arduino-wireless-communication-0c13d4
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.

void setup() {
  Serial.begin(9600);
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
  Serial.println("RF set up");
}

void loop() {
  if (Serial.available()) {  // check for incoming serial data
    String command = Serial.readString();  // read command from serial port

    if (command.indexOf("open") > -1) {
      Serial.println("Sending blinds_open");
      const char text[] = "blinds_open";
      radio.write(&text, sizeof(text)); // send message to receiver
    } else if (command.indexOf("shut") > -1) {
      Serial.println("Sending blinds_shut");
      const char text[] = "blinds_shut";
      radio.write(&text, sizeof(text)); // send message to receiver
    } else {
      Serial.print("Received unknown serial command:");
      Serial.println(command);
    }
  }
}
      Serial.println(command);
    }
  }
}
