#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <DHT.h>

const int buzzer = 2; // Buzzer connected to pin 2
#define RST_PIN   5    // Reset pin (RST) for RFID
#define SS_PIN    10   // Slave Select pin (SDA/SS) for RFID
#define PIN_MQ2 A1
#define LED_MQ2 4

Servo myServo;
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create RFID object

int valueMQ2;

void setup() {
  pinMode(12, OUTPUT);
  pinMode(6, OUTPUT); // Set pin 6 as an output for the motor
  Serial.begin(9600);  // Initialize serial communication
  SPI.begin();         // Initialize SPI bus for RFID
  myServo.attach(8);   // Use the correct pin for the servo
  pinMode(LED_MQ2, OUTPUT);
  pinMode(PIN_MQ2, INPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 2 as an output
  mfrc522.PCD_Init();   // Initialize communication with the RFID card

  Serial.println("Ready to read RFID cards, detect gas, motion, and measure temperature/humidity!");
}

void loop() {
  // RFID card reading
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("Card detected: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    if (checkCarte(mfrc522.uid.uidByte)) {
      Serial.println("Correct card! Activating the servo and buzzer...");
      myServo.write(0);  // Move the servo to the 180-degree position
      delay(2000);
      myServo.write(180);    // Move the servo back to the 0-degree position
      delay(1000);
    } else {
      Serial.println("Incorrect card.");
    }

    mfrc522.PICC_HaltA();  // Stop communication with the current RFID card
  }

  // MQ2 gas sensor reading
  valueMQ2 = analogRead(PIN_MQ2);
  Serial.println("MQ2 Sensor Value: " + String(valueMQ2));

  if (valueMQ2 > 50) {
    Serial.println("Gas detected! Turning on MQ2 LED...");
    digitalWrite(LED_MQ2, HIGH);
    tone(buzzer, 1000);
    digitalWrite(6, HIGH); // Turn on the motor
    delay(1000);
  } else {
    Serial.println("No gas detected. Turning off MQ2 LED...");
    digitalWrite(LED_MQ2, LOW);
    digitalWrite(6, LOW); // Turn off the motor
    delay(1000);
  }

  
}

bool checkCarte(byte* uidBytes) {
  // Define the expected UID values
  byte expectedUID1[] = {0x43, 0x90, 0x28, 0x13};
  byte expectedUID2[] = {0x83, 0x19, 0x0F, 0x0C};

  // Compare the received UID with the expected values
  return (memcmp(uidBytes, expectedUID1, 4) == 0 || memcmp(uidBytes, expectedUID2, 4) == 0);
}
