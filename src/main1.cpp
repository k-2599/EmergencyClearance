#include<Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); 
byte readCard[4];
String MasterTag = "596E795A";	// REPLACE this Tag ID with your Tag ID!!!
String tagID = "";

boolean getID(); //function to read RF ID
void check_ir(int& IRstatus,int& green,int& flag,int& flag_inc,unsigned long& previousMillisIR,int lane_no);

unsigned long currentMillis;    // Store the current running time of ardiuno in milliseconds
unsigned long previousMillis = 0;
unsigned long previousMillisIR1 = 0;  
unsigned long previousMillisIR2 = 0;  
unsigned long previousMillisIR3 = 0;

const long sec = 1000;
const long IR_time = 4000;   //Milliseconds to increment green signal time  
const int green_time =10 ;  // Default Green signal time (seconds)

int count = 0;
int flag1 = 0;
int flag_inc1 = 0;

int flag2 = 0;
int flag_inc2 = 0;

int flag3 = 0;
int flag_inc3 = 0;

int flag_rf = 0;
int flag_rf1 = 0;

//Pin Number of IR and LED
const int IR1 = 7;
const int IR2 = 6;
const int IR3 = 5;

const int LEDG1 = A0;
const int LEDR1 = A1;   

const int LEDG2 = A2;
const int LEDR2 = A3;   

const int LEDG3 = A4;
const int LEDR3 = A5;   

int green1=green_time;    //variable for counting green lights
int green2=0;
int green3=0;

void setup() {

  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println(" Arduino Started - ");

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(LEDG1, OUTPUT);
  pinMode(LEDR1, OUTPUT);
  pinMode(LEDG2, OUTPUT);
  pinMode(LEDR2, OUTPUT);
  pinMode(LEDG3, OUTPUT);
  pinMode(LEDR3, OUTPUT);
}

void loop() {

    currentMillis = millis();
    int IRstatus1 = digitalRead(IR1);
    int IRstatus2 = digitalRead(IR2);
    int IRstatus3 = digitalRead(IR3);
    
    while (getID()) {
      if (tagID == MasterTag) 
      {
        Serial.println(" Emergency Vehicle Detected - ");
        if(!flag_rf1){
          flag_rf = 1;
          previousMillisIR2 = 0;
          previousMillisIR3 = 0;
        }
        flag_rf1 = 1;
      }
      else
      {
        Serial.println("Unrecognized Emergency Vehicle Detected - ");
      }
    }

    //Checking IR
    check_ir(IRstatus1, green1,flag1,flag_inc1,previousMillisIR1,1);
    check_ir(IRstatus2, green2,flag2,flag_inc2,previousMillisIR2,2);
    check_ir(IRstatus3, green3,flag3,flag_inc3,previousMillisIR3,3);

    //Updating Signal timing per seconds
    if(currentMillis - previousMillis >= sec) {
      previousMillis = currentMillis;

      if(green1>0){
          digitalWrite(LEDG1,HIGH);
          digitalWrite(LEDG2,LOW);
          digitalWrite(LEDG3,LOW);

          digitalWrite(LEDR1,LOW);
          digitalWrite(LEDR2,HIGH);
          digitalWrite(LEDR3,HIGH);
  
          --green1;
          Serial.print("Green 1 = ");
          Serial.println(green1);

          if(green1==0){
              flag_rf1 = 0;
              green2 = green_time;
              count=0;
          }
      }
      if(green2>0){
          digitalWrite(LEDG1,LOW);
          digitalWrite(LEDG2,HIGH);
          digitalWrite(LEDG3,LOW);

          digitalWrite(LEDR1,HIGH);
          digitalWrite(LEDR2,LOW);
          digitalWrite(LEDR3,HIGH);

          --green2;
          Serial.print("Green 2 = ");
          Serial.println(green2);

          if(flag_rf && green2 > 3){
            green2 = 3;
            flag_rf = 0;    
          }
          if(green2==0){
              count=0;
              if(flag_rf1){
                green1 = green_time;
              }
              else{
                green3 = green_time;
              }
          }
      }
      if(green3>0){
          digitalWrite(LEDG1,LOW);
          digitalWrite(LEDG2,LOW);
          digitalWrite(LEDG3,HIGH);

          digitalWrite(LEDR1,HIGH);
          digitalWrite(LEDR2,HIGH);
          digitalWrite(LEDR3,LOW);

          --green3;
          Serial.print("Green 3 = ");
          Serial.println(green3);
          if(flag_rf && green3 > 3){
            green3 = 3;
            flag_rf = 0;    
          }
          if(green3==0){
              count=0;
              green1 = green_time;
          }
        }  
    }
}

boolean getID() 
{
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
    return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
  //readCard[i] = mfrc522.uid.uidByte[i];
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}

void check_ir(int& IRstatus,int& green,int& flag,int& flag_inc,unsigned long& previousMillisIR,int lane_no){
    if(count<3 || flag_rf1){
        if(IRstatus == 0 && green != 0){                               // Checking if IR is activated
            if(flag == 0){
                Serial.println("Current time save of IR " + lane_no);
                previousMillisIR = currentMillis;
                flag = 1;
            }
            if((previousMillisIR + IR_time) <= currentMillis){       // Incrementing green light time if IR is activated for IR_time 
                if(flag_inc == 0){
                    green = green + (IR_time/1000);
                    ++count;
                    Serial.print("Green Increment in lane = ");
                    Serial.println(lane_no);
                    Serial.print("Count = ");
                    Serial.println(count);
                    flag_inc = 1;
                    flag = 0;
                }
            }
            else
                flag_inc = 0;
            }
        else
            flag = 0;
  }
}