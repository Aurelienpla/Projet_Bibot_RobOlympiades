#include <Servo.h>

Servo servoA;
Servo servoB;

int pos = 90;    // variable to store the servo position 

void setup() {
  // put your setup code here, to run once:
  servoA.attach(3);
  servoB.attach(5);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  servoA.write(pos);
  servoB.write(pos);
}
