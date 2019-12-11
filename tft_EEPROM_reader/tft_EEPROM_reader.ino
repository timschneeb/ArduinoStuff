/*
  EEPROM Read

  Reads the value of each byte of the EEPROM and prints it
  to the computer.
  This example code is in the public domain.
*/
#include <MCUFRIEND_kbv.h>
#include <EEPROM.h>
#include <UTFTGLUE.h>
#include "back_bw_norm.c"

const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
MCUFRIEND_kbv tft;
UTFTGLUE myGLCD(0, A2, A1, A3, A4, A0);
int address = 0;
int lcount = 0;
byte value;

void setup()
{
  Serial.begin(9600);
  pinMode(52, OUTPUT);
  digitalWrite(52, HIGH);
  myGLCD.InitLCD();
  myGLCD.setColor(0xFFFF);
  myGLCD.fillScreen(0x0000);
  myGLCD.drawRGBBitmap(320-40, 0, back_bw_norm, 40, 40);
}

void loop()
{
  // read a byte from the current address of the EEPROM
  value = EEPROM.read(address);
  myGLCD.setColor(0x0000);
  myGLCD.fillRect(0, lcount * 10, 320 - 50, lcount * 10 + 10);
  myGLCD.setColor(0xFFFF);

  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.print("\t");
  Serial.print(char(value));
  Serial.println();
  myGLCD.print("0x" + String(int(address)), 0,  lcount * 10);
  myGLCD.print(String(int(value)), 70, lcount * 10);
  myGLCD.print(String(char(value)), 120, lcount * 10);
  myGLCD.print(String(char(address)), 120, lcount * 10);
  
  // advance to the next address of the EEPROM
  address = address + 1;
  lcount = lcount + 1;
  // there are only 512 bytes of EEPROM, from 0 to 511, so if we're
  // on address 512, wrap around to address 0
  if (address == 512)
    address = 0;
  if (lcount > 23) {
    lcount = 0;
    delay(5000);
  }
}
