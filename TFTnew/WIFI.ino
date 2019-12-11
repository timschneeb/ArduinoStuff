/*int countInc = 0;

boolean find(String string, String value) {
  if (string.indexOf(value) >= 0)
    return true;
  return false;
}
bool isNotMsgEnd(int charAscii) {
  Serial.println(charAscii);
  if (charAscii == 38 ) {
    return false;
  }
  else {
    return true;
  }
}
String AsciiToChar(int code)
{
  switch (code) {
    case 38: return "&";
    case 61: return "=";
    case 63: return "?";
    case 32: return " ";
    case 48: return "0";
    case 49: return "1";
    case 50: return "2";
    case 51: return "3";
    case 52: return "4";
    case 53: return "5";
    case 54: return "6";
    case 55: return "7";
    case 56: return "8";
    case 57: return "9";
    case 65: return "A";
    case 66: return "B";
    case 67: return "C";
    case 68: return "D";
    case 69: return "E";
    case 70: return "F";
    case 71: return "G";
    case 72: return "H";
    case 73: return "I";
    case 74: return "J";
    case 75: return "K";
    case 76: return "L";
    case 77: return "M";
    case 78: return "N";
    case 79: return "O";
    case 80: return "P";
    case 81: return "Q";
    case 82: return "R";
    case 83: return "S";
    case 84: return "T";
    case 85: return "U";
    case 86: return "V";
    case 87: return "W";
    case 88: return "X";
    case 89: return "Y";
    case 90: return "Z";
    case 97: return "a";
    case 98: return "b";
    case 99: return "c";
    case 100: return "d";
    case 101: return "e";
    case 102: return "f";
    case 103: return "g";
    case 104: return "h";
    case 105: return "i";
    case 106: return "j";
    case 107: return "k";
    case 108: return "l";
    case 109: return "m";
    case 110: return "n";
    case 111: return "o";
    case 112: return "p";
    case 113: return "q";
    case 114: return "r";
    case 115: return "s";
    case 116: return "t";
    case 117: return "u";
    case 118: return "v";
    case 119: return "w";
    case 120: return "x";
    case 121: return "y";
    case 122: return "z";
    case 95: return "_";
    case -1: return "-";
    default: return "";
  }

}
String RemoveAndFromString(String code)
{
  int indexAnd = code.indexOf('&');
  if (indexAnd > 1) {
    code.remove(indexAnd, 1);
  }
  return code;
}
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";

  int dataSize = command.length();
  char data[dataSize];
  command.toCharArray(data, dataSize);

  Serial2.write(data, dataSize); // send the read character to the Serial2
  if (debug)
  {
    Serial.println("\r\n====== HTTP Response From Arduino ======");
    Serial.write(data, dataSize);
    Serial.println("\r\n========================================");
  }

  long int time = millis();

  while ( (time + timeout) > millis())
  {
    while (Serial2.available())
    {

      // The esp has data so display its output to the serial window
      char c = Serial2.read(); // read the next character.
      response += c;
    }
  }

  if (debug)
  {
    Serial.print(response);
  }

  return response;
}
void sendHTTPResponse(int connectionId, String content, int timeout, bool debug)
{

  // build HTTP response
  String httpResponse;
  String httpHeader;
  // HTTP Header
  httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n";
  httpHeader += "Content-Length: ";
  httpHeader += content.length();
  httpHeader += "\r\n";
  httpHeader += "Access-Control-Allow-Origin: *";
  httpHeader += "\r\n";
  httpHeader += "Connection: close\r\n\r\n";
  httpResponse = httpHeader + content + " "; // There is a bug in this code: the last character of "content" is not sent, I cheated by adding this extra space
  sendCIPData(connectionId, httpResponse, timeout, debug);
}
void sendCIPData(int connectionId, String data, int timeout, bool DEBUG)
{
  String cipSend = "AT+CIPSEND=";
  cipSend += connectionId;
  cipSend += ",";
  cipSend += data.length();
  cipSend += "\r\n";
  sendCommand(cipSend, timeout, DEBUG);
  sendData(data, timeout, DEBUG);
}
String sendCommand(String command, const int timeout, boolean debug)
{
  String response = "";
  if (debug)Serial.println("_____" + command);
  Serial2.print(command); // send the read character to the Serial2

  long int time = millis();

  while ( (time + timeout) > millis())
  {
    while (Serial2.available())
    {

      // The esp has data so display its output to the serial window
      char c = Serial2.read(); // read the next character.
      response += c;
    }
  }

  if (debug)
  {
    Serial.print(response);
  }

  return response;
}

void WebToSerial(String response) {
  Serial.println(response);
  //COLORS
  if ("green") == 0 || "grn") == 0) {
    Serial.println("Web: Green");
    SendSerialCommand("GRN", 3, 0, 0);
  }
  if ("red") == 0  || "rot") == 0)
  {
    Serial.println("Web: Red");
    SendSerialCommand("RED", 3, 0, 0);
  }
  if ("blue") == 0 || "blau") == 0 && "blau20grn") != 0)
  {
    Serial.println("Web: Blue");
    SendSerialCommand("BLU", 3, 0, 0);
  }
  if ("yellow") == 0 || "gelb") == 0 && "gelb20grn") != 0)
  {
    Serial.println("Web: Yellow");
    SendSerialCommand("YEL", 3, 0, 0);
  }
  if ("orange") == 0)
  {
    Serial.println("Web: Orange");
    SendSerialCommand("ORA", 3, 0, 0);
  }
  if ("bgreen") == 0 || "blau20grn") == 0)
  {
    Serial.println("Web: Bluegreen");
    SendSerialCommand("BGR", 3, 0, 0);
  }
  if ("ultraviolet") == 0 || "ultraviolett") == 0)
  {
    Serial.println("Web: Ultraviolet");
    SendSerialCommand("VIO", 3, 0, 0);
  }
  if ("ygreen") == 0 || "gelb20grn") == 0)
  {
    Serial.println("Web: YellowGreen");
    SendSerialCommand("YGR", 3, 0, 0);
  }
  if ("turquoise") == 0 || "trkis") == 0)
  {
    Serial.println("Web: Turquoise");
    SendSerialCommand("TUR", 3, 0, 0);
  }
  if ("darkmagenta") == 0 || "dunkelrosa") == 0)
  {
    Serial.println("Web: Dark Magenta");
    SendSerialCommand("DMA", 3, 0, 0);
  }
  if ("magenta") == 0)
  {
    Serial.println("Web: Magenta");
    SendSerialCommand("MAG", 3, 0, 0);
  }
  if ("lightturquoise") == 0 || "helltrkis") == 0 && "hellviolett") != 0 && "hellgrn") != 0)
  {
    Serial.println("Web: Light Turquoise");
    SendSerialCommand("LTU", 3, 0, 0);
  }
  if ("lightgreen") == 0 || "hellgrn") == 0 && "hellviolett") != 0 && "helltrkis") != 0)
  {
    Serial.println("Web: Light Green");
    SendSerialCommand("LGR", 3, 0, 0);
  }
  if ("cyan") == 0)
  {
    Serial.println("Web: Cyan");
    SendSerialCommand("CYA", 3, 0, 0);
  }
  if ("lightviolet") == 0 || "hellviolett") == 0 && "helltrkis") != 0 && "hellgrn") != 0)
  {
    Serial.println("Web: Lightviolet");
    SendSerialCommand("LVI", 3, 0, 0);
  }
  //BRIGHTNESS
  if ("bright") == 0)
  {
    char webparam = response.charAt(6);
    char webparam2 = response.charAt(7);
    String webparam_str = String(webparam);
    int webparam_int = webparam_str.toInt();
    String webparam2_str = String(webparam2);
    int webparam2_int = webparam2_str.toInt();
    Serial.println("Web: B_UP" + webparam_str);
    if (webparam2_int >= 1 && webparam2_int <= 9) SendSerialCommand("BUP", 3, 9, 0);
    else {
      if (isDigit(webparam) && webparam_int > 0 && webparam_int < 10) SendSerialCommand("BUP", 3, webparam_int, 0);
      else SendSerialCommand("BUP", 3, 0, 0);
    }
  }
  if ("dim") == 0)
  {
    char webparam = response.charAt(3);
    char webparam2 = response.charAt(4);
    String webparam_str = String(webparam);
    int webparam_int = webparam_str.toInt();
    String webparam2_str = String(webparam2);
    int webparam2_int = webparam2_str.toInt();
    Serial.println("Web: B_DOWN" + webparam_str);
    if (webparam2_int >= 1 && webparam2_int <= 9) SendSerialCommand("BDN", 3, 9, 0);
    else {
      if (isDigit(webparam) && webparam_int > 0 && webparam_int < 10) SendSerialCommand("BDN", 3, webparam_int, 0);
      else SendSerialCommand("BDN", 3, 0, 0);
    }
  }
  if ("white") == 0 || "wei") == 0)
  {
    Serial.println("Web: White");
    SendSerialCommand("WHI", 3, 0, 0);
  }
  //OTHER MODES
  if ("fade") == 0)
  {
    Serial.println("Web: Fade");
    SendSerialCommand("FAD", 3, 0, 0);
  }
  if ("flash") == 0)
  {
    Serial.println("Web: Flash");
    SendSerialCommand("FLA", 3, 0, 0);
  }
  if ("sfade") == 0)
  {
    Serial.println("Web: Slow Fade");
    SendSerialCommand("SFA", 3, 0, 0);
  }
  if ("sflash") == 0)
  {
    Serial.println("Web: Slow Flash");
    SendSerialCommand("SFL", 3, 0, 0);
  }
  if ("random") == 0)
  {
    Serial.println("Web: Random");
    SendSerialCommand("RND", 3, 0, 0);
  }
  if ("strobe") == 0)
  {
    Serial.println("Web: Strobe (!)");
    SendSerialCommand("STR", 3, 0, 0);
  }
  //POWER
  if ("on") == 0)
  {
    Serial.println("Web: On");
    SendSerialCommand("PWR", 1, 0, 0);
  }
  if ("off") == 0)
  {
    Serial.println("Web: Off");
    SendSerialCommand("PWR", 0, 0, 0);
  }
  if ("power") == 0)
  {
    Serial.println("Web: Power Toggle");
    SendSerialCommand("PWR", 2, 0, 0);
  }
  if ("spower") == 0)
  {
    Serial.println("Web: SPower Toggle");
    SendSerialCommand("PWR", 2, 1, 0);
  }

  //TIMERS
  if ("cleartimer") == 0)
  {
    Serial.println("Web: Clear Timer");
    SendSerialCommand("CTM", 0, 0, 0);
  }
  if ("timeroff") == 0)
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
    } else {
      char p1 = amount.charAt(0) ;
      char p2 = amount.charAt(1) ;
      char p3 = amount.charAt(2) ;

      Serial.println(p1); Serial.println(p2); Serial.println(p3);
      if (unit.indexOf("mi") == 0) {
        SendSerialCommandC("TFM", p1, p2, p3);
      }
      else if (unit.indexOf("st") == 0) {
        SendSerialCommandC("TFH", p1, p2, p3);
      }
      else  SendSerialCommand("ERR", 0, 0, 0);

    }

  }



  if ("timeron") == 0)
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
    } else {
      char p1 = amount.charAt(0) ;
      char p2 = amount.charAt(1) ;
      char p3 = amount.charAt(2) ;

      Serial.println(p1); Serial.println(p2); Serial.println(p3);
      if (unit.indexOf("min") == 0) {
        SendSerialCommandC("TNM", p1, p2, p3);
      }
      else if (unit.indexOf("stu") == 0) {
        SendSerialCommandC("TNH", p1, p2, p3);
      }
      else  SendSerialCommand("ERR", 0, 0, 0);

    }

  }


  if ("screen") == 0)
  {
    Serial.println("Web: Screen Toggle");
    lcdPower();
  }
  if ("stop") == 0)
  {
    Serial.println("Web: Disable Serial1");
    SendSerialCommand("STO", 0, 0, 0);
  }
}


void CheckWifi() {
  if (Serial2.available()) // check if the esp is sending a message
  {
    if (Serial2.find("+IPD,"))
    {
      delay(1000); // wait for the serial buffer to fill up (read all the serial data)
      // get the connection id so that we can then disconnect
      int connectionId = Serial2.read() - 48; // subtract 48 because the read() function returns
      // the ASCII decimal value and 0 (the first decimal number) starts at 48

      int char1 = 0;
      int char2 = 0;
      int char3 = 0;
      int char4 = 0;
      int char5 = 0;
      int char6 = 0;
      int char7 = 0;
      int char8 = 0;
      int char9 = 0;
      int char10 = 0;
      int char11 = 0;
      int char12 = 0;
      int char13 = 0;
      int char14 = 0;
      int char15 = 0;
      String decodedRequest;
      String content;
      bool performReset = false;
      bool echoCmd = true;
      Serial2.find("cmd=");
      char1 = Serial2.read();


      if (isNotMsgEnd(char1)) {
        char2 = Serial2.read();
        if (isNotMsgEnd(char2)) {
          char3 = Serial2.read();
          if (isNotMsgEnd(char3)) {
            char4 = Serial2.read();
            if (isNotMsgEnd(char4)) {
              char5 = Serial2.read();
              if (isNotMsgEnd(char5)) {
                char6 = Serial2.read();
                if (isNotMsgEnd(char6)) {
                  char7 = Serial2.read();
                  if (isNotMsgEnd(char7)) {
                    char8 = Serial2.read();
                    if (isNotMsgEnd(char8)) {
                      char9 = Serial2.read();
                      if (isNotMsgEnd(char9)) {
                        char10 = Serial2.read();
                        if (isNotMsgEnd(char10)) {
                          char11 = Serial2.read();
                          if (isNotMsgEnd(char11)) {
                            char12 = Serial2.read();
                            if (isNotMsgEnd(char12)) {
                              char13 = Serial2.read();
                              if (isNotMsgEnd(char13)) {
                                char14 = Serial2.read();
                                if (isNotMsgEnd(char14)) {
                                  char15 = Serial2.read();
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (char1 == -1 ) {
        content = "<link href='https://fonts.googleapis.com/css?family=Roboto' rel='stylesheet'>";
        content += "<body style=\"font-family: 'Roboto', sans-serif;\">";
        content += "<h3>ESP8266 Server</h3>";
        decodedRequest = "Usage:<br>&nbsp;&nbsp;&nbsp;&nbsp;<i><code>?cmd=[Command]& - Execute specific command</code></i>";
      }
      else if (char1 == 32 && char2 == 72 && char3 == 84 && char4 == 84 && char5 == 80 || char1 == 38) {
        content = "<link href='https://fonts.googleapis.com/css?family=Roboto' rel='stylesheet'>";
        content += "<body style=\"font-family: 'Roboto', sans-serif;\">";
        content += "<h3>An error occurred</h3>";
        decodedRequest = "No Command";
      }
      else {

        decodedRequest = AsciiToChar(char1);
        decodedRequest += AsciiToChar(char2);
        decodedRequest += AsciiToChar(char3);
        decodedRequest += AsciiToChar(char4);
        decodedRequest += AsciiToChar(char5);
        decodedRequest += AsciiToChar(char6);
        decodedRequest += AsciiToChar(char7);
        decodedRequest += AsciiToChar(char8);
        decodedRequest += AsciiToChar(char9);
        decodedRequest += AsciiToChar(char10);
        decodedRequest += AsciiToChar(char11);
        decodedRequest += AsciiToChar(char12);
        decodedRequest += AsciiToChar(char13);
        decodedRequest += AsciiToChar(char14);
        decodedRequest += AsciiToChar(char15);
        decodedRequest = RemoveAndFromString(decodedRequest);

        WebToSerial(decodedRequest);
        if (decodedRequest.indexOf("reset") == 0) {
          Serial.println("Web: Reset");
          content = "<link href='https://fonts.googleapis.com/css?family=Roboto' rel='stylesheet'>";
          content += "<body style=\"font-family: 'Roboto', sans-serif;\">";
          content += "<h3>Rebooting...</h3>";
          decodedRequest = "Please wait";
          performReset = true;
        }

        if (decodedRequest.indexOf("temp") == 0) {
          float temp = dht.readTemperature();
          content = (int)temp;
          echoCmd = false;
        }
        else if (decodedRequest.indexOf("humidity") == 0) {
          float hu = dht.readHumidity();
          content = (int)hu;
          echoCmd = false;
        } else if (decodedRequest.indexOf("sensor") == 0) {         
          float hu = dht.readHumidity();
          float temp = dht.readTemperature();
          content = String((int)temp) + "," + String((int)hu);
          echoCmd = false;
        } else if (decodedRequest.indexOf("dashboard") == 0) {
          float temp = dht.readTemperature();
          float hu = dht.readHumidity();
          content = HTML_DrawDashboard("", (int)temp, (int)hu);
          echoCmd = false;

        }
        else {
          if (!performReset) {
            content = "<link href='https://fonts.googleapis.com/css?family=Roboto' rel='stylesheet'>";
            content += "<body style=\"font-family: 'Roboto', sans-serif;\">";
            content += "<h3>Request processed</h3>";
          }
        }

        DrawFooter("\"" + decodedRequest + "\" issued by Web Client");
        footerWebTimer = 0;
        footerWebTimerOn = true;
      }

      if (echoCmd)
      {
        content += decodedRequest;
        content += "<p><hr><a href='/?cmd=dashboard&'>Dashboard</a>&nbsp;&nbsp;";
        content += "<span class='sep'></span>&nbsp;&nbsp;";
        if (performReset) {
          content += "<a href='/'>Home</a>";
        } else {
          content += "<a href='http://espremote.ml'>Remote Control</a>";
        }


        content += "</body><style>.sep{border-left: 1.5px solid gray;height: 10px;}a:visited{color: blue;}</style></body>";
      }
      sendHTTPResponse(connectionId, content, 1000, DEBUG);

      // make close command
      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId; // append connection id
      closeCommand += "\r\n";

      sendCommand(closeCommand, 1000, DEBUG); // close connection

      if (performReset)resetFunc();
    }
  }
}
String HTML_DrawDashboard(String prepend, int temp, int hu) {
  prepend += "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>";
  prepend += "<link href='https://fonts.googleapis.com/css?family=Roboto' rel='stylesheet'>";
  prepend += "<body style=\"font-family: 'Roboto', sans-serif;\"><h3>Dashboard</h3>";
  prepend += "Temperatur: " + String(temp) + "°C<br>";
  prepend += "Luftfeuchtigkeit: " + String(hu) + "%</body>";
  Serial.println(prepend);
  return prepend;
}
void ESPBoot(int x, int y) { //Offset

  myGLCD.setColor(WHITE);
  myGLCD.setBackColor(BLACK);
  myGLCD.setTextSize(1 );
  myGLCD.print("Loading Login-Data... ", x, 0 + y);

  String ssid = GetStringEEPROM(6, 33);
  char _ssid[33];
  ssid.toCharArray(_ssid, 33);
  String dec_ssid = strtok(_ssid, ">");
  String pwd = GetStringEEPROM(39, 65);
  char _pwd[65];
  pwd.toCharArray(_pwd, 65);
  String dec_pwd = strtok(_pwd, ">");


  if (ssid.indexOf(">") < 0) {
    myGLCD.setColor(RED);
    myGLCD.print("No network saved", 220, 0 + y);
    myGLCD.setColor(WHITE);
    myGLCD.print("Go to Network -> Scan to add one.", x, 10 + y);
    delay(2000);
  }
  else {
    myGLCD.print(dec_ssid, 130, 0 + y);

    //_______________________________________________
    myGLCD.setColor(WHITE);
    myGLCD.print("Booting ESP...", x, 10 + y);
    if (find(sendCommand("AT+RST\r\n", 3000, DEBUG), "OK") ) {
      myGLCD.setColor(GREEN);
      myGLCD.print("DONE", 290, 10 + y);
    }
    else {
      myGLCD.setColor(RED);
      myGLCD.print("FAIL", 290, 10 + y);
    }
    //_______________________________________________
    myGLCD.setColor(WHITE);
    myGLCD.print("Configuring Network Mode...", x, 20 + y);

    if (find(sendCommand("AT+CWMODE=1\r\n", 1000, DEBUG), "OK")) {
      myGLCD.setColor(GREEN);
      myGLCD.print("DONE", 290, 20 + y);
    }
    else {
      myGLCD.setColor(RED);
      myGLCD.print("FAIL", 290, 20 + y);
    }
    //_______________________________________________
    myGLCD.setColor(WHITE);
    myGLCD.print("Connecting to AP...", x, 30 + y);

    if (find(sendCommand("AT+CWJAP=\"" + String(dec_ssid) + "\",\"" + String(dec_pwd) + "\"\r\n", 10000, DEBUG), "OK")) {
      myGLCD.setColor(GREEN);
      myGLCD.print("DONE", 290, 30 + y);
    }
    else {
      myGLCD.setColor(RED);
      myGLCD.print("FAIL", 290, 30 + y);
    }
    //_______________________________________________
    myGLCD.setColor(WHITE);
    myGLCD.print("Getting IP...", x, 40 + y);
    if (find(sendCommand("AT+CIFSR\r\n", 1000, DEBUG), "OK")) {
      myGLCD.setColor(GREEN);
      myGLCD.print("DONE", 290, 40 + y);
    }
    else {
      myGLCD.setColor(RED);
      myGLCD.print("FAIL", 290, 40 + y);
    }
    //_______________________________________________
    myGLCD.setColor(WHITE);
    myGLCD.print("Enabling multiple connections...", x, 50 + y);
    if (find(sendCommand("AT+CIPMUX=1\r\n", 1000, DEBUG), "OK")) {
      myGLCD.setColor(GREEN);
      myGLCD.print("DONE", 290, 50 + y);
    }
    else {
      myGLCD.setColor(RED);
      myGLCD.print("FAIL", 290, 50 + y);
    }
    //_______________________________________________
    myGLCD.setColor(WHITE);
    myGLCD.print("Starting server...", x, 60 + y);
    if (find(sendCommand("AT+CIPSERVER=1,80\r\n", 1000, DEBUG), "OK")) {
      myGLCD.setColor(GREEN);
      myGLCD.print("DONE", 290, 60 + y);
    }
    else {
      myGLCD.setColor(RED);
      myGLCD.print("FAIL", 290, 60 + y);
    }

    myGLCD.setColor(WHITE);
    myGLCD.print("Server ready", x, 70 + y);
    Serial.println("Server Ready");
  }
}*/
