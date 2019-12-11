/********************************
   TFTnew - Handles Screen, Wifi,
            Sensors, Time, EEPROM

   TheBone_ (thebone.main@gmail.com)
********************************/
//Sketch Details
#define _name_ "Arduino IoT Controller"
#define _version_ "2.0.4"
#define _EEPROMSIZE_ "4096"
#include <DS1302.h>
//LIBRARIES
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

#include <UTFTGLUE.h>
#include <EEPROM.h>
#include "DHT.h"
#include <SPI.h>
#include <Ethernet.h>
#include <math.h>

//COLORS
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define ORANGE  0xFFFF00
#define YELLOW  0xFFF0
#define TFT_BLUEGREEN 0x8FFD
#define TFT_VIOLET 0xC819
#define TFT_LIGHTVIOLET  0xF8BF
#define TFT_LIGHTMAGENTA 0xFADF
#define TFT_LIGHTBLUE 0x7DFF

//ETHERNET
#define REQ_BUF_SZ   70
//RTC
#define rstPin 39
#define dataPin 37
#define clkPin 35
#define secondsOffset 20
//Sensors
#define DHTPIN A8
#define DHTTYPE DHT11
//Serial
#define SERIAL_DELAY 250
//Touchscreen
#define MINPRESSURE 200
#define MAXPRESSURE 1000
//Debug
#define SKIP_ESPBOOT false
#define EEPROM_DEBUG true
#define ETH_DEBUG false
#define ENABLE_EEPROMVIEWER true
#define ENABLE_BITMAPS true
#define ENABLE_SCREEN true
#define FASTBOOT false

#if ENABLE_BITMAPS
#include "powerbmp.c"
#include "color.c"
#include "clock.c"
#include "random.c"
#include "net.c"
#include "settings.c"
#include "reload.c"
#include "back_bw_norm.c"
#include "arrow_down_32x32.c"
#include "arrow_up_32x32.c"
#include "arrow_down_24x24_black.c"
#include "arrow_up_24x24_black.c"
#else
const uint16_t arrow_down_24x24_black[1] PROGMEM = {0x000};
const uint16_t arrow_down_32x32[1] PROGMEM = {0x000};
const uint16_t arrow_up_24x24_black[1] PROGMEM = {0x000};
const uint16_t arrow_up_32x32[1] PROGMEM = {0x000};
const uint16_t back_bw_norm[1] PROGMEM = {0x000};
const uint16_t clock_bmp[1] PROGMEM = {0x000};
const uint16_t color[1] PROGMEM = {0x000};
const uint16_t net[1] PROGMEM = {0x000};
const uint16_t powerbmp[1] PROGMEM = {0x000};
const uint16_t random_bmp[1] PROGMEM = {0x000};
const uint16_t reload[1] PROGMEM = {0x000};
const uint16_t settings[1] PROGMEM = {0x000};
#endif

//Init Calibration
const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;
const uint8_t Orientation = 0;
const int center_x = 275 / 2;
int pixel_x, pixel_y;

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 178, 210); // IP address, may need to change depending on network
EthernetServer server(80);  // create a server at port 80
char HTTP_req[REQ_BUF_SZ] = {0}; // buffered HTTP request stored as null terminated string
char req_index = 0;              // index into HTTP_req buffer

//Button Positions
//MAIN PAGE
#define power_x 49
#define power_y 45
#define color_x 128
#define color_y 45
#define net_x 207
#define net_y 45
#define random_x 49
#define random_y 124
#define clock_x 128
#define clock_y 124
#define settings_x 207
#define settings_y 124

//COLOR
#define colback_x 10
#define colback_y 30

//SETTINGS
#define setback_x 10
#define setback_y 30
#define setpgnext_x 12
#define setpgnext_y 180
#define set_debug_x 60
#define set_debug_y 30
#define set_debug_rx 300
#define set_debug_ry 70
#define set_syncclock_x 60
#define set_syncclock_y 77
#define set_syncclock_rx 300
#define set_syncclock_ry 117
#define set_clear_eeprom_x 60
#define set_clear_eeprom_y 124
#define set_clear_eeprom_rx 300
#define set_clear_eeprom_ry 164
#define set_smoothpwr_x 60
#define set_smoothpwr_y 171
#define set_smoothpwr_rx 300
#define set_smoothpwr_ry 211

