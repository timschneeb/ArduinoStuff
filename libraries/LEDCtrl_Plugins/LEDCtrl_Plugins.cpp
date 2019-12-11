/*
  LEDCtrl_Plugins.cpp - Library for Arduino LED Controller.
  Created by TheBone_, November 1, 2018.
*/

#include "Arduino.h"
#include <EEPROM.h>
#include "LEDCtrl_Plugins.h"
#include <DS1302.h>

#define SERIAL_DELAY 250


String midString(String str, String start, String finish, bool resetIndex) {
  if (resetIndex)locFinish = 0;
  locStart = str.indexOf(start, locFinish);
  if (locStart == -1) return "";
  locStart += start.length();
  locFinish = str.indexOf(finish, locStart);
  if (locFinish == -1) return "";
  return str.substring(locStart, locFinish);
}

void ClearRangeEEPROM(int start, int end)
{
  for (int i = start ; i <= end ; i++) {
    EEPROM.write(i, 0);
    Serial.print("Clearing Address ");
    Serial.println(String(i));
  }
}

String GetStringEEPROM(int startAddress, int maxLength)
{
  String str;
  for (byte b = startAddress ; b < maxLength + startAddress ; b++) {
    char f = EEPROM.read(b);
    Serial.print("Reading ");
    Serial.print(String(f));
    Serial.print(" from Address ");
    Serial.println(String(b));
    str += (f);
    if (String(f) == ">") break;
  }
  Serial.print("Decoded String: ");
  Serial.println(str);
  return str;
}

void StoreStringEEPROM(char str[], int address) {
  Serial.print(str);
  Serial.print(" - Size: ");
  Serial.print(strlen(str));
  Serial.print(" - Address: ");
  Serial.println(address);
  for (int i = address ; i < strlen(str) + address ; i++)
  {
    EEPROM.write( i, str[i - address] );
    Serial.print("Writing ");
    Serial.print(String(str[i - address]));
    Serial.print(" to Address ");
    Serial.println(String(i));
  }
}
void SendSerialCommand(char cmd[3], int flag, int param) {
  String packet = "<" + String(flag) + String(cmd[0]) + String(cmd[1]) + String(cmd[2]) + String(param) + ">";

  char* cString = (char*) malloc(sizeof(char) * (packet.length() + 1));
  packet.toCharArray(cString, packet.length() + 1);
  Serial1.write(cString);
  Serial.println(cString);
  delay(SERIAL_DELAY);
}

void SyncRTC(DS1302 rtc, int secondsOffset) {
  rtc.writeProtect(false);
  rtc.halt(false);

  int h, m, s, y, mo, d;
  char* sTime = strtok(__TIME__, ":");
  int countT = 0;
  while (sTime != NULL) {
    int a = atoi(sTime);
    if (countT == 0) h = a;
    else if (countT == 1) m = a;
    else if (countT == 2) s = a;
    sTime = strtok(NULL, ":");
    countT++;
  }
  countT = 0;

  char* sDate = strtok(__DATE__, "  ");
  int countD = 0;
  while (sDate != NULL) {
    if (countD == 0) {
      String s = String(sDate);
      if (s == "Jan") mo = 1;
      else if (s == "Feb") mo = 2;
      else if (s == "Mar") mo = 3;
      else if (s == "Apr") mo = 4;
      else if (s == "May") mo = 5;
      else if (s == "Jun") mo = 6;
      else if (s == "Jul") mo = 7;
      else if (s == "Aug") mo = 8;
      else if (s == "Sep") mo = 9;
      else if (s == "Oct") mo = 10;
      else if (s == "Nov") mo = 11;
      else if (s == "Dec") mo = 12;
    }
    else if (countD == 1) d = atoi(sDate);
    else if (countD == 2) y = atoi(sDate);
    sDate = strtok (NULL, " ");
    countD++;
  }
  countD = 0;

  Time t(y, mo, d, h, m, s + secondsOffset, Time::kSunday);

  rtc.time(t);
}







