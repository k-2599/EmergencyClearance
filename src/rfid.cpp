// /*
//  * 
//  * All the resources for this project: https://www.hackster.io/Aritro
//  * Modified by Aritro Mukherjee
//  * 
//  * 
//  */
 
// #include <SPI.h>
// #include <MFRC522.h>
 
// #define SS_PIN 10
// #define RST_PIN 9
// MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

// byte readCard[4];
// String MasterTag = "596E795A";	// REPLACE this Tag ID with your Tag ID!!!
// String tagID = "";

// boolean getID();

// void setup() 
// {
//   Serial.begin(9600);   // Initiate a serial communication
//   SPI.begin();      // Initiate  SPI bus
//   mfrc522.PCD_Init();   // Initiate MFRC522
//   Serial.println("Approximate your card to the reader...");
//   Serial.println();

// }
// void loop() 
// {
//     while (getID()) 
//   {
    
//     if (tagID == MasterTag) 
//     {
      
//       Serial.println(" Access Granted!");
//       // You can write any code here like opening doors, switching on a relay, lighting up an LED, or anything else you can think of.
//     }
//     else
//     {
//       Serial.println("Access Denied!");
//     }
    
//       Serial.print("ID : ");
//       Serial.println(tagID);

//     Serial.println("\nScan Your Card>>");
//   }
// }


// boolean getID() 
// {
//   // Getting ready for Reading PICCs
//   if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
//   return false;
//   }
//   if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
//   return false;
//   }
//   tagID = "";
//   for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
//   //readCard[i] = mfrc522.uid.uidByte[i];
//   tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
//   }
//   tagID.toUpperCase();
//   mfrc522.PICC_HaltA(); // Stop reading
//   return true;
// }