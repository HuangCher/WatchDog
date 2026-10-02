#ifndef ALERT_H
#define ALERT_H

#include <Arduino.h>
#include "pins.h"

void setup_alert();

void studyMode();
void warningMode();
void breakMode();
void idleMode();

void loop_alert();

#endif