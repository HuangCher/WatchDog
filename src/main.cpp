// dw abt this file yet lol
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

    // Initialize all modules
    buttonSetup();
    motionSetup();
    setup_alert();
    init_servo();

    // Start FSM
    fsm.begin();

    Serial.println("System initialized");
}

void loop() {
    fsm.update();
}