//NETWORK
#define netback_x 10
#define netback_y 30
#define net_scan_x 60
#define net_scan_y 30
#define net_scan_rx 290
#define net_scan_ry 70
#define net_rst_x 60
#define net_rst_y 77
#define net_rst_rx 290
#define net_rst_ry 117
#define net_rom_x 60
#define net_rom_y 124
#define net_rom_rx 290
#define net_rom_ry 164

//CLOCK
#define clockback_x 10
#define clockback_y 30

//DIALOG_ONEBTN
#define hs_dialog_x 135
#define hs_dialog_y 137
#define hs_dialog_rx 185
#define hs_dialog_ry 157

//ROW1
#define red_x 68
#define red_y 28
#define red_rx 68 + 40
#define red_ry 28 + 40
#define green_x 118
#define green_y 28
#define green_rx 118 + 40
#define green_ry 28 + 40
#define blue_x 168
#define blue_y 28
#define blue_rx 168 + 40
#define blue_ry 28 + 40
#define flash_x 218
#define flash_y 28
#define flash_rx 218 + 75
#define flash_ry 28 + 40
//ROW2
#define orange_x 68
#define orange_y 76
#define orange_rx 68 + 40
#define orange_ry 76 + 40
#define bluegreen_x 118
#define bluegreen_y 76
#define bluegreen_rx 118 + 40
#define bluegreen_ry 76 + 40
#define violet_x 168
#define violet_y 76
#define violet_rx 168 + 40
#define violet_ry 76 + 40
#define fade_x 218
#define fade_y 76
#define fade_rx 218 + 75
#define fade_ry 76 + 40
//ROW3
#define yellow_x 68
#define yellow_y 126
#define yellow_rx 68 + 40
#define yellow_ry 126 + 40
#define cyan_x 118
#define cyan_y 126
#define cyan_rx 118 + 40
#define cyan_ry 126 + 40
#define lightviolet_x 168
#define lightviolet_y 126
#define lightviolet_rx 168 + 40
#define lightviolet_ry 126 + 40
#define strobe_x 218
#define strobe_y 126
#define strobe_rx 218 + 75
#define strobe_ry 126 + 40
//ROW4
#define brightnessup_x 68
#define brightnessup_y 176
#define brightnessup_rx 68 + 40
#define brightnessup_ry 176 + 40
#define white_x 118
#define white_y 176
#define white_rx 118 + 40
#define white_ry 176 + 40
#define brightnessdown_x 168
#define brightnessdown_y 176
#define brightnessdown_rx 168 + 40
#define brightnessdown_ry 176 + 40
#define rand_x 218
#define rand_y 176
#define rand_rx 218 + 75
#define rand_ry 176 + 40

//Software Keyboard
#define keyWidth 30
#define keyHeight 40

//Init Objects
MCUFRIEND_kbv tft;
DHT dht(DHTPIN, DHTTYPE);
DS1302 rtc(rstPin, dataPin, clkPin);
UTFTGLUE myGLCD(0, A2, A1, A3, A4, A0);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

//Variables
bool DEBUG = true;
String currentPage = "Main";
int loopCount = 0;
bool ENABLE_SCROLL = true;
bool hideFooter = false;
bool hideHeader = false;
bool smoothPower = false;
bool performReset = false;
bool performEEPROMClear = false;
//Software Keyboard
String keybuffer = "";
bool shiftP = false;

//Wifi Scan
//String wifiNames[8];
//String selectedSSID = "";

//Dialog Actions
bool clearEEPROMAfterDlg = false;
bool doCancelRTCAfterDlg = false;
bool preBootRTC = false;

//Web Stuff
int footerWebTimer = 0;
bool footerWebTimerOn = false;
int responseTime = 100;

