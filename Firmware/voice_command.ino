#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

VR myVR(2, 3); //rx, tx of vr

Adafruit_PWMServoDriver pwm;

const int numOfFinger = 5;
int fingers[numOfFinger] = {0, 1, 2, 3, 4};


uint8_t records[7]; 
uint8_t buf[64];



#define hallo (0)
#define genggam (10)
#define lepas (1)
#define satu (2)
#define dua (3)
#define tiga (4)
#define empat (5)
#define lima (6)
#define nol (7)
#define wave (8)
#define cubit (9)

void printSignature(uint8_t *buf, int len)
{
  int i;
  for (i = 0; i < len; i++) 
  {
    if (buf[i] > 0x19 && buf[i] < 0x7F) {
      Serial.write(buf[i]);
    }
    else 
    {
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}


void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if (buf[0] == 0xFF) {
    Serial.print("NONE");
  }
  else if (buf[0] & 0x80) {
    Serial.print("UG ");
    Serial.print(buf[0] & (~0x80), DEC);
  }
  else {
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if (buf[3] > 0) {
    printSignature(buf + 4, buf[3]);
  }
  else {
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  //servo driver
  pwm.begin();
  pwm.setPWMFreq(60);
  palmar(0, 180);
  palmar(1, 0);
  palmar(2, 0);
  palmar(3, 180);
  palmar(4, 180);

  //vr
  myVR.begin(9600);

  Serial.begin(115200);
  Serial.println("Voice Controlled Prosthesis");
  delay(500);
  Serial.println("Lab CNC Unila");
  delay(500);
  Serial.println("Budro Gerung");
  

  if (myVR.clear() == 0) {
    Serial.println("Recognizer cleared.");
  } else 
  {
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while (1);
  }

  if(myVR.load((uint8_t)hallo) >= 0){
    Serial.println("hallo");
  }

  if(myVR.load((uint8_t)genggam) >= 0){
    Serial.println("genggam");
  }
  
  if(myVR.load((uint8_t)lepas) >= 0){
    Serial.println("lepas");
  }

   if(myVR.load((uint8_t)satu) >= 0){
    Serial.println("satu");
  }
  
  if(myVR.load((uint8_t)dua) >= 0){
    Serial.println("dua");
  }
  
  if(myVR.load((uint8_t)tiga) >= 0){
    Serial.println("tiga");
  }

  if(myVR.load((uint8_t)empat) >= 0){
    Serial.println("empat");
  }

  if(myVR.load((uint8_t)lima) >= 0){
    Serial.println("lima");
  }

  if(myVR.load((uint8_t)nol) >= 0){
    Serial.println("nol");
  }

  if(myVR.load((uint8_t)wave) >= 0){
    Serial.println("wave");
  }

  if(myVR.load((uint8_t)cubit) >= 0){
    Serial.println("cubit");
  }
}

void loop()
{
 
  int ret;
  ret = myVR.recognize(buf, 50);
  if (ret > 0) 
  {
    switch (buf[1]) 
    {
      case genggam:
        palmar(0, 100);
        palmar(1, 120);
        palmar(2, 160);
        palmar(3, 80);
        palmar(4, 60);
        break;
        
      case lepas:
        palmar(0, 180);
        palmar(1, 0);
        palmar(2, 0);
        palmar(3, 180);
        palmar(4, 180);
        break;

      case satu:
        palmar(0, 60);
        palmar(1, 0);
        palmar(2, 170);
        palmar(3, 100);
        palmar(4, 120);
        break;
        
      case dua:
        palmar(0, 60);
        palmar(1, 0);
        palmar(2, 0);
        palmar(3, 100);
        palmar(4, 120);
        break;
        
      case tiga:
        palmar(0, 60);
        palmar(1, 0);
        palmar(2, 0);
        palmar(3, 180);
        palmar(4, 120);
        break;

      case empat:
        palmar(0, 60);
        palmar(1, 0);
        palmar(2, 0);
        palmar(3, 180);
        palmar(4, 180);
        break;

        
      default:
        palmar(0, 180);
        Serial.println("Record function undefined");
        break;
    }
    
    printVR(buf);
  }
}

void palmar(int i, int angle)
{
  
  int servo = map(angle, 0, 180, 150, 600);
  pwm.setPWM(fingers[i], 0, servo);
  Serial.println(fingers[i]);
  Serial.println(servo);
}
