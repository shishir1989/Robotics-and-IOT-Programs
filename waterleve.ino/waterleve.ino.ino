// int sense=A1;
// // int relay=12;
// int ledpin =9;

// void setup() {
//   Serial.begin(9600);
//   // pinMode(relay,OUTPUT);
//   pinMode(sense,INPUT);
//    pinMode(ledPin, OUTPUT);
 


// }

// void loop() {

//  int value= analogRead(sense);
//  Serial.print("Waterlevel:");
//  Serial.println(value);
//  delay(1000);

//  int brightness = map(value, 0, 1023, 0, 255);
//   analogWrite(ledPin, brightness);  // Set LED brightness

//   delay(1000);
  

// }
int sensorPin = A0;     // Analog input from sensor
int ledPin = 9;         // PWM output to LED (D3, D5, D6, D9, D10, or D11 on most Arduino boards)

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);       // Read analog value (0–1023)
  int ledBrightness = map(sensorValue, 0, 1023, 0, 255);  // Map to PWM range (0–255)
  Serial.println("SensorValue :");
  Serial.println(sensorValue);

  analogWrite(ledPin, ledBrightness);            // Set LED brightness
    Serial.print("ledBrightness :");
  Serial.print(ledBrightness);

  delay(500);  // Small delay for stability
}

