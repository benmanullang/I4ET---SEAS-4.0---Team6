#include "dweetESP8266.h"

#define THIG_NAME "teamsixseas"

//Water Level
    int adc_id = A0;
    int HistoryValue = 0;
    char printBuffer[128];

//Pump - RGB LED
    int redPin = D4;
    int greenPin = D3;   
    int valled;

//Connect to wifi
const char* ssid = "";
const char* password = "";

dweet DweetClient;
int i = 0;
float f = 0;
char *key1 = "WaterLevel"; 
char *key2 = "Temperature"; 
char *key3 = "WaterFeedPump";
char *key4 = "HighAlarm";
char *key5 = "Heater";
char *key6 = "OutletValve"; 
char *key7 = "Buzzer";

char val [16];

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

    //Pump - RGB LED Aimen
        // Configure the pins
        pinMode(redPin, OUTPUT);
        pinMode(greenPin, OUTPUT);
        //Set default condition - Heater is OFF
      analogWrite(redPin, 255-valled);
      analogWrite(greenPin, 0-valled);
      //Sending an integer results from LED to Dweet.io
      int valuepump = 0;
      itoa(valuepump, val, 10); // to convert an integer value into a char array 
      Serial.println(val);
      DweetClient.add(key3, val);
      DweetClient.sendAll(THIG_NAME);
      redPin; // the integer 'i' is increased by 1
}

void loop(){

  //Water level requesting...
    Serial.print("Requesting Water Level...");
    int value = analogRead(adc_id);
    if(((HistoryValue>=value) && ((HistoryValue - value) >10))  || ((HistoryValue<value) && ((value - HistoryValue) >10)))
      {
      Serial.println("DONE");
      Serial.println(value);
      HistoryValue = value;
      }

      //Sending Water level - integer to Dweet.io
      itoa(value, val, 10); // to convert an integer value into a char array 
      Serial.println(val);
      DweetClient.add(key1, val);
      DweetClient.sendAll(THIG_NAME);

      //If value below, turn on pump
      if (value < 749){ 
        //Sending to dweet
              int valuepump = 1;
              itoa(valuepump, val, 10); // to convert an integer value into a char array 
              Serial.println(val);
              DweetClient.add(key3, val);
              DweetClient.sendAll(THIG_NAME);
            
            analogWrite(greenPin, 255-valled);
            analogWrite(redPin, 0-valled);
            Serial.println("HEATER ON");
            
              
            } 

      //if ((value >= 300) && (value <600)) {}

      //if value exceed, turn off pump
      if (value >= 750) { 
        //Sending to dweet
              int valuepump = 0;
              itoa(valuepump, val, 10); // to convert an integer value into a char array 
              Serial.println(val);
              DweetClient.add(key3, val);
              DweetClient.sendAll(THIG_NAME);

            Serial.println("High level, turn off Pump");
            analogWrite(redPin, 255-valled);
            analogWrite(greenPin, 0-valled);
            Serial.println("HEATER OFF");
            
              
            }   
   
}
