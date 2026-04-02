#include "motion.h" // new addtion so that we can use the motionDetected flag in fsm.cpp when we integrate the modules together
// Motion Detection Module
// Owner: Johanna
//
// Responsibilities:
// - Read PIR sensor
// - Track last motion time
// - Calculate inactivity duration
// - Provide motion information to system logic

//#define ledPin #
//#define buzzer 15

//setting up the PIR sensor and the LED and buzzer pins
void setup(){
//Serial.begin(9600);
pinMode(PIR_PIN, INPUT);
motionDetected = false;
//pinMode (ledPin, OUTPUT);     LED Pin
//pinMode (15, OUTPUT);         Buzzer Pin
}


//main loop to read the PIR sensor and control the LED and buzzer
void loop(){
    motionDetected = digitalRead(PIR_PIN); 

    // these all can be in the main fsm.cpp file
    if (motionDetected==true){
    //digitalWrite(ledPin, HIGH);               LED turns on when motion is detected
    //Serial.println("MOTION DETECTED!!");      output to serial monitor

    } 
    else {
    //digitalWrite (ledPin, LOW);       LED turns off when no motion is detected

    //tone (15, 1000);                  Buzzer makes noise when no motion is detected
    //delay(1000);
    //noTone(15);
    }
}

//GONNA UPDATE THIS CODE 