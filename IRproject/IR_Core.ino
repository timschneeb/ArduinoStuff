void DisplayError() {
  int oldCID = lastColorId;
  if (oldCID == 4 )UpdateLEDbyID(7);
  else UpdateLEDbyID(4);
  delay(500);
  UpdateLEDbyID(oldCID);
}
void DisplayFatalError() {
  int oldCID = lastColorId;
  if (oldCID == 4 )UpdateLEDbyID(7);
  else UpdateLEDbyID(4);
  delay(500);
  UpdateLEDbyID(oldCID);
  delay(500);
  if (oldCID == 4 )UpdateLEDbyID(7);
  else UpdateLEDbyID(4);
  delay(500);
  InstantOff();
  
}
void DisplaySuccess() {
  int oldCID = lastColorId;
  if (oldCID == 5)UpdateLEDbyID(16);
  else UpdateLEDbyID(5);
  delay(500);
  UpdateLEDbyID(oldCID);
}
void PerformPower(char flag, char param) {
    if (String(flag) == "0") TurnOff();
    else if (String(flag) == "1") TurnOn();
    else {
      if (String(param) == "0") {
        if (powerState) {
          irsend.sendNEC( OFF, 32);
          powerState = false;

        } else {
          irsend.sendNEC( ON, 32);
          powerState = true;
        }
      }
      else if (String(param) == "1") {
        if (powerState) TurnOff();
        else TurnOn();
      }
    }
}

void RandomLEDController() {
    int randomValue = random(3, 18);
    if (randomValue != oldrandVal) {
      //if (randomValue!=0)TurnOn();
      UpdateLEDbyID(randomValue);
      oldrandVal = randomValue;
    }
}
void TurnOff() {
    for (int i = 0; i <= 9; i++) {
      irsend.sendNEC( DIM, 32);
    }
    irsend.sendNEC( OFF, 32);
    powerState = false;
}
void TurnOn() {
    irsend.sendNEC( ON, 32);
    for (int i = 0; i <= 9; i++) {
      irsend.sendNEC( BRIGHT, 32);
    }
    powerState = true;
}
void InstantOff(){
    irsend.sendNEC( OFF, 32);  
}
void UpdateLEDbyID(int id) {
    lastColorId = id;
    switch (id) {
      case 1:
        irsend.sendNEC( BRIGHT, 32);
        break;
      case 2:
        irsend.sendNEC( DIM, 32);
        break;
      case 3:
        irsend.sendNEC( WHITE, 32);
        break;
      case 4:
        irsend.sendNEC( RED, 32);
        break;
      case 5:
        irsend.sendNEC( GREEN, 32);
        break;
      case 6:
        irsend.sendNEC( BLUE, 32);
        break;
      case 7:
        irsend.sendNEC( ORANGE, 32);
        break;
      case 8:
        irsend.sendNEC( BLUEGREEN, 32);
        break;
      case 9:
        irsend.sendNEC( ULTRAVIOLET, 32);
        break;
      case 10:
        irsend.sendNEC( YELLOW, 32);
        break;
      case 11:
        irsend.sendNEC( LIGHTTURQUOISE, 32);
        break;
      case 12:
        irsend.sendNEC( LIGHTVIOLET, 32);
        break;
      case 13:
        irsend.sendNEC( YELLOWGREEN, 32);
        break;
      case 14:
        irsend.sendNEC( TURQUOISE, 32);
        break;
      case 15:
        irsend.sendNEC( DARKMAGENTA, 32);
        break;
      case 16:
        irsend.sendNEC( LIGHTGREEN, 32);
        break;
      case 17:
        irsend.sendNEC( LIGHTBLUE, 32);
        break;
      case 18:
        irsend.sendNEC( MAGENTA, 32);
        break;
      case 19:
        irsend.sendNEC( FLASH, 32);
        break;
      case 20:
        irsend.sendNEC( SFLASH, 32);
        break;
      case 21:
        irsend.sendNEC( FADE, 32);
        break;
      case 22:
        irsend.sendNEC( SFADE, 32);
        break;
    }
}
