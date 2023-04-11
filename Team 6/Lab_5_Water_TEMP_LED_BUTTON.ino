#include "dweetESP8266.h"

#define THIG_NAME "teamsixseas" // Put here your thing name

//Water Level
int adc_id = A0;
int HistoryValue = 0;
char printBuffer[128];

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

//Push Button (As Outlet Valve from tank to engine)
int Led = LED_BUILTIN; //define LED pin
int Button = D1; //define push button pin
int valbutton;//define digital variable val

//Connect to wifi
const char* ssid = "J.L.F";
const char* password = "20487760";

dweet DweetClient;
int i = 0; // a random initial value
float f = 0; //another random initial value
char *key = "WaterLevel"; //this is the name of the parameter sent to Dweet.io
char *key2 = "Temperature"; //this is the name of the parameter sent to Dweet.io
char *key3 = "Heater"; //this is the name of the parameter sent to Dweet.io
char *key4 = "OutletValve"; //this is the name of the parameter sent to Dweet.io

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

    //Temperature Sensor
    sensors.begin();

    //RGB LED as a Heater Indicator (Only using Red (Heater On) and Green (Heater off))
    pinMode(redpin, OUTPUT);
    pinMode (greenpin, OUTPUT);

    //Push Button as a Outlet Valve
    pinMode(Led, OUTPUT); //set the LED pin as an output pin 
    pinMode (Button, INPUT); //set the button pin as as input pin

    //Set default condition - Heater is OFF
    analogWrite(redpin, 255-valled);
      //Sending an integer results from LED to Dweet.io
      itoa(redpin, val, 10); // to convert an integer value into a char array 
      Serial.println(val);
      DweetClient.add(key3, val);
      DweetClient.sendAll(THIG_NAME);
      redpin; // the integer 'i' is increased by 1

    //Set default condition - Outlet Valve is CLOSED
    valbutton = digitalRead(Button);
      //Sending an integer results from Push Button to Dweet.io
      itoa(valbutton, val, 10); // to convert an integer value into a char array 
      Serial.println(val);
      DweetClient.add(key4, val);
      DweetClient.sendAll(THIG_NAME);
      valbutton; // the integer 'i' is increased by 1
     
}

void loop(){

  //Water level requesting...
  Serial.print("Requesting Water Level...");
  delay (1000);
  int value = analogRead(adc_id);
    if(((HistoryValue>=value) && ((HistoryValue - value) >10))  || ((HistoryValue<value) && ((value - HistoryValue) >10)))
      {
      Serial.println("DONE");
      Serial.println(value);
      HistoryValue = value;
      }

      // EXAMPLE 1: Sending an integer to Dweet.io
      itoa(value, val, 10); // to convert an integer value into a char array 
      Serial.println(val);
      DweetClient.add(key, val);
      DweetClient.sendAll(THIG_NAME);
      value; // the integer 'i' is increased by 1
    
        // Every 5 seconds the value for parameter 1key' is requested
        //delay (1000);
        //If water level
          if (value >= 250) { 

              //Temperature requesting process. During this process, no LED will be on.
              delay (1000);
              analogWrite(redpin, 0-valled);
              analogWrite(greenpin, 0-valled);
              Serial.print("Requesting temperature...");
              sensors. requestTemperatures();
              Serial.println("DONE");
              Serial.print("Temperature is: ");
              Serial.println(sensors.getTempCByIndex(0));

              // Sending a float results from Temperature sensor to Dweet.io
                String temp = String(f,2); // 'f' is converted to String with 2 decimals
                temp.toCharArray(val, 16); // temp is converted to a char array Serial.println(val);
                DweetClient.add(key2, val);
                DweetClient.sendAll(THIG_NAME);
                f = sensors.getTempCByIndex(0);
              
              // If Temperature is above 23, red LED will be on (Heater is Off).
              if (sensors.getTempCByIndex(0) > 23) {
                Serial.println("Temperature is above 23 C.");
                analogWrite(redpin, 255-valled);
                //    delay (2000);
                //analogWrite(redpin, 0-val);
                Serial.println("HEATER OFF");
                Serial.println("Engine Cooling Water in good condition");
                Serial.println("Outlet Valve is safe to be Opened");

                //Volume and Temperature are in goood condition, water can be pumped to Engine
                Serial.println("Outlet Valve is stand by");
                
                delay(5000); //delay to push the button - Default: ON
                valbutton = digitalRead(Button); //we read the state of the button
                if (valbutton == LOW) //if the button is pressed, we turn on the LED
                    {     
                    digitalWrite(Led, HIGH);
                    Serial.println("Outlet Valve is Open");
                    
                    }
                else
                    {
                    digitalWrite(Led, LOW);
                    Serial.println("Outlet Valve is Closed");
                    
                    }

                
                //Sending an integer results from LED to Dweet.io
                itoa(redpin, val, 10); // to convert an integer value into a char array 
                Serial.println(val);
                DweetClient.add(key3, val);
                DweetClient.sendAll(THIG_NAME);
                redpin; // the integer 'i' is increased by 1
              
                //Sending an integer results from Push Button to Dweet.io
                itoa(valbutton, val, 10); // to convert an integer value into a char array 
                Serial.println(val);
                DweetClient.add(key4, val);
                DweetClient.sendAll(THIG_NAME);
                valbutton; // the integer 'i' is increased by 1
                
                  } 
                  
              // If Temperature below 25, green LED will be on.
              if (sensors.getTempCByIndex(0) <= 23) {
                Serial.println("Temperature is below 23 C.");
                analogWrite(greenpin, 255-valled);
                //delay (2000);
                //analogWrite(greenpin, 0-val);
                Serial.println("HEATER ON");

                // EXAMPLE 1: Sending an integer results from LED to Dweet.io
                itoa(greenpin, val, 10); // to convert an integer value into a char array 
                Serial.println(val);
                DweetClient.add(key3, val);
                DweetClient.sendAll(THIG_NAME);
                greenpin; // the integer 'i' is increased by 1
              
                  }
            }
      
        if (value < 250){ 
            Serial.println("Water volume is not enough.");
            } 
}