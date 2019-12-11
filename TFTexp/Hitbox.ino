#if ENABLE_SCREEN
/*void CheckSSIDHitbox(int x, int y) {
  selectedSSID = "";
  if (x >= 70 && x <= 70 + 200 && y >= 65 && y <= 84 ) {
    selectedSSID = wifiNames[0];
  } else if (x >= 70 && x <= 70 + 200 && y >= 85 && y <= 104) {
    selectedSSID = wifiNames[1];
  } else if (x >= 70 && x <= 70 + 200 && y >= 105 && y <= 124) {
    selectedSSID = wifiNames[2];
  } else if (x >= 70 && x <= 70 + 200 && y >= 125 && y <= 144) {
    selectedSSID = wifiNames[3];
  } else if (x >= 70 && x <= 70 + 200 && y >= 145 && y <= 164) {
    selectedSSID = wifiNames[4];
  } else if (x >= 70 && x <= 70 + 200 && y >= 165 && y <= 184) {
    selectedSSID = wifiNames[5];
  } else if (x >= 70 && x <= 70 + 200 && y >= 185 && y <= 204) {
    selectedSSID = wifiNames[6];
  } else if (x >= 70 && x <= 70 + 200 && y >= 205 && y <= 224) {
    selectedSSID = wifiNames[7];
  }

  if (selectedSSID != "") {
    myGLCD.fillScreen(BLACK);
    myGLCD.setColor(WHITE);
    myGLCD.setTextSize(2);
    myGLCD.print("Please enter your", 20, 50);
    myGLCD.print("wifi password", 20, 70);
    myGLCD.setColor(ORANGE);
    myGLCD.print(selectedSSID, 20, 100);
    delay(1500);
    currentPage = "Keyboard_Net";
    PrintKeyboard(shiftP);
  }
}*/

void CheckHitbox(int pixel_x, int pixel_y) {
  myGLCD.setColor(0, 0, 0);

  if (currentPage == "Main") {
 

    if (pixel_x >= set_debug_x && pixel_x <= set_debug_rx && pixel_y >= set_debug_y && pixel_y <= set_debug_ry ) {
    PrintKeyboard(false);
    currentPage="Keyboard";
   
      TouchDebug("SETDBG");
    }
    if (pixel_x >= set_clear_eeprom_x && pixel_x <= set_clear_eeprom_rx && pixel_y >= set_clear_eeprom_y && pixel_y <= set_clear_eeprom_ry ) {
     
  
      TouchDebug("SETFTR");
    }
    if (pixel_x >= set_smoothpwr_x && pixel_x <= set_smoothpwr_rx && pixel_y >= set_smoothpwr_y && pixel_y <= set_smoothpwr_ry ) {
DEBUG = !DEBUG;
myGLCD.fillScreen(BLACK);
DrawMainMenu();
      TouchDebug("SETHEAD");
    }
  }

  
  else if (currentPage == "Keyboard") {
    CheckKeyboardHitbox(pixel_x, pixel_y);
  }
  
 
}
#endif