//EEPROM Viewer
int address = 0;
int lcount = 0;
byte address_value;

long Day = 0;
int Hour = 0;
int Minute = 0;
int Second = 0;
int HighMillis = 0;
int Rollover = 0;

//Power Button
volatile bool powerState = true;
void(* resetFunc) (void) = 0;


String sim_t = "";


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Compile Date: " __DATE__ " "__TIME__);
  Serial.println("GCC Version: " __VERSION__);

  // disable Ethernet chip
  //pinMode(10, OUTPUT);
  //digitalWrite(10, HIGH);

  pinMode(31, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(20, INPUT_PULLUP);
  digitalWrite(49, HIGH);
#if ENABLE_SCREEN
  digitalWrite(31, HIGH);
#endif
  digitalWrite(33, LOW);
  dht.begin();
  attachInterrupt(digitalPinToInterrupt(20), lcdPower, RISING );
#if ENABLE_SCREEN
  myGLCD.InitLCD();
  myGLCD.print("Booting...", 0, 0);
#endif

  SetupEthernet();
#if ENABLE_SCREEN
  lcdPower();
#endif

  Serial2.begin(115200); // your esp's baud rate might be different4
  DEBUG = GetBoolEEPROM(1);

#if ENABLE_SCREEN
  if (GetBoolEEPROM(0)) {
    if (secondsOffset == 0) {
      DrawDialogButtonBoxHS(false, F("RTC Sync"), F("The RTC has been synced to"), __TIME__ , F("PreBootRTC_Dialog"), true, BLUE, "OK");
    } else {
      DrawDialogButtonBoxHS(false, F("RTC Sync"), F("The RTC has been synced to"), String(__TIME__) + " +" + String(secondsOffset) + "s (Offset)", F("PreBootRTC_Dialog"), true, BLUE, "OK");
    }
    StoreBoolEEPROM(0, 0x0);
    preBootRTC = true ;
    SyncRTC();
  }

  if (DEBUG)FastScreenEffect();
  else if (FASTBOOT) {}
  else StartupScreen();
#endif

  if (!SKIP_ESPBOOT) {
    //ESPBoot(0,0);
  }

  ENABLE_SCROLL = GetBoolEEPROM(2);
  hideFooter = GetBoolEEPROM(3);
  hideHeader = GetBoolEEPROM(4);
  smoothPower = GetBoolEEPROM(5);

#if ENABLE_SCREEN
  lcdPower();
  myGLCD.fillScreen(BLACK);
  DrawMainMenu();
#endif
  Serial.println();
}

void loop()
{
  //CheckWifi();
  CheckEthernet();
  CheckSerial();
  if ( ((loopCount % 1000) == 0 ) && (CountSchedules() != 0) )CheckSchedule();

#if ENABLE_SCREEN
  int buf[318];
  int x, x2;
  int y, y2;
  int r;
  tp = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) {
  } else {
    //if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570) {}
    pixel_x =  map(tp.x, TS_LEFT, TS_RT, 0, myGLCD.width());
    pixel_y = map( tp.y, TS_BOT , TS_TOP , 0, myGLCD.height());


    if (currentPage != "PreBootRTC_Dialog") {
      CheckHitbox(pixel_x, pixel_y);
      TouchDebug("CAL");
      TouchDebug("CS");
    }
  }
  if (currentPage != "PreBootRTC_Dialog") {
    if ( (loopCount % 200) == 0 ) {
      loopCount = 0;
      TouchDebug("RAM");
    }

    myGLCD.setColor(0, 0, 255);
  }

  if (currentPage == "Clock") {
    if ( (loopCount % 100) == 0 )UpdateClockApp();
  }
  if (currentPage == "EEPROM_View") {
    UpdateEEPROMViewer();
  }

  if (footerWebTimerOn) {
    footerWebTimer++;
    TouchDebug("FWT");
    if (footerWebTimer >= 100) {
      footerWebTimerOn = false;
      footerWebTimer = 0;
      DrawFooter(F("- Arduino LED Controller -"));
      if (DEBUG) {

        myGLCD.setBackColor(255, 0, 0);
        myGLCD.setColor(255, 0, 0);
        myGLCD.fillRect(120, 11, 170, 20);//reprint debug msg

        TouchDebug("FWT");
      }
    }
  }
