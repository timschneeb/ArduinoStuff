

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();
    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
        if (ndx > 5) {
          receivedChars[ndx] = '\0'; // handle corruption
          recvInProgress = false;
          ndx = 0;
          newData = true;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void showNewData() {
  if (newData == true) {

    recv.cmd = String(receivedChars[0]) + String(receivedChars[1]) + String(receivedChars[2]);
    recv.flag = receivedChars[3];
    recv.param = receivedChars[4];
    recv.param2 = receivedChars[5];

    ProcessRequest();
    newData = false;
  }
}
void ProcessRequest() {
  if (recv.cmd == "PWR") PerformPower(recv.flag, recv.param);
  else if (recv.cmd == "RND") RandomLEDController();
  else if (recv.cmd == "BUP") {
    if (String(recv.param) == "" || String(recv.param) == "0") UpdateLEDbyID(1);
    else {
      for (int i = 1; i <= String(recv.param).toInt(); i++) {
        UpdateLEDbyID(1);
      }
    }
  }
  else if (recv.cmd == "BDN") {
    if (String(recv.param) == "" || String(recv.param) == "0") UpdateLEDbyID(2);
    else {
      for (int i = 1; i <= String(recv.param).toInt(); i++) {
        UpdateLEDbyID(2);
      }
    }
  }

  else if (recv.cmd == "RED") UpdateLEDbyID(4);
  else if (recv.cmd == "GRN") UpdateLEDbyID(5);
  else if (recv.cmd == "BLU") UpdateLEDbyID(6);
  else if (recv.cmd == "FLA") UpdateLEDbyID(19);
  else if (recv.cmd == "ORA") UpdateLEDbyID(7);
  else if (recv.cmd == "BGR") UpdateLEDbyID(8);
  else if (recv.cmd == "VIO") UpdateLEDbyID(9);
  else if (recv.cmd == "FAD") UpdateLEDbyID(21);
  else if (recv.cmd == "YEL") UpdateLEDbyID(10);
  else if (recv.cmd == "CYA") UpdateLEDbyID(17);
  else if (recv.cmd == "LVI") UpdateLEDbyID(15);
  else if (recv.cmd == "YGR") UpdateLEDbyID(13);
  else if (recv.cmd == "LTU") UpdateLEDbyID(11);
  else if (recv.cmd == "TUR") UpdateLEDbyID(14);
  else if (recv.cmd == "DMA") UpdateLEDbyID(12);
  else if (recv.cmd == "MAG") UpdateLEDbyID(18);
  else if (recv.cmd == "LGR") UpdateLEDbyID(16);
  else if (recv.cmd == "WHI") UpdateLEDbyID(3);
  else if (recv.cmd == "SFA") UpdateLEDbyID(22);
  else if (recv.cmd == "SFL") UpdateLEDbyID(20);
  else if (recv.cmd == "CTM") ClearTimer();
  else if (recv.cmd == "GTN") { //GetTimerOn
    PrintCTimer(minOn, secOn);
    return;
  }
  else if (recv.cmd == "GTF") { //GetTimerOff
    PrintCTimer(minOff, secOff);
    return;
  }
  else if (recv.cmd == "TFM") {
    TurnOn();
    SetTimerOff("m", recv.flag, recv.param, recv.param2);
  }
  else if (recv.cmd == "TNM") {
    TurnOff();
    SetTimerOn("m", recv.flag, recv.param, recv.param2);
  }
  else if (recv.cmd == "ERR") {
    if (recv.flag == '1') DisplayFatalError();
    else DisplayError();
  }
  else if (recv.cmd == "SUC") DisplaySuccess();
  else if (recv.cmd == "KNC") {
    switch (String(recv.flag).toInt()) {
      case 0:
        knockEnabled = false;
        break;
      case 1:
        knockEnabled = true;
        break;
      case 2:
        knockEnabled = !knockEnabled;
        break;
    }

    StoreBoolEEPROM(knockEnabled, 0x00);
  }
  else if (recv.cmd == "KNT") {
    StoreBoolEEPROM(knockEnabled, 0x00);
    int len = 3;
    int amount = 0;
    char digit1 = recv.flag;
    char digit2 = recv.param;
    char digit3 = recv.param2;
    if (digit1 == 0)len = 0;
    else if (digit2 == 0)len = 1;
    else if (digit3 == 0)len = 2;

    if (len == 0)DisplayError();
    else if (len == 1)amount = (String(digit1)).toInt();
    else if (len == 2)amount = (String(digit1) + String(digit2)).toInt();
    else if (len == 3)amount = (String(digit1) + String(digit2) + String(digit3)).toInt();

    knockThres = amount;
    StoreIntEEPROM(0x01,amount);
  }
  else if (recv.cmd == "STO") Serial.end();
  else {
    Serial.println("Command not recognized: " + recv.cmd);
    return;
  }
  Serial.print("Data recieved ... ");
  Serial.println(receivedChars);
}
