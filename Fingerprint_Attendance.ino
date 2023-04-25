#include <Wire.h>                                   // Include All Required Libraries 
#include<EEPROM.h>
#include "Adafruit_Fingerprint.h"
#include <SoftwareSerial.h>



SoftwareSerial fingerPrint(2, 3);
uint8_t id;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint);
#define enroll 14
#define del 15
#define match 5
#define indFinger 7
#define buzzer 5
#define records 4                                   // replace number (4) with number of user in system

int user1,user2,user3,user4,user5;                  //put 5 for 5 user
void setup()
{
    delay(1000);
    Serial.begin(9600);
    pinMode(enroll, INPUT_PULLUP);
    pinMode(del, INPUT_PULLUP);
    pinMode(match, INPUT_PULLUP);
    pinMode(buzzer, OUTPUT);
    pinMode(indFinger, OUTPUT);
    digitalWrite(buzzer, LOW);

    if(digitalRead(enroll) == 0)
    {
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);

      Serial.println("Data Downloading");
    }
    if(digitalRead(del) == 0)
    {

       Serial.println("System Reset");
      delay(1000);
    }
    
    Serial.println(" ***Attendance System*** ");
    Serial.println("Best Engg. Project - 2023");
    Serial.println("Project Batch - 8");

  
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
  for(int i=1000;i<1000+records;i++)
  {
    if(EEPROM.read(i) == 0xff)
        EEPROM.write(i,0);
   }
    finger.begin(57600);
    Serial.begin(9600);
    Serial.println("Finding Module");
    delay(1000);
    if (finger.verifyPassword())
    {
      Serial.println("Found fingerprint sensor!");
      delay(1000);
    }
    else
    {
    Serial.println("Did not find fingerprint sensor. Please Check Connections..");

    while (1);
    }
    
    Serial.println("Press Match to ");
    Serial.println("Start System");
    delay(2000);

    user1=EEPROM.read(1000);
    user2=EEPROM.read(1001);
    user3=EEPROM.read(1002); 
    user4=EEPROM.read(1003);
    user5=EEPROM.read(1004);
    
    digitalWrite(indFinger, HIGH);
    
}

// Function To read Input ID
uint8_t readnumber(void) {
  uint8_t num = 0;

  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

void loop()
{

    //Serial.println("     ");
    delay(500);
    int result=getFingerprintIDez();
    if(result>0)
    {
              digitalWrite(indFinger, LOW);
              digitalWrite(buzzer, HIGH);
              delay(100);
              digitalWrite(buzzer, LOW);
              Serial.println("ID:");
              Serial.println(result);
              Serial.println("Waiting...");
              delay(1000);
              attendance(result);
              Serial.println("Attendance Registed Successfully..!");
              delay(1000);
        digitalWrite(indFinger, HIGH);
        return;
 }
 checkKeys();
 delay(300);
}
//     dmyyhms - 7 bytes
void attendance(int id)
{
  int user=0,eepLoc=0;
  if(id == 1)
  {
    eepLoc=0;
    user=user1++;
  }
  else if(id == 2)
  {
    eepLoc=210;
    user=user2++;
  }
  else if(id == 3)
  {
    eepLoc=420;
    user=user3++;
  }
  else if(id == 4)
  {
    eepLoc=630;
    user=user4++;
  }
  /*else if(id == 5)   // if 5th user is used
  {
    eepLoc=840;
    user=user5++;
  }*/
  else 
  return;
  
    int eepIndex=(user*7)+eepLoc;

    EEPROM.write(1000,user1);
    EEPROM.write(1001,user2);
    EEPROM.write(1002,user3);
    EEPROM.write(1003,user4);
  //  EEPROM.write(1004,user5);   // figth user
}

void checkKeys()
{
   if(digitalRead(enroll) == 0)
   {
    //lcd.clear();
    Serial.println("Waiting...");
    delay(1000);
    while(digitalRead(enroll) == 0);
    Enroll();
   }
   else if(digitalRead(del) == 0)
   {
    Serial.println("Waiting...");
    delay(1000);
    delet();
   }
}

// Function To Enroll Finger 

void Enroll()
{
  int count=1;
  Serial.println("Enter Finger ID:");
  id = readnumber();
  getFingerprintEnroll();
  for(int i=0;i<records;i++)
  {
    if(EEPROM.read(i) != 0xff)
    {
      EEPROM.write(i, id);
      break;
    }
  }
}

//Function To delete Existing User Finger

void delet()
{
  int count=1;
  Serial.println("Enter Finger ID");
  id = readnumber();
  deleteFingerprint(id);
  for(int i=0;i<records;i++)
  {
    if(EEPROM.read(i) == id)
    {
      EEPROM.write(i, 0xff);
      break;
    }
  }
}



//Function to convert finger print image to templete

uint8_t getFingerprintEnroll()
{
  int p = -1;
  Serial.println("finger ID:");
  Serial.println(id);
  Serial.println("Place Finger");
  delay(2000);
  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
    switch (p)
    {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No Finger");
      delay(1000);
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success! Converting 1st Image of Finger 

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");

      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // After Capturing 1 st Image of Finger 

  Serial.println("Please Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      return;
    }
  }

  // OK success! If 2 nd time finger enrolled gets Converted
  
  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted! If New Enrolled finger Matches Successfully...

  Serial.print("Creating model for #");  Serial.println(id);
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
    delay(2000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  }
  else {
    Serial.println("Unknown error");
    return p;
  }
}


//Function to compare finger print image with stored IDs for matching

int getFingerprintIDez()
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)
  return -1;
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)
  return -1;
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)
  {
   Serial.println("Finger Not Found Please Try Later..!");
   delay(2000);
  return -1;
  }

  // Matching Id is Found..!

  Serial.print("Found ID\n");
  Serial.print(int(finger.fingerID));
  Serial.print("\n");
  return finger.fingerID;
}


uint8_t deleteFingerprint(uint8_t id)
{
  uint8_t p = -1;
  Serial.println("Delete ID\n");

  p = finger.deleteModel(id);
  Serial.println(id);
  Serial.print("\n");
  Serial.println("Deleting Finger - ");
  Serial.println(id);

  if (p == FINGERPRINT_OK)
  {
    Serial.println("Finger Deleted Successfully..!");
    delay(1000);
  }
  else
  {
    Serial.print("Something Wrong..Please Try Again Later..!");
    delay(2000);
    return p;
  }
}
