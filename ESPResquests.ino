#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "SIGNET_ROOT";
const char* password = "48263590+L";
int y  =  0;
int x  =  0;
char* argX  = "0";
char* argy = "0";
String baseURL = "http://a5cb2a3c56a7.ngrok.io/args?";

int pinBotX = 15;
int pinBotY = 4;
int pinResult = 18;

int pinLedX = 22; // VERMELHO 
int pinLedY = 19; // verde
int pinLedResult = 5; //azul

void setup() {
  //LED VERMELHO
  pinMode(22, OUTPUT);
  //LED VERDE
  pinMode(19, OUTPUT);
  //LED AZUL
  pinMode(5, OUTPUT);

  //BOTAO VERMELHO X
  pinMode(15, INPUT);
  //BOTÃO AMARELO DIREITO
  pinMode(4, INPUT);
  //BOTÃO AMARELO ESQUERDO Y
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

   int result  = digitalRead(pinResult);
  
   if(x == HIGH){
     digitalWrite(22, HIGH);
     argX = "1";
   }else{
     argX = "0";
      digitalWrite(22, LOW);
   }


  if(y == HIGH){
    digitalWrite(19, HIGH);
    argy = "1";
  }else{
    argy = "0";
     digitalWrite(19, LOW);
  }

 

  if(result == HIGH){
   // baseURL = baseURL + "x=" + argX + "&" + "y=" + argy; 
 //   Serial.println(baseURL);
    api(baseURL + "x=" + argX + "&" + "y=" + argy);
  }
//  delay(10000);
}



void api(String url) {
if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    HTTPClient http;
    //"http://bedb3e080ce9.ngrok.io/args?x=1&y=1"
    Serial.println(url);
    http.begin(url); //Specify the URL
    int httpCode = http.GET();  //Make the request
    if (httpCode > 0) { //Check for the returning code
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
        showLed(payload);
        delay(10000);
      }
    else {
      Serial.println("Error on HTTP request");
        //return('Error on HTTP request');
    }
    http.end(); //Free the resources
  }
}

void showLed(String dataMl){
   StaticJsonBuffer<256> jsonBuffer;
  Serial.println(dataMl);
  JsonObject& root = jsonBuffer.parseObject(dataMl);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }

   const int dados = root["data"];
    Serial.println(dados);
  if(dados == 1){
      digitalWrite(5, HIGH);
    } else {
     digitalWrite(5, LOW);
      }
}
