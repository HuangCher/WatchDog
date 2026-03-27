#include <Arduino.h>

#define LED_PIN 15

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // LED ON
  delay(3000);                  // wait 1 second

  digitalWrite(LED_PIN, LOW);   // LED OFF
  delay(3000);                  // wait 1 second
}