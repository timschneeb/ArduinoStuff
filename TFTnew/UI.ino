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
  
  DrawHeaderFooter("* Menu *", "- Arduino LED Controller -", -10);
  myGLCD.setColor(WHITE);
  myGLCD.setBackColor(BLACK);
  myGLCD.setTextSize(2);
  
  myGLCD.drawRGBBitmap(power_x, power_y, powerbmp, 64, 64);
  myGLCD.drawRGBBitmap(color_x, color_y, color, 64, 64);
  myGLCD.drawRGBBitmap(random_x, random_y, random_bmp, 64, 64);
  myGLCD.drawRGBBitmap(net_x, net_y, net, 64, 64);
  myGLCD.drawRGBBitmap(clock_x, clock_y, clock_bmp, 64, 64);
  myGLCD.drawRGBBitmap(settings_x, settings_y, settings, 64, 64);
 

  if (DEBUG) {
    myGLCD.drawRect(power_x, power_y, power_x + 64, power_y + 64);
    myGLCD.drawRect(color_x, color_y, color_x + 64, color_y + 64);
    myGLCD.drawRect(random_x, random_y, random_x + 64, random_y + 64);
    myGLCD.drawRect(net_x, net_y, net_x + 64, net_y + 64);
    myGLCD.drawRect(clock_x, clock_y, clock_x + 64, clock_y + 64);
    myGLCD.drawRect(settings_x, settings_y, settings_x + 64, settings_y + 64);
  }
  
}

void DrawEEPROMViewer() {
  if(!ENABLE_EEPROMVIEWER) DrawDialogButtonBoxHS(false, "Security", F("This EEPROM Viewer feature"), F("has been disabled"), "", true, BLUE, "Back");
  else myGLCD.drawRGBBitmap(320 - 40, 0, back_bw_norm, 40, 40);
  address = 0;
  lcount = 0;
}
void UpdateEEPROMViewer() {
  if (ENABLE_EEPROMVIEWER) {
    myGLCD.setTextSize(1);
    address_value = EEPROM.read(address);
    myGLCD.setColor(0x0000);
    myGLCD.fillRect(0, lcount * 10, 320 - 50, lcount * 10 + 10);
    myGLCD.setColor(0xFFFF);

    Serial.print(address);
    Serial.print("\t");
    Serial.print(address_value, DEC);
    Serial.print("\t");
    Serial.print(char(address_value));
    Serial.println();
    myGLCD.print("0x" + String(int(address)), 0,  lcount * 10);
    myGLCD.print(String(int(address_value)), 70, lcount * 10);
    myGLCD.print(String(char(address_value)), 120, lcount * 10);

    address = address + 1;
    lcount = lcount + 1;
    if (address == _EEPROMSIZE_)
      address = 0;
    if (lcount > 23) {
      lcount = 0;
      delay(1500);
    }
  }
}

void UpdateClockApp() {
  
  myGLCD.setBackColor(BLACK);
  myGLCD.setColor(255, 255, 255);


  Time t = rtc.time();
  String hr = String(t.hr);
  String min = String(t.min);
  String sec = String(t.sec);
  float hu = dht.readHumidity();
  float temp = dht.readTemperature();

  if (hr == "27" || min == "165" || sec == "85") {
    myGLCD.setTextSize(2);
    myGLCD.print("RTC disconnected", 70, 70);
  } else {
    myGLCD.setTextSize(4);
    if (hr.length() == 1) {
      hr = "0" + hr;
    }
    if (min.length() == 1) {
      min = "0" + min;
    }
    if (sec.length() == 1) {
      sec = "0" + sec;
    }
    myGLCD.print(" " + hr + ":" + min + ":" + sec + " ", 53, 70);
    myGLCD.setTextSize(2);
    myGLCD.print(String(t.date) + "." + String(t.mon) + "." + String(t.yr), 110, 120);


  }
  myGLCD.setTextSize(2);
  if (isnan(temp) || isnan(hu) || (int)hu == 0)myGLCD.print(F("DHT disconnected"), 70, 160);
  else myGLCD.print("    " + String((int)temp) + String(char(int(9))) + "C - " + String((int)hu) + "%    ", 60, 160);
  Serial.print(String(char(int(9))));
  
}

