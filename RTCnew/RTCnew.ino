#include <stdio.h>
#include <DS1302.h>
#define UPDATE_CLOCK false

const int kCePin   = 8;  // Chip Enable
const int kIoPin   = 9;  // Input/Output
const int kSclkPin = 10;  // Serial Clock

// Create a DS1302 object.
DS1302 rtc(kCePin, kIoPin, kSclkPin);

void printTime() {
  // Get the current time and date from the chip.
  Time t = rtc.time();

  // Format the time and date and insert into the temporary buffer.
  char buf[50];
  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  // Print the formatted string to serial so we can see the time.
  Serial.println(buf);
}

void setup() {
  Serial.begin(9600);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(12,HIGH);
  digitalWrite(11,LOW);
  rtc.writeProtect(false);
  rtc.halt(false);
  int h;
  int m;
  int s;
  int y;
  int mo;
  int d;

  if (UPDATE_CLOCK) {
    char* sTime = strtok(__TIME__, ":");
    int countT = 0;
    while (sTime != NULL) {
      int a = atoi(sTime);
      if (countT == 0) h = a;
      else if (countT == 1) m = a;
      else if (countT == 2) s = a;
      sTime = strtok (NULL, ":");
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

    Time t(y, mo, d, h, m, s, Time::kSunday);

    rtc.time(t);
  }
}

// Loop and print the time every second.
void loop() {
  printTime();
  delay(1000);
}
