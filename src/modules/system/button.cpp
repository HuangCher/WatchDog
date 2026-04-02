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

#define BUTTON_PIN 2          // Change only if your button is on a different pin

// Global variables for button
unsigned long lastButtonPressTime = 0;
const unsigned long DEBOUNCE_DELAY = 250;   // milliseconds
bool systemOn = false;                      // System starts OFF


// Button Functions


void buttonSetup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);   // Button connected between pin and GND
  systemOn = false;
  Serial.println("Button initialized - Press to START the system");
}

// Returns true only once when the button is newly pressed (debounced)
bool buttonWasPressed() {
  if (digitalRead(BUTTON_PIN) == LOW) {                    // Button is pressed (LOW)
    if (millis() - lastButtonPressTime > DEBOUNCE_DELAY) { // Debounce check
      lastButtonPressTime = millis();
      
      // Toggle system state every time button is pressed
      systemOn = !systemOn;
      
      return true;   // Button was just pressed
    }
  }
  return false;
}

// Returns current system state
bool isSystemOn() {
  return systemOn;
}

// Force the system state (optional, useful for resets)
void setSystemState(bool on) {
  systemOn = on;
}

// Optional: Check if button is currently held down
bool isButtonHeld() {
  return digitalRead(BUTTON_PIN) == LOW;
}