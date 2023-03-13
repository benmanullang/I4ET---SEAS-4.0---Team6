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

//RGB LED (Only using Red and Green)
int redpin = D1; //pin for the red LED
int greenpin = D2;//pin for the green LED
int val;

void setup(void)
{
  //Temperature Sensor
  Serial.begin(9600);
  Serial.println("Starting to measure temperature...");
  sensors.begin();

  //RGB LED (Only using Red and Green)
  pinMode(redpin, OUTPUT);
  pinMode (greenpin, OUTPUT);
}

void loop(void)
{

  //Temperature requesting process. During this process, no LED will be on.
  delay (3000);
  Serial.print("Requesting temperature...");
  sensors. requestTemperatures();
  Serial.println("DONE");
  Serial.print("Temperature is: ");
  Serial.println(sensors.getTempCByIndex(0));
  
  // If Temperature is above 25, red LED will be on.
  if (sensors.getTempCByIndex(0) > 25) {
    Serial.println("Temperature is above 25 C.");
    analogWrite(redpin, 255-val);
        delay (2000);
    analogWrite(redpin, 0-val);
      } 
      
  // If Temperature below 25, green LED will be on.
  if (sensors.getTempCByIndex(0) <= 25) {
    Serial.println("Temperature is below 25 C.");
    analogWrite(greenpin, 255-val);
    delay (2000);
    analogWrite(greenpin, 0-val);
      }
}
