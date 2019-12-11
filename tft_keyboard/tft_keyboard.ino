//LIBRARIES
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <UTFTGLUE.h>

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <FreeDefaultFonts.h>

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

#define MINPRESSURE 200
#define MAXPRESSURE 1000

//Init Calibration
const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;
uint8_t Orientation = 0;
int pixel_x, pixel_y;
int center_x = 275 / 2;

String wifiNames[8];

//Init Objects
MCUFRIEND_kbv tft;
UTFTGLUE myGLCD(0, A2, A1, A3, A4, A0);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

//Sizes
int keyWidth = 30;
int keyHeight = 40;
String keybuffer = "";
bool shiftP = false;

void setup() {
  Serial.begin(9600);
  pinMode(31, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(52, OUTPUT);
  digitalWrite(52, HIGH);
  digitalWrite(31, HIGH);
  digitalWrite(33, LOW);

  myGLCD.InitLCD();
  myGLCD.fillScreen(BLACK);
  PrintKeyboard(shiftP);
}

void loop() {
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

  }

}
void CheckHitbox(int x, int y) {
  if (x >= 0 && x <= 0 + 30 && y >= 0 && y <= 0 + 24 ) {
    myGLCD.fillScreen(BLACK);
    keybuffer = "";
    PrintKeyboard(shiftP);
  } else if (x >= 1 && x <= 1 + keyWidth && y >= 33 && y <= 33 + keyHeight ) {
    KeyboardUpdate("1");
  } else if (x >= 33 && x <= 33 + keyWidth && y >= 33 && y <= 33 + keyHeight ) {
    KeyboardUpdate("2");
  } else if (x >= 65 && x <= 65 + keyWidth && y >= 33 && y <= 33 + keyHeight ) {
    KeyboardUpdate("3");
  } else if (x >= 97 && x <= 97 + keyWidth && y >= 33 && y <= 33 + keyHeight ) {
    KeyboardUpdate("4");
  } else if (x >= 129 && x <= 129 + keyWidth && y >= 33 && y <= 33 + keyHeight ) {
    KeyboardUpdate("5");
  } else if (x >= 161 && x <= 161 + keyWidth && y >= 33 && y <= 33 + keyHeight ) {
    KeyboardUpdate("6");
  } else if (x >= 193 && x <= 193 + keyWidth && y >= 33 && y <= 33 + keyHeight ) {
    KeyboardUpdate("7");
  } else if (x >= 225 && x <= 225 + keyWidth && y >= 33 && y <= 33 + keyHeight ) {
    KeyboardUpdate("8");
  } else if (x >= 257 && x <= 257 + keyWidth && y >= 33 && y <= 33 + keyHeight ) {
    KeyboardUpdate("9");
  } else if (x >= 289 && x <= 289 + keyWidth && y >= 33 && y <= 33 + keyHeight ) {
    KeyboardUpdate("0");
  }
  //Row 2
  else if (x >= 1 && x <= 1 + keyWidth && y >= 75 && y <= 75 + keyHeight ) {
    KeyboardUpdate("q");
  } else if (x >= 33 && x <= 33 + keyWidth && y >= 75 && y <= 75 + keyHeight ) {
    KeyboardUpdate("w");
  } else if (x >= 65 && x <= 65 + keyWidth && y >= 75 && y <= 75 + keyHeight ) {
    KeyboardUpdate("e");
  } else if (x >= 97 && x <= 97 + keyWidth && y >= 75 && y <= 75 + keyHeight ) {
    KeyboardUpdate("r");
  } else if (x >= 129 && x <= 129 + keyWidth && y >= 75 && y <= 75 + keyHeight ) {
    KeyboardUpdate("t");
  } else if (x >= 161 && x <= 161 + keyWidth && y >= 75 && y <= 75 + keyHeight ) {
    KeyboardUpdate("z");
  } else if (x >= 193 && x <= 193 + keyWidth && y >= 75 && y <= 75 + keyHeight ) {
    KeyboardUpdate("u");
  } else if (x >= 225 && x <= 225 + keyWidth && y >= 75 && y <= 75 + keyHeight ) {
    KeyboardUpdate("i");
  } else if (x >= 257 && x <= 257 + keyWidth && y >= 75 && y <= 75 + keyHeight ) {
    KeyboardUpdate("o");
  } else if (x >= 289 && x <= 289 + keyWidth && y >= 75 && y <= 75 + keyHeight ) {
    KeyboardUpdate("p");
  }
  //Row 3
  else if (x >= 17 && x <= 17 + keyWidth && y >= 117 && y <= 117 + keyHeight ) {
    KeyboardUpdate("a");
  } else if (x >= 49 && x <= 49 + keyWidth && y >= 117 && y <= 117 + keyHeight ) {
    KeyboardUpdate("s");
  } else if (x >= 81 && x <= 81 + keyWidth && y >= 117 && y <= 117 + keyHeight ) {
    KeyboardUpdate("d");
  } else if (x >= 113 && x <= 113 + keyWidth && y >= 117 && y <= 117 + keyHeight ) {
    KeyboardUpdate("f");
  } else if (x >= 145 && x <= 145 + keyWidth && y >= 117 && y <= 117 + keyHeight ) {
    KeyboardUpdate("g");
  } else if (x >= 177 && x <= 177 + keyWidth && y >= 117 && y <= 117 + keyHeight ) {
    KeyboardUpdate("h");
  } else if (x >= 209 && x <= 209 + keyWidth && y >= 117 && y <= 117 + keyHeight ) {
    KeyboardUpdate("j");
  } else if (x >= 241 && x <= 241 + keyWidth && y >= 117 && y <= 117 + keyHeight ) {
    KeyboardUpdate("k");
  } else if (x >= 273 && x <= 273 + keyWidth && y >= 117 && y <= 117 + keyHeight ) {
    KeyboardUpdate("l");
  }
  //Row 4
  else if (x >= 1 && x <= 1 + keyWidth && y >= 159 && y <= 159 + keyHeight ) {
    KeyboardUpdate("y");
  } else if (x >= 33 && x <= 33 + keyWidth && y >= 159 && y <= 159 + keyHeight ) {
    KeyboardUpdate("x");
  } else if (x >= 65 && x <= 65 + keyWidth && y >= 159 && y <= 159 + keyHeight ) {
    KeyboardUpdate("c");
  } else if (x >= 97 && x <= 97 + keyWidth && y >= 159 && y <= 159 + keyHeight ) {
    KeyboardUpdate("v");
  } else if (x >= 129 && x <= 129 + keyWidth && y >= 159 && y <= 159 + keyHeight ) {
    KeyboardUpdate("b");
  } else if (x >= 161 && x <= 161 + keyWidth && y >= 159 && y <= 159 + keyHeight ) {
    KeyboardUpdate("n");
  } else if (x >= 193 && x <= 193 + keyWidth && y >= 159 && y <= 159 + keyHeight ) {
    KeyboardUpdate("m");
  } else if (x >= 225 && x <= 225 + keyWidth && y >= 159 && y <= 159 + keyHeight ) {
    KeyboardUpdate(",");
  } else if (x >= 257 && x <= 257 + keyWidth && y >= 159 && y <= 159 + keyHeight ) {
    KeyboardUpdate(".");
  } else if (x >= 289 && x <= 289 + keyWidth && y >= 159 && y <= 159 + keyHeight ) {
    KeyboardUpdate("-");
  }
  //Row 5
  else if (x >= 1 && x <= 1 + 30 && y >= 201 && y <= 201 + 33 ) {
    KeyboardUpdate("remove");
  } else if (x >= 33 && x <= 33 + 78 && y >= 201 && y <= 201 + 33 ) {
    KeyboardUpdate("shift");
  } else if (x >= 113 && x <= 113 + 110 && y >= 201 && y <= 201 + 33 ) {
    KeyboardUpdate("space");
  } else if (x >= 225 && x <= 225 + 94 && y >= 201 && y <= 201 + 33 ) {
    KeyboardUpdate("apply");
  }

}
void KeyboardUpdate(String key) {
  if(keybuffer.length() >= 23){
    Serial.println("Overflow!");
    return false;  
  }
  if (key == "remove") {
    keybuffer = keybuffer.substring(0, keybuffer.length() - 1);
    myGLCD.setColor(BLACK);
    myGLCD.fillRect(40, 5,320, 29);
    myGLCD.setColor(WHITE);
  } else if (key == "space") keybuffer += " ";
  else if (key == "apply") SubmitKeyValue(keybuffer);
  else if (key == "shift") {
    shiftP = !shiftP;
    PrintKeyboard(shiftP);
  }
  else {
    if (shiftP) {
      if (key == "0")keybuffer += "=";
      else if (key == "1")keybuffer += "!";
      else if (key == "2")keybuffer += "\"";
      else if (key == "3")keybuffer += "?";
      else if (key == "4")keybuffer += "$";
      else if (key == "5")keybuffer += "%";
      else if (key == "6")keybuffer += "&";
      else if (key == "7")keybuffer += "/";
      else if (key == "8")keybuffer += "(";
      else if (key == "9")keybuffer += ")";
      else if (key == ",")keybuffer += ";";
      else if (key == ".")keybuffer += ":";
      else if (key == "-")keybuffer += "_";
      else {
        key.toUpperCase();
        keybuffer += key;  
      }
    }
    else keybuffer += key;
  }
  myGLCD.print(keybuffer, 40, 5);
  delay(150);
}
void SubmitKeyValue(String input){
  keybuffer = "";
  shiftP = false;
  myGLCD.fillScreen(BLACK);
  myGLCD.print(input,0,0);
}

