/********************************
   TFTnew - Handles Screen, Wifi,
            Sensors, Time, EEPROM

   TheBone_ (thebone.main@gmail.com)
********************************/
//Sketch Details
#define _name_ "Arduino IoT Controller"
#define _version_ "2.0.4"
#define _EEPROMSIZE_ "4096"

//LIBRARIES
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <UTFTGLUE.h>
#include <EEPROM.h>
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

//Serial
#define SERIAL_DELAY 250
//Touchscreen
#define MINPRESSURE 200
#define MAXPRESSURE 1000
//Debug
#define SKIP_ESPBOOT true
#define EEPROM_DEBUG true
#define ETH_DEBUG false
#define ENABLE_EEPROMVIEWER true
#define ENABLE_BITMAPS false
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

//DIALOG_ONEBTN
#define hs_dialog_x 135
#define hs_dialog_y 137
#define hs_dialog_rx 185
#define hs_dialog_ry 157


//Software Keyboard
#define keyWidth 30
#define keyHeight 40

//Init Objects
MCUFRIEND_kbv tft;
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

void SendSerialCommand(String,int,int,int){
//Stub  
}
void setup() {
  Serial.begin(9600);
 
  Serial.println("Compile Date: " __DATE__ " "__TIME__);
  Serial.println("GCC Version: " __VERSION__);

  // disable Ethernet chip
  //pinMode(10, OUTPUT);
  //digitalWrite(10, HIGH);

#if ENABLE_SCREEN
  digitalWrite(31, HIGH);
#endif
  digitalWrite(33, LOW);
  attachInterrupt(digitalPinToInterrupt(20), lcdPower, RISING );
#if ENABLE_SCREEN
  myGLCD.InitLCD();
  myGLCD.print("Booting...", 0, 0);
#endif

#if ENABLE_SCREEN
  lcdPower();
#endif
// your esp's baud rate might be different4
  DEBUG = GetBoolEEPROM(1);


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

      CheckHitbox(pixel_x, pixel_y);
      TouchDebug("CAL");
      TouchDebug("CS");
    
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
