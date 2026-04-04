#include "timer.h"
//#include <pins.h>??

 
//Include the calculations as last time? or is it in fsm?

//TIMER VARIABLES

// Study Timer (25 minutes focus time)
unsigned long studyStartTime = 0;      // Timestamp when study timer started
unsigned long studyPausedTime = 0;     // Stores elapsed time when timer was paused
bool studyTimerRunning = false;        // True when study timer is active
bool studyTimerPaused = false;         // True when study timer is paused

// Break Timer (5 minutes break time)
unsigned long breakStartTime = 0;
unsigned long breakPausedTime = 0;
bool breakTimerRunning = false;
bool breakTimerPaused = false;

// Inactivity Timer (5 minutes no motion → triggers warning)
unsigned long inactivityStartTime = 0;
unsigned long inactivityPausedTime = 0;
bool inactivityTimerRunning = false;
bool inactivityTimerPaused = false;

// START TIMER FUNCTIONS

// Starts the 25-minute study timer from zero
void startStudyTimer() {
  studyStartTime = millis();
  studyPausedTime = 0;
  studyTimerRunning = true;
  studyTimerPaused = false;
  Serial.println("Study Timer Started (25 minutes)");
}

// Starts the 5-minute break timer from zero
void startBreakTimer() {
  breakStartTime = millis();
  breakPausedTime = 0;
  breakTimerRunning = true;
  breakTimerPaused = false;
  Serial.println("Break Timer Started (5 minutes)");
}

// Starts the inactivity timer (used to detect when user stops moving)
void startInactivityTimer() {
  inactivityStartTime = millis();
  inactivityPausedTime = 0;
  inactivityTimerRunning = true;
  inactivityTimerPaused = false;
}

// PAUSE TIMER FUNCTIONS

// Pauses the study timer and saves current progress (used in WARNING state)
void pauseStudyTimer() {
  if (studyTimerRunning && !studyTimerPaused) {
    studyPausedTime = millis() - studyStartTime;   // Save how much time has already passed
    studyTimerPaused = true;
    Serial.println("Study Timer PAUSED");
  }
}

/*void pauseBreakTimer() {
  if (breakTimerRunning && !breakTimerPaused) {
    breakPausedTime = millis() - breakStartTime;
    breakTimerPaused = true;
    Serial.println("Break Timer PAUSED");
  }
}
  
no need to include this function */

void pauseInactivityTimer() {
  if (inactivityTimerRunning && !inactivityTimerPaused) {
    inactivityPausedTime = millis() - inactivityStartTime;
    inactivityTimerPaused = true;
  }
}

// RESUME TIMER FUNCTIONS

// Resumes the study timer from where it was paused (important for WARNING → STUDY transition)
void resumeStudyTimer() {
  if (studyTimerPaused) {
    studyStartTime = millis() - studyPausedTime;   // Restore the saved elapsed time
    studyTimerPaused = false;
    Serial.println("Study Timer RESUMED");
  }
}

/*void resumeBreakTimer() {
  if (breakTimerPaused) {
    breakStartTime = millis() - breakPausedTime;
    breakTimerPaused = false;
    Serial.println("Break Timer RESUMED");
  }
}

  no need to include this function */

void resumeInactivityTimer() {
  if (inactivityTimerPaused) {
    inactivityStartTime = millis() - inactivityPausedTime;
    inactivityTimerPaused = false;
  }
}

// STOP / RESET TIMER FUNCTIONS

void stopStudyTimer() {
  studyTimerRunning = false;
  studyTimerPaused = false;
  studyPausedTime = 0;
}

void stopBreakTimer() {
  breakTimerRunning = false;
  breakTimerPaused = false;
  breakPausedTime = 0;
}

void stopInactivityTimer() {
  inactivityTimerRunning = false;
  inactivityTimerPaused = false;
  inactivityPausedTime = 0;
}

//TIMER STATUS FUNCTIONS

// Returns true when the 25-minute study time is complete
bool isStudyTimerFinished() {
  if (!studyTimerRunning || studyTimerPaused) return false;
  return (millis() - studyStartTime >= 25UL * 60 * 1000);
}

// Returns true when the 5-minute break time is complete
bool isBreakTimerFinished() {
  if (!breakTimerRunning || breakTimerPaused) return false;
  return (millis() - breakStartTime >= 5UL * 60 * 1000);
}

// Returns true when inactivity timeout has been reached
bool isInactivityTimerFinished() {
  if (!inactivityTimerRunning || inactivityTimerPaused) return false;
  return (millis() - inactivityStartTime >= 5UL * 60 * 1000);
}

// PROGRESS FUNCTION

/*
Calculates and returns the progress of the currently active timer
Total duration of the timer in milliseconds
0.0  = timer just started
0.5  = 50% completed
1.0  = timer finished
 */

float getTimerProgress(unsigned long totalTime) {
  unsigned long elapsed = 0;

  // Check which timer is active and calculate elapsed time
  if (studyTimerRunning) {
    elapsed = studyTimerPaused ? studyPausedTime : (millis() - studyStartTime);
  }
  else if (breakTimerRunning) {
    elapsed = breakTimerPaused ? breakPausedTime : (millis() - breakStartTime);
  }
  else if (inactivityTimerRunning) {
    elapsed = inactivityTimerPaused ? inactivityPausedTime : (millis() - inactivityStartTime);
  }

  if (totalTime == 0) return 0.0f;
  if (elapsed >= totalTime) return 1.0f;

  return (float)elapsed / (float)totalTime;   // Returns progress as fraction (0.0 - 1.0)
}
