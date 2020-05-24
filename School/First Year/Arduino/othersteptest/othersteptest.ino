#include <Stepper.h>

int stepsPerRev = 200;
  Stepper myStepper(stepsPerRev, 5, 6, 7, 8);
int i = 0;

  
void setup() {

  Serial.begin(9600);
  myStepper.setSpeed(1000);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:
 
  myStepper.step(800);
  digitalWrite(13, HIGH);
  myStepper.step(800);
  delay(500);
}