void CheckHitbox(int pixel_x, int pixel_y) {
  myGLCD.setColor(0, 0, 0);

  if (currentPage == "Main") {
    if (pixel_x >= power_x && pixel_x <= power_x + 64 && pixel_y >= power_y && pixel_y <= power_y + 64 ) {
      TouchDebug("PWR");
      if (smoothPower) plg.SendSerialCommand("PWR", 2, 1);
      else plg.SendSerialCommand("PWR", 2, 0);

      delay(500);
    }
    if (pixel_x >= random_x && pixel_x <= random_x + 64 && pixel_y >= random_y && pixel_y <= random_y + 64 ) {
      TouchDebug("RND");
      plg.SendSerialCommand("RND", 3, 0);
    }
    if (pixel_x >= color_x && pixel_x <= color_x + 64 && pixel_y >= color_y && pixel_y <= color_y + 64 ) {
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      TouchDebug("COL");
      ScrollRight(true);
      currentPage = "Color";
      DrawColorMenu();
    }
    if (pixel_x >= clock_x && pixel_x <= clock_x + 64 && pixel_y >= clock_y && pixel_y <= clock_y + 64 ) {
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      TouchDebug("CLK");
      ScrollRight(true);
      currentPage = "Clock";
      DrawClockMenu();

    }
    if (pixel_x >= net_x && pixel_x <= net_x + 64 && pixel_y >= net_y && pixel_y <= net_y + 64 ) {
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      TouchDebug("NET");
      ScrollRight(true);
      currentPage = "Net";
      DrawNetMenu();

    }
    if (pixel_x >= settings_x && pixel_x <= settings_x + 64 && pixel_y >= settings_y && pixel_y <= settings_y + 64 ) {
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      TouchDebug("SET");
      ScrollRight(true);
      currentPage = "Settings";
      DrawSettingsMenu(1);

    }
  }
  else if (currentPage == "Color") {
    if (pixel_x >= colback_x && pixel_x <= colback_x + 40 && pixel_y >= colback_y && pixel_y <= colback_y + 40 ) {
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      ScrollLeft(true);
      currentPage = "Main";
      DrawMainMenu();
      TouchDebug("COLBCK");
    }
    if (pixel_x >= red_x && pixel_x <= red_x + 40 && pixel_y >= red_y && pixel_y <= red_y + 40 ) {
      TouchDebug("COLRED");
      plg.SendSerialCommand("RED", 3, 0);
    }
    if (pixel_x >= green_x && pixel_x <= green_x + 40 && pixel_y >= green_y && pixel_y <= green_y + 40 ) {
      TouchDebug("COLGRN");
      plg.SendSerialCommand("GRN", 3, 0);
    }
    if (pixel_x >= blue_x && pixel_x <= blue_x + 40 && pixel_y >= blue_y && pixel_y <= blue_y + 40 ) {
      TouchDebug("COLBLU");
      plg.SendSerialCommand("BLU", 3, 0);
    }
    if (pixel_x >= flash_x && pixel_x <= flash_x + 75 && pixel_y >= flash_y && pixel_y <= flash_y + 40 ) {
      TouchDebug("COLFLA");
      plg.SendSerialCommand("FLA", 3, 0);
    }
    if (pixel_x >= orange_x && pixel_x <= orange_x + 40 && pixel_y >= orange_y && pixel_y <= orange_y + 40 ) {
      TouchDebug("COLORA");
      plg.SendSerialCommand("ORA", 3, 0);
    }

    if (pixel_x >= bluegreen_x && pixel_x <= bluegreen_x + 40 && pixel_y >= bluegreen_y && pixel_y <= bluegreen_y + 40 ) {
      TouchDebug("COLBGR");
      plg.SendSerialCommand("BGR", 3, 0);
    }

    if (pixel_x >= violet_x && pixel_x <= violet_x + 40 && pixel_y >= violet_y && pixel_y <= violet_y + 40 ) {
      TouchDebug("COLVIO");
      plg.SendSerialCommand("VIO", 3, 0);
    }

    if (pixel_x >= fade_x && pixel_x <= fade_x + 75 && pixel_y >= fade_y && pixel_y <= fade_y + 40 ) {
      TouchDebug("COLFAD");
      plg.SendSerialCommand("FAD", 3, 0);
    }

    if (pixel_x >= yellow_x && pixel_x <= yellow_x + 40 && pixel_y >= yellow_y && pixel_y <= yellow_y + 40 ) {
      TouchDebug("COLYEL");
      plg.SendSerialCommand("YEL", 3, 0);
    }

    if (pixel_x >= cyan_x && pixel_x <= cyan_x + 40 && pixel_y >= cyan_y && pixel_y <= cyan_y + 40 ) {
      TouchDebug("COLCYA");
      plg.SendSerialCommand("CYA", 3, 0);
    }

    if (pixel_x >= lightviolet_x && pixel_x <= lightviolet_x + 40 && pixel_y >= lightviolet_y && pixel_y <= lightviolet_y + 40 ) {
      TouchDebug("COLLVIO");
      plg.SendSerialCommand("LVI", 3, 0);
    }

    if (pixel_x >= strobe_x && pixel_x <= strobe_x + 75 && pixel_y >= strobe_y && pixel_y <= strobe_y + 40 ) {
      TouchDebug("COLAIR");
      plg.SendSerialCommand("STR", 3, 0);
    }

    if (pixel_x >= brightnessup_x && pixel_x <= brightnessup_x + 40 && pixel_y >= brightnessup_y && pixel_y <= brightnessup_y + 40 ) {
      TouchDebug("COLBUP");
      plg.SendSerialCommand("BUP", 3, 0);
    }
    if (pixel_x >= white_x && pixel_x <= white_x + 40 && pixel_y >= white_y && pixel_y <= white_y + 40 ) {
      TouchDebug("COLRWHI");
      plg.SendSerialCommand("WHI", 3, 0);
    }
    if (pixel_x >= brightnessdown_x && pixel_x <= brightnessdown_x + 40 && pixel_y >= brightnessdown_y && pixel_y <= brightnessdown_y + 40 ) {
      TouchDebug("COLBDN");
      plg.SendSerialCommand("BDN", 3, 0);

    }
    if (pixel_x >= rand_x && pixel_x <= rand_x + 75 && pixel_y >= rand_y && pixel_y <= rand_y + 40 ) {
      TouchDebug("COLRND");
      plg.SendSerialCommand("RND", 3, 0);
    }



  }
  else if (currentPage == "Main_Dialog1") {
    if (pixel_x >= hs_dialog_x && pixel_x <= hs_dialog_rx && pixel_y >= hs_dialog_y && pixel_y <= hs_dialog_ry ) {
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      currentPage = "Main";
      DrawMainMenu();
      TouchDebug("DLG_OK");
    }
  }
  else if (currentPage == "Net_Scan") {

    if (pixel_x >= netback_x && pixel_x <= netback_x + 40 && pixel_y >= netback_y && pixel_y <= netback_y + 40 ) {
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      ScrollLeft(true);
      currentPage = "Net";
      DrawNetMenu();
      TouchDebug("NSCANBCK");

    }
    if (pixel_x >= netback_x && pixel_x <= netback_x + 40 && pixel_y >= netback_y + 50 && pixel_y <= netback_y + 90 ) {
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      DrawScanMenu();
      TouchDebug("RESCAN");

    }
    CheckSSIDHitbox(pixel_x, pixel_y);
  }
  else if (currentPage == "Keyboard_Net") {
    CheckKeyboardHitbox(pixel_x, pixel_y);
  }

  else if (currentPage == "Net") {

    if (pixel_x >= netback_x && pixel_x <= netback_x + 40 && pixel_y >= netback_y && pixel_y <= netback_y + 40 ) {
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
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
      drawing = true;
      myGLCD.setColor(BLACK);
      myGLCD.fillRect(1, 21, 324, 223);
      myGLCD.setColor(WHITE);
      myGLCD.setBackColor(BLACK);
      myGLCD.setTextSize(1);
      //_______________________________________________
      myGLCD.print("Resetting ESP...", 10, 23);
      if (find(sendCommand("AT+RST\r\n", 3000, DEBUG), "OK") ) {
        myGLCD.setColor(GREEN);
        myGLCD.print("DONE", 210, 23);
      }
      else {
        myGLCD.setColor(RED);
        myGLCD.print("FAIL", 210, 23);
      }
      //_______________________________________________
      myGLCD.setColor(WHITE);
      myGLCD.print("Configuring Network Mode...", 10, 33);

      if (find(sendCommand("AT+CWMODE=1\r\n", 1000, DEBUG), "OK")) {
        myGLCD.setColor(GREEN);
        myGLCD.print("DONE", 210, 33);
      }
      else {
        myGLCD.setColor(RED);
        myGLCD.print("FAIL", 210, 33);
      }
      //_______________________________________________
      myGLCD.setColor(WHITE);
      myGLCD.print("Connecting to AP...", 10, 43);

      if (find(sendCommand("AT+CWJAP=\"GS\",\"weissbraun287Tim\"\r\n", 5000, DEBUG), "OK")) {
        myGLCD.setColor(GREEN);
        myGLCD.print("DONE", 210, 43);
      }
      else {
        myGLCD.setColor(RED);
        myGLCD.print("FAIL", 210, 43);
      }
      //_______________________________________________
      myGLCD.setColor(WHITE);
      myGLCD.print("Getting IP...", 10, 53);
      if (find(sendCommand("AT+CIFSR\r\n", 1000, DEBUG), "OK")) {
        myGLCD.setColor(GREEN);
        myGLCD.print("DONE", 210, 53);
      }
      else {
        myGLCD.setColor(RED);
        myGLCD.print("FAIL", 210, 53);
      }
      //_______________________________________________
      myGLCD.setColor(WHITE);
      myGLCD.print("Enabling multiple connections...", 10, 63);
      if (find(sendCommand("AT+CIPMUX=1\r\n", 1000, DEBUG), "OK")) {
        myGLCD.setColor(GREEN);
        myGLCD.print("DONE", 210, 63);
      }
      else {
        myGLCD.setColor(RED);
        myGLCD.print("FAIL", 210, 63);
      }
      //_______________________________________________
      myGLCD.setColor(WHITE);
      myGLCD.print("Starting server...", 10, 73);
      if (find(sendCommand("AT+CIPSERVER=1,80\r\n", 1000, DEBUG), "OK")) {
        myGLCD.setColor(GREEN);
        myGLCD.print("DONE", 210, 73);
      }
      else {
        myGLCD.setColor(RED);
        myGLCD.print("FAIL", 210, 73);
      }

      myGLCD.setColor(WHITE);
      myGLCD.print("Server ready", 10, 83);
      Serial.println("Server Ready");

      currentPage = "Net";
      myGLCD.setColor(BLACK);
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      DrawNetMenu();
    }
  }
  else if (currentPage == "News") {
    if (pixel_x >= newback_x && pixel_x <= newback_x + 40 && pixel_y >= newback_y && pixel_y <= newback_y + 40 ) {
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      ScrollLeft(true);
      currentPage = "Net";
      DrawNetMenu();
      TouchDebug("NEWBCK");

    }
  }
  else if (currentPage == "Net_Dialog") {
    // if (pixel_x >= hs_dialog_x && pixel_x <= hs_dialog_rx && pixel_y >= hs_dialog_y && pixel_y <= hs_dialog_ry ) {

    //}
  }
  else if (currentPage == "Settings") {

    if (pixel_x >= setback_x && pixel_x <= setback_x + 40 && pixel_y >= setback_y && pixel_y <= setback_y + 40 ) {
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      ScrollLeft(true);
      currentPage = "Main";
      DrawMainMenu();
      TouchDebug("SETBCK");

    }
    if (pixel_x >= setpgnext_x && pixel_x <= setpgnext_x + 32 && pixel_y >= setpgnext_y && pixel_y <= setpgnext_y + 32 ) {
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      currentPage = "Settings2";
      DrawSettingsMenu(2);
      TouchDebug("SETNXT");

    }

    if (pixel_x >= set_debug_x && pixel_x <= set_debug_rx && pixel_y >= set_debug_y && pixel_y <= set_debug_ry ) {
      //Disable Serial in Clients
      plg.SendSerialCommand("STO", 0, 0);
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
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      ScrollLeft(true);
      currentPage = "Main";
      DrawMainMenu();
      TouchDebug("SETBCK");

    }
    if (pixel_x >= setpgnext_x && pixel_x <= setpgnext_x + 32 && pixel_y >= setpgnext_y && pixel_y <= setpgnext_y + 32 ) {
      //PrevPG
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
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
      if (showBorder) {
        showBorder = false;
        drawing = true;
        myGLCD.fillRect(1, 21, 324, 223);
        drawing = false;
        DrawDialogButtonBoxHS(false, "Settings", "Borders have", "been disabled!", "Settings2", false, RED, "OK");
        StoreBoolEEPROM(false, 2);
      }
      else {
        showBorder = true;
        DrawDialogButtonBoxHS(false, "Settings", "Borders have", "been enabled!", "Settings2", false, RED, "OK");
        StoreBoolEEPROM(true, 2);
      }
      TouchDebug("SETBOR");
    }
    if (pixel_x >= set_clear_eeprom_x && pixel_x <= set_clear_eeprom_rx && pixel_y >= set_clear_eeprom_y && pixel_y <= set_clear_eeprom_ry ) {
      //Set Footer
      if (hideFooter) {
        hideFooter = false;
        drawing = true;
        myGLCD.fillRect(1, 21, 324, 223);
        drawing = false;
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
        drawing = true;
        myGLCD.fillRect(1, 21, 324, 223);
        drawing = false;
        DrawDialogButtonBoxHS(false, "Settings", "Header has", "been enabled!", "Settings2", false, RED, "OK");
        StoreBoolEEPROM(false, 4);
      }
      else {
        hideHeader = true;
        DrawDialogButtonBoxHS(false, "Settings", "Header has", "been disabled!", "Settings2", false, RED, "OK");
        StoreBoolEEPROM(true, 4);
      }
      TouchDebug("SETHEAD");
    }
  }
  else if (currentPage == "Settings_Dialog") {
    if (pixel_x >= hs_dialog_x && pixel_x <= hs_dialog_rx && pixel_y >= hs_dialog_y && pixel_y <= hs_dialog_ry ) {
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
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
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      currentPage = "Settings2";
      DrawSettingsMenu(2);
      TouchDebug("DLGS2_OK");
    }
  }
  else if (currentPage == "PreBootRTC_Dialog") {
    if (pixel_x >= hs_dialog_x && pixel_x <= hs_dialog_rx && pixel_y >= hs_dialog_y && pixel_y <= hs_dialog_ry ) {
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
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
      drawing = true;
      myGLCD.fillRect(1, 21, 324, 223);
      drawing = false;
      ScrollLeft(true);
      currentPage = "Main";
      DrawMainMenu();
      TouchDebug("CLKBCK");

    }
  }
}
