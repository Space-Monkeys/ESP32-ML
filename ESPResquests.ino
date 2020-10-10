#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "SIGNET_ROOT";
const char* password = "48263590+L";
int y  =  0;
int x  =  0;
char* argX  = "0";
char* argy = "0";
const char* baseURL = "http://bedb3e080ce9.ngrok.io/args?";

int pinBotX = 15;
int pinBotY = 4;
int pinResult = 18;

int pinLedX = 22; //
int pinLedY = 19; // verde
int pinLedResult = 5; //azul

void setup() {
  pinMode(22, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(15, INPUT);
  pinMode(4, INPUT);
  pinMode(18, INPUT);



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

   x = digitalRead(pinBotX);
   y = digitalRead(pinBotY);

   int result  = digitalRead(pinLedResult);

   if(x == HIGH){
     argX = "1";
   }else{
     argX = "0";
   }


  if(y == HIGH){
    argy = "1";
  }else{
    argy = "0";
  }


  if(result == HIGH){
    baseURL = baseURL + "x=" + argX + "&" + "y=" + argy;
    const char* response = api();
  }
  delay(10000);
}



String api() {
if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    HTTPClient http;
    //"http://bedb3e080ce9.ngrok.io/args?x=1&y=1"
    http.begin(baseURL); //Specify the URL
    int httpCode = http.GET();  //Make the request
    if (httpCode > 0) { //Check for the returning code
         digitalWrite(13, HIGH);
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
        return(payload);
        delay(10000);
      }
    else {
      Serial.println("Error on HTTP request");
        return('Error on HTTP request');
    }
    http.end(); //Free the resources
  }
}