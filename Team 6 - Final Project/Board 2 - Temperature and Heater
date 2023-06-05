#include "dweetESP8266.h"

#define THIG_NAME "teamsixseas" // Put here your thing name

//Temperature Sensor
#include <OneWire.h>
#include <DallasTemperature.h>
int temp = 25;
// Data wire is plugged into D1 on the ESP8266
#define ONE_WIRE_BUS D4
// A OneWire instance is created to communicate with the sensor
OneWire oneWire(ONE_WIRE_BUS);
// We connect the OneWire bus with the temperature sensor.
DallasTemperature sensors(&oneWire);

//RGB LED as a Heater Indicator (Only using Red (Heater On) and Green (Heater off))
int redpin = D3; //pin for the red LED
int greenpin = D2;//pin for the green LED
int valled;

//Connect to wifi
const char* ssid = "J.L.F";
const char* password = "20487760";

dweet DweetClient;
int i = 0; // a random initial value
float f = 0; //another random initial value
char *key1 = "WaterLevel"; //this is the name of the parameter sent to Dweet.io
char *key2 = "Temperature"; //this is the name of the parameter sent to Dweet.io
char *key3 = "WaterFeedPump"; //this is the name of the parameter sent to Dweet.io
char *key4 = "HighAlarm"; //this is the name of the parameter sent to Dweet.io
char *key5 = "Heater"; //this is the name of the parameter sent to Dweet.io
char *key6 = "OutletValve"; //this is the name of the parameter sent to Dweet.io
char *key7 = "Buzzer"; //this is the name of the parameter sent to Dweet.io

char val [16]; // it stores a number composed by up to 16 characters

void setup() {
    // Start serial
    Serial. begin(115200);
    
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

    //Temperature Sensor
    sensors.begin();

    //RGB LED as a Heater Indicator (Only using Red (Heater On) and Green (Heater off))
    pinMode(redpin, OUTPUT);
    pinMode (greenpin, OUTPUT);

    //Set default condition - Heater is OFF
    analogWrite(redpin, 255-valled);
      //Sending an integer results from LED to Dweet.io
      int heater = 0;
      itoa(heater, val, 10); // to convert an integer value into a char array 
      Serial.println(val);
      DweetClient.add(key5, val);
      DweetClient.sendAll(THIG_NAME);}

void loop(){
  //Reading Waterlevel from dweet
  String value = DweetClient.getDweet(THIG_NAME, key1);
      int intvalue = value.toInt();
      itoa(intvalue, val, 10);
      Serial.println(value);
  
          if (intvalue >= 500) { 
              //Temperature requesting process.
              sensors. requestTemperatures();
              Serial.println(sensors.getTempCByIndex(0));
                String temp = String(f,2); 
                temp.toCharArray(val, 16);
                DweetClient.add(key2, val);
                DweetClient.sendAll(THIG_NAME);
                f = sensors.getTempCByIndex(0);
                        
              // Heater logic
              if (sensors.getTempCByIndex(0) > 31) {             
                    int heater = 0;
                    itoa(heater, val, 10);
                    Serial.println(val);
                    DweetClient.add(key5, val);
                    DweetClient.sendAll(THIG_NAME);
                analogWrite(greenpin, 0-valled);
                analogWrite(redpin, 255-valled);} 
                  
              if (sensors.getTempCByIndex(0) <= 30) {               
                    int heater = 1;
                    itoa(heater, val, 10);
                    Serial.println(val);
                    DweetClient.add(key5, val);
                    DweetClient.sendAll(THIG_NAME);              
                analogWrite(redpin, 0-valled);
                analogWrite(greenpin, 255-valled);}}}
