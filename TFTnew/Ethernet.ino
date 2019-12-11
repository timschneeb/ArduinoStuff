void SetupEthernet() {
  String savedMac = GetStringEEPROM(6, 17);
  if (savedMac.length() == 17) {
    bool valid = true;
    savedMac.replace(":", "");
    for (int k = 0; k < 12; k++) {
      Serial.print(savedMac.charAt(k));
      Serial.print(" - ");
      Serial.println(isHexadecimalDigit(savedMac.charAt(k)));
      if (!isHexadecimalDigit(savedMac.charAt(k)))valid = false;
    }
    if (valid) {
      char msg[13];
      savedMac.toCharArray(msg, 13);
      Serial.println(msg);
      byte b[12];
      int i;
      int j;
      char temp[3];

      j = 0;
      for (int i = 0; i < 12; i += 2)
      {
        msg[i] = toupper(msg[i]);
        strncpy(temp, &msg[i], 2);

        // Convert hex string to numeric:
        b[j] = (temp[0] <= '9') ? (temp[0] - '0') : (temp[0] - 'A' + 10);
        b[j] *= 16;
        b[j] += (temp[1] <= '9') ? (temp[1] - '0') : (temp[1] - 'A' + 10);

        Serial.print(b[j++], HEX);
        Serial.print(", ");
      }
      Ethernet.begin(b, ip);
    }
    else {
      Serial.println("Invalid MAC in EEPROM, continuing with default");
      Ethernet.begin(mac, ip);
    }
  }
  else {
    Serial.println("Invalid MAC in EEPROM, continuing with default (Invalid Length)");
    Ethernet.begin(mac, ip);
  }

  server.begin();
}
void CheckEthernet() {
  EthernetClient client = server.available();  // try to get client

  if (client) {  // got client?
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {   // client data available to read
        char c = client.read(); // read 1 byte (character) from client
        // buffer first part of HTTP request in HTTP_req array (string)
        // leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)
        if (req_index < (REQ_BUF_SZ - 1)) {
          HTTP_req[req_index] = c;          // save HTTP request character
          req_index++;
        }
        // print HTTP request character to serial monitor
        if (ETH_DEBUG)Serial.print(c);
        // last line of client request is blank and ends with \n
        // respond to client only after last line received
        if (c == '\n' && currentLineIsBlank) {
          // open requested web page file
          if (StrContains(HTTP_req, "GET / ")
              || StrContains(HTTP_req, "GET /index.html")) {
            client.println(F("HTTP/1.1 200 OK"));
            client.println(F("Content-Type: text/html"));
            client.println(F("Connnection: close"));
            client.println();
            client.println(GeneratePage("WS5100 Server", "No command", "WS5100 Server"));
          }
          else if (StrContains(HTTP_req, "GET /?cmd=")) {
            client.println(F("HTTP/1.1 200 OK"));
            client.println(F("Content-Type: text/html"));
            client.println(F("Connnection: close"));
            client.println(F("Access-Control-Allow-Origin: *"));
            client.println();
            String cmd = midString(HTTP_req, "=", " ");
            TriggerWebSchedule(cmd);
            String out = WebToSerial(cmd);

            if (out != "")client.println(out);
            else client.println(GeneratePage(F("Request processed"), cmd, "Request processed"));
            //DrawFooter("\"" + cmd + "\" issued by Web Client");
            //footerWebTimer = 0;
            //footerWebTimerOn = true;

          }
          else if (StrContains(HTTP_req, "GET /GET /?cmd=")) {
            client.println(F("HTTP/1.1 200 OK"));
            client.println(F("Content-Type: text/html"));
            client.println(F("Connnection: close"));
            client.println(F("Access-Control-Allow-Origin: *"));
            client.println();
            String cmd = midString(HTTP_req, "=", " ");
            TriggerWebSchedule(cmd);
            String out = WebToSerial(cmd);

            if (out != "")client.println(out);
            else client.println(GeneratePage(F("Request processed"), cmd, "Request processed"));

          }
          else if (StrContains(HTTP_req, "GET /")) {
            String reqFile = midString(HTTP_req, "/", " ");
            client.println(F("HTTP/1.1 404 Not Found"));
            client.println(F("Content-Type: text/html"));
            client.println(F("Connnection: close"));
            client.println();
            client.println(F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><link href='https://fonts.googleapis.com/css?family=Roboto' rel='stylesheet'><body style=\"font-family: 'Roboto', sans-serif;\"><h2 style=\"margin-bottom:10px;\">404.</h2><sub>File not found</sub>"));
          }
          // reset buffer index and all buffer elements to 0
          req_index = 0;
          StrClear(HTTP_req, REQ_BUF_SZ);
          break;
        }
        // every line of text received from the client ends with \r\n
        if (c == '\n') {
          // last character on line of received text
          // starting new line with next character read
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // a text character was received from client
          currentLineIsBlank = false;
        }
      } // end if (client.available())
    } // end while (client.connected())
    delay(100);      // give the web browser time to receive the data
    client.stop(); // close the connection



    if (performReset)resetFunc();
    if (performEEPROMClear)ClearEEPROM();


  } // end if (client)
}
void StrClear(char *str, char length) {
  for (int i = 0; i < length; i++) {
    str[i] = 0;
  }
}

// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
char StrContains(char *str, char *sfind) {
  char found = 0;
  char index = 0;
  char len;

  len = strlen(str);

  if (strlen(sfind) > len) {
    return 0;
  }
  while (index < len) {
    if (str[index] == sfind[found]) {
      found++;
      if (strlen(sfind) == found) {
        return 1;
      }
    }
    else {
      found = 0;
    }
    index++;
  }

  return 0;
}
char* subStr (char* input_string, char *separator, int segment_number) {
  char *act, *sub, *ptr;
  static char copy[100];
  int i;

  strcpy(copy, input_string);
  for (i = 1, act = copy; i <= segment_number; i++, act = NULL)
  {
    sub = strtok_r(act, separator, &ptr);
    if (sub == NULL) break;
  }
  return sub;
}
String WebToSerial(String response) {
  Serial.println(response);
  String origResponse = response;
  response.toLowerCase();
  //COLORS
  if (response == "green" || (response.charAt(0) == 'g' && response.charAt(1) == 'r' && response.charAt(3) == 'n')) {
    Serial.println(F("Web: Green"));
    SendSerialCommand("GRN", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "red" || response == "rot")
  {
    Serial.println(F("Web: Red"));
    SendSerialCommand("RED", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "blue" || response == "blau")
  {
    Serial.println(F("Web: Blue"));
    SendSerialCommand("BLU", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "yellow" || response == "gelb")
  {
    Serial.println(F("Web: Yellow"));
    SendSerialCommand("YEL", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "orange")
  {
    Serial.println(F("Web: Orange"));
    SendSerialCommand("ORA", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "bgreen" || response.indexOf("blau%20") == 0)
  {
    Serial.println(F("Web: Bluegreen"));
    SendSerialCommand("BGR", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "ultraviolet" || response == "ultraviolett")
  {
    Serial.println(F("Web: Ultraviolet"));
    SendSerialCommand("VIO", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "ygreen" || response.indexOf("gelb%20") == 0)
  {
    Serial.println(F("Web: YellowGreen"));
    SendSerialCommand("YGR", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "turquoise" || response.indexOf("rkis") == 2)
  {
    Serial.println(F("Web: Turquoise"));
    SendSerialCommand("TUR", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "darkmagenta" || response == "dunkelrosa")
  {
    Serial.println(F("Web: Dark Magenta"));
    SendSerialCommand("DMA", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "magenta")
  {
    Serial.println(F("Web: Magenta"));
    SendSerialCommand("MAG", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "lightturquoise" || (response.indexOf("hellt") == 0 && response.indexOf("rkis") == 6))
  {
    Serial.println(F("Web: Light Turquoise"));
    SendSerialCommand("LTU", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "lightgreen" || response.indexOf("hellg") == 0)
  {
    Serial.println(F("Web: Light Green"));
    SendSerialCommand("LGR", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "cyan")
  {
    Serial.println(F("Web: Cyan"));
    SendSerialCommand("CYA", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "lightviolet" || response == "hellviolett")
  {
    Serial.println(F("Web: Lightviolet"));
    SendSerialCommand("LVI", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  //BRIGHTNESS
  if (response.indexOf("bright") == 0)
  {
    char webparam = response.charAt(6);
    char webparam2 = response.charAt(7);
    String webparam_str = String(webparam);
    int webparam_int = webparam_str.toInt();
    String webparam2_str = String(webparam2);
    int webparam2_int = webparam2_str.toInt();
    Serial.println("Web: B_UP" + webparam_str);
    if (webparam2_int >= 1 && webparam2_int <= 9) {
      SendSerialCommand("BUP", 3, 9, 0);
      return GeneratePage("Command processed", "Brightness +9", "Brightness: +9");
    }
    else {
      if (isDigit(webparam) && webparam_int > 0 && webparam_int < 10) {
        SendSerialCommand("BUP", 3, webparam_int, 0);
        return GeneratePage("Command processed", "Brightness +" + webparam_str, "Brightness: +" + webparam_str);
      }
      else {
        SendSerialCommand("BUP", 3, 0, 0);
        return GeneratePage("Command processed", "Brightness +1", "Brightness: +1");
      }
    }
  }
  if (response.indexOf("dim") == 0)
  {
    char webparam = response.charAt(3);
    char webparam2 = response.charAt(4);
    String webparam_str = String(webparam);
    int webparam_int = webparam_str.toInt();
    String webparam2_str = String(webparam2);
    int webparam2_int = webparam2_str.toInt();
    Serial.println("Web: B_DOWN" + webparam_str);
    if (webparam2_int >= 1 && webparam2_int <= 9) {
      SendSerialCommand("BDN", 3, 9, 0);
      return GeneratePage("Command processed", "Brightness -9", "Brightness: -9");
    }
    else {
      if (isDigit(webparam) && webparam_int > 0 && webparam_int < 10) {
        SendSerialCommand("BDN", 3, webparam_int, 0);
        return GeneratePage("Command processed", "Brightness -" + webparam_str, "Brightness: -" + webparam_str);
      }
      else {
        SendSerialCommand("BDN", 3, 0, 0);
        return GeneratePage("Command processed", "Brightness -1", "Brightness: -1");
      }
    }
  }
  if (response == "white" || response.indexOf("wei") == 0)
  {
    Serial.println(F("Web: White"));
    SendSerialCommand("WHI", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  //OTHER MODES
  if (response == "fade")
  {
    Serial.println(F("Web: Fade"));
    SendSerialCommand("FAD", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "flash")
  {
    Serial.println(F("Web: Flash"));
    SendSerialCommand("FLA", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "sfade")
  {
    Serial.println(F("Web: Slow Fade"));
    SendSerialCommand("SFA", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "sflash")
  {
    Serial.println(F("Web: Slow Flash"));
    SendSerialCommand("SFL", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "random")
  {
    Serial.println(F("Web: Random"));
    SendSerialCommand("RND", 3, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");
  }
  if (response == "strobe")
  {
    Serial.println(F("Web: Strobe (!)"));
    SendSerialCommand("STR", 3, 0, 0);
    return GeneratePage("This feature has been disabled", "Strobe", "This feature has been disabled");
  }
  //POWER
  if (response == "on")
  {
    Serial.println(F("Web: On"));
    SendSerialCommand("PWR", 1, 0, 0);
    return GeneratePage("Command processed", response, "Command processed");

  }
  if (response == "off")
  {
    Serial.println(F("Web: Off"));
    SendSerialCommand("PWR", 0, 0, 0);
    return GeneratePage("Command processed", "Power toggled", "Power toggled");

  }
  if (response == "power")
  {
    Serial.println(F("Web: Power Toggle"));
    SendSerialCommand("PWR", 2, 0, 0);
    return GeneratePage("Command processed", "Power toggled", "Power toggled");

  }
  if (response == "spower")
  {
    Serial.println(F("Web: SPower Toggle"));
    SendSerialCommand("PWR", 2, 1, 0);
    return GeneratePage("Command processed", "Power toggled (smooth)", "Power toggled (smooth)");
  }

  //TIMERS
  if (response == "cleartimer")
  {
    Serial.println(F("Web: Clear Timer"));
    SendSerialCommand("CTM", 0, 0, 0);
    return GeneratePage("Command processed", "Timers cleared", "Timers cleared");
  }
  if (response.indexOf("timeroff") == 0)
  {
    Serial.println("Web: Set OffTimer");

    String amount, unit;
    String resp_param = response.substring(8);
    char resp_param_c[resp_param.length() + 1];
    resp_param.toCharArray(resp_param_c, resp_param.length() + 1);

    char* resp = strtok(resp_param_c, "_");
    int countInc = 0;
    while (resp != NULL) {
      String a = String(resp);
      if (countInc == 0) amount = a;
      else if (countInc == 1) unit = a;
      resp = strtok(NULL, "_");
      countInc++;
    }
    countInc = 0;
    unit.toLowerCase();
    Serial.println(amount + " - " + unit);

    int amountI = amount.toInt();
    if (amountI > 999 || amountI < 1 || amount.length() > 3 || amount.length() < 1) {
      SendSerialCommand("ERR", 0, 0, 0);
      return GeneratePage("Command not successfully processed", "Off-Timer not set, invalid duration", "Error: Invalid duration");
    } else {
      char p1 = amount.charAt(0) ;
      char p2 = amount.charAt(1) ;
      char p3 = amount.charAt(2) ;

      Serial.println(p1); Serial.println(p2); Serial.println(p3);
      if (unit.indexOf("mi") == 0) {
        SendSerialCommandC("TFM", p1, p2, p3);
        return GeneratePage("Command processed", "Off-Timer set for " + String(amount) + " minutes", "Off-Timer set for " + String(amount) + " minutes");
      }
      //else if (unit.indexOf("st") == 0) {
      // SendSerialCommandC("TFH", p1, p2, p3);
      //}
      else {
        SendSerialCommand("ERR", 0, 0, 0);
        return GeneratePage("Command not successfully processed", "Off-Timer not set, invalid unit", "Error: Invalid unit");
      }

    }

  }
  if (response.indexOf("timeron") == 0)
  {
    Serial.println("Web: Set OnTimer");

    String amount, unit;
    String resp_param = response.substring(7);
    char resp_param_c[resp_param.length() + 1];
    resp_param.toCharArray(resp_param_c, resp_param.length() + 1);

    char* resp = strtok(resp_param_c, "_");
    int countIncOn = 0;
    while (resp != NULL) {
      String a = String(resp);
      if (countIncOn == 0) amount = a;
      else if (countIncOn == 1) unit = a;
      resp = strtok(NULL, "_");
      countIncOn++;
    }
    countIncOn = 0;
    unit.toLowerCase();
    Serial.println(amount + " - " + unit);

    int amountI = amount.toInt();
    if (amountI > 999 || amountI < 1 || amount.length() > 3 || amount.length() < 1) {
      SendSerialCommand("ERR", 0, 0, 0);
      return GeneratePage("Command not successfully processed", "On-Timer not set, invalid duration", "Error: Invalid duration");
    } else {
      char p1 = amount.charAt(0) ;
      char p2 = amount.charAt(1) ;
      char p3 = amount.charAt(2) ;

      Serial.println(p1); Serial.println(p2); Serial.println(p3);
      if (unit.indexOf("min") == 0) {
        SendSerialCommandC("TNM", p1, p2, p3);
        return GeneratePage("Command processed", "On-Timer set for " + String(amount) + " minutes", "On-Timer set for " + String(amount) + " minutes");
      }
      //else if (unit.indexOf("stu") == 0) {
      //  SendSerialCommandC("TNH", p1, p2, p3);
      //}
      else {
        SendSerialCommand("ERR", 0, 0, 0);
        return GeneratePage("Command not successfully processed", "On-Timer not set, invalid unit", "Error: Invalid unit");
      }

    }

  }

  if (response.indexOf("newschedule") == 0)
  {
    Serial.println("Web: New Schedule");

    int triggerInt = String(response.charAt(11)).toInt();
    String trigger = ConvertScheduleTrigger(triggerInt);

    String action, parameter;
    String resp_param = response.substring(12);
    char resp_param_c[resp_param.length() + 1];
    resp_param.toCharArray(resp_param_c, resp_param.length() + 1);

    char* resp = strtok(resp_param_c, "_");
    int countInc = 0;
    while (resp != NULL) {
      String a = String(resp);
      if (countInc == 0) action = a;
      else if (countInc == 1) parameter = a;
      resp = strtok(NULL, "_");
      countInc++;
    }
    countInc = 0;
    action.toLowerCase();
    parameter.toLowerCase();
    if (parameter.indexOf("%3c") == 0) {
      parameter = "<" + parameter.substring(3);
    } else if (parameter.indexOf("%3e") == 0) {
      parameter = ">" + parameter.substring(3);
    }

    Serial.println(action + " - " + parameter);
    Serial.println(triggerInt);
    set_scheduleslot(get_nextfreeslot(), triggerInt, parameter, action);
    return GeneratePage("Schedule updated", "Trigger: " + ConvertScheduleTrigger(triggerInt) + "<br>Parameter: " + parameter + "<br>Action: " + action, "Schedule updated");

  }

  if (response.indexOf("removeevent") == 0)
  {
    Serial.println("Web: Remove Schedule");
    int slot = String(response.charAt(11)).toInt();
    clear_scheduleslot(slot);
    return GeneratePage("Schedule updated", "Slot " + String(slot) + " removed", "Schedule updated");

  }
  if (response == "screen")
  {
    Serial.println(F("Web: Screen Toggle"));
    lcdPower();
#if ENABLE_SCREEN
    return GeneratePage("Command processed", "Screen Backlight toggled", "Screen Backlight toggled");
#else
    return GeneratePage("Command processed", "<b>Notice:</b> Screen Feature is not enabled", "Notice: Screen Feature is not enabled");
#endif
  }
  if (response == "stop")
  {
    Serial.println(F("Web: Disable Serial1"));
    SendSerialCommand("STO", 0, 0, 0);
    return GeneratePage("Command processed.", "Serial Connection to UNO disabled (Reboot required to reactivate)", "Serial1 has been disabled");
  }

  if (response == "reset") {
    Serial.println(F("Web: Reset"));
    performReset = true;
    return GeneratePage("Rebooting...", "Please wait and <a href='/'>click here</a>", "Rebooting...");

  }
  if (response.indexOf("serial") == 0)
  {
    Serial.println(F("Web: Send Serial"));
    String serialcmd = "<" + origResponse.substring(6) + ">";
    Serial1.println(serialcmd);
    Serial.println(serialcmd);
    return GeneratePage("Serial Command processed", origResponse.substring(6), "Serial Command processed: " + origResponse.substring(6));
  }
  if (response.indexOf("sim") == 0)
  {
    Serial.println(F("Web: Sim_T"));
    sim_t = origResponse.substring(3);

    return GeneratePage("Var updated", sim_t, "Var updated to " + sim_t);
  }
  if (response.indexOf("synctime") == 0)
  {
    Serial.println(F("Web: Sync Time"));
    String timeS = origResponse.substring(8);
    if (timeS.length() == 5)timeS += ":00";
    Serial.println(timeS);
    SyncRTCTime(timeS);
    return GeneratePage("Time updated", timeS, "Time updated to " + timeS);
  }
  if (response.indexOf("syncdate") == 0)
  {
    Serial.println(F("Web: Sync Date"));
    String dateS = origResponse.substring(8);
    Serial.println(dateS);
    SyncRTCDate(dateS + " ");
    return GeneratePage("Date updated", dateS, "Date updated to " + dateS);
  }
  if (response == "uptime") {
    Serial.println(F("Web: Uptime"));
    return GetUptime();
  }
  if (response == "compiledate") {
    Serial.println(F("Web: Compiledate"));
    String content;
    content += __DATE__;
    content += " ";
    content += __TIME__;
    return content;
  }

  if (response == "dewpoint") {
    Serial.println(F("Web: Dewpoint"));
    return String(calcDewpoint((int)dht.readHumidity(), (int)dht.readTemperature()));
  }
  if (response == "temp") {
    Serial.println(F("Web: Temp"));
    return String((int)dht.readTemperature());
  }
  if (response == "humidity") {
    Serial.println(F("Web: Humidity"));
    return String((int)dht.readHumidity());
  }
  if (response == "sensor") {
    Serial.println(F("Web: Sensor"));
    return String((int)dht.readTemperature()) + "," + String((int)dht.readHumidity());
  }
  if (response == "dashboard") {
    Serial.println(F("Web: Dashboard"));
    return GenerateDashboard((int)dht.readTemperature(), (int)dht.readHumidity());
  }
  if (response == "sync") {
    Serial.println(F("Web: SyncInterface"));
    return GenerateSyncTimeInterface();
}
  if (response == "info") {
    Serial.println(F("Web: Info"));
    return GenerateInfo();
  }
  if (response == "addevent") {
    Serial.println(F("Web: AddEventInterface"));
    return GenerateAddEventInterface();
  }
  if (response == "schedule") {
    Serial.println(F("Web: ScheduleInterface"));
    return GenerateScheduleInterface();
  }
  if (response == "editmac") {
    Serial.println(F("Web: EditMacInterface"));
    byte macBuffer[6];
    String mac = "";
    Ethernet.MACAddress(macBuffer);
    for (byte octet = 0; octet < 6; octet++) {
      mac += String(macBuffer[octet], HEX);
      if (octet < 5) {
        mac += ":";
      }
    }
    mac.toUpperCase();
    return GenerateMacInterface(mac);
  }
  if (response == "cleareeprom") {
    Serial.println(F("Web: ClearEEPROM"));
    performEEPROMClear = true;
    String scriptInsert = F("<script>var timeleft = 4096;var downloadTimer = setInterval(function(){document.getElementById(\"prog\").innerHTML = (4096 - --timeleft) + '/4096 Bytes';document.getElementById(\"progressBar\").value = 4096 - timeleft;if(timeleft <= 0){clearInterval(downloadTimer);document.getElementById(\"prog\").innerHTML = 'Completed';document.getElementById(\"heading\").innerHTML = 'EEPROM cleared';}},3);</script>");
    return GeneratePage("Clearing EEPROM...", "Estimated progress: <progress value=\"0\" max=\"4096\" id=\"progressBar\"></progress>&nbsp;<small id='prog'></small>" + scriptInsert, "Clearing EEPROM... (This will take a while)");
  }
  if (response.indexOf("updatemac") == 0) {
    Serial.println(F("Web: UpdateMac"));
    String mac = origResponse.substring(9);
    mac.toUpperCase();
    String displayMac = mac;
    mac += ">";//Bugfix/TermChar
    char m_buf[mac.length()];
    mac.toCharArray(m_buf, mac.length());
    StoreStringEEPROM(m_buf, 6);
    return GeneratePageC("MAC updated", displayMac + " (Reboot required)", "MAC updated (Reboot to apply changes)", "<a href='/?cmd=reset'>Reboot now</a>");
  }
  return GeneratePage("Command not recognized", response, "Command not recognized");


}
