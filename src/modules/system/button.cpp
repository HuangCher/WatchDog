// johanna

#include "pins.h"
// Responsibilities:
//- Detect/read button press 
//Then when the button is pressed, we start the system
//- Toggle system ON/OFF

// Button.cpp
// Responsibilities:
// - Detect/read button press
// - Start the system when button is pressed
// - Toggle system ON/OFF

#include <Arduino.h>


// // Global variables for button
unsigned long lastButtonPressTime = 0;
const unsigned long DEBOUNCE_DELAY = 250;   // milliseconds
// bool systemOn = false;                      // System starts OFF


// Button Functions
void buttonSetup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);   // Button connected between pin and GND
}

// Returns true only once when the button is newly pressed (debounced)
bool buttonWasPressed() {
  if (digitalRead(BUTTON_PIN) == LOW) {                    // Button is pressed (LOW)
    if (millis() - lastButtonPressTime > DEBOUNCE_DELAY) { // Debounce check
      lastButtonPressTime = millis();
      
      return true;   // Button was just pressed
    }
  }
  return false;
  // return digitalRead(BUTTON_PIN) == LOW; 
}

bool isButtonHeld() {
  return digitalRead(BUTTON_PIN) == LOW;
}