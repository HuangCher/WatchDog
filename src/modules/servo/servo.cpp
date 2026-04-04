// veronica
#pragma once
#include <Servo.h>
// #include <iostream>
#include "pins.h" //VSCODE only
#include <Arduino.h>
#include <ESP32Servo.h>
#include "timer.h"
#define SERVO_PIN 16

// using namespace std;

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
    myservo.write(0);
    paused = true; // ?
    //Stays at 0 degrees unless button is pressed
}

void servo_progress(float progress){   
  paused = false; //Motor should not be paused
  // myservo.write(0);
  float current_angle = 0 * 180; //Start at 0
  if (current_angle < 0) current_angle = 0;
  if (current_angle > 180) current_angle = 180;

  angle = (int)current_angle;
  myservo.write(angle);

  // if (paused == false){
  //   while (current_angle < 180){
  //     current_angle = progress * 180;
  //     angle = current_angle;
  //     myservo.write(current_angle);
  //   }
  // }
  // angle = 180;

  //Make flag to pause (on/off) and put in header file
  //float progress * 180 = study angle 
  //progress = elapsed time / maximum time (aka STUDY_TIME)
  // use functions to take in Johanna's progress variable 
}

void servo_warning() {
    angle = 180;
    myservo.write(angle);
    paused = false;
}

void servo_break() {
    angle = 90;
    myservo.write(angle);
    paused = false;
}

void restore_position(){ //Return servo motor to original angle
  myservo.write(angle);
}