#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <DHT.h>
#define DHT11PIN 3
DHT dht(DHT11PIN, DHT11);


const int buzzer = 2; 
#define RST_PIN   5    

#define SS_PIN    10   
#define PIN_MQ2 A1
#define LED_MQ2 4

Servo myServo;
MFRC522 mfrc522(SS_PIN, RST_PIN);  
#define pirPin 7

int ledPIR = 9;        // Pin for PIR LED
//int sensorPIR = 7;      // Pin for PIR sensor
//int statePIR = LOW;     // by default, no motion detected
//int valPIR = 0;         // variable to store the PIR sensor status (value)
int val = 0;
bool motionState = false; // Utilisez false au lieu de faux.

int valueMQ2;
int randomTemperature;

void setup() {
  pinMode(12, OUTPUT);
  Serial.begin(9600);  // Initialize serial communication
  SPI.begin();         // Initialize SPI bus for RFID
  myServo.attach(8);   // Use the correct pin for the servo
  pinMode(LED_MQ2, OUTPUT);
  pinMode(PIN_MQ2, INPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
     pinMode(pirPin, INPUT);

  mfrc522.PCD_Init();   // Initialize communication with the RFID card
  pinMode(ledPIR, OUTPUT);     // initialize PIR LED as an output
  //pinMode(sensorPIR, INPUT);   // initialize PIR sensor as an input
  Serial.println("Ready to read RFID cards, detect gas, and motion!");
}

void loop() {
  // Lit le pirPin et stocke comme val :
  val = digitalRead(pirPin);

  // Si un mouvement est détecté (pirPin = HIGH), procédez comme suit :
  if (val == HIGH) {
    digitalWrite(ledPin, HIGH); // Allumez la LED embarquée.

    // Changer l'état du mouvement en vrai (mouvement détecté) :
    if (motionState == false) {
      Serial.println("Mouvement détecté !");
      motionState = true; // Utilisez true au lieu de vrai.
    }
  }

  // Si aucun mouvement n'est détecté (pirPin = LOW), procédez comme suit :
  else {
    digitalWrite(ledPin, LOW); // Éteignez la LED intégrée.

    // Change l'état du mouvement en faux (pas de mouvement) :
    if (motionState == true) {
      Serial.println("Motion terminé !");
      motionState = false;
    }
 }
}
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  
  Serial.println(humidity, 2);

 
  Serial.println(temperature, 2);
  delay(2000);

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
      //activateServo();
     // activateBuzzer();
      //tone(buzzer,5000);
     myServo.write(90);  // Move the servo to the 180-degree position

     delay(2000);
     myServo.write(180);    // Move the servo back to the 0-degree position
     delay(1000);
    } else {
      Serial.println("Incorrect card.");
    }

    mfrc522.PICC_HaltA();  // Stop communication with the current RFID card
  }
   PIRSensor();

  // MQ2 gas sensor reading
  valueMQ2 = analogRead(PIN_MQ2);
  Serial.println("MQ2 Sensor Value: " + String(valueMQ2));

  if (valueMQ2 > 1200) {
    Serial.println("Gas detected! Turning on MQ2 LED...");
    digitalWrite(LED_MQ2, HIGH);
    //activateBuzzer();
    tone(buzzer,1000);

  } else {
    Serial.println("No gas detected. Turning off MQ2 LED...");
    digitalWrite(LED_MQ2, LOW);
  }

  // PIR motion sensor reading
  /*valPIR = digitalRead(sensorPIR);
  if (valPIR == HIGH) {
    digitalWrite(ledPIR, HIGH);
    delay(100);

    if (statePIR == LOW) {
      Serial.println("Motion detected!");
      statePIR = HIGH;
       delay(2000);
    }
  } else {
    digitalWrite(ledPIR, LOW);
    delay(200);

    if (statePIR == HIGH) {
      Serial.println("Motion stopped!");
      statePIR = LOW;
     
    }
  }*/

  

bool checkCarte(byte* uidBytes) {
  // Define the expected UID values
  byte expectedUID1[] = {0x43, 0x90, 0x28, 0x13};
  byte expectedUID2[] = {0x83, 0x19, 0x0F, 0x0C};

  // Compare the received UID with the expected values
  return (memcmp(uidBytes, expectedUID1, 4) == 0 || memcmp(uidBytes, expectedUID2, 4) == 0);
}

void activateServo() {
  // Code to activate the servo motor
  myServo.write(0);  // Move the servo to the 180-degree position
  delay(2000);
  myServo.write(180);    // Move the servo back to the 0-degree position
  delay(1000);
}

void activateBuzzer() {
  // Code to activate the buzzer
  tone(buzzer,8000);
}