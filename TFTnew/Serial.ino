const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;
void CheckSerial() {
  recvWithEndMarker();
  showNewData();
}
void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  // if (Serial.available() > 0) {
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    Serial.print("SERIAL: ");
    Serial.println(receivedChars);
    WebToSerial(receivedChars);
    newData = false;
  }
}
