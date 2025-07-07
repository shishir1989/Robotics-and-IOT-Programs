#define BLYNK_TEMPLATE_ID "TMPL61BdfNfwE"
#define BLYNK_TEMPLATE_NAME "iot"
#define BLYNK_AUTH_TOKEN "cNwqy_wrulUHOB2LXEeB9sdOqkkNkKqn"

#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>
//your wifi credentials
char ssid[]="2841";
char password[]="12345678";

int relayPin=D1;

void setup(){
  Serial.begin(9600);
  pinMode(relayPin,OUTPUT);
  digitalWrite(relayPin,LOW);//Relay off by default

  Blynk.begin(BLYNK_AUTH_TOKEN,ssid,password);
}

//when v1 buttton is prennsed in blynk app
BLYNK_WRITE(V0){

  int value=param.asInt();
  digitalWrite(relayPin,value);
}

void loop(){
  Blynk.run();
}