#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#define relay 4    // relay 모듈 4번 핀 사용
Servo servoMain; // Define our Servo
int val = 1000;
int i = 0;
int flag=1;
const char* ssid = "mine";
const char* pass = "alsrnalsrn";
const char* host = "maker.ifttt.com"; 
String ApiKey = "cY9eJKG56s3uce7M-aEeQi";
String path = "/trigger/hot_temp/with/key/" + ApiKey + "/?value1=";  



void setup()
{
  //pinMode(relay, OUTPUT);
   servoMain.attach(10); // servo on digital pin 10
   Serial.begin(9600);
  pinMode(relay, OUTPUT);
  //digitalWrite(relay,HIGH);
  Serial.print("ssibal");
   WiFi.begin(ssid, pass);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

   
   
}

void loop()
{
  //Serial.println(val);
 // Serial.println(getTime());
 
 ////////////////////////////////
  //digitalWrite(relay, HIGH);
  //delay(3000);
  //digitalWrite(relay,LOW);
  //delay(3000);
  /////////////////////////////
  
  val = analogRead(A0);
  if( val >= 500 ) {
    servoMain.write(i);
    delay(45);
    if(flag == 1){
      if( i < 180) i ++;
      else{
        flag = 0;
      }
    }
    else if( flag == 0){
      if( i > 0 ) i --;
      else{
        flag = 1;
      }
    }
  }
  else {
    if( flag == 1 ) {
      servoMain.write(i+10);
      delay(45);
    }
    else if( flag == 0 ) {
      servoMain.write(i-10);
      delay(45);
    }
    //Serial.print("jotgatne");
    digitalWrite(relay, HIGH);
    delay(3000);
    digitalWrite(relay, LOW);
    WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  client.print(String("GET ") + path + "2018.05.28" + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");
  //delay(5000);
    
    servoMain.detach();
    //delay(5000);
    //val = 0;
    //servoMain.attach(10);
  }

}

String getTime() {
  WiFiClient client;
  while (!client.connect("google.com", 80)) {}
  client.print("HEAD / HTTP/1.1\r\n\r\n");
  while(!client.available()) {}
  
 while(client.available()) {
    if (client.read() == '\n') {    
      if (client.read() == 'D') {    
        if (client.read() == 'a') {    
          if (client.read() == 't') {    
            if (client.read() == 'e') {    
              if (client.read() == ':') {    
                client.read();
                String timeData = client.readStringUntil('\r');
                Serial.println(timeData);
                client.stop();
                return timeData;
              }
            }
          }
        }
      }
    }
 }
  
}
