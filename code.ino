#include <ESP8266WiFi.h>
#include "max6675.h"

int thermoDO = 12;
int thermoCS = 15;
int thermoCLK = 14;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
 
String apiKey = "Q6UX562Z8OC7CGFP"; // Enter your Write API key from ThingSpeak
const char *ssid = "projetos_auto";     // replace with your wifi ssid and wpa2 key
const char *pass = "CybertronIFM23";
const char* server = "api.thingspeak.com";
 
 
WiFiClient client;
 
 
void setup() {
  Serial.begin(9600);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
    Serial.println("");
    Serial.println("WiFi connected");
}
 
void loop() 
{
      int celsius=thermocouple.readCelsius();
 
     Serial.print("C = "); 
     Serial.println(celsius);
 
 
    if (client.connect(server, 80)) // "184.106.153.149" or api.thingspeak.com
  {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(celsius);
    postStr += "r\n";
    
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    
    Serial.println("Data Send to Thingspeak");
  }
    client.stop();
    Serial.println("Waiting...");
 
    delay(2000);      // thingspeak needs minimum 15 sec delay between updates.
}
