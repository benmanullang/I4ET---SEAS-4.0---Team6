// Define the pins for the ultrasonic sensor and RGB LED
#include <NewPingESP8266.h>
#define TRIGGER_PIN D1
#define ECHO_PIN    D2
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is 400-500cm.
NewPingESP8266 sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Initialization of the sonar

const int redPin = D5;
const int greenPin = D6;

void setup() {
  // Initialize the serial communication for debugging purposes
  Serial.begin(9600);

  // Configure the pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  // Turn off the RGB LED initially
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
}

void loop() {
  // Send a 10us pulse to the ultrasonic sensor to trigger a measurement
  delay(500); // Wait 500ms between pings (about 2 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (US).
 
  // Debugging output
  //Serial.print("Distance: ");
  //Serial.print(uS / US_ROUNDTRIP_CM);
  //Serial.println(" cm");

  // Turn on the red LED if an object is detected within 30 cm, otherwise turn on the green LED
  if (uS / US_ROUNDTRIP_CM <= 30) {
    digitalWrite(redPin, LOW); // Turn on red LED
    digitalWrite(greenPin, HIGH);
    Serial.print("WARNING ! YOUR ARE AT LEAST 30 cm CLOSE | "); // Print Warning message
    Serial.print("Distance: ");
    Serial.print(uS / US_ROUNDTRIP_CM);
    Serial.println(" cm");

  } else {
    digitalWrite(redPin, HIGH); // Turn off red LED
    digitalWrite(greenPin, LOW); // Turn on green LED
  }

  // Wait for a short time before taking the next measurement
  delay(100);
}





