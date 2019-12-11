#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <UTFTGLUE.h>
#include <EEPROM.h>

#include <LEDCtrl_Plugins.h>

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
//TOUCHSCREEN
#define MINPRESSURE 200
#define MAXPRESSURE 1000
//Init Calibration
const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;
uint8_t Orientation = 0;
MCUFRIEND_kbv tft;
UTFTGLUE myGLCD(0, A2, A1, A3, A4, A0);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;
LEDCtrl_Plugins plg;

void setup() {
  Serial.begin(9600);

  pinMode(31, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(52, OUTPUT);
  digitalWrite(52, HIGH);
  digitalWrite(31, HIGH);
  digitalWrite(33, LOW);
  myGLCD.InitLCD();
  myGLCD.print("Ready.", 0, 0);

  plg.ClearRangeEEPROM(6, 38);
  plg.StoreStringEEPROM("GS>", 6);
  String ssid = plg.GetStringEEPROM(6, 33);
  char* _ssid;
  ssid.toCharArray(_ssid, 33);
  char* dec_ssid = strtok(_ssid, ">");
  Serial.println(String(dec_ssid));

  plg.ClearRangeEEPROM(39, 64);
  plg.StoreStringEEPROM("weissbraun287Tim>", 39);
  String pwd = plg.GetStringEEPROM(39, 64);
  char* _pwd;
  ssid.toCharArray(_pwd, 64);
  char* dec_pwd = strtok(_pwd, ">");
  Serial.println(String(dec_pwd));

}

void loop() {}
