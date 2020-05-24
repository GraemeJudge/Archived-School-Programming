#include <Stepper.h>

int stepsPerRev = 200;
  Stepper myStepper(stepsPerRev, 5, 6, 7, 8);
int i = 0;
int r = 0;
  
void setup() {

  Serial.begin(9600);
  myStepper.setSpeed(100);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  
}

void Drive(){
    digitalWrite(13, HIGH);
    myStepper.step(800);
    delay(500);
    digitalWrite(13, LOW);
    i = i + 1;
    //Serial.println(i);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (r == 50){
    digitalWrite(12, HIGH);
    Drive();
  } else if (r == 51) {
    digitalWrite(12, LOW);
    Drive();
  } else {
    //Serial.println("No input");
  }
  delay(50);
}
