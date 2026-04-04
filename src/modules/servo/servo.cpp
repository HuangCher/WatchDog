// veronica
#pragma once
#include <Servo.h>
#include "pins.h"
#include <Arduino.h>
#include <ESP32Servo.h>
#include "timer.h"
#define SERVO_PIN 16

// Responsibilities:j
// - Initialize servo motor
// - Implement movement patterns for different robot states
//
// Functions to implement:
// servo_idle()      => neutral position
// servo_warning()   => alert motion
// servo_break()     => relaxed movement

//Initialization
Servo myservo;
int angle = 0;
bool paused = false;
int STUDY_TIME = 10000;
enum State {IDLE, STUDY, WARNING, BREAK};
State current_state = IDLE;

void init_servo(){
    myservo.attach(SERVO_PIN);
    myservo.write(angle); //Start in middle
    paused = false;
}


//Implementation
void servo_idle(){ //Neutral position
    angle = 0;
    myservo.write(angle);
    paused = true; // ?
    //Stays at 0 degrees unless button is pressed
}

void servo_progress(float progress){   
    if(paused) return;

    if(progress < 0) progress = 0;
    if(progress > 1) progress = 1;

    float current_angle = progress * 180.0;
    myservo.write((int)current_angle);
    angle = (int)current_angle;
}

void servo_warning() {
    angle = 180;
    myservo.write(angle);
    paused = true;
}

void servo_break() {
    angle = 90;
    myservo.write(angle);
    paused = false;
}

void restore_position(){ //Return servo motor to original angle
  myservo.write(angle);
}