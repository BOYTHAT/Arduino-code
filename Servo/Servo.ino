#include <Servo.h>

// Create a servo object
Servo servoMotor;

void setup() {
  // Attach the servo to pin 9
  servoMotor.attach(9);
}

void loop() {
  // Move the servo from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle++) {
    servoMotor.write(angle);
    delay(10); // Adjust delay as needed for your servo
  }
  
  // Move the servo from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle--) {
    servoMotor.write(angle);
    delay(10); // Adjust delay as needed for your servo
  }
}
