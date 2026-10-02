#include <Arduino.h> 
#include "pins.h" 
#include "motion.h"
// Motion Detection Module
// Owner: Johanna
//
// Responsibilities:
// - Read PIR sensor
// - Track last motion time
// - Calculate inactivity duration
// - Provide motion information to system logic

static unsigned long lastMotionTime = 0;
const unsigned long MOTION_GRACE_MS = 4000;

void motionSetup()
{
    pinMode(PIR_PIN, INPUT);
}

bool motionIsDetected()
{
    return digitalRead(PIR_PIN) == HIGH;
}

bool motionIsActive() {
    if (digitalRead(PIR_PIN) == HIGH) {
        lastMotionTime = millis();  // refresh on real detection
        return true;
    }
    // Stay "active" during the blind period so inactivity timer doesn't falsely run
    return (millis() - lastMotionTime < MOTION_GRACE_MS);
}