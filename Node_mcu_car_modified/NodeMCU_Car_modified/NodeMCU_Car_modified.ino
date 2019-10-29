         // Enable/speed motors Left         GPIO12(D6)
#define IN_1  5          // L298N in1 motors Right           GPIO15(D8)
#define IN_2  4          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  0           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  2           // L298N in4 motors Left            GPIO0(D3)

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String command;             //String to store app command state.
int speedCar = 1;         // 400 - 1023.

const char* ssid = "NodeMCU Car";
ESP8266WebServer server(80);

void setup() {

 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
  
  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void goAhead(){ 

      analogWrite(IN_1, 16*speedCar + 90);
      digitalWrite(IN_2, LOW);
 

      analogWrite(IN_3, 16*speedCar + 90);
      digitalWrite(IN_4, LOW);
  
  }

void goBack(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, 16*speedCar + 90);
     

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, 16*speedCar + 90);
      
  }

void goRight(){ 

      digitalWrite(IN_1, 16*speedCar + 90);
      digitalWrite(IN_2, LOW);
     

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, 16*speedCar + 90);
    
  }

void goLeft(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, 16*speedCar + 90);
    

      digitalWrite(IN_3, 16*speedCar + 90);
      digitalWrite(IN_4, LOW);
  
  }

void goAheadRight(){
      
      digitalWrite(IN_1, 16*speedCar + 90);//LEFT
      digitalWrite(IN_2, LOW);
     

      digitalWrite(IN_3, LOW);//RIGHT
      digitalWrite(IN_4, LOW);

   }

void goAheadLeft(){
      
       digitalWrite(IN_1, LOW);//Left
      digitalWrite(IN_2, LOW);
    

      digitalWrite(IN_3, 16*speedCar + 90);//right
      digitalWrite(IN_4, LOW);

  }

void goBackRight(){ 

      digitalWrite(IN_1, LOW);//left
      digitalWrite(IN_2, 16*speedCar + 90);
     

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
  }

void goBackLeft(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
    

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, 16*speedCar + 90);
  }

void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
 }

void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "0") speedCar = 1;
      else if (command == "1") speedCar = 2;
      else if (command == "2") speedCar = 3;
      else if (command == "3") speedCar = 4;
      else if (command == "4") speedCar = 5;
      else if (command == "5") speedCar = 6;
      else if (command == "6") speedCar = 7;
      else if (command == "7") speedCar = 8;
      else if (command == "8") speedCar = 9;
      else if (command == "9") speedCar = 10;
      else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