void PrintKeyboard(bool shift) {
  myGLCD.setTextSize(2);

  myGLCD.setColor(RED);
  myGLCD.drawRect(0, 0, 0 + 30, 0 + 24); //exit

  myGLCD.setColor(WHITE);
  myGLCD.drawRect(1, 33, 1 + keyWidth, 33 + keyHeight); //1
  myGLCD.drawRect(33, 33, 33 + keyWidth, 33 + keyHeight); //2
  myGLCD.drawRect(65, 33, 65 + keyWidth, 33 + keyHeight); //3
  myGLCD.drawRect(97, 33, 97 + keyWidth, 33 + keyHeight); //4
  myGLCD.drawRect(129, 33, 129 + keyWidth, 33 + keyHeight); //5
  myGLCD.drawRect(161, 33, 161 + keyWidth, 33 + keyHeight); //6
  myGLCD.drawRect(193, 33, 193 + keyWidth, 33 + keyHeight); //7
  myGLCD.drawRect(225, 33, 225 + keyWidth, 33 + keyHeight); //8
  myGLCD.drawRect(257, 33, 257 + keyWidth, 33 + keyHeight); //9
  myGLCD.drawRect(289, 33, 289 + keyWidth, 33 + keyHeight); //0

  myGLCD.drawRect(1, 75, 1 + keyWidth, 75 + keyHeight); //q
  myGLCD.drawRect(33, 75, 33 + keyWidth, 75 + keyHeight); //w
  myGLCD.drawRect(65, 75, 65 + keyWidth, 75 + keyHeight); //e
  myGLCD.drawRect(97, 75, 97 + keyWidth, 75 + keyHeight); //r
  myGLCD.drawRect(129, 75, 129 + keyWidth, 75 + keyHeight); //t
  myGLCD.drawRect(161, 75, 161 + keyWidth, 75 + keyHeight); //z
  myGLCD.drawRect(193, 75, 193 + keyWidth, 75 + keyHeight); //u
  myGLCD.drawRect(225, 75, 225 + keyWidth, 75 + keyHeight); //i
  myGLCD.drawRect(257, 75, 257 + keyWidth, 75 + keyHeight); //o
  myGLCD.drawRect(289, 75, 289 + keyWidth, 75 + keyHeight); //p

  myGLCD.drawRect(17, 117, 17 + keyWidth, 117 + keyHeight); //a
  myGLCD.drawRect(49, 117, 49 + keyWidth, 117 + keyHeight); //s
  myGLCD.drawRect(81, 117, 81 + keyWidth, 117 + keyHeight); //d
  myGLCD.drawRect(113, 117, 113 + keyWidth, 117 + keyHeight); //f
  myGLCD.drawRect(145, 117, 145 + keyWidth, 117 + keyHeight); //g
  myGLCD.drawRect(177, 117, 177 + keyWidth, 117 + keyHeight); //h
  myGLCD.drawRect(209, 117, 209 + keyWidth, 117 + keyHeight); //j
  myGLCD.drawRect(241, 117, 241 + keyWidth, 117 + keyHeight); //k
  myGLCD.drawRect(273, 117, 273 + keyWidth, 117 + keyHeight); //l

  myGLCD.drawRect(1, 159, 1 + keyWidth, 159 + keyHeight); //y
  myGLCD.drawRect(33, 159, 33 + keyWidth, 159 + keyHeight); //x
  myGLCD.drawRect(65, 159, 65 + keyWidth, 159 + keyHeight); //c
  myGLCD.drawRect(97, 159, 97 + keyWidth, 159 + keyHeight); //v
  myGLCD.drawRect(129, 159, 129 + keyWidth, 159 + keyHeight); //b
  myGLCD.drawRect(161, 159, 161 + keyWidth, 159 + keyHeight); //n
  myGLCD.drawRect(193, 159, 193 + keyWidth, 159 + keyHeight); //m
  myGLCD.drawRect(225, 159, 225 + keyWidth, 159 + keyHeight); //,
  myGLCD.drawRect(257, 159, 257 + keyWidth, 159 + keyHeight); //.
  myGLCD.drawRect(289, 159, 289 + keyWidth, 159 + keyHeight); //-

  if (shift) {

    myGLCD.setColor(RED);
    myGLCD.drawRect(1, 201, 1 + 30, 201 + 33); //remove
    myGLCD.setColor(WHITE);
    myGLCD.fillRect(33, 201, 33 + 78, 201 + 33); //shift
    myGLCD.drawRect(113, 201, 113 + 110, 201 + 33); //space
    myGLCD.setColor(GREEN);
    myGLCD.drawRect(225, 201, 225 + 94, 201 + 33); //apply
    myGLCD.setColor(WHITE);

    myGLCD.setColor(RED);
    myGLCD.print("<<", 3, 5);
    myGLCD.setColor(WHITE);

    myGLCD.print("!", 11, 45);
    myGLCD.print("\"", 43, 45);
    myGLCD.print("?", 75, 45);
    myGLCD.print("$", 107, 45);
    myGLCD.print("%", 139, 45);
    myGLCD.print("&", 171, 45);
    myGLCD.print("/", 203, 45);
    myGLCD.print("(", 235, 45);
    myGLCD.print(")", 267, 45);
    myGLCD.print("=", 299, 45);

    myGLCD.print("Q", 11, 85);
    myGLCD.print("W", 43, 85);
    myGLCD.print("E", 75, 85);
    myGLCD.print("R", 107, 85);
    myGLCD.print("T", 139, 85);
    myGLCD.print("Z", 171, 85);
    myGLCD.print("U", 203, 85);
    myGLCD.print("I", 235, 85);
    myGLCD.print("O", 267, 85);
    myGLCD.print("P", 299, 85);


    myGLCD.print("A", 27, 128);
    myGLCD.print("S", 59, 128);
    myGLCD.print("D", 91, 128);
    myGLCD.print("F", 123, 128);
    myGLCD.print("g", 155, 128);
    myGLCD.print("H", 187, 128);
    myGLCD.print("J", 219, 128);
    myGLCD.print("K", 251, 128);
    myGLCD.print("L", 283, 128);

    myGLCD.print("Y", 11, 170);
    myGLCD.print("X", 43, 170);
    myGLCD.print("C", 75, 170);
    myGLCD.print("V", 107, 170);
    myGLCD.print("B", 139, 170);
    myGLCD.print("N", 171, 170);
    myGLCD.print("M", 203, 170);
    myGLCD.print(";", 235, 170);
    myGLCD.print(":", 267, 170);
    myGLCD.print("_", 299, 170);

    myGLCD.print("<", 9, 208);
    myGLCD.setColor(BLACK);
    myGLCD.print("shift", 44 , 208);
    myGLCD.setColor(WHITE);
    myGLCD.print("space", 134, 208);
    myGLCD.print("apply", 245, 208);

  }
  else {

    myGLCD.setColor(RED);
    myGLCD.drawRect(1, 201, 1 + 30, 201 + 33); //remove
    myGLCD.setColor(BLACK);
    myGLCD.fillRect(33, 201, 33 + 78, 201 + 33); //clear shift
    myGLCD.setColor(WHITE);
    myGLCD.drawRect(33, 201, 33 + 78, 201 + 33); //shift
    myGLCD.drawRect(113, 201, 113 + 110, 201 + 33); //space
    myGLCD.setColor(GREEN);
    myGLCD.drawRect(225, 201, 225 + 94, 201 + 33); //apply
    myGLCD.setColor(WHITE);

    myGLCD.setColor(RED);
    myGLCD.print("<<", 3, 5);
    myGLCD.setColor(WHITE);

    myGLCD.print("1", 11, 45);
    myGLCD.print("2", 43, 45);
    myGLCD.print("3", 75, 45);
    myGLCD.print("4", 107, 45);
    myGLCD.print("5", 139, 45);
    myGLCD.print("6", 171, 45);
    myGLCD.print("7", 203, 45);
    myGLCD.print("8", 235, 45);
    myGLCD.print("9", 267, 45);
    myGLCD.print("0", 299, 45);

    myGLCD.print("q", 11, 85);
    myGLCD.print("w", 43, 85);
    myGLCD.print("e", 75, 85);
    myGLCD.print("r", 107, 85);
    myGLCD.print("t", 139, 85);
    myGLCD.print("z", 171, 85);
    myGLCD.print("u", 203, 85);
    myGLCD.print("i", 235, 85);
    myGLCD.print("o", 267, 85);
    myGLCD.print("p", 299, 85);

    myGLCD.print("a", 27, 128);
    myGLCD.print("s", 59, 128);
    myGLCD.print("d", 91, 128);
    myGLCD.print("f", 123, 128);
    myGLCD.print("g", 155, 128);
    myGLCD.print("h", 187, 128);
    myGLCD.print("j", 219, 128);
    myGLCD.print("k", 251, 128);
    myGLCD.print("l", 283, 128);

    myGLCD.print("y", 11, 170);
    myGLCD.print("x", 43, 170);
    myGLCD.print("c", 75, 170);
    myGLCD.print("v", 107, 170);
    myGLCD.print("b", 139, 170);
    myGLCD.print("n", 171, 170);
    myGLCD.print("m", 203, 170);
    myGLCD.print(",", 235, 170);
    myGLCD.print(".", 267, 170);
    myGLCD.print("-", 299, 170);

    myGLCD.print("<", 9, 208);
    myGLCD.print("shift", 44 , 208);
    myGLCD.print("space", 134, 208);
    myGLCD.print("apply", 245, 208);
  }
}
