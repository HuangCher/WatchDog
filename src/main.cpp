#include <Arduino.h>
#include "fsm.h"
#include "button.h"
#include "motion.h"
#include "alert.h"
#include "servo.h"

// Create the FSM object
FSM fsm;

void setup() {
    Serial.begin(9600);
    pinMode(LED_R_RIGHT_PIN, OUTPUT);
    pinMode(LED_G_RIGHT_PIN, OUTPUT);
    pinMode(LED_B_RIGHT_PIN, OUTPUT);

    // Test pin 5
    Serial.println("PIN 5 ON");
    digitalWrite(LED_R_LEFT_PIN, HIGH); // pin 5
    delay(1500);
    digitalWrite(LED_R_LEFT_PIN, LOW);
    delay(500);

    // Test pin 18
    Serial.println("PIN 18 ON");
    digitalWrite(LED_G_LEFT_PIN, HIGH); // pin 18
    delay(1500);
    digitalWrite(LED_G_LEFT_PIN, LOW);
    delay(500);

    // Test pin 19
    Serial.println("PIN 19 ON");
    digitalWrite(LED_B_LEFT_PIN, HIGH); // pin 19
    delay(1500);
    digitalWrite(LED_B_LEFT_PIN, LOW);
    delay(500);
}

void loop() {
    fsm.update();
}