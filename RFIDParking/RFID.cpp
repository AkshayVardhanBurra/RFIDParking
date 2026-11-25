#include "RFID.h"

#define RST_PIN 5   // Configurable reset pin
#define SS_PIN  53  // Mega hardware SS pin

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

byte firstNameBlock = 4; // Safe data block in Sector 1
byte lastNameBlock = 5;

void rfid_init(){
  mfrc522.PCD_Init();


  // Prepare the default factory security key (0xFFFFFFFFFFFF)
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println("THE RFID IS INITIALIZED!");
}

//Returns true if successfully written. Returns false if error occurs
bool writeFirstName(char firstName[16]){

  MFRC522::StatusCode status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, firstNameBlock, &key, &(mfrc522.uid));
      
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Authentication failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return false;
  }
  status = mfrc522.MIFARE_Write(firstNameBlock, firstName, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Authentication failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    mfrc522.PICC_HaltA();       // Reset card state
    mfrc522.PCD_StopCrypto1();  // Stop encryption on reader
    return false;
  } else {
    Serial.println("Success! Data written to block.");
    return true;
  }
}

//Returns true if successfully written. Returns false if error occurs
bool writeLastName(char lastName[16]){
  MFRC522::StatusCode status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, lastNameBlock, &key, &(mfrc522.uid));
      
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Authentication failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return false;
  }
  status = mfrc522.MIFARE_Write(lastNameBlock, lastName, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Authentication failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    mfrc522.PICC_HaltA();       // Reset card state
    mfrc522.PCD_StopCrypto1();  // Stop encryption on reader
    return false;
  } else {
    Serial.println("Success! Data written to block.");
    return true;
  }
}

//Returns empty string if error happens while reading.
String readFirstName() {
  char buffer[18];
  byte bufferSize = sizeof(buffer);
  MFRC522::StatusCode status = mfrc522.MIFARE_Read(firstNameBlock, buffer, &bufferSize);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Read failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return "";
  } 
  // Overwrite index 16 (the first CRC byte) with a null terminator
  buffer[16] = '\0'; 

  // Cast to (char*) so String() reads it as text
  String result = String((char*)buffer);
  
  // Optional: removes the trailing spaces from "John            "
  result.trim();

  return result;

}

//Returns empty string if error happens while reading.
String readLastName(){
  char buffer[18];
  byte bufferSize = sizeof(buffer);
  MFRC522::StatusCode status = mfrc522.MIFARE_Read(lastNameBlock, buffer, &bufferSize);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Read failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return "";
  } 

  // Overwrite index 16 (the first CRC byte) with a null terminator
  buffer[16] = '\0'; 

  // Cast to (char*) so String() reads it as text
  String result = String((char*)buffer);
  
  // Optional: removes the trailing spaces from "John            "
  result.trim();

  return result;
}

uint8_t isCardTapped(){
  return mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial();
}

void stopRFID(){
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}