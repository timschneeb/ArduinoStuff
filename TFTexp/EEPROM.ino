//Address 0x0000 - RTC Sync (Bool)
//        0x0001 - Debug (Bool)
//        0x0002 - Scroll (Bool)
//        0x0003 - Hide Footer (Bool)
//        0x0004 - Hide Header (Bool)
//        0x0005 - Smooth Power (Bool)
//        0x0006 - MAC (char*)
//        0x0022

void ClearRangeEEPROM(int start, int end)
{
  for (int i = start ; i <= end ; i++) {
    EEPROM.write(i, 0);
    if (EEPROM_DEBUG) {
      Serial.print("Clearing Address ");
      Serial.println(String(i));
    }
  }
}

String GetStringEEPROM(int startAddress, int maxLength)
{
  String str;
  for (byte b = startAddress ; b < maxLength + startAddress ; b++) {
    char f = EEPROM.read(b);
    if (EEPROM_DEBUG) {
      Serial.print("Reading ");
      Serial.print(String(f));
      Serial.print(" from Address ");
      Serial.println(String(b));
    }
    str += (f);
    if (String(f) == ">") break;
  }
  if (EEPROM_DEBUG) {
    Serial.print("Decoded String: ");
    Serial.println(str);
  }
  return str;
}

void StoreStringEEPROM(char str[], int address) {
  if (EEPROM_DEBUG) {
    Serial.print(str);
    Serial.print(" - Size: ");
    Serial.print(strlen(str));
    Serial.print(" - Address: ");
    Serial.println(address);
  }
  for (int i = address ; i < strlen(str) + address ; i++)
  {
    EEPROM.write( i, str[i - address] );
    if (EEPROM_DEBUG) {
      Serial.print("Writing ");
      Serial.print(String(str[i - address]));
      Serial.print(" to Address ");
      Serial.println(String(i));
    }
  }
}
bool GetBoolEEPROM(int address) {
  bool b = false;
  EEPROM.get(address, b);
  return b;
}

void StoreBoolEEPROM(bool value, int address) {
  EEPROM.put(address, value);
}

void ClearEEPROM() {
  #if ENABLE_SCREEN
  clearEEPROMAfterDlg = false;
  DrawHeaderFooter(F("* EEPROM *"), F("- Arduino LED Controller -"), -10);
  DrawDialogBox(false, F("Clearing EEPROM..."), F("Please wait"), "",false,RED);
  myGLCD.setColor(WHITE);
  #endif
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
    if((i % 1000)==0)Serial.println("Clearing EEPROM: " + String(i) + "/" + String(EEPROM.length()) + " Bytes");
    #if ENABLE_SCREEN
    if(!powerState)myGLCD.print( String(i) + "/" + String(EEPROM.length()) + " Bytes", 115, 150);
    #endif
  }
  performEEPROMClear = false;
}
