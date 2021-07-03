#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd[] = {
  LiquidCrystal_I2C(0x27,16,2),
  LiquidCrystal_I2C(0x26,16,2),
  LiquidCrystal_I2C(0x25,16,2),
  LiquidCrystal_I2C(0x24,16,2),
  LiquidCrystal_I2C(0x23,16,2),
  LiquidCrystal_I2C(0x22,16,2),
  LiquidCrystal_I2C(0x21,16,2),
  LiquidCrystal_I2C(0x20,16,2)
};

void setup(){
  for(int i = 0; i < 8; i++){
    lcd[i].init();
    lcd[i].setCursor(2,0);
    lcd[i].print("Hello World!");
    lcd[i].setCursor(2, 1);
    lcd[i].print("Display 0x");
    lcd[i].print(27 - i);
  }
}


void loop() {  
  digitalWrite(13, HIGH);
  for(int i = 0; i < 8; i++)
    lcd[i].backlight();
  delay(1000); 

  digitalWrite(13, LOW);
  for(int i = 0; i < 8; i++)
    lcd[i].noBacklight();
  delay(1000);
}
