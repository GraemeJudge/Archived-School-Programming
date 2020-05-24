#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5 ,6 , 7, 3, POSITIVE);

float AnalogB = 0;
int DigitalB = 0;
float AnalogV = 0;
int QuiesVol = 2.5;

int AnInA = 0;//Sets which port to read analog input from
int AnInB = 1;
String Pole = "N";

void setup() {

  Serial.begin(9600);
  lcd.begin(20,4);
  
}

void loop() {

  lcd.setCursor(0,1);
  lcd.print("B(T)=");
  lcd.setCursor(0,0);
  lcd.print("Vdc(V)=");


  AnalogV = analogRead(AnInA);
  AnalogV = AnalogV * 5 / 1023;
  Serial.print("Vdc(V)= ");
  Serial.println(AnalogV);
  lcd.print(AnalogV);


  AnalogB = analogRead(AnInB);
  AnalogB = AnalogB * 5 / 1023;
  DigitalB = AnalogB;
  AnalogB = (AnalogB - QuiesVol) / 25;

  //if tesla meter output is lower than QuiesVol than it is a south pole
  //else it sets it to a north pole
  if (AnalogB < 2.5)
  {
    Pole = "S";
  } else 
  {
    Pole = "N";
  }
  
  Serial.print("B(T)= ");
  Serial.println(AnalogB + Pole);
  lcd.setCursor(5,1);
  lcd.print(String(AnalogB) + " " + Pole + " ");

  lcd.setCursor(0,3);
  if (AnalogV > AnalogB)
  {
    lcd.print("Vdc gt Vh");
  } else
  {
    lcd.print("Vdc lw Vh");
  }
  
  
  
  Serial.println(" ");
  delay (200);
}
