#include <ESP8266WiFi.h>
const char* ssid = "2841";
const char* password = "12345678";
const int relayPin = D1;
int relayState = 0;
WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  Serial.print("ESP8266 IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("Client connected");
  while (!client.available()) {
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println("Request: " + request);
  client.flush();
  if (request.indexOf("GET /ON") != -1) {
    digitalWrite(relayPin, HIGH);
    relayState = 1;
    Serial.println("Relay turned ON");
  }
  if (request.indexOf("GET /OFF") != -1) {
    digitalWrite(relayPin, LOW);
    relayState = 0;
    Serial.println("Relay turned OFF");
  }
  String html = "<!DOCTYPE html><html><head><title>Relay Control</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>button{font-size:30px; padding:10px 30px; margin:10px;}</style></head><body>";
  html += "<h2>Relay (Light) Control</h2>";
  html += "<p>Relay Status: <strong>" + String(relayState == 1 ? "ON" : "OFF") + "</strong></p>";
  html += "<a href=\"/ON\"><button style='background:green;'>Turn ON</button></a>";
  html += "<a href=\"/OFF\"><button style='background:red;'>Turn OFF</button></a>";
  html += "</body></html>";
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(html);
  delay(1);
  client.stop();
  Serial.println("Client disconnected");
}



//API= agent =url


// Libarary Install = thingSpeak 


// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>
// #include "ThingSpeak.h"
// // WiFi credentials
// const char* ssid = "RUBINA 2841";
// const char* password = "^0643zM7";

// // ThingSpeak API details
// unsigned long channelID = 2988698;
// const char* writeAPIKey = "0PI1GD7H2D54UKP1";
// WiFiClient client;
// // Ultrasonic sensor pins
// const int trigPin = D1;
// const int echoPin = D2;
// void setup() {
//  Serial.begin(115200);
//  pinMode(trigPin, OUTPUT);
//  pinMode(echoPin, INPUT);
//  WiFi.begin(ssid, password);
//  Serial.print("Connecting to WiFi");
//  while (WiFi.status() != WL_CONNECTED) {
//  delay(500);
//  Serial.print(".");
//  }
//  Serial.println("\nWiFi connected.");
//  ThingSpeak.begin(client);
// }
// void loop() {
//  // Trigger the ultrasonic pulse
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  // Measure the pulse duration
//  long duration = pulseIn(echoPin, HIGH);
 
//  // Calculate distance in centimeters
//  float distance = duration * 0.034 / 2;
//  Serial.print("Distance: ");
//  Serial.print(distance);
//  Serial.println(" cm");
//  // Write distance to ThingSpeak channel field 1
//  int x = ThingSpeak.writeField(channelID, 1, distance, writeAPIKey);
//  if (x == 200) {
//  Serial.println("Data sent to ThingSpeak.");
//  } else {
//  Serial.print("Error sending data. HTTP error code: ");
//  Serial.println(x);
//  }
//  delay(15000); // ThingSpeak rate limit: 15 seconds
// }
