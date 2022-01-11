# Wifi-RC-Car-with-Gyrocontrol
 ![image](https://user-images.githubusercontent.com/79988029/148889192-9b5726c1-27fd-4c90-8ff4-75f3f792b415.png)

Convert your RC Car to Wi-Fi Car

Hello friends! Welcome to this new blog. We all might have played with RC Cars. The main problem with those cheap RC Cars is its circuit board. They stop working after some couple of weeks. You can notice that all the hardware components except the controller circuit, works fine. In this case you can convert or create your RC Car to Wi-Fi Car and can control with an Android app. You just need to follow the below steps.
Objective

The main objective of this project is to convert the old RC Cars to Wi-Fi Cars under low budget and also on your own. You can also make your own Wi-Fi Car and can demonstrate in your School Science fair.
Materials Required 

Hardware
1.	NodeMCU or ESp12e Module
 ![image](https://user-images.githubusercontent.com/79988029/148889229-d8c7bb8b-8ddf-4bdf-98b2-6bd1ffb0b9ff.png)
![image](https://user-images.githubusercontent.com/79988029/148889245-f50c5f23-715a-4c3b-a1da-b422c549da03.png)

Buy NodeMCU here: https://www.hnhcart.com/products/node-mcu-cp-210x?_pos=1&_sid=632f1b67a&_ss=r
Buy ESP 12E here: https://www.hnhcart.com/products/esp-12e-wifi-module?_pos=1&_sid=e8606e8df&_ss=r

2.	Dual H Bridge DC PWM Motor Driver
 ![image](https://user-images.githubusercontent.com/79988029/148889258-752f553a-a019-4ffd-99c4-a0cdca9abb06.png)

You can use any Dual H Bridge DC Motor Driver. Here, I am using MX1508 Motor Driver. But you must be in strict that the motor driver can work in the voltage range between 3v to 5v.
 
Software
1.	The Code

Upload the below code into your Wi-Fi Module.
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
2.	The Android app to control the Wi-Fi Car

Download the app from here:
 
![image](https://user-images.githubusercontent.com/79988029/148889303-082aaaa9-9681-448c-81a2-3dcb6d16454a.png)

 

Circuit Diagram
![image](https://user-images.githubusercontent.com/79988029/148889385-916ef392-15f7-4645-a921-dfa616136b89.png)

1.	If you want to use the NodeMCU, this is the Circuit diagram. 
 
Note: If you want to give an external power supply, it is must to connect the ground of the Motor driver to the power supply.
2.	If you want to use the ESP12-E module, the above Circuit diagram with respective connections is also applicable to it.
Here are the Gerber files of ESP 12 E breakout board and of the whole circuit. You can download them from here.
  
![image](https://user-images.githubusercontent.com/79988029/148889489-fdcb3888-776a-44d4-b320-ac0edef5f24c.png)

                                                                 N 
![image](https://user-images.githubusercontent.com/79988029/148889476-0f80b7c0-74a1-479c-b2f7-a46aa9a512bb.png)

Note: If your power supply is between 3.7v to 5v use Ht7333 3.3v voltage regulator.
           If your power supply is above 5v you can use any of both Ht733 and Ams1117 voltage regulator.
You can buy it from here: https://www.hnhcart.com/products/reg1117-ic?_pos=2&_sid=66c05b2eb&_ss=r
You can buy 10 micro farad capacitors from here: 
Smd: https://www.hnhcart.com/collections/capacitors/products/10-uf-smd-capacitor-10-pieces
Tht:   https://www.hnhcart.com/collections/capacitors/products/polar-capacitors


