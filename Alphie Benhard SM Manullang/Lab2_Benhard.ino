byte blue;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(230400);
}

void loop() {
  if (Serial.available())
  {
    blue=Serial.read();
  
    if (blue == 66 )
    {
    Serial.println("ON");
    digitalWrite(LED_BUILTIN, LOW); 
    }
    if (blue == 68) 
    {
    Serial.println("OFF");
    digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}
