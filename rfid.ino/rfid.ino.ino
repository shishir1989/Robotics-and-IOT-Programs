#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10   // SDA, SS pin of RFID
#define RST_PIN 9   // Reset pin of RFID
#define SERVO_PIN 3 // Servo connected to digital pin 3

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create RFID object
Servo myServo; // Create Servo object

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  myServo.attach(SERVO_PIN); // Attach servo to the defined pin
  myServo.write(0);          // Start with servo at 0°
  Serial.println("Place your RFID card near the reader...");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  byte knownUID[] = {0x83, 0x7F, 0x00, 0x28}; // Replace with your actual UID
  bool isMatch = true;

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] != knownUID[i]) {
      isMatch = false;
      break;
    }
  }

  if (isMatch) {
    Serial.println("Access Granted");
    myServo.write(90);      // Rotate servo to 90°
    delay(2000);            // Wait 2 seconds
    myServo.write(0);       // Return to 0°
  } else {
    Serial.println("Access Denied");
  }

  delay(1000);
}
