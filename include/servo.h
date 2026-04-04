// veronica
#pragma once
#include <Servo.h>
#include <iostream>
#include "pins.h" //VSCODE only
#include <Arduino.h>
#include "timer.h"
#define SERVO_PIN 16

using namespace std;

bool paused = false; 

void init_servo();
void servo_idle();
void servo_progress(float progress);
void restore_position();