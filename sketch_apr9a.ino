#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <LittleFS.h>

#define RED 16
#define YELLOW 5
#define GREEN 4

#define STASSID "452265 (2)"
#define STAPSK "test1test1"

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
  
  if (!LittleFS.begin()) {
      Serial.println("LittleFS mount failed");
      return;
    }
  // File file = LittleFS.open("/test.html", "w");
// const char* html_code = "<DOCTYPE html> \n" 
//     "<html>\n"
//     "    <head>\n"
//     "        <script src=\"https://cdn.tailwindcss.com\"></script>\n"
//     "        <style>\n"
//     "            .on{\n"
//     "                opacity: 100%;\n"
//     "            }\n"
//     "        </style>\n"
//     "        <script>\n"
//     "            let red = true;\n"
//     "            let yellow = false; \n"
//     "            let green = false;\n"
//     "            let flashingEvent;\n"
//     "            let ip_addr = window.location.host\n"
//     "        </script>\n"
//     "        <script defer>\n"
//     "            async function SetRed(bool){\n"
//     "                await fetch(`http://${ip_addr}/?color=red&state=${String(bool).toLowerCase()}`, {mode : \"no-cors\"})\n"
//     "                document.getElementById(\"red\").style.backgroundColor = bool ? \"rgb(220 38 38)\" : \"rgba(23, 23, 23, 0.9)\"\n"
//     "                red = bool;\n"
//     "            }\n"
//     "            async function SetYellow(bool){\n"
//     "                await fetch(`http://${ip_addr}/?color=yellow&state=${String(bool).toLowerCase()}`, {mode : \"no-cors\"})\n"
//     "                document.getElementById(\"yellow\").style.backgroundColor = bool ? \"rgb(250 204 21)\" : \"rgba(23, 23, 23, 0.9)\"\n"
//     "                yellow = bool;\n"
//     "            }\n"
//     "            async function SetGreen(bool){\n"
//     "                await fetch(`http://${ip_addr}/?color=green&state=${String(bool).toLowerCase()}`, {mode : \"no-cors\"})\n"
//     "                document.getElementById(\"green\").style.backgroundColor = bool ? \"rgb(22 163 74)\" : \"rgba(23, 23, 23, 0.9)\"\n"
//     "                green = bool;\n"
//     "            }\n"
//     "            async function setLight(str, bool){\n"
//     "                await fetch(`http://${ip_addr}/?color=${str}&state=${String(bool)}`, {method : \"GET\"})\n"
//     "            }\n"
//     "        </script>\n"
//     "    </head>\n"
//     "    <body class=\"min-h-screen\">\n"
//     "            <div id=\"traffic_light\" class=\"h-[500px] w-[12rem] absolute left-0 right-0 top-0 bottom-0 mx-auto my-auto grid grid-cols-1 rounded-[10rem] bg-gray-600/80 grid-rows-3 border border-black py-4\" style=\"row-gap: 10px;\">\n"
//     "                <div class=\"row-span-1 hover:cursor-pointer\">\n"
//     "                    <div id=\"red\" class=\"mx-auto rounded-full border-4  border-black h-full aspect-square\" style=\"background-color: rgb(220 38 38);\"></div>\n"
//     "                </div>\n"
//     "                <div class=\"row-span-1 hover:cursor-pointer\">\n"
//     "                    <div id=\"yellow\" class=\"mx-auto rounded-full border-4  border-black bg-yellow-400 h-full aspect-square\" style=\"background-color: rgb(250 204 21);\"></div>\n"
//     "                </div>\n"
//     "                <div class=\"row-span-1 hover:cursor-pointer\">\n"
//     "                    <div id=\"green\" class=\"mx-auto rounded-full border-4  border-black bg-green-600 h-full aspect-square\" style=\"background-color: rgb(22 163 74);\"></div>\n"
//     "                </div>\n"
//     "            </div>\n"
//     "    </body>\n"
//     "    <footer>\n"
//     "        <script>\n"
//     "            function sleep(ms) {\n"
//     "                return new Promise(resolve => setTimeout(resolve, ms));\n"
//     "            }\n"
//     "            document.addEventListener(\"DOMContentLoaded\", ()=>{\n"
//     "                SetRed(false)\n"
//     "                SetYellow(false)\n"
//     "                SetGreen(false)\n"
//     "            })\n"
//     "            function disableInput(boolean){\n"
//     "                document.getElementById(\"red\").style.cursor = boolean ? \"not-allowed\" : \"pointer\"\n"
//     "                document.getElementById(\"yellow\").style.cursor = boolean ? \"not-allowed\" : \"pointer\"\n"
//     "                document.getElementById(\"green\").style.cursor = boolean ? \"not-allowed\" : \"pointer\"\n"
//     "                document.body.style.cursor = boolean ? \"progress\" : \"default\"\n"
//     "            }\n"
//     "            async function toggleLights() {\n"
//     "                disableInput(true)\n"
//     "                if (!red && !yellow && !green){\n"
//     "                    await SetRed(true);\n"
//     "                }\n"
//     "                else if (red && !yellow && !green) {\n"
//     "                    await SetGreen(true);\n"
//     "                    await SetRed(false);\n"
//     "                    await SetYellow(false);\n"
//     "                } \n"
//     "                // Green to Red transition\n"
//     "                else if (!red && !yellow && green) {\n"
//     "                    await SetYellow(true);\n"
//     "                    await new Promise(resolve => setTimeout(resolve, 2000));\n"
//     "                    await SetGreen(false);\n"
//     "                    await SetYellow(false);\n"
//     "                    await SetRed(true);\n"
//     "                }\n"
//     "                disableInput(false)\n"
//     "        }\n"
//     "            document.getElementById(\"traffic_light\").addEventListener((\"click\"), async(e)=>{\n"
//     "                await toggleLights();\n"
//     "            });\n"
//     "            document.getElementById(\"yellow\").addEventListener((\"click\"), async(e)=>{\n"
//     "                e.stopPropagation()\n"
//     "                if (flashingEvent){\n"
//     "                    clearInterval(flashingEvent)\n"
//     "                    flashingEvent = null;\n"
//     "                    await SetGreen(false);\n"
//     "                    await SetYellow(false);\n"
//     "                    await SetRed(true);\n"
//     "                }\n"
//     "                else {\n"
//     "                    await SetGreen(false);\n"
//     "                    await SetYellow(false);\n"
//     "                    await SetRed(false);\n"
//     "                    flashingEvent = setInterval(async()=>{\n"
//     "                        await SetYellow(!yellow)\n"
//     "                    }, 500)"
//     "                }\n"
//     "            });\n"
//     "        </script>\n"
//     "    </footer>\n"
//     "</html>";
  if (file.print(html_code)) {
    Serial.println("File written");
  }
  delay(2000);
  file.close();
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
  server.on("/traffic", HTTP_GET, getFile);
  server.begin();
  Serial.println("HTTP server started");
}
void getFile(){
  File file = LittleFS.open("/test.html","r");
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  
  Serial.println("File Content:");
  String response;
  while (file.available()){
    response = file.readString();
  }
    server.send(200, "text/html", response);
  file.close();
  
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
