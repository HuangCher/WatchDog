#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

void buttonSetup();
bool buttonWasPressed();
bool isSystemOn();
void setSystemState(bool on);
bool isButtonHeld();

#endif