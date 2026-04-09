#ifndef MOTION_H
#define MOTION_H
// Motion Detection Module
// Owner: Johanna

#include "pins.h"
#include <Arduino.h>
// Responsibilities:
// - Read PIR sensor
// - Track last motion time
// - Calculate inactivity duration
// - Provide motion information to system logic
// create a flag to track if motion is detected, and use it to control the LED and buzzer in fsm.cpp later on when we integrate the modules together
// extern bool motionDetected;

void motionSetup();
bool motionIsDetected();
bool motionIsActive();

#endif