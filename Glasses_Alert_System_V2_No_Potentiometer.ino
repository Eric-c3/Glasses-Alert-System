
// Eric Chao
// Glasses_Alert_System_V2

// Pin definitions
const int trigPin = 9;    // Trigger pin for ultrasonic sensor
const int echoPin = 10;   // Echo pin for ultrasonic sensor
const int buzzerPin = 11; // Buzzer pin

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600); // Initialize Serial Monitor
}

void loop() {
  // Measure distance
  long duration, distanceCm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2; // Convert to centimeters

  // Convert to feet
  float distanceFeet = distanceCm / 30.48; // 1 foot = 30.48 cm

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.print(" cm (");
  Serial.print(distanceFeet, 2); // Print distance in feet with two decimal places
  Serial.println(" ft)");

  // Buzzer logic
  if (distanceFeet <= 1.0) { // Within 1 foot threshold
    // Map distance to frequency: closer = higher tone
    // Note that this buzzer will be on glasses so lower Frequency
    // Frequency range: 50 Hz (at 1 foot) to 200 Hz (at 0.1 feet)
    int frequency = map(distanceFeet * 10, 10, 1, 50, 200); // Scale range ... max frequency to 200hz... hurts my ears... 
    frequency = constrain(frequency, 50, 200); // Ensure frequency stays in range
    tone(buzzerPin, frequency);
  } else {
    noTone(buzzerPin); // Turn off buzzer if distance > 1 foot
  }

  delay(100); // Short delay for stability
}
