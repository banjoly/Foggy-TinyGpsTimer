//Tiny GPS
#include "TinyGPS++.h"
#include "SoftwareSerial.h"

SoftwareSerial serial_connection(3,1 ); //RX=pin 10, TX=pin 11
TinyGPSPlus gps;

//

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6E8xXcYA6"
#define BLYNK_TEMPLATE_NAME "GUNGGING"
#define BLYNK_AUTH_TOKEN "u6cb3DMP0xfj2XYT4WtWXgPQEIHSURK1"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


//NTP
#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP);
NTPClient timeClient(ntpUDP);



// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SAHOUSE2020  2G";
char pass[] = "11012709";
int hr;
int minx;
void setup(){
  serial_connection.begin(9600);
  Serial.println("GPS Start");
  pinMode(17,OUTPUT);
  digitalWrite(17,1);
  // Debug console
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop(){
 while(serial_connection.available()){
gps.encode(serial_connection.read());
}
if(gps.location.isUpdated()){
  
  Serial.print(gps.time.hour()+7);
  Serial.print(":");
  Serial.print(gps.time.minute());
   Serial.print(":");
  Serial.println(gps.time.second());
  hr=gps.time.hour()+7;
  minx=gps.time.minute();
  delay(100);
}

  Blynk.run();
  if((digitalRead(4)==1)||((hr>=9&&hr<=18)&&(minx>=5&&minx<=10))||((hr>=9&&hr<=18)&&(minx>=35&&minx<=40))){
    digitalWrite(17,0);
  }else digitalWrite(17,1);
  if(digitalRead(0)==1){
    digitalWrite(17,1);
  }
}
