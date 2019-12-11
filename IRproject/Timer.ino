void SetTimerOff(char unit, char digit1, char digit2, char digit3) {
  int len = 3;
  int amount = 0;
  if (digit1 == 0)len = 0;
  else if (digit2 == 0)len = 1;
  else if (digit3 == 0)len = 2;

  if (len == 0)DisplayError();
  else if (len == 1)amount = (String(digit1)).toInt();
  else if (len == 2)amount = (String(digit1) + String(digit2)).toInt();
  else if (len == 3)amount = (String(digit1) + String(digit2) + String(digit3)).toInt();

  int inputtime = amount * 60;
  countdowntime = inputtime;
  int showminutes = inputtime / 60;
  int showseconds = inputtime % 60;
  timerSet = true;


  DisplaySuccess();
}
void SetTimerOn(char unit, char digit1, char digit2, char digit3) {
  int len = 3;
  int amount = 0;
  if (digit1 == 0)len = 0;
  else if (digit2 == 0)len = 1;
  else if (digit3 == 0)len = 2;

  if (len == 0)DisplayError();
  else if (len == 1)amount = (String(digit1)).toInt();
  else if (len == 2)amount = (String(digit1) + String(digit2)).toInt();
  else if (len == 3)amount = (String(digit1) + String(digit2) + String(digit3)).toInt();


  int inputtime = amount * 60;
  countdowntimeOn = inputtime;
  int showminutes = inputtime / 60;
  int showseconds = inputtime % 60;
  timerSetOn = true;


  DisplaySuccess();
}

void CheckTimer() {
  bool enabledelay = false;
  val = digitalRead(tick);
  if (timerSet) {
    if (countdowntime > 0 )
    {
      if (val != lastval)countdowntime--;
      minutes = countdowntime / 60;      // Aufteilung der "countdowntime" in Minuten
      seconds = countdowntime % 60;      // und Sekunden               // LCD ausgabe in Zeile 2 Zeichen 1
      minOff = minutes;
      secOff = seconds;
      enabledelay = true;
      val = lastval;
    }
    else {
      timerSet = false;
      TurnOff();
    }
  }

  valOn = digitalRead(tickOn);
  if (timerSetOn) {
    if (countdowntimeOn > 0 && timerSetOn)
    {
      if (valOn != lastvalOn)countdowntimeOn--;
      minutesOn = countdowntimeOn / 60;      // Aufteilung der "countdowntime" in Minuten
      secondsOn = countdowntimeOn % 60;      // und Sekunden               // LCD ausgabe in Zeile 2 Zeichen 1
      minOn = minutesOn;
      secOn = secondsOn;
      enabledelay = true;
      valOn = lastvalOn;
    }
    else {
      timerSetOn = false;
      TurnOn();
    }
  }
  if(enabledelay)delay(1000);
}
void PrintCTimer(int minutesOn, int secondsOn) {
  if (minutesOn < 10) Serial.print('0');
  Serial.print(minutesOn);
  Serial.print(":");
  if (secondsOn < 10)
  {
    Serial.print("0");
    Serial.print(secondsOn);
    Serial.write(' ');
  }
  else Serial.print(secondsOn);
  Serial.println();
}
void ClearTimer() {
    if (timerSet || timerSetOn) {
      timerSet = false;
      timerSetOn = false;
      DisplaySuccess();
    }
    else {
      DisplayError();
    }
}
