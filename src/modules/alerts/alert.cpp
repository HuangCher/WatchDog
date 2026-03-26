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
    //Serial.begin(9600);

    // BUZZER
    pinMode(BUZZER_PIN, OUTPUT);

    // RGB LED
    pinMode(LED_R_LEFT_PIN, OUTPUT);
    pinMode(LED_G_LEFT_PIN, OUTPUT);
    pinMode(LED_B_LEFT_PIN, OUTPUT);

    pinMode(LED_R_RIGHT_PIN, OUTPUT);
    pinMode(LED_G_RIGHT_PIN, OUTPUT);
    pinMode(LED_B_RIGHT_PIN, OUTPUT);
}

// Green
void studyMode(){ 
    // Left LED
    digitalWrite(LED_R_LEFT_PIN, LOW);
    digitalWrite(LED_G_LEFT_PIN, HIGH);
    digitalWrite(LED_B_LEFT_PIN, LOW);

    digitalWrite(LED_R_RIGHT_PIN, LOW);
    digitalWrite(LED_G_RIGHT_PIN, HIGH);
    digitalWrite(LED_B_RIGHT_PIN, LOW);
}

// Red
void warningMode(){ 
    // Left LED
    digitalWrite(LED_R_LEFT_PIN, HIGH);
    digitalWrite(LED_G_LEFT_PIN, LOW);
    digitalWrite(LED_B_LEFT_PIN, LOW);

    digitalWrite(LED_R_RIGHT_PIN, HIGH);
    digitalWrite(LED_G_RIGHT_PIN, LOW);
    digitalWrite(LED_B_RIGHT_PIN, LOW);

    // Buzzer
    digitalWrite(BUZZER_PIN, HIGH); 
    tone(BUZZER_PIN, 1000);
}

void breakMode(){
    // Left LED
    digitalWrite(LED_R_LEFT_PIN, LOW);
    digitalWrite(LED_G_LEFT_PIN, LOW);
    digitalWrite(LED_B_LEFT_PIN, HIGH);

    digitalWrite(LED_R_RIGHT_PIN, LOW);
    digitalWrite(LED_G_RIGHT_PIN, LOW);
    digitalWrite(LED_B_RIGHT_PIN, HIGH);
}

void loop_alert(){
    // Example usage:
    studyMode();
    delay(5000);

    warningMode();
    delay(5000); // Stay in warning mode for 5 seconds

    breakMode();
    delay(5000);
}

void setup() {
    setup_alert();
}

void loop() {
    loop_alert();
}