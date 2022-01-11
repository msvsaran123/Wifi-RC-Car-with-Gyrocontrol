// This Code is written by Madugula Sai Venkata Saran
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
     
#define IN_1  14         
#define IN_2  12         
#define IN_3  4           
#define IN_4  15          
#define Front_Light 5
#define Back_Light 2

int Front=0;
int Back=0;
int Left=0;
int Right=0;
int Stop=0;
int Fl=0;
int Bl=0;
int SteerSpeed=512;
int CarSpeed=512;
int x=0;
String symbol;             
const char* ssid = "WiFi Rock Crawler";
ESP8266WebServer server(80);



void setup() {
 
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT);
 pinMode(Front_Light, OUTPUT); 
 pinMode(Back_Light, OUTPUT);  
  
 Serial.begin(115200);
 


 WiFi.mode(WIFI_AP);
 WiFi.softAP(ssid);
 IPAddress myIP = WiFi.softAPIP();
 Serial.print("AP IP address: ");
 Serial.println(myIP);
 
 
 server.on ( "/", HTTP_handleRoot );
 server.onNotFound ( HTTP_handleRoot );
 server.begin();    
}



void loop() {
      server.handleClient();
      symbol = server.arg("value");
 
      x= symbol.toInt();
    
      if (symbol == "F1")Front = 1;
      else if (symbol == "B1")Back = 1;
      else if (symbol == "L1")Left = 1; 
      else if (symbol == "R1")Right = 1;
      else if (symbol == "S1")Stop = 1;
      else if (symbol == "FL1")Fl = 1;
      else if (symbol == "BL1")Bl = 1;
      else if (symbol == "F0")Front = 0;
      else if (symbol == "B0")Back = 0; 
      else if (symbol == "L0")Left = 0;
      else if (symbol == "R0")Right = 0;
      else if (symbol == "S0")Stop = 0;
      else if (symbol == "FL0")Fl = 0;
      else if (symbol == "BL0")Bl = 0;  
      else if (1<x && x<512)SteerSpeed = x*2;
      else if (513<x && x<1024)CarSpeed = (x-512)*2;
      
      analogWrite(IN_1,CarSpeed*Front);
      analogWrite(IN_2,CarSpeed*Back);
      analogWrite(IN_3,SteerSpeed*Left);
      analogWrite(IN_4,SteerSpeed*Right);
      digitalWrite(Front_Light,Fl*1);
      digitalWrite(Back_Light,Bl*1);
      
      delayMicroseconds(1);
      
}

void HTTP_handleRoot(void) {

if( server.hasArg("value") ){
       Serial.println(server.arg("value"));
  }
  server.send ( 200, "text/html", "" );
  delayMicroseconds(1);
}
