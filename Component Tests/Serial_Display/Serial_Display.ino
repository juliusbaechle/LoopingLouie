// Das serielle Display (neben Knöpfen und Potentiometer) zeigt "hello world!"

#include <LiquidCrystal.h>

LiquidCrystal lcd (7, 6, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("hello world!");
}

void loop() {
  delay(3000);
  lcd.blink();
  delay(3000);
  lcd.noBlink();
}
