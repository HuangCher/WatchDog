// a bunch of bool that we can use to track the state of the system, and 
// use them in fsm.cpp to control the flow of the system

// timer for the break (5 min)

/*timer for the study state, after the button is pressed timer for 25 min starts
 when it ends, we go to break state and start the break timer */

#ifndef TIMER_H 
#define TIMER_H
#pragma once
#include <Arduino.h>


// Timer variables
extern unsigned long studyStartTime;
extern unsigned long studyPausedTime;
extern bool studyTimerRunning;
extern bool studyTimerPaused;

extern unsigned long breakStartTime;
extern unsigned long breakPausedTime;
extern bool breakTimerRunning;
extern bool breakTimerPaused;

extern unsigned long inactivityStartTime;
extern unsigned long inactivityPausedTime;
extern bool inactivityTimerRunning;
extern bool inactivityTimerPaused;

// Timer control functions
void startStudyTimer();
void startBreakTimer();
void startInactivityTimer();

void pauseStudyTimer();
//void pauseBreakTimer();
void pauseInactivityTimer();

void resumeStudyTimer();
//void resumeBreakTimer();
void resumeInactivityTimer();

void stopStudyTimer();
void stopBreakTimer();
void stopInactivityTimer();

// Status checks
bool isStudyTimerFinished();
bool isBreakTimerFinished();
bool isInactivityTimerFinished();

// Progress (0.0 to 1.0)
float getTimerProgress(unsigned long totalTime);

#endif