void DrawColorMenu() {
  
  myGLCD.setTextSize(2);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 21, 324, 223);
  DrawHeaderFooter(F("* Colors *"), F("- Arduino LED Controller -"), -25);

  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawRGBBitmap(netback_x, netback_y, back_bw_norm, 40, 40);
  myGLCD.setTextSize(2);



  myGLCD.setColor(RED);
  myGLCD.fillRoundRect(red_x , red_y, red_rx, red_ry);

  myGLCD.setColor(TFT_GREEN);
  myGLCD.fillRoundRect(green_x , green_y, green_rx, green_ry);

  myGLCD.setColor(TFT_BLUE);
  myGLCD.fillRoundRect(blue_x , blue_y, blue_rx, blue_ry);

  myGLCD.setColor(WHITE);
  myGLCD.fillRoundRect(flash_x , flash_y, flash_rx, flash_ry);
  myGLCD.setColor(BLACK);
  myGLCD.print("Flash", 222, 40);

  myGLCD.setColor(ORANGE);
  myGLCD.fillRoundRect(orange_x , orange_y, orange_rx, orange_ry);

  myGLCD.setColor(TFT_BLUEGREEN);
  myGLCD.fillRoundRect(bluegreen_x , bluegreen_y, bluegreen_rx, bluegreen_ry);

  myGLCD.setColor(TFT_VIOLET);
  myGLCD.fillRoundRect(violet_x , violet_y, violet_rx, violet_ry);

  myGLCD.setColor(WHITE);
  myGLCD.fillRoundRect(fade_x , fade_y, fade_rx, fade_ry);
  myGLCD.setColor(BLACK);
  myGLCD.print("Fade", 222, 88);


  myGLCD.setColor(YELLOW);
  myGLCD.fillRoundRect(yellow_x , yellow_y, yellow_rx, yellow_ry);

  myGLCD.setColor(TFT_LIGHTBLUE);
  myGLCD.fillRoundRect(cyan_x , cyan_y, cyan_rx, cyan_ry);

  myGLCD.setColor(TFT_LIGHTVIOLET);
  myGLCD.fillRoundRect(lightviolet_x , lightviolet_y, lightviolet_rx, lightviolet_ry);

  myGLCD.setColor(WHITE);
  myGLCD.fillRoundRect(strobe_x , strobe_y, strobe_rx, strobe_ry);
  myGLCD.setColor(BLACK);
  myGLCD.print("Strobe", 222, strobe_y + 12);


  myGLCD.setColor(WHITE);
  myGLCD.fillRoundRect(brightnessup_x , brightnessup_y, brightnessup_rx, brightnessup_ry);
  myGLCD.drawRGBBitmap(brightnessup_x + 8, brightnessup_y + 8, arrow_up_24x24_black, 24, 24);


  myGLCD.fillRoundRect(white_x , white_y, white_rx, white_ry);
  myGLCD.fillRoundRect(brightnessdown_x , brightnessdown_y, brightnessdown_rx, brightnessdown_ry);
  myGLCD.drawRGBBitmap(brightnessdown_x + 8, brightnessdown_y + 8, arrow_down_24x24_black, 24, 24);
  myGLCD.fillRoundRect(rand_x , rand_y, rand_rx, rand_ry);

  myGLCD.setColor(BLACK);
  myGLCD.print("Rand", 222, rand_y + 12);
  

}


