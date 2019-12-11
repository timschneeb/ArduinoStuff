//Arduino UNO Serial-Client

#include <IRremote.h>
#include <math.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>

#define WHITE 0xFFE11E
#define BRIGHT 0xFF01FE
#define DIM 0xFF817E
#define OFF 0xFF41BE
#define ON 0xFFC13E
#define RED 0xFF21DE
#define GREEN 0xFFA15E
#define BLUE 0xFF619E
#define ORANGE 0xFF11EE
#define BLUEGREEN 0xFF916E
#define ULTRAVIOLET 0xFF51AE
#define FLASH 0xFFD12E
#define YELLOW 0xFF31CE
#define LIGHTTURQUOISE 0xFFB14E
#define LIGHTVIOLET 0xFF718E
#define SFLASH 0xFFF10E
#define YELLOWGREEN 0xFF09F6
#define TURQUOISE 0xFF8976
#define DARKMAGENTA 0xFF49B6
#define FADE 0xFFC936
#define LIGHTGREEN 0xFF29D6
#define LIGHTBLUE 0xFFA956
#define MAGENTA 0xFF6996
#define SFADE 0xFFE916

#define DEBUG true
#define EEPROM_DEBUG true

IRsend irsend;
int oldrandVal = -1;
bool powerState = false;
bool strobeState = false;
int lastColorId = 7;

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;
int loopCount = 0;

struct serialrecv
{
  String cmd;
  char flag;
  char param;
  char param2;
};
typedef struct serialrecv Recv;
Recv recv;

bool knockEnabled = true;
int knockThres = true;

bool timerSet = false;
int long countdowntime;                  // Countdown Variable bzw. Resetwert
int val;                                 // Variable für aktuellen Zustand
int lastval;                             // Variable für den vorherigen Zustand
int long minutes;                        // Countdown in Minuten
int long seconds;                        // Countdown in Sekunden
volatile unsigned char tick;             // Variable für den Timer
ISR (TIMER2_OVF_vect) {
  -tick;
}
int minOn = 0;
int secOn = 0;
int minOff = 0;
int secOff = 0;
bool timerSetOn = false;
int long countdowntimeOn;                  // Countdown Variable bzw. Resetwert
int valOn;                                 // Variable für aktuellen Zustand
int lastvalOn;                             // Variable für den vorherigen Zustand
int long minutesOn;                        // Countdown in Minuten
int long secondsOn;                        // Countdown in Sekunden
volatile unsigned char tickOn;             // Variable für den Timer
ISR (TIMER3_OVF_vect) {
  -tickOn;
}
void(* resetFunc) (void) = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("Compile Date: " __DATE__ " "__TIME__);
  Serial.println("GCC Version: " __VERSION__);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(A1, INPUT);

  knockEnabled = GetBoolEEPROM(0x00);
  knockThres = GetIntEEPROM(0x01);

  Serial.println("Knock enabled: " + String(knockEnabled));
  Serial.println("Knock Threshold: " + String(knockThres));
}

void loop() {
  //Format: <AAABCD>
  //        <      > - Packet Marker
  //         RND     - Command/Function (char[3])
  //            1    - 0/1/2/.. On, Off, Toggle-Flag (int)
  //             0   - Parameter (char,int)
  //              0  - Parameter 2 (char,int)
 recvWithStartEndMarkers();
 showNewData();
 CheckTimer();
 if(knockEnabled){
  int sample = analogRead(A1);
  if(sample<=knockThres){
    PerformPower('2','0');
    delay(400);
  }
 }
}
