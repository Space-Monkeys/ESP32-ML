#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "SIGNET_ROOT";
const char* password = "48263590+L";
 
void setup() {
   pinMode(13, OUTPUT);
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}
 
void loop() {
 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin("http://bedb3e080ce9.ngrok.io/args?x=1&y=1"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
    if (httpCode > 0) { //Check for the returning code
         digitalWrite(13, HIGH);
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
        delay(10000);
        digitalWrite(13, LOW);
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
 
  delay(10000);
 
}
