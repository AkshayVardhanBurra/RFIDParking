#include <SPI.h>
#include <MFRC522.h>
#include <string.h>
#include "RFID.h"

// Data MUST be exactly 16 bytes long (pad with spaces or zeros if shorter)
byte firstName[16] = {"John            "};
byte lastName[16] =  {"Dingle          "}; 

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid_init();
  Serial.println("Scan a MIFARE 1K card to write data...");
}

void loop() {

  // CARD READING LOGIC:
  if (isCardTapped()) {
 
  Serial.print("Card detected. UID:");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }

  Serial.println();
  writeFirstName(firstName);
  writeLastName(lastName);


  byte buffer[18];
  byte bufferSize = sizeof(buffer);
  String firstName = readFirstName();
  Serial.println(firstName);
  String lastName = readLastName();
  Serial.println(lastName);
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  delay(1500);

  }
}