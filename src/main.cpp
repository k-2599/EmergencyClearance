// #include<Arduino.h>
// #include <SPI.h>
// #include <MFRC522.h>
// #define SS_PIN 10
// #define RST_PIN 9

// MFRC522 mfrc522(SS_PIN, RST_PIN); 
// byte readCard[4];
// String MasterTag = "596E795A";	// REPLACE this Tag ID with your Tag ID!!!
// String tagID = "";

// boolean getID();

// unsigned long previousMillis = 0;
// unsigned long previousMillisIR1 = 0;  
// unsigned long previousMillisIR2 = 0;  
// unsigned long previousMillisIR3 = 0;       
// const long sec = 1000;
// const long IR_time = 3000;   
// const int green_time = 10;
// const int em_time = 3;

// int flag1 = 0;
// int flag_inc1 = 0;

// int flag2 = 0;
// int flag_inc2 = 0;

// int flag3 = 0;
// int flag_inc3 = 0;

// int flag_rf = 0;
// int flag_rf1 = 0;

// const int IR1 = 7;
// const int IR2 = 6;
// const int IR3 = 5;

// const int LEDG1 = A0;
// const int LEDR1 = A1;   

// const int LEDG2 = A2;
// const int LEDR2 = A3;   

// const int LEDG3 = A4;
// const int LEDR3 = A5;   


// int red1=0;
// int red1_temp=0;
// int green1=10;

// int red2=0;
// int red2_temp=0;
// int green2=0;

// int red3=0;
// int red3_temp=0;
// int green3=0;

// void setup() {

//   Serial.begin(9600);
//   SPI.begin();      // Initiate  SPI bus
//   mfrc522.PCD_Init();   // Initiate MFRC522
//   Serial.println(" Arduino Started - ");

//   pinMode(IR1, INPUT);
//   pinMode(IR2, INPUT);
//   pinMode(IR3, INPUT);
//   pinMode(LEDG1, OUTPUT);
//   pinMode(LEDR1, OUTPUT);
//   pinMode(LEDG2, OUTPUT);
//   pinMode(LEDR2, OUTPUT);
//   pinMode(LEDG3, OUTPUT);
//   pinMode(LEDR3, OUTPUT);
// }

// void loop() {

//     unsigned long currentMillis = millis();
//     int IRstatus1 = digitalRead(IR1);
//     int IRstatus2 = digitalRead(IR2);
//     int IRstatus3 = digitalRead(IR3);
    
//     while (getID()) {
//       if (tagID == MasterTag) 
//       {
//         Serial.println(" Emergency Vehicle Detected - ");

//         if(!flag_rf1)
//           flag_rf = 1;

//         flag_rf1 = 1;
//         // You can write any code here like opening doors, switching on a relay, lighting up an LED, or anything else you can think of.
//       }
//       else
//       {
//         Serial.println("Unrecognized Emergency Vehicle Detected - ");
//       }
//     }

//     //Checking IR 1
//     if(IRstatus1 == 0 && green1 != 0){
//       if(flag1 == 0){
//         Serial.println("Current time save of IR 1");
//         previousMillisIR1 = currentMillis;
//         flag1 = 1;
//       }
//       if((previousMillisIR1 + IR_time) <= currentMillis){
//         if(flag_inc1 == 0){
//           green1= green1 + 3;
//           Serial.println("Green 1 Increment");
//           flag_inc1 = 1;
//           flag1 = 0;
//         }
//       }
//       else
//         flag_inc1 = 0;
//     }
//     else
//       flag1 = 0;

//     //Checking IR 2
//     if(IRstatus2 == 0 && green2 != 0 && !flag_rf1){
//       if(flag2 == 0){
//         Serial.println("Current time save of IR 2");
//         previousMillisIR2 = currentMillis;
//         flag2 = 1;
//       }
//       if((previousMillisIR2 + IR_time) <= currentMillis){
//         if(flag_inc2 == 0){
//           green2= green2 + 3;
//           Serial.println("Green 2 Increment");
//           flag_inc2 = 1;
//           flag2 = 0;
//         }
//       }
//       else
//         flag_inc2 = 0;
//     }
//     else
//       flag2 = 0;

//     // Checking IR 3
//     if(IRstatus3 == 0 && green3 != 0 && !flag_rf1){
//       if(flag3 == 0){
//         Serial.println("Current time save of IR 3");
//         previousMillisIR3 = currentMillis;
//         flag3 = 1;
//       }
//       if((previousMillisIR3 + IR_time) <= currentMillis){
//         if(flag_inc3 == 0){
//           green3= green3 + 3;
//           Serial.println("Green 3 Increment");
//           flag_inc3 = 1;
//           flag3 = 0;
//         }
//       }
//       else
//         flag_inc3 = 0;
//     }
//     else
//       flag3 = 0;


//     if (currentMillis - previousMillis >= sec) {
//       previousMillis = currentMillis;

//       if(green1>0){
//           digitalWrite(LEDG1,HIGH);
//           digitalWrite(LEDG2,LOW);
//           digitalWrite(LEDG3,LOW);

//           digitalWrite(LEDR1,LOW);
//           digitalWrite(LEDR2,HIGH);
//           digitalWrite(LEDR3,HIGH);
  
//           --green1;
//           ++red1_temp;
//           Serial.print("Green 1 = ");
//           Serial.println(green1);

//           if(green1==0){
//               flag_rf1 = 0;
//               red1 = red1_temp;
//               green2 = green_time;
//           }
//       }
//       if(green2>0){
//           digitalWrite(LEDG1,LOW);
//           digitalWrite(LEDG2,HIGH);
//           digitalWrite(LEDG3,LOW);

//           digitalWrite(LEDR1,HIGH);
//           digitalWrite(LEDR2,LOW);
//           digitalWrite(LEDR3,HIGH);

//           --green2;
//           Serial.print("Green 2 = ");
//           Serial.println(green2);
//           ++red2_temp;
//           if(flag_rf && green2 > em_time){
//             green2 = em_time;
//             flag_rf = 0;    
//           }
//           if(green2==0){
//               if(flag_rf1){
//                 green1 = green_time;
//               }
//               else{
//                 green3 = green_time;
//                 red2 = red2_temp;
//               }
//           }
//       }
//       if(green3>0){
//           digitalWrite(LEDG1,LOW);
//           digitalWrite(LEDG2,LOW);
//           digitalWrite(LEDG3,HIGH);

//           digitalWrite(LEDR1,HIGH);
//           digitalWrite(LEDR2,HIGH);
//           digitalWrite(LEDR3,LOW);

//           --green3;
//           ++red3_temp;
//           Serial.print("Green 3 = ");
//           Serial.println(green3);
//           if(flag_rf && green3 > em_time){
//             green3 = em_time;
//             flag_rf = 0;    
//           }
//           if(green3==0){
//               red3 = red3_temp;
//               green1 = green_time;
//           }
//       }
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