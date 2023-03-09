byte Myletter;  // Define a variable to store the input value

void setup() {
  Serial.begin(230400);  // Set the data rate in bits per second (baud) for serial data transmission
  pinMode(LED_BUILTIN,OUTPUT); // Set the LED_BUILTIN pin as output
  digitalWrite(LED_BUILTIN,HIGH); // Start with the LED off
}

void loop() {
  if (Serial.available() > 0) {  // Check if there is any input from the keyboard
    Myletter = Serial.read();    // Read the input value

    if (Myletter == 65) {       // If the input value is A , turn on the LED
      digitalWrite(LED_BUILTIN, LOW);
    } else if (Myletter == 78) {    // If the input value is N , turn off the LED
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}