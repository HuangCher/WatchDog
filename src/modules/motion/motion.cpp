#include "motion.h"
// Motion Detection Module
// Owner: Johanna
//
// Responsibilities:
// - Read PIR sensor
// - Track last motion time
// - Calculate inactivity duration
// - Provide motion information to system logic


void motionSetup()
{
    pinMode(PIR_PIN, INPUT);
}

bool motionIsDetected()
{
    return digitalRead(PIR_PIN) == HIGH;
}
