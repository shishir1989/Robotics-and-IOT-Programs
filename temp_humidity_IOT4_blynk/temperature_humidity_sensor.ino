#define BLYNK_TEMPLATE_ID "TMPL61BdfNfwE"
#define BLYNK_TEMPLATE_NAME "iot"
#define BLYNK_AUTH_TOKEN "cNwqy_wrulUHOB2LXEeB9sdOqkkNkKqn"

// Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// WiFi credentials
char ssid[] = "2841";
char pass[] = "12345678";

// Pin Configurations
#define RELAY_PIN D1
#define DHTPIN D2
#define DHTTYPE DHT11

// Object Initialization
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensorData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Celsius

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V1, t);  // Send Temperature to V1
  Blynk.virtualWrite(V2, h);  // Send Humidity to V2
}

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Relay OFF by default

  dht.begin();  // Start DHT Sensor
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  // Connect to Blynk

  timer.setInterval(2000L, sendSensorData);  // Read DHT every 2 sec
}

// Button to control relay from Blynk
BLYNK_WRITE(V0) {
  int value = param.asInt();
  digitalWrite(RELAY_PIN, value);
}

void loop() {
  Blynk.run();
  timer.run();  // Run timer to read sensors
}
