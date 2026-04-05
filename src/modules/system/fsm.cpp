#include "pins.h"
#include <Arduino.h>
#include "fsm.h"
#include "button.h"
#include "timer.h"
#include "motion.h"
#include "alert.h"
#include "servo.h"

// Responsibilities:
// - Manage robot states
// - Call functions from other modules
//
// States:
// Idle
// Study
// Warning
// Break

// add a loop to constantly check for update

FSM::FSM()
{
    currentState = NULL;

    // intialize timers
    // lastMotionTime = 0;
    // studyStartTime = 0;
    // breakStartTime = 0;

    lastButtonState = false;

    // timing settings (change for testing if needed)
    // inactivityLimit = 10000; // 10 seconds for testing
    // studyLength = 25 * MINUTE; 
    // breakLength = 5 * MINUTE;
}

void FSM::begin()
{
    // start timers at beginning 
    // lastMotionTime = millis();
    // studyStartTime = millis();
    // breakStartTime = millis();

    // save intial button state
    // lastButtonState = buttonIsPressed();

    stopStudyTimer();
    stopBreakTimer();
    stopInactivityTimer();

    // start in idle
    currentState = IdleState::getInstance();
    currentState->enter(this);
}

void FSM::update()
{
    if (currentState != NULL) {
        currentState->update(this);
    }
}

void FSM::setState(State *newState)
{
    // leave current state
    if (currentState != NULL) {
        currentState->exit(this);
    }

    // switch state
    currentState = newState;

    // enter new state
    if (currentState != NULL) {
        currentState->enter(this);
    }
}

// void FSM::resetMotionTimer()
// {
//     lastMotionTime = millis();
// }

// void FSM::startStudyTimer()
// {
//     studyStartTime = millis();
// }

// void FSM::startBreakTimer()
// {
//     breakStartTime = millis();
// }

// GETTER
// unsigned long FSM::getInactiveTime()
// {
//     return millis() - lastMotionTime;
// }

// GETTER
// unsigned long FSM::getStudyTime()
// {
//     return millis() - studyStartTime;
// }

// GETTER
// unsigned long FSM::getBreakTime()
// {
//     return millis() - breakStartTime;
// }

// debounce - otherwise may see multiple fast presses 
// bool FSM::buttonPressed()
// {
//     return buttonWasPressed();
//     // static unsigned long lastDebounceTime = 0;
//     // const unsigned long debounceDelay = 50;

//     // bool currentButtonState = buttonIsPressed();

//     // // only trigger once when button is first pressed (not held)
//     // bool pressedEvent = false;
//     // if (currentButtonState != lastButtonState) {
//     //     if (millis() - lastDebounceTime > debounceDelay) {
//     //         lastDebounceTime = millis();
//     //     }

//     //     // trigger only when button changes from not pressed to pressed 
//     //     if (lastButtonState == false && currentButtonState == true) {
//     //         lastButtonState = currentButtonState;
//     //     }
        
//     //     pressedEvent = true;
//     // }

//     // lastButtonState = currentButtonState;
//     // return pressedEvent;
// }

// bool FSM::motionDetected()
// {
//     return motionIsDetected();
// }

// GETTER 
// unsigned long FSM::getInactivityLimit()
// {
//     return inactivityLimit;
// }

// GETTER
// unsigned long FSM::getStudyLength()
// {
//     return studyLength;
// }

// GETTER
// unsigned long FSM::getBreakLength()
// {
//     return breakLength;
// }

// GETTER
const char *FSM::getStateName()
{
    if (currentState == NULL) {
        return "NONE";
    }

    return currentState->getName();
}

/*------- IDLE STATE --------*/

IdleState *IdleState::getInstance()
{
    static IdleState state;
    return &state;
}

void IdleState::enter(FSM *fsm)
{
    // robot is "off"
    Serial.println("entering idle state");
    idleMode(); // idle alert (buzzer + lights)
    servo_idle();

    stopStudyTimer();
    stopBreakTimer();
    stopInactivityTimer();
}

