byte benhard;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(230400);
}

void loop() {
  if (Serial.available())
  {
    benhard=Serial.read();
  
    if (benhard == 66 )
    {
    Serial.println("Light: ON");
    digitalWrite(LED_BUILTIN, LOW); 
    }
    if (benhard == 68) 
    {
    Serial.println("Light: OFF");
    digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}
