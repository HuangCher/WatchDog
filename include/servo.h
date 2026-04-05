// veronica
#pragma once
#include <Servo.h>
#include <iostream>
#include "pins.h" //VSCODE only
#include <Arduino.h>
#include "timer.h"

using namespace std;

extern bool paused; 

void init_servo();
void servo_idle();
void servo_progress(float progress);
void servo_warning();
void servo_break();
void restore_position();