void DrawClockMenu() {
  
  myGLCD.setTextSize(2);
  unsigned long M = 1000000;
  unsigned int k = 1000;
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 21, 324, 223);
  DrawHeaderFooter(F("* Clock *"), F("- Arduino LED Controller -"), -15);

  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawRGBBitmap(clockback_x, clockback_y, back_bw_norm, 40, 40);

  UpdateClockApp();

  myGLCD.setTextSize(1);
  
}
void DrawSettingsMenu(int page) {
  
  myGLCD.setTextSize(2);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 21, 324, 223);
  DrawHeaderFooter(F("* Settings *"), F("- Arduino LED Controller -"), -30);

  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawRGBBitmap(setback_x, setback_y, back_bw_norm, 40, 40);
  myGLCD.setTextSize(2);


  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(set_debug_x, set_debug_y, set_debug_rx, set_debug_ry);
  myGLCD.fillRoundRect(set_syncclock_x, set_syncclock_y, set_syncclock_rx, set_syncclock_ry);
  myGLCD.fillRoundRect(set_clear_eeprom_x, set_clear_eeprom_y, set_clear_eeprom_rx, set_clear_eeprom_ry);
  myGLCD.fillRoundRect(set_smoothpwr_x, set_smoothpwr_y, set_smoothpwr_rx, set_smoothpwr_ry);

  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setColor(BLACK);

  if (page == 1) {
    myGLCD.drawRGBBitmap(setpgnext_x, setpgnext_y, arrow_down_32x32, 32, 32);
    myGLCD.print(F("Disable Serial Dev."), 70, 40);
    myGLCD.print(F("Sync RTC with PC"), 70, 87);
    myGLCD.print(F("Clear EEPROM"), 70, 134);
    myGLCD.print(F("Smooth Power"), 70, 181);
  }
  else if (page == 2) {
    myGLCD.drawRGBBitmap(setpgnext_x, setpgnext_y, arrow_up_32x32, 32, 32);
    myGLCD.print(F("Toggle Debug Mode"), 70, 40);
    myGLCD.print(F("Toggle Scroll"), 70, 87);
    myGLCD.print(F("Toggle Footer"), 70, 134);
    myGLCD.print(F("Toggle Header"), 70, 181);
  }
  
}
void DrawNetMenu() {
  
  myGLCD.setTextSize(2);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 21, 324, 223);
  DrawHeaderFooter(F("* Network *"), F("- Arduino LED Controller -"), -30);

  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawRGBBitmap(netback_x, netback_y, back_bw_norm, 40, 40);
  myGLCD.setTextSize(2);

  myGLCD.setColor(WHITE);
  myGLCD.fillRoundRect(net_scan_x , net_scan_y, net_scan_rx, net_scan_ry);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setColor(BLACK);
  myGLCD.print(F("Network Scan"), 70, 40);

  myGLCD.setColor(WHITE);
  myGLCD.fillRoundRect(net_rst_x , net_rst_y, net_rst_rx, net_rst_ry);
  myGLCD.setBackColor(WHITE);
  myGLCD.setColor(BLACK);
  myGLCD.print(F("Reboot ESP"), 70, 87);

  myGLCD.setColor(WHITE);
  myGLCD.fillRoundRect(net_rom_x , net_rom_y, net_rom_rx, net_rom_ry);
  myGLCD.setBackColor(WHITE);
  myGLCD.setColor(BLACK);
  myGLCD.print(F("EEPROM Viewer"), 70, 134);

  
}
void DrawScanMenu() {
  
  myGLCD.setTextSize(2);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(1, 21, 324, 223);
  DrawHeaderFooter(F("* Scan *"), F("- Arduino LED Controller -"), -15);

  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawRGBBitmap(netback_x, netback_y, back_bw_norm, 40, 40);
  myGLCD.drawRGBBitmap(netback_x, netback_y + 50, reload , 40, 32);
  myGLCD.setTextSize(2);


/*  myGLCD.print("Scanning...", 70, 30);
  String rpl = sendCommand("AT+CWLAP\r\n", 3000, DEBUG);
  Serial.println(rpl);

  int countNames = 0;
  for (int i = 0; i <= 28; i++) {
    String dec =  midString(rpl, "\"", "\"");
    if (i % 4 == 0) {
      wifiNames[countNames] = dec;
      countNames++;
    }
  }
  myGLCD.print("Select a network", 70, 30);
  myGLCD.fillRect(70, 55, 280, 56);
  myGLCD.print(wifiNames[0], 70, 65);
  myGLCD.print(wifiNames[1], 70, 85);
  myGLCD.print(wifiNames[2], 70, 105);
  myGLCD.print(wifiNames[3], 70, 125);
  myGLCD.print(wifiNames[4], 70, 145);
  myGLCD.print(wifiNames[5], 70, 165);
  myGLCD.print(wifiNames[6], 70, 185);
  myGLCD.print(wifiNames[7], 70, 205);


  midString("", "", ""); //Reset midstring
  */
  
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
  else if (main_page == ""){}
  else currentPage = "Main_Dialog" + String(main_page);
  
}
void DrawDialogBox(bool fullscreen, String title, String line1, String line2,bool large, uint16_t color) {
  
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
