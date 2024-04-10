#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define RED 16
#define YELLOW 5
#define GREEN 4

#define STASSID "GL-SFT1200-065"
#define STAPSK "goodlife"

const char *ssid = STASSID;
const char *password = STAPSK;

ESP8266WebServer server(80);

void resetLights(){
  digitalWrite(RED, HIGH); 
  digitalWrite(YELLOW, LOW); 
  digitalWrite(GREEN, LOW); 
}

void setup(void) {
  // variable for each light
  // variable for light state (options are green/red)
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(RED, LOW);
    delay(500);
    digitalWrite(RED, HIGH);
    delay(500);
  }
  resetLights();

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (MDNS.begin("esp8266")) { Serial.println("MDNS responder started"); }
  
  // int time = millis();
  pinMode(RED, OUTPUT); //red
  pinMode(YELLOW, OUTPUT); //yellow
  pinMode(GREEN, OUTPUT); //green

  digitalWrite(RED, HIGH);  
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);  
  server.on("/", HTTP_GET, SETSTATE);
  server.begin();
  Serial.println("HTTP server started");
}

void SETSTATE(){
  String colorParam = server.arg("color");
  String stateParam = server.arg("state");
  int state = stateParam == "true" ? HIGH : LOW;
  if (colorParam == "red") {
    digitalWrite(RED, state);
  }
  else if (colorParam == "yellow") {
    digitalWrite(YELLOW, state);

  }
  else if (colorParam == "green") {
    digitalWrite(GREEN, state);
  }
  else if (stateParam == "clearLights"){
    resetLights();
  }
  server.send(200, "text/html", "OK");
}

// void green_state(int state){
//   // when activated it will blink the yellow light and then go to the green light
//   if (state == 1){
//     digitalWrite(RED, HIGH);
//     delay(500);
//     digitalWrite(YELLOW, HIGH);
//     delay(1500);
//     digitalWrite(RED, LOW);
//     digitalWrite(YELLOW, LOW);
//     digitalWrite(GREEN, HIGH);
//   }

//   if (state == 0){
//     digitalWrite(GREEN, HIGH);
//     delay(500);    
//     digitalWrite(YELLOW, HIGH);  
//     digitalWrite(GREEN, LOW);    
//     delay(1500);   
//     digitalWrite(YELLOW, LOW);   
//     digitalWrite(RED, HIGH);     

//   }  

//   if (state == 2){
//     digitalWrite(YELLOW, HIGH);       
//     delay(500);    
//     digitalWrite(YELLOW, LOW);       
//     delay(500);    
//     digitalWrite(YELLOW, HIGH); 
//     delay(500);    
//     digitalWrite(YELLOW, LOW);       
//     delay(500);    
//     digitalWrite(YELLOW, HIGH); 
//     delay(500);    
//     digitalWrite(YELLOW, LOW);       
//     delay(500);    
//     digitalWrite(YELLOW, HIGH); 
//     delay(500);    
//     digitalWrite(YELLOW, LOW);       
//     delay(500);    
//     digitalWrite(YELLOW, HIGH); 
//     delay(500);    
//     digitalWrite(YELLOW, LOW);       
//     delay(500);    
//     digitalWrite(YELLOW, HIGH); 
//     delay(500);    
//     digitalWrite(YELLOW, LOW);       
//     delay(500);    
//     digitalWrite(YELLOW, HIGH); 
//   }

// }



void loop() {  
  server.handleClient();
}
