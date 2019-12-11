#if ENABLE_SCREEN
void StartupScreen() {

  myGLCD.fillScreen(BLACK);
  myGLCD.setColor(WHITE);
  myGLCD.setBackColor(BLACK);
  myGLCD.setTextSize(2);

  myGLCD.print(_name_, center_x - 110, 80);
  myGLCD.print(_version_, center_x - 15, 105);

  for (uint16_t i = 0; i <= 320; i++) {
    myGLCD.drawLine(i, 160, i, 170);
    delay(3);
  }
  myGLCD.fillScreen(BLACK);

}

void DrawMainMenu() {

myGLCD.setTextSize(2);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 21, 324, 223);


  DrawHeaderFooter("* Menu *", "- Arduino LED Controller -", -10);

  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setTextSize(2);


  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(set_debug_x, set_debug_y, set_debug_rx, set_debug_ry);
  myGLCD.fillRoundRect(set_syncclock_x, set_syncclock_y, set_syncclock_rx, set_syncclock_ry);
  myGLCD.fillRoundRect(set_clear_eeprom_x, set_clear_eeprom_y, set_clear_eeprom_rx, set_clear_eeprom_ry);
  myGLCD.fillRoundRect(set_smoothpwr_x, set_smoothpwr_y, set_smoothpwr_rx, set_smoothpwr_ry);

  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setColor(BLACK);

    myGLCD.print(F("Keyboard"), 70, 40);
    myGLCD.print(F(""), 70, 87);
    myGLCD.print(F(""), 70, 134);
    myGLCD.print(F("Debug Mode"), 70, 181);

}

void DrawHeaderFooter(String header, String footer, int headerOffset) {

  if (!hideHeader) {
    myGLCD.setColor(255, 0, 0);
    myGLCD.fillRect(0, 0, 319, 20);
  }
  myGLCD.setColor(BLACK);
  myGLCD.fillRect(0, 226, 319, 239);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  int centerH = tft.width() / 2 + headerOffset;
  myGLCD.setTextSize(2);
  if (!hideHeader) {
    if (!DEBUG)myGLCD.print(header, centerH, 3);
  }
  myGLCD.setTextSize(1);
  myGLCD.setBackColor(BLACK);
  myGLCD.setColor(255, 255, 0);
  if (!hideFooter || currentPage == "News")myGLCD.print(footer, CENTER, 227);
  myGLCD.setColor(0, 0, 255);

}
void DrawFooter(String footer) {

  myGLCD.setTextSize(1);
  myGLCD.setBackColor(BLACK);
  myGLCD.setColor(BLACK);
  myGLCD.fillRect(1, 224, 324, 240);
  myGLCD.setColor(255, 255, 0);
  if (!hideFooter || currentPage == "News")myGLCD.print(footer, CENTER, 227);

}

void DrawDialogButtonBoxHS(bool fullscreen, String title, String line1, String line2, String main_page, bool large, uint16_t backcolor, String btn_text) {

  myGLCD.setTextSize(1);
  if (fullscreen) {
    myGLCD.fillScr(0, 0, 255);
  }
  myGLCD.setColor(backcolor);
  if (large)myGLCD.fillRoundRect(40, 70, 280, 169);
  else myGLCD.fillRoundRect(80, 70, 239, 169);

  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(backcolor);
  myGLCD.print(title, CENTER, 80);
  myGLCD.print(line1, CENTER, 100);
  myGLCD.print(line2, CENTER, 115);
  myGLCD.fillRoundRect(135, 137, 185, 157);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setColor(backcolor);
  myGLCD.print(btn_text, CENTER, 143);
  if (main_page == "Settings") currentPage = "Settings_Dialog";
  else if (main_page == "Settings2") currentPage = "Settings2_Dialog";
  else if (main_page == "PreBoot") currentPage = "PreBootRTC_Dialog";
  else if (main_page == "") {}
  else currentPage = "Main_Dialog" + String(main_page);

}
void DrawDialogBox(bool fullscreen, String title, String line1, String line2, bool large, uint16_t color) {

  myGLCD.setTextSize(1);
  if (fullscreen) {
    myGLCD.fillScr(0, 0, 255);
  }
  myGLCD.setColor(color);
  if (large)myGLCD.fillRoundRect(40, 70, 280, 169);
  else myGLCD.fillRoundRect(80, 70, 239, 169);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print(title, CENTER, 93);
  myGLCD.print(line1, CENTER, 119);
  myGLCD.print(line2, CENTER, 132);

}

void FastScreenEffect() {

  myGLCD.fillScreen(BLACK);
  myGLCD.fillScreen(RED);
  myGLCD.fillScreen(GREEN);
  myGLCD.fillScreen(BLUE);
  myGLCD.fillScreen(BLACK);

}

void TouchDebug(String mode) {
  if (DEBUG) {

    myGLCD.setTextSize(1);
    myGLCD.setBackColor(255, 0, 0);
    myGLCD.setColor(255, 0, 0);
    if (mode == "CAL") {
      myGLCD.fillRect(0, 2, 199, 10);
      myGLCD.setColor(255, 255, 255);
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.print("CAL x=" + String(pixel_x) + " y=" + String(pixel_y) + " z=" + String(tp.z), 0, 2, 0);
      myGLCD.setBackColor(0, 0, 0);
    }
    else if (mode == "CS") {
      myGLCD.fillRect(0, 11, 119, 20);
      myGLCD.setColor(255, 255, 255);
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.print("CS=" + currentPage, 0, 11, 0);
    }
    else if (mode == "RAM") {
      myGLCD.setColor(255, 255, 255);
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.print("SRAM: " + String( freeMemory()) + "B", 200, 2, 0);
      myGLCD.setBackColor(0, 0, 0);
    }
    else if (mode == "FWT") {
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.setColor(255, 255, 255);
      myGLCD.print("FWT=" + String(footerWebTimer), 120, 11, 0);
      myGLCD.setBackColor(0, 0, 0);
    }
    else {
      myGLCD.fillRect(275, 0, 340, 12);
      myGLCD.setColor(255, 255, 255);
      myGLCD.print(mode, 275, 2, 0);
    }

  }
}

void ScrollRight(bool erase) {
  if (ENABLE_SCROLL) {

    myGLCD.setColor(0, 0, 0);
    for (uint16_t i = 1; i <= 360; i++) {
      myGLCD.vertScroll(0, 360, i);
      if ( (i % 1) == 0 && i < 320 && erase) {
        myGLCD.drawLine(i, 21, i, 224);
        //myGLCD.fillRect(80, 15, i, 220);
      }
    }

  }
}
void ScrollLeft(bool erase) {
  if (ENABLE_SCROLL) {

    myGLCD.setColor(0, 0, 0);
    for (uint16_t i = 360; i >= 1; i--) {
      myGLCD.vertScroll(-1, 360, i);
      if ( (i % 1) == 0 && i < 320 && erase) {
        myGLCD.drawLine(i, 21, i, 224);
        //myGLCD.fillRect(0, 15, 360-i, 220);
      }
    }

  }
}
#endif
