#include "dweetESP8266.h"

#define THIG_NAME "teamsixseas" // Put here your thing name

//Ultrasonic Sensor
    #include <NewPingESP8266.h>
    #define TRIGGER_PIN D1
    #define ECHO_PIN    D2
    #define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is 400-500cm.
    NewPingESP8266 sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Initialization of the sonar

//HighAlarm - Buzzer
    #include "pitches.h"
    int melody [] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_D5,NOTE_A5, NOTE_B5, NOTE_C5};
    int duration = 5;

//Connect to wifi
const char* ssid = "J.L.F";
const char* password = "20487760";

dweet DweetClient;
int i = 0; // a random initial value
float f = 0; //another random initial value
char *key1 = "WaterLevel"; //this is the name of the parameter sent to Dweet.io
char *key2 = "Temperature"; //this is the name of the parameter sent to Dweet.io
char *key3 = "WaterFeedPump"; //this is the name of the parameter sent to Dweet.io
char *key4 = "Ultrasonic"; //this is the name of the parameter sent to Dweet.io
char *key5 = "Heater"; //this is the name of the parameter sent to Dweet.io
char *key6 = "OutletValve"; //this is the name of the parameter sent to Dweet.io
char *key7 = "Buzzer"; //this is the name of the parameter sent to Dweet.io

char val [16]; // it stores a number composed by up to 16 characters

void setup() {
    // Start serial
    Serial. begin(115200);
    //a small delay is added to initialize the serial port
    delay(10);

    // Connecting to a WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());   

    //Innitial condition: buzzer OFF
    int buzzer = 0;
    itoa(buzzer, val, 10); // to convert an integer value into a char array 
    Serial.println(val);
    DweetClient.add(key7, val);
    DweetClient.sendAll(THIG_NAME);

}

void loop(){
  //System Safety (Ultrasonic Sensor): ON
      
      unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (US).

      //Sending an integer to Dweet.io
          itoa(uS, val, 10); // to convert an integer value into a char array 
          Serial.println(val);
          DweetClient.add(key4, val);
          DweetClient.sendAll(THIG_NAME);

      // Level measuring
      //Serial.print(" WATER LEVEL IS : "); // Print Warning message
      //Serial.print(15 - uS / US_ROUNDTRIP_CM);
      //Serial.println(" cm");

        if (uS <= 449) { 
          int buzzer = 1;
          itoa(buzzer, val, 10); // to convert an integer value into a char array 
          Serial.println(val);
          DweetClient.add(key7, val);
          DweetClient.sendAll(THIG_NAME);
        for (int thisNote=0; thisNote<8; thisNote++) {
          tone(D3,melody[thisNote],5);
          delay(500);
         
        }
        //Serial.print("EXCEEDED MAX LEVEL ALARME");
      }
      if (uS > 450) { 
          int buzzer = 0;
          itoa(buzzer, val, 10); // to convert an integer value into a char array 
          Serial.println(val);
          DweetClient.add(key7, val);
          DweetClient.sendAll(THIG_NAME);
                 
        
        //Serial.print("EXCEEDED MAX LEVEL ALARME");
      }
}
