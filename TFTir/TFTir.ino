#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 200
#define MAXPRESSURE 1000

const int XP=7,XM=A1,YP=A2,YM=6; //240x320 ID=0x9335
const int TS_LEFT=907,TS_RT=136,TS_TOP=670,TS_BOT=139;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn, random_btn, lsd_btn, stop_btn;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width())*(-1)+240; //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height())*(-1)+240;
    }
    return pressed;
}

#define TFT_BLACK   0x0000
#define TFT_BLUE    0x001F
#define TFT_RED     0xF800
#define TFT_GREEN   0x07E0
#define TFT_CYAN    0x07FF
#define TFT_MAGENTA 0xF81F
#define TFT_YELLOW  0xFFE0
#define TFT_WHITE   0xFFFF

void setup(void)
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(0);            //PORTRAIT
    tft.fillScreen(TFT_BLACK);
    on_btn.initButton(&tft,  60, 40, 1000, 40, TFT_WHITE, TFT_CYAN, TFT_BLACK, "ON", 2);
    off_btn.initButton(&tft, 180, 40, 100, 40, TFT_WHITE, TFT_CYAN, TFT_BLACK, "OFF", 2);
    on_btn.drawButton(false);
    off_btn.drawButton(false);
    random_btn.initButton(&tft,  60, 60, 100, 40, TFT_WHITE, TFT_CYAN, TFT_BLACK, "Random", 2);
    lsd_btn.initButton(&tft, 180, 60, 100, 40, TFT_WHITE, TFT_CYAN, TFT_BLACK, "LSD", 2);
    lsd_btn.initButton(&tft, 180, 60, 100, 40, TFT_WHITE, TFT_CYAN, TFT_BLACK, "Stop", 2);
   
    random_btn.drawButton(false);
    lsd_btn.drawButton(false);
    stop_btn.drawButton(false);
  
    tft.fillRect(40, 80, 160, 80, TFT_RED);
}

/* two buttons are quite simple
 */
void loop(void)
{
    bool down = Touch_getXY();
    on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
    off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
    if (on_btn.justReleased())
        on_btn.drawButton();
    if (off_btn.justReleased())
        off_btn.drawButton();
    if (on_btn.justPressed()) {
        on_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, TFT_GREEN);
    }
    if (off_btn.justPressed()) {
        off_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, TFT_RED);
    }
}