#endif

  loopCount++;
}
String midString(String str, String start, String finish) {
  int locStart = 0;
  int locFinish = 0;
  locStart = str.indexOf(start, locFinish);
  if (locStart == -1) return "";
  locStart += start.length();
  locFinish = str.indexOf(finish, locStart);
  if (locFinish == -1) return "";
  return str.substring(locStart, locFinish);
}
void SendSerialCommandC(char cmd[3], char flag, char param, char param2) {
  String packet = "<" + String(cmd[0]) + String(cmd[1]) + String(cmd[2]) + String(flag) + String(param) + String(param2) + ">";

  char* cString = (char*) malloc(sizeof(char) * (packet.length() + 1));
  packet.toCharArray(cString, packet.length() + 1);
  Serial1.write(cString);
  Serial.println(cString);
  delay(SERIAL_DELAY);
}
void SendSerialCommand(char cmd[3], int flag, int param, int param2) {
  String packet = "<" + String(cmd[0]) + String(cmd[1]) + String(cmd[2]) + String(flag) + String(param) + String(param2) + ">";

  char* cString = (char*) malloc(sizeof(char) * (packet.length() + 1));
  packet.toCharArray(cString, packet.length() + 1);
  Serial1.write(cString);
  Serial.println(cString);
  delay(SERIAL_DELAY);
}
void lcdPower() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200)
  {
    powerState = !powerState;
    Serial.println(powerState);
    if (powerState) digitalWrite(49, LOW);
    else digitalWrite(49, HIGH);
    last_interrupt_time = interrupt_time;
  }

}
int GetIntLength(int in) {
  if (in > 9999)
    return 5;
  else if (in > 999)
    return 4;
  else if (in > 99)
    return 3;
  else if (in > 9)
    return 2;
  else
    return 1;
}
float calcDewpoint(int humi, int temp) {
  float k;
  k = log((float)humi / 100) + (17.62 * (float)temp) / (243.12 + (float)temp);
  return 243.12 * k / (17.62 - k);
}
void SyncRTCTime(String input) {
  rtc.writeProtect(false);
  rtc.halt(false);
  char i_buf[input.length()];
  input.toCharArray(i_buf, input.length());

  int h, m, s;
  char* sTime = strtok(i_buf, ":");
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

  Time ot = rtc.time();
  Time t(ot.yr, ot.mon, ot.date, h, m, s, Time::kSunday);
  rtc.time(t);
}
void SyncRTCDate(String input) {
  rtc.writeProtect(false);
  rtc.halt(false);
  char i_buf[input.length()];
  input.toCharArray(i_buf, input.length());

  int y, mo, d;
  char* sDate = strtok(i_buf, "-");
  int countD = 0;
  while (sDate != NULL) {
    if (countD == 0) y = atoi(sDate);
    else if (countD == 1) mo = atoi(sDate);
    else if (countD == 2) d = atoi(sDate);
    sDate = strtok (NULL, "-");
    countD++;
  }
  countD = 0;
  Time ot = rtc.time();
  Time t(y, mo, d, ot.hr, ot.min, ot.sec, Time::kSunday);

  rtc.time(t);
}
void SyncRTC() {
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
void uptime() {
  //** Making Note of an expected rollover *****//
  if (millis() >= 3000000000) {
    HighMillis = 1;

  }
  //** Making note of actual rollover **//
  if (millis() <= 100000 && HighMillis == 1) {
    Rollover++;
    HighMillis = 0;
  }
  long secsUp = millis() / 1000;
  Second = secsUp % 60;
  Minute = (secsUp / 60) % 60;
  Hour = (secsUp / (60 * 60));// % 24;
  //Day = (Rollover * 50) + (secsUp / (60 * 60 * 24)); //First portion takes care of a rollover [around 50 days]
};
