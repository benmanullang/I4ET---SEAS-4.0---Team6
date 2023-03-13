// Sensor pins
#define sensorPower 7
#define sensorPin A0
int val_wl;
int Led = LED_BUILTIN;
int Button = D1;
int val;

void setup()
{
  pinMode(Led, OUTPUT);
  pinMode(Button, INPUT);
  Serial.begin(9600);
}
void loop() 
{ val = digitalRead(Button);
  if(val==LOW)
  { 
    digitalWrite(sensorPower,LOW);
    Serial.print("Sensor Interrupted");
  }
  if(val==HIGH)
  {
    digitalWrite(sensorPower,HIGH);
    Serial.print("Water level Sensor Value:");
    val_wl = analogRead(sensorPin);
    Serial.println(analogRead(A0));
    delay(100);
  }

}
