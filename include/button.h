#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define BUTTON_PIN 2

void buttonSetup();
bool buttonWasPressed();
bool isSystemOn();
void setSystemState(bool on);
bool isButtonHeld();

#endif