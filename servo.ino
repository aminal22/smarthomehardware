#include <Servo.h>
void activateServo();

Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(12); // Use the correct pin
}

void loop() {
  activateServo();
}
void activateServo() {
  // Code to activate the servo motor
  myServo.write(180);  // Move the servo to the 180-degree position
  delay(2000);
  myServo.write(0);   // Move the servo back to the 0-degree position
  delay(1000);
}