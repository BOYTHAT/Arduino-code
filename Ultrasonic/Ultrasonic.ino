#define trigPin 3
#define echoPin 2

long duration; // variable to store the duration of the pulse

void setup() {
  pinMode(trigPin, OUTPUT); // set trigger pin as output
  pinMode(echoPin, INPUT); // set echo pin as input
  Serial.begin(9600); // start serial communication at 9600 baud
}
void loop() {
  // clear the trigger pin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // trigger the sensor by setting the trigPin high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // read the echo pin, pulseIn() returns the duration (length of the pulse) in microseconds
  duration = pulseIn(echoPin, HIGH);

  // calculate the distance (sound travels at 34300 cm/s, divided by 2 for round trip)
  int distance = duration * 0.034 / 2;

  // print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100); // wait 100 milliseconds before next measurement
}
