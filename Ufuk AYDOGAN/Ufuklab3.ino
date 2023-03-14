#include "pitches.h"
int sensorPin=A0;
int ledPin= LED_BUILTIN;
int sensorValue=0;


int melody [] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_D5,NOTE_A5, NOTE_B5, NOTE_C5};
int duration = 500;

void setup()
  // put your setup code here, to run once:
{
pinMode(ledPin,OUTPUT);
Serial.begin(9600);
Serial.println("Welcome to the Best Project Ever :), Ferrol 13/03/2023");
}


void loop() {
  // put your main code here, to run repeatedly:
  sensorValue= analogRead(sensorPin);
  if (sensorValue>400)
  {
    digitalWrite(ledPin, LOW);
    for (int thisNote=0; thisNote<8; thisNote++) {
    tone(D3,melody[thisNote],duration);
    Serial.print("WARNING ! Here is quite hot! | ");
  }

  }else
  {
    digitalWrite(ledPin, HIGH);
  }
  Serial.println(sensorValue, DEC);    

}


