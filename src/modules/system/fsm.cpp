// naydelin

// use fake functions to test the FSM logic without 
// needing the actual hardware modules

#include "pins.h"
#include <Arduino.h>
#include "motion.h"

// Responsibilities:
// - Manage robot states
// - Call functions from other modules
//
// States:
// Idle
// Study
// Warning
// Break
