 #include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include"ThingSpeak.h"
// WiFi credentials
const char* ssid = "2841";
const char* password = "12345678";

// ThingSpeak API details
unsigned long channelID = 2988698;
const char* writeAPIKey = "0PI1GD7H2D54UKP1";
WiFiClient client;
// Ultrasonic sensor pins
const int trigPin = D1; //u need to specifically mension the digital pin through D
const int echoPin = D2;
void setup() {
 Serial.begin(115200);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 WiFi.begin(ssid, password);
 Serial.print("Connecting to WiFi");
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 Serial.println("\nWiFi connected.");
 ThingSpeak.begin(client);
}
void loop() {
 // Trigger the ultrasonic pulse
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 // Measure the pulse duration
 long duration = pulseIn(echoPin, HIGH);
 
 // Calculate distance in centimeters
 float distance = duration * 0.034 / 2;
 Serial.print("Distance: ");
 Serial.print(distance);
 Serial.println(" cm");
 // Write distance to ThingSpeak channel field 1
 int x = ThingSpeak.writeField(channelID, 1, distance, writeAPIKey);
 if (x == 200) {
 Serial.println("Data sent to ThingSpeak.");
 } else {
 Serial.print("Error sending data. HTTP error code: ");
 Serial.println(x);
 }
 delay(15000); // ThingSpeak rate limit: 15 seconds 
}

// Data will be tracked in thingspeak
