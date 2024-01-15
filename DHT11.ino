#include <dht11.h>

#define DHT11_PIN 2

dht DHT;
int sensorValue = 0;

void setup(){
  Serial.begin(9600);
}

void loop(){
  int chk = DHT.read11(DHT11_PIN);
  Serial.print(DHT.temperature);
  Serial.print("/");
  Serial.println(DHT.humidity);
  delay(1000);
}