void IdleState::update(FSM *fsm)
{
    // button pressed starts study mode
    if (buttonWasPressed()) {
        startStudyTimer();
        startInactivityTimer();
        fsm->setState(StudyState::getInstance());
    }
}

void IdleState::exit(FSM *fsm)
{
    Serial.println("exiting idle state");
}

const char *IdleState::getName()
{
    return "IDLE";
}

/*------- STUDY STATE --------*/

StudyState *StudyState::getInstance()
{
    static StudyState state;
    return &state;
}

void StudyState::enter(FSM *fsm)
{
    // normal monitoring state
    // Hardware* hw = fsm->getHardware();

    Serial.println("entering study state");
    studyMode();
    servo_study();

    // reset inactivity timer when entering study
    // fsm->resetMotionTimer();
}

void StudyState::update(FSM *fsm)
{
    // button pressed again -> system off and goes back to idle
    if (buttonWasPressed()) {
        fsm->setState(IdleState::getInstance());
        return;
    }

    // if motion is detected, reset inactivity timer bc user is active
    if (motionIsDetected()) {
        startInactivityTimer();
    }

    float progress = getTimerProgress(STUDY_TIME_MS);
    servo_progress(progress);

    // if inactive too long, go to warning
    if (isInactivityTimerFinished()) {
        fsm->setState(WarningState::getInstance());
        return;
    }

    // if 25 min is over, go to break
    if (isStudyTimerFinished()) {
        fsm->setState(BreakState::getInstance());
        return;
    }
}

void StudyState::exit(FSM *fsm)
{
    Serial.println("exiting study state");
}

const char *StudyState::getName()
{
    return "STUDY";
}

/*------- WARNING STATE --------*/

WarningState *WarningState::getInstance()
{
    static WarningState state;
    return &state;
}

void WarningState::enter(FSM *fsm)
{
    // alert user bc no motion detected
    // Hardware* hw = fsm->getHardware();

    Serial.println("entering warning state");
    warningMode(); // warning alert (buzzer + lights)
    servo_warning();

    pauseStudyTimer();
    pauseInactivityTimer();
}

void WarningState::update(FSM *fsm)
{
    // button pressed -> go to idle state
    if (buttonWasPressed()) {
        fsm->setState(IdleState::getInstance());
        return;
    }

    // motion means user came back, so go back to study
    if (motionIsDetected()) {
        resumeStudyTimer();
        startInactivityTimer();
        fsm->setState(StudyState::getInstance());
        return;
    }
}

void WarningState::exit(FSM *fsm) {}

// GETTER
const char *WarningState::getName()
{
    return "WARNING";
}

/*------- BREAK STATE --------*/

BreakState *BreakState::getInstance()
{
    static BreakState state;
    return &state;
}

void BreakState::enter(FSM *fsm)
{
    // Hardware* hw = fsm->getHardware();

    Serial.println("entering break state");
    breakMode(); // break alert (buzzer + lights)
    servo_break();
    
    startBreakTimer();
    stopInactivityTimer();
    stopStudyTimer();
}

void BreakState::update(FSM *fsm)
{
    // button pressed -> go to idle state
    if (buttonWasPressed()) {
        fsm->setState(IdleState::getInstance());
        return;
    }

    float progress = getTimerProgress(BREAK_TIME_MS);
    servo_progress(progress);

    // after break time is over, go back to study
    if (isBreakTimerFinished()) {
        stopBreakTimer();
        startStudyTimer();
        startInactivityTimer();
        fsm->setState(StudyState::getInstance());
        return;
    }
}

// void BreakState::exit(FSM *fsm)
// {
//     // Hardware* hw = fsm->getHardware();

//     Serial.println("exiting break state");
//     hw->turnLightsOff();
// }

const char *BreakState::getName()
{
    return "BREAK";
}

void BreakState::exit(FSM *fsm) {
    // optional cleanup when leaving break
}