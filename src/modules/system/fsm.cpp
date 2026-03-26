// naydelin

// use fake functions to test the FSM logic without 
// needing the actual hardware modules

#include "pins.h"
#include <Arduino.h>
#include "motion.h"
#include "fsm.h"
#define MINUTE 60000UL // one min in millisecond

// Responsibilities:
// - Manage robot states
// - Call functions from other modules
//
// States:
// Idle
// Study
// Warning
// Break

FSM::FSM(Hardware *hw)
{
    hardware = hw;
    currentState = NULL;

    // intialize timers
    lastMotionTime = 0;
    studyStartTime = 0;
    breakStartTime = 0;

    lastButtonState = false;

    // timing settings (change for testing if needed)
    inactivityLimit = 10000; // 10 seconds for testing
    studyLength = 25 * MINUTE; 
    breakLength = 5 * MINUTE;
}

void FSM::begin()
{
    // start timers at beginning 
    lastMotionTime = millis();
    studyStartTime = millis();
    breakStartTime = millis();

    // save intial button state
    lastButtonState = hardware->readButton();

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

Hardware* FSM::getHardware() {
    return hardware;
}

void FSM::resetMotionTimer()
{
    lastMotionTime = millis();
}

void FSM::startStudyTimer()
{
    studyStartTime = millis();
}

void FSM::startBreakTimer()
{
    breakStartTime = millis();
}

// GETTER
unsigned long FSM::getInactiveTime()
{
    return millis() - lastMotionTime;
}

// GETTER
unsigned long FSM::getStudyTime()
{
    return millis() - studyStartTime;
}

// GETTER
unsigned long FSM::getBreakTime()
{
    return millis() - breakStartTime;
}

bool FSM::buttonPressed()
{
    bool currentButtonState = hardware->readButton();

    // only trigger once when button is first pressed (not held)
    bool pressedEvent = false;
    if (lastButtonState == false && currentButtonState == true) {
        pressedEvent = true;
    }

    lastButtonState = currentButtonState;
    return pressedEvent;
}

bool FSM::motionDetected()
{
    return hardware->readMotion();
}

// GETTER 
unsigned long FSM::getInactivityLimit()
{
    return inactivityLimit;
}

// GETTER
unsigned long FSM::getStudyLength()
{
    return studyLength;
}

// GETTER
unsigned long FSM::getBreakLength()
{
    return breakLength;
}

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
    Hardware* hw = fsm->getHardware();

    hw->logMessage("entering idle state");
    hw->turnLightsOff();
    hw->buzzerOff();
    hw->servoIdle();
}

void IdleState::update(FSM *fsm)
{
    // button pressed starts study mode
    if (fsm->buttonPressed()) {
        fsm->startStudyTimer();
        fsm->resetMotionTimer();
        fsm->setState(StudyState::getInstance());
    }
}

void IdleState::exit(FSM *fsm)
{
    fsm->getHardware()->logMessage("exiting idle state");
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
    Hardware* hw = fsm->getHardware();

    hw->logMessage("entering study state");
    hw->turnLightsOff();
    hw->buzzerOff();
    hw->servoStudy();

    // reset inactivity timer when entering study
    fsm->resetMotionTimer();
}

void StudyState::update(FSM *fsm)
{
    // button pressed again -> system off and goes back to idle
    if (fsm->buttonPressed()) {
        fsm->setState(IdleState::getInstance());
        return;
    }

    // if motion is detected, reset inactivity timer bc user is active
    if (fsm->motionDetected()) {
        fsm->resetMotionTimer();
    }

    // if inactive too long, go to warning
    if (fsm->getInactiveTime() >= fsm->getInactivityLimit()) {
        fsm->setState(WarningState::getInstance());
        return;
    }

    // if 25 min is over, go to break
    if (fsm->getStudyTime() >= fsm->getStudyLength()) {
        fsm->setState(BreakState::getInstance());
        return;
    }
}

void StudyState::exit(FSM *fsm)
{
    fsm->getHardware()->logMessage("exiting study state");
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
    Hardware* hw = fsm->getHardware();

    hw->logMessage("entering warning state");
    hw->setWarningLights();
    hw->buzzerOn();
    hw->servoWarning();
}

void WarningState::update(FSM *fsm)
{
    // button pressed -> go to idle state
    if (fsm->buttonPressed()) {
        fsm->setState(IdleState::getInstance());
        return;
    }

    // motion means user came back, so go back to study
    if (fsm->motionDetected()) {
        fsm->resetMotionTimer();
        fsm->setState(StudyState::getInstance());
        return;
    }
}

void WarningState::exit(FSM *fsm)
{
    Hardware* hw = fsm->getHardware();

    hw->logMessage("exiting warning state");
    hw->buzzerOff();
    hw->turnLightsOff();
}

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
    Hardware* hw = fsm->getHardware();

    hw->logMessage("entering break state");
    fsm->startBreakTimer();

    hw->setBreakLights();
    hw->buzzerOff();
    hw->servoBreak();
}

void BreakState::update(FSM *fsm)
{
    // button pressed -> go to idle state
    if (fsm->buttonPressed()) {
        fsm->setState(IdleState::getInstance());
        return;
    }

    // after break time is over, go back to study
    if (fsm->getBreakTime() >= fsm->getBreakLength()) {
        fsm->startStudyTimer();
        fsm->resetMotionTimer();
        fsm->setState(StudyState::getInstance());
        return;
    }
}

void BreakState::exit(FSM *fsm)
{
    Hardware* hw = fsm->getHardware();

    hw->logMessage("exiting break state");
    hw->turnLightsOff();
}

const char *BreakState::getName()
{
    return "BREAK";
}