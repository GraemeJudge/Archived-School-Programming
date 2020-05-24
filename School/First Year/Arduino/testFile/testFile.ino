#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(20,4);
  //lcd.cursor();
  //lcd.blink();
  lcd.home();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 1000; i++){
    
    lcd.home();
    
    lcd.print(i);
    delay (1000);
  }
}
