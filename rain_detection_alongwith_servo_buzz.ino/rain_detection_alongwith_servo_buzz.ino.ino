#include <Servo.h>

Servo servo1;
int rainsensor=2;
int relay=5;

void setup() {
  pinMode(rainsensor,INPUT);
  servo1.attach(4);
  pinMode(relay,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  int status=digitalRead(rainsensor);
  if(status==HIGH){
    Serial.println("Rain 404 error");
    servo1.write(0);
    digitalWrite(relay,LOW);

  }else{
    Serial.println("Rain Detected");
    servo1.write(90);
    digitalWrite(relay,HIGH);
  }
delay(1000);
}


