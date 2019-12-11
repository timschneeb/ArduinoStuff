//Address 0x0000 - Knock Enabled (bool)
//        0x0001 - Knock Threshold (int)
//        0x0002

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
void StoreIntEEPROM(int p_address, int p_value)
{
  byte lowByte = ((p_value >> 0) & 0xFF);
  byte highByte = ((p_value >> 8) & 0xFF);

  EEPROM.write(p_address, lowByte);
  EEPROM.write(p_address + 1, highByte);
}
unsigned int GetIntEEPROM(int p_address)
{
     byte lowByte = EEPROM.read(p_address);
     byte highByte = EEPROM.read(p_address + 1);

     return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
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
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
    if((i % 1000)==0)Serial.println("Clearing EEPROM: " + String(i) + "/" + String(EEPROM.length()) + " Bytes");
  }
}
