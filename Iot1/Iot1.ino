#include <ESP8266WiFi.h>

const char* ssid = "2841";         // WiFi to connect to
const char* password = "12345678";

void setup() {
  Serial.begin(115200);

  // Enable both Station and Access Point modes
  WiFi.mode(WIFI_AP_STA);

  // Start STA (connect to router)
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi!");
    Serial.print("STA IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi.");
  }

  // Start Access Point
  WiFi.softAP("Robotics", "12345678");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Nothing for now
}
