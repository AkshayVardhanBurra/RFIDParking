

#include <SPI.h>
#include <MFRC522.h>
#include <string.h>



extern MFRC522 mfrc522;
extern MFRC522::MIFARE_Key key;

extern byte firstNameBlock; // Safe data block in Sector 1
extern byte lastNameBlock;


void rfid_init();

void writeFirstName(char firstName[16]);

void writeLastName(char lastName[16]);

String readFirstName();

String readLastName();

uint8_t isCardTapped();

void stopRFID();