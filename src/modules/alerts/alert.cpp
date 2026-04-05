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

static const int BUZZER_CH = 7;      // dedicated channel for buzzer
static const int BUZZER_RES = 8;     // 8-bit resolution


void setup_alert(){
    pinMode(BUZZER_PIN, OUTPUT);

    // Dedicated LEDC setup for buzzer (avoid tone/noTone conflict with servo)
    ledcSetup(BUZZER_CH, 1000, BUZZER_RES);
    ledcAttachPin(BUZZER_PIN, BUZZER_CH);

    pinMode(LED_R_LEFT_PIN, OUTPUT);
    pinMode(LED_G_LEFT_PIN, OUTPUT);
    pinMode(LED_B_LEFT_PIN, OUTPUT);

    pinMode(LED_R_RIGHT_PIN, OUTPUT);
    pinMode(LED_G_RIGHT_PIN, OUTPUT);
    pinMode(LED_B_RIGHT_PIN, OUTPUT);
}

void studyMode(){
    ledcWriteTone(BUZZER_CH, 0); // stop buzzer

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

    ledcWriteTone(BUZZER_CH, 1000); // 1kHz tone for warning
}

void breakMode(){
    ledcWriteTone(BUZZER_CH, 0); // stop buzzer

    digitalWrite(LED_R_LEFT_PIN, LOW);
    digitalWrite(LED_G_LEFT_PIN, LOW);
    digitalWrite(LED_B_LEFT_PIN, HIGH);

    digitalWrite(LED_R_RIGHT_PIN, LOW);
    digitalWrite(LED_G_RIGHT_PIN, LOW);
    digitalWrite(LED_B_RIGHT_PIN, HIGH);
}

void idleMode() {
    ledcWriteTone(BUZZER_CH, 0); // stop buzzer

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