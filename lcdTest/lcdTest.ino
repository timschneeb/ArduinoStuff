#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
lcd.begin(16, 2);
}

void loop() 
{
lcd.setCursor(0, 0);
lcd.print("Oben"); //Beginn beim ersten Zeichen in der ersten Zeile mit dem Text „Oben“.
delay (2000); //Zwei Sekunden warten.
lcd.clear(); //Display löschen.
lcd.setCursor(5, 1);
lcd.print("unten"); //Erneuter Beginn beim fünften Zeichen in der zweiten Zeile mit dem Text „Unten“.
delay (2000); //Zwei Sekunden warten.
lcd.clear(); //Display löschen.
}
