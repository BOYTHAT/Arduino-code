#include <Servo.h>

const int triggerPin = 8;   // Trigger pin of the ultrasonic sensor
const int echoPin = 9;     // Echo pin of the ultrasonic sensor
const int servoPin = 7;     // Servo control pin

Servo myServo;              // Create a servo object

const int thresholdDistance = 20;  // Distance threshold for triggering servo movement
const unsigned long interval = 2000; // Interval for servo movement in milliseconds
unsigned long previousTime = 0;   // Variable to store the previous time

int counter = 0;  // Counter for number of times servo moved from 90 to 0 degrees

void setup() {
  Serial.begin(9600);       // Initialize serial communication
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(servoPin); // Attaches the servo on pin 6 to the servo object
  myServo.write(90);         // Set initial position of the servo to 90 degrees
}

void loop() {
  // Ultrasonic sensor measurement
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  int distance = pulseIn(echoPin, HIGH) / 58; // Convert pulse duration to distance in cm
  
  Serial.print("Distance: ");
  Serial.println(distance);

  // Check if distance is less than the threshold
  if (distance < thresholdDistance) {
    if (myServo.read() == 90) {  // Check if the servo is at 90 degrees
      unsigned long startTime = millis();  // Record the start time
      for (int i = 90; i >= 0; i--) { // Move servo incrementally from 90 to 0 degrees
        myServo.write(i);          // Move servo to current degree
        delay(15); // Delay for smoother movement
      }
      counter++;                 // Increment the counter
      unsigned long endTime = millis();    // Record the end time
      float speed = 2000.0 / (endTime - startTime) * 100;  // Calculate speed in degrees per second
      Serial.print("Speed: ");
      Serial.print(speed);
      Serial.println(" degrees/second");
      previousTime = millis();   // Record the time when servo moved
    }
  }
  
  // Check if interval has passed since last servo movement
  if (millis() - previousTime >= interval && myServo.read() == 0) {
    for (int i = 0; i <= 90; i++) { // Move servo incrementally from 0 to 90 degrees
      myServo.write(i);  // Move servo to current degree
      delay(15); // Delay for smoother movement
    }
  }

  // Print counter value to serial monitor
  Serial.print("Counter: ");
  Serial.println(counter);

  delay(200); // Delay for stability
}
