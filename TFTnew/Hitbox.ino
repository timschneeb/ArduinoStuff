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
    if (pixel_x >= power_x && pixel_x <= power_x + 64 && pixel_y >= power_y && pixel_y <= power_y + 64 ) {
      TouchDebug("PWR");
      if (smoothPower)  SendSerialCommand("PWR", 2, 1,0);
      else  SendSerialCommand("PWR", 2, 0,0);

      delay(500);
    }
    if (pixel_x >= random_x && pixel_x <= random_x + 64 && pixel_y >= random_y && pixel_y <= random_y + 64 ) {
      TouchDebug("RND");
      SendSerialCommand("RND", 3, 0,0);
    }
    if (pixel_x >= color_x && pixel_x <= color_x + 64 && pixel_y >= color_y && pixel_y <= color_y + 64 ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      TouchDebug("COL");
      ScrollRight(true);
      currentPage = "Color";
      DrawColorMenu();
    }
    if (pixel_x >= clock_x && pixel_x <= clock_x + 64 && pixel_y >= clock_y && pixel_y <= clock_y + 64 ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      TouchDebug("CLK");
      ScrollRight(true);
      currentPage = "Clock";
      DrawClockMenu();

    }
    if (pixel_x >= net_x && pixel_x <= net_x + 64 && pixel_y >= net_y && pixel_y <= net_y + 64 ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      TouchDebug("NET");
      ScrollRight(true);
      currentPage = "Net";
      DrawNetMenu();

    }
    if (pixel_x >= settings_x && pixel_x <= settings_x + 64 && pixel_y >= settings_y && pixel_y <= settings_y + 64 ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      TouchDebug("SET");
      ScrollRight(true);
      currentPage = "Settings";
      DrawSettingsMenu(1);

    }
  }
  else if (currentPage == "Color") {
    if (pixel_x >= colback_x && pixel_x <= colback_x + 40 && pixel_y >= colback_y && pixel_y <= colback_y + 40 ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      ScrollLeft(true);
      currentPage = "Main";
      DrawMainMenu();
      TouchDebug("COLBCK");
    }
    if (pixel_x >= red_x && pixel_x <= red_x + 40 && pixel_y >= red_y && pixel_y <= red_y + 40 ) {
      TouchDebug("COLRED");
      SendSerialCommand("RED", 3, 0,0);
    }
    if (pixel_x >= green_x && pixel_x <= green_x + 40 && pixel_y >= green_y && pixel_y <= green_y + 40 ) {
      TouchDebug("COLGRN");
      SendSerialCommand("GRN", 3, 0,0);
    }
    if (pixel_x >= blue_x && pixel_x <= blue_x + 40 && pixel_y >= blue_y && pixel_y <= blue_y + 40 ) {
      TouchDebug("COLBLU");
      SendSerialCommand("BLU", 3, 0,0);
    }
    if (pixel_x >= flash_x && pixel_x <= flash_x + 75 && pixel_y >= flash_y && pixel_y <= flash_y + 40 ) {
      TouchDebug("COLFLA");
      SendSerialCommand("FLA", 3, 0,0);
    }
    if (pixel_x >= orange_x && pixel_x <= orange_x + 40 && pixel_y >= orange_y && pixel_y <= orange_y + 40 ) {
      TouchDebug("COLORA");
      SendSerialCommand("ORA", 3, 0,0);
    }

    if (pixel_x >= bluegreen_x && pixel_x <= bluegreen_x + 40 && pixel_y >= bluegreen_y && pixel_y <= bluegreen_y + 40 ) {
      TouchDebug("COLBGR");
      SendSerialCommand("BGR", 3, 0,0);
    }

    if (pixel_x >= violet_x && pixel_x <= violet_x + 40 && pixel_y >= violet_y && pixel_y <= violet_y + 40 ) {
      TouchDebug("COLVIO");
      SendSerialCommand("VIO", 3, 0,0);
    }

    if (pixel_x >= fade_x && pixel_x <= fade_x + 75 && pixel_y >= fade_y && pixel_y <= fade_y + 40 ) {
      TouchDebug("COLFAD");
      SendSerialCommand("FAD", 3, 0,0);
    }

    if (pixel_x >= yellow_x && pixel_x <= yellow_x + 40 && pixel_y >= yellow_y && pixel_y <= yellow_y + 40 ) {
      TouchDebug("COLYEL");
      SendSerialCommand("YEL", 3, 0,0);
    }

    if (pixel_x >= cyan_x && pixel_x <= cyan_x + 40 && pixel_y >= cyan_y && pixel_y <= cyan_y + 40 ) {
      TouchDebug("COLCYA");
      SendSerialCommand("CYA", 3, 0,0);
    }

    if (pixel_x >= lightviolet_x && pixel_x <= lightviolet_x + 40 && pixel_y >= lightviolet_y && pixel_y <= lightviolet_y + 40 ) {
      TouchDebug("COLLVIO");
      SendSerialCommand("LVI", 3, 0,0);
    }

    if (pixel_x >= strobe_x && pixel_x <= strobe_x + 75 && pixel_y >= strobe_y && pixel_y <= strobe_y + 40 ) {
      TouchDebug("COLAIR");
      SendSerialCommand("STR", 3, 0,0);
    }

    if (pixel_x >= brightnessup_x && pixel_x <= brightnessup_x + 40 && pixel_y >= brightnessup_y && pixel_y <= brightnessup_y + 40 ) {
      TouchDebug("COLBUP");
      SendSerialCommand("BUP", 3, 0,0);
    }
    if (pixel_x >= white_x && pixel_x <= white_x + 40 && pixel_y >= white_y && pixel_y <= white_y + 40 ) {
      TouchDebug("COLRWHI");
      SendSerialCommand("WHI", 3, 0,0);
    }
    if (pixel_x >= brightnessdown_x && pixel_x <= brightnessdown_x + 40 && pixel_y >= brightnessdown_y && pixel_y <= brightnessdown_y + 40 ) {
      TouchDebug("COLBDN");
      SendSerialCommand("BDN", 3, 0,0);

    }
    if (pixel_x >= rand_x && pixel_x <= rand_x + 75 && pixel_y >= rand_y && pixel_y <= rand_y + 40 ) {
      TouchDebug("COLRND");
      SendSerialCommand("RND", 3, 0,0);
    }



  }
  else if (currentPage == "Main_Dialog1") {
    if (pixel_x >= hs_dialog_x && pixel_x <= hs_dialog_rx && pixel_y >= hs_dialog_y && pixel_y <= hs_dialog_ry ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      currentPage = "Main";
      DrawMainMenu();
      TouchDebug("DLG_OK");
    }
  }
  else if (currentPage == "Net_Scan") {

    if (pixel_x >= netback_x && pixel_x <= netback_x + 40 && pixel_y >= netback_y && pixel_y <= netback_y + 40 ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      ScrollLeft(true);
      currentPage = "Net";
      DrawNetMenu();
      TouchDebug("NSCANBCK");

    }
    if (pixel_x >= netback_x && pixel_x <= netback_x + 40 && pixel_y >= netback_y + 50 && pixel_y <= netback_y + 90 ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      DrawScanMenu();
      TouchDebug("RESCAN");

    }
    //CheckSSIDHitbox(pixel_x, pixel_y);
  }
  else if (currentPage == "Keyboard_Net") {
    CheckKeyboardHitbox(pixel_x, pixel_y);
  }
  else if (currentPage == "EEPROM_View") {
    
    currentPage = "Net";
    myGLCD.fillScreen(BLACK);
    
    DrawNetMenu();
  }
  else if (currentPage == "Net") {

    if (pixel_x >= netback_x && pixel_x <= netback_x + 40 && pixel_y >= netback_y && pixel_y <= netback_y + 40 ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      ScrollLeft(true);
      currentPage = "Main";
      DrawMainMenu();
      TouchDebug("NETBCK");

    }
    if (pixel_x >= net_scan_x && pixel_x <= net_scan_rx && pixel_y >= net_scan_y && pixel_y <= net_scan_ry ) {
      ScrollRight(true);
      currentPage = "Net_Scan";
      DrawScanMenu();
      TouchDebug("NETSCAN");
    }
    if (pixel_x >= net_rst_x && pixel_x <= net_rst_rx && pixel_y >= net_rst_y && pixel_y <= net_rst_ry ) {
      TouchDebug("NETRST");
      currentPage = "Net_Dialog";
      
      myGLCD.setColor(BLACK);
      myGLCD.fillRect(1, 21, 324, 223);

      //ESPBoot(1, 23);

      currentPage = "Net";
      myGLCD.setColor(BLACK);
      myGLCD.fillRect(1, 21, 324, 223);
      
      DrawNetMenu();
    }
    if (pixel_x >= net_rom_x && pixel_x <= net_rom_rx && pixel_y >= net_rom_y && pixel_y <= net_rom_ry ) {
      currentPage = "EEPROM_View";
      
      myGLCD.fillScreen(BLACK);
      DrawEEPROMViewer();
      
      TouchDebug("NETRVW");
    }
  }
  else if (currentPage == "Settings") {

    if (pixel_x >= setback_x && pixel_x <= setback_x + 40 && pixel_y >= setback_y && pixel_y <= setback_y + 40 ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      ScrollLeft(true);
      currentPage = "Main";
      DrawMainMenu();
      TouchDebug("SETBCK");

    }
    if (pixel_x >= setpgnext_x && pixel_x <= setpgnext_x + 32 && pixel_y >= setpgnext_y && pixel_y <= setpgnext_y + 32 ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      currentPage = "Settings2";
      DrawSettingsMenu(2);
      TouchDebug("SETNXT");

    }

    if (pixel_x >= set_debug_x && pixel_x <= set_debug_rx && pixel_y >= set_debug_y && pixel_y <= set_debug_ry ) {
      //Disable Serial in Clients
      SendSerialCommand("STO", 0, 0,0);
      DrawDialogButtonBoxHS(false, "Serial Communiation", "The device has been disabled", "Reset it before communicating again", "Settings2", true, BLUE, "OK");
      TouchDebug("SETSER");
    }
    if (pixel_x >= set_syncclock_x && pixel_x <= set_syncclock_rx && pixel_y >= set_syncclock_y && pixel_y <= set_syncclock_ry ) {
      StoreBoolEEPROM(true, 0);
      DrawDialogButtonBoxHS(false, "Sync RTC Clock (WIP)", "Please update the sketch ", "from a PC to continue", "Settings", true, BLUE, "CANCEL");
      doCancelRTCAfterDlg = true;
      TouchDebug("SETRTC");
    }
    if (pixel_x >= set_clear_eeprom_x && pixel_x <= set_clear_eeprom_rx && pixel_y >= set_clear_eeprom_y && pixel_y <= set_clear_eeprom_ry ) {
      DrawDialogButtonBoxHS(false, "Clear EEPROM", "This will delete all saved data!", "Press OK to continue.", "Settings", true, RED, "OK");
      clearEEPROMAfterDlg = true;
      TouchDebug("SETCLR_E");
    }
    if (pixel_x >= set_smoothpwr_x && pixel_x <= set_smoothpwr_rx && pixel_y >= set_smoothpwr_y && pixel_y <= set_smoothpwr_ry ) {
      if (smoothPower) {
        smoothPower = false;
        DrawDialogButtonBoxHS(false, "Settings", "Smooth Power", "been disabled!", "Settings", false, RED, "OK");
        StoreBoolEEPROM(false, 5);
      }
      else {
        smoothPower = true;
        DrawDialogButtonBoxHS(false, "Settings", "Smooth Power", "been enabled!", "Settings", false, RED, "OK");
        StoreBoolEEPROM(true, 5);
      }
      TouchDebug("SETSMP");
    }
  }
  else if (currentPage == "Settings2") {

    if (pixel_x >= setback_x && pixel_x <= setback_x + 40 && pixel_y >= setback_y && pixel_y <= setback_y + 40 ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      ScrollLeft(true);
      currentPage = "Main";
      DrawMainMenu();
      TouchDebug("SETBCK");

    }
    if (pixel_x >= setpgnext_x && pixel_x <= setpgnext_x + 32 && pixel_y >= setpgnext_y && pixel_y <= setpgnext_y + 32 ) {
      //PrevPG
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      currentPage = "Settings";
      DrawSettingsMenu(1);
      TouchDebug("SETPREV");

    }

    if (pixel_x >= set_debug_x && pixel_x <= set_debug_rx && pixel_y >= set_debug_y && pixel_y <= set_debug_ry ) {
      //Toggle Debug
      if (DEBUG) {
        DEBUG = false;
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(0, 0, 319, 20);
        DrawDialogButtonBoxHS(false, "Debug", "Debug mode has", "been disabled!", "Settings", false, RED, "OK");
        StoreBoolEEPROM(false, 1);
      }
      else {
        DEBUG = true;
        DrawDialogButtonBoxHS(false, "Debug", "Debug mode has", "been enabled!", "Settings", false, RED, "OK");
        StoreBoolEEPROM(true, 1);
      }
      TouchDebug("SETDBG");
    }
    if (pixel_x >= set_syncclock_x && pixel_x <= set_syncclock_rx && pixel_y >= set_syncclock_y && pixel_y <= set_syncclock_ry ) {
      //Set Borders
      if (ENABLE_SCROLL) {
        ENABLE_SCROLL = false;
        
        myGLCD.fillRect(1, 21, 324, 223);
        
        DrawDialogButtonBoxHS(false, "Settings", "Scroll has", "been disabled!", "Settings2", false, RED, "OK");
        StoreBoolEEPROM(false, 2);
      }
      else {
        ENABLE_SCROLL = true;
        DrawDialogButtonBoxHS(false, "Settings", "Scroll has", "been enabled!", "Settings2", false, RED, "OK");
        StoreBoolEEPROM(true, 2);
      }
      TouchDebug("SETSCR");
    }
    if (pixel_x >= set_clear_eeprom_x && pixel_x <= set_clear_eeprom_rx && pixel_y >= set_clear_eeprom_y && pixel_y <= set_clear_eeprom_ry ) {
      //Set Footer
      if (hideFooter) {
        hideFooter = false;
        
        myGLCD.fillRect(1, 21, 324, 223);
        
        DrawDialogButtonBoxHS(false, "Settings", "Footer has", "been enabled!", "Settings2", false, RED, "OK");
        StoreBoolEEPROM(false, 3);
      }
      else {
        hideFooter = true;
        DrawDialogButtonBoxHS(false, "Settings", "Footer has", "been disabled!", "Settings2", false, RED, "OK");
        StoreBoolEEPROM(true, 3);
      }
      TouchDebug("SETFTR");
    }
    if (pixel_x >= set_smoothpwr_x && pixel_x <= set_smoothpwr_rx && pixel_y >= set_smoothpwr_y && pixel_y <= set_smoothpwr_ry ) {
      //Set Header
      if (hideHeader) {
        hideHeader = false;
        
        myGLCD.fillRect(1, 21, 324, 223);
        
        DrawDialogButtonBoxHS(false, "Settings", "Header has", "been enabled!", "Settings2", false, RED, "OK");
        StoreBoolEEPROM(false, 4);
      }
      else {
        myGLCD.setColor(BLACK);
        myGLCD.fillRect(0, 0, 320, 21);
        hideHeader = true;
        DrawDialogButtonBoxHS(false, "Settings", "Header has", "been disabled!", "Settings2", false, RED, "OK");
        StoreBoolEEPROM(true, 4);

      }
      TouchDebug("SETHEAD");
    }
  }
  else if (currentPage == "Settings_Dialog") {
    if (pixel_x >= hs_dialog_x && pixel_x <= hs_dialog_rx && pixel_y >= hs_dialog_y && pixel_y <= hs_dialog_ry ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      if (doCancelRTCAfterDlg) {
        StoreBoolEEPROM(false, 0);
        doCancelRTCAfterDlg = false;
      }
      if (clearEEPROMAfterDlg) ClearEEPROM();
      currentPage = "Settings";
      DrawSettingsMenu(1);
      TouchDebug("DLGS_OK");
    }
  }
  else if (currentPage == "Settings2_Dialog") {
    if (pixel_x >= hs_dialog_x && pixel_x <= hs_dialog_rx && pixel_y >= hs_dialog_y && pixel_y <= hs_dialog_ry ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      currentPage = "Settings2";
      DrawSettingsMenu(2);
      TouchDebug("DLGS2_OK");
    }
  }
  else if (currentPage == "PreBootRTC_Dialog") {
    if (pixel_x >= hs_dialog_x && pixel_x <= hs_dialog_rx && pixel_y >= hs_dialog_y && pixel_y <= hs_dialog_ry ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      preBootRTC = false;
      currentPage = "Main";
      TouchDebug("PBRTC_OK");
      FastScreenEffect();
      ScrollRight(true);
      DrawMainMenu();
    }
  }
  else if (currentPage == "Clock") {
    if (pixel_x >= clockback_x && pixel_x <= clockback_x + 40 && pixel_y >= clockback_y && pixel_y <= clockback_y + 40 ) {
      
      myGLCD.fillRect(1, 21, 324, 223);
      
      ScrollLeft(true);
      currentPage = "Main";
      DrawMainMenu();
      TouchDebug("CLKBCK");

    }
  }
}
#endif
