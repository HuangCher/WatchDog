// rosetta
#include <Arduino.h>
#include "pins.h"
// Responsibilities:
// - Control RGB LED colors
// - Control buzzer alerts
//
// Color scheme suggestion:
// Study mode => Green
// Warning => Red// Break => Blue


void setup_alert(){
    pinMode(BUZZER_PIN, OUTPUT);

    pinMode(LED_R_LEFT_PIN, OUTPUT);
    pinMode(LED_G_LEFT_PIN, OUTPUT);
    pinMode(LED_B_LEFT_PIN, OUTPUT);

    pinMode(LED_R_RIGHT_PIN, OUTPUT);
    pinMode(LED_G_RIGHT_PIN, OUTPUT);
    pinMode(LED_B_RIGHT_PIN, OUTPUT);
}

void studyMode(){
    noTone(BUZZER_PIN);

    digitalWrite(LED_R_LEFT_PIN, LOW);
    digitalWrite(LED_G_LEFT_PIN, HIGH);
    digitalWrite(LED_B_LEFT_PIN, LOW);

    digitalWrite(LED_R_RIGHT_PIN, LOW);
    digitalWrite(LED_G_RIGHT_PIN, HIGH);
    digitalWrite(LED_B_RIGHT_PIN, LOW);
}

void warningMode(){
    digitalWrite(LED_R_LEFT_PIN, HIGH);
    digitalWrite(LED_G_LEFT_PIN, LOW);
    digitalWrite(LED_B_LEFT_PIN, LOW);

    digitalWrite(LED_R_RIGHT_PIN, HIGH);
    digitalWrite(LED_G_RIGHT_PIN, LOW);
    digitalWrite(LED_B_RIGHT_PIN, LOW);

    tone(BUZZER_PIN, 1000);
}

void breakMode(){
    noTone(BUZZER_PIN);

    digitalWrite(LED_R_LEFT_PIN, LOW);
    digitalWrite(LED_G_LEFT_PIN, LOW);
    digitalWrite(LED_B_LEFT_PIN, HIGH);

    digitalWrite(LED_R_RIGHT_PIN, LOW);
    digitalWrite(LED_G_RIGHT_PIN, LOW);
    digitalWrite(LED_B_RIGHT_PIN, HIGH);
}

void idleMode() {
    noTone(BUZZER_PIN);

    // Turn OFF left RGB LED
    digitalWrite(LED_R_LEFT_PIN, LOW);
    digitalWrite(LED_G_LEFT_PIN, LOW);
    digitalWrite(LED_B_LEFT_PIN, LOW);

    // Turn OFF right RGB LED
    digitalWrite(LED_R_RIGHT_PIN, LOW);
    digitalWrite(LED_G_RIGHT_PIN, LOW);
    digitalWrite(LED_B_RIGHT_PIN, LOW);
}

// void loop_alert(){
//     studyMode();
//     delay(5000);

//     warningMode();
//     delay(5000);

//     breakMode();
//     delay(5000);
// }

// void setup() {
//     setup_alert();
// }

// void loop() {
//     loop_alert();
// }