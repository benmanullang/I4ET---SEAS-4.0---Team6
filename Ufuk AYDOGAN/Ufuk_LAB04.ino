#include <ESP8266WiFi.h>

// WiFi network paramaters
const char* ssid = "Kagan";
const char* password = "70977097k";
//Host to connect to and Wifi Client Paramaters
const char* host = "postman-echo.com";
WiFiClient client;
const int httpPort=80;

void setup() {

  Serial.begin(115200);
  delay(10);
  //Conecting to a WiFi Network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() !=WL_CONNECTED) {
    delay(500);
    Serial.print(" . ");
  }
  Serial.println(" ");
  Serial.println("WiFi Connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
  // put your setup code here, to run once:

}

void loop() {

  delay(5000);
  Serial.print("Connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpPort))
  {
    Serial.println("connection failed");
    return;
  }

  String url = "/get";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  unsigned long timeout =millis();
  while (client.available()==0) { 
    if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
    }
  }

  while(client.available()){
    String line =client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
    Serial.println("closing connection");
      
}
