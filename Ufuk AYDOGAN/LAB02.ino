char Turnon ='U';
char Turnoff ='K';

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(230400);
  Serial.println("Do you wanna close or open :), please U for turn on, K for turn off");
}

// the loop function runs over and over again forever
void loop() {
  char input=Serial.read();

   if(input == Turnon){
     digitalWrite(LED_BUILTIN, LOW);
   }
  
  if(input == Turnoff){
     digitalWrite(LED_BUILTIN, HIGH);
   }

}