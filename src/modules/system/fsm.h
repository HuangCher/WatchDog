#ifndef FSM_H
#define FSM_H

#include <Arduino.h>

// hardware interface
// fake hardware for testing but will be swapped with real hardware later
class Hardware {
    public: 
        // inputs
        virtual bool readButton() = 0;
        virtual bool readMotion() = 0;

        // outputs
        virtual void setIdleLights() = 0;
        virtual void setWarningLights() = 0;
        virtual void setBreakLights() = 0;
        virtual void turnLightsOff() = 0;

        virtual void buzzerOn() = 0;
        virtual void buzzerOff() = 0;

        virtual void servoStudy() = 0;
        virtual void servoWarning() = 0;
        virtual void servoBreak() = 0;
        virtual void servoIdle() = 0;

        // debug printing
        virtual void logMessage(const char* msg) = 0;

};

class FSM; 

// base state class
// every state must define:
    // enter() -> runs once when we enter state
    // update() -> runs every loop
    // exit() -> runs once when leaving state
class State {
    public:
        virtual void enter(FSM* fsm) = 0;
        virtual void update(FSM* fsm) = 0;
        virtual void exit(FSM* fsm) = 0;
        virtual const char* getName() = 0;
};

// main FSM
// stores: current state, timers, hardware pointer
class FSM {
    private:
        State* currentState;
        Hardware* hardware;

        // timers
        unsigned long lastMotionTime;
        unsigned long studyStartTime;
        unsigned long breakStartTime;

        // used to detect button press event
        bool lastButtonState;

        // timing values (can tweak later)
        unsigned long inactivityLimit;
        unsigned long studyLength;
        unsigned long breakLength;
    public:
        FSM(Hardware* hardware);
        
        void begin();
        void update();
        void setState(State* newState);

        Hardware* getHardware();

        // timer helpers
        void resetMotionTimer();
        void startStudyTimer();
        void startBreakTimer();

        unsigned long getInactiveTime();
        unsigned long getStudyTime();
        unsigned long getBreakTime();

        // input checks
        bool buttonPressed();
        bool motionDetected();

        // GETTERS
        unsigned long getInactivityLimit();
        unsigned long getStudyLength();
        unsigned long getBreakLength();

        const char* getStateName();
};

// state classes
// each one controls what watchdog will do in that state and when to switch to another state
class IdleState : public State {
    public:
        static IdleState* getInstance();

        void enter(FSM* fsm);
        void update(FSM* fsm);
        void exit(FSM* fsm);
        const char* getName();

    private:
        IdleState() {}
};

class StudyState : public State {
    public:
        static StudyState* getInstance();

        void enter(FSM* fsm);
        void update(FSM* fsm);
        void exit(FSM* fsm);
        const char* getName();

    private:
        StudyState() {}
};

class WarningState : public State {
    public:
        static WarningState* getInstance();

        void enter(FSM* fsm);
        void update(FSM* fsm);
        void exit(FSM* fsm);
        const char* getName();

    private:
        WarningState() {}
};

class BreakState : public State {
    public:
        static BreakState* getInstance();

        void enter(FSM* fsm);
        void update(FSM* fsm);
        void exit(FSM* fsm);
        const char* getName();

    private:
        BreakState() {}
};

#endif FSM_H