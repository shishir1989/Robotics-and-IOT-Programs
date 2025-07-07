#include <ESP8266WiFi.h>

const char* ssid = "2841";
const char* password = "12345678";

#define trigPin D1
#define echoPin D2

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  WiFi.mode(WIFI_AP_STA); // Enable both Station and Access Point mode
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi!");
    Serial.print("STA IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi.");
  }

  server.begin();
}

// Function to read distance from ultrasonic sensor
float readDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  float distance = duration * 0.034 / 2;

  if (distance == 0 || distance > 400) {
    return -1; // Invalid or out-of-range reading
  }

  return distance;
}

void loop() {
  WiFiClient client = server.available();  // Check if a client is connected

  if (client) {
    Serial.println("Client connected");

    // Read the request (not actually used here, but logged)
    String request = client.readStringUntil('\r');
    Serial.println("Request: " + request);
    client.flush();

    // Read distance
    float distance = readDistanceCM();

    // Send HTTP response headers
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();

    // Begin HTML content
    client.println("<!DOCTYPE html>");
    client.println("<html>");
    client.println("<head><meta http-equiv='refresh' content='2'><title>Ultrasonic ESP8266</title></head>");
    client.println("<body>");
    client.println("<h2>ESP8266 Ultrasonic Sensor</h2>");

    if (distance > 0) {
      client.print("<p>Distance: ");
      client.print(distance);
      client.println(" cm</p>");
    } else {
      client.println("<p>Error: Distance: Out of range</p>");
    }

    client.println("</body></html>");

    delay(100); // Optional: let the client receive data before disconnecting
    client.stop();
    Serial.println("Client disconnected");
  }
}
