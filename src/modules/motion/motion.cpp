// johanna

#include "pins.h"
#include <Arduino.h>
// Motion Detection Module
// Owner: Johanna
//
// Responsibilities:
// - Read PIR sensor
// - Track last motion time
// - Calculate inactivity duration
// - Provide motion information to system logic



//Code from the Arduino IDE

#define PIR_PIN 17
//#define ledPin #
//#define buzzer 15

//setting up the PIR sensor and the LED and buzzer pins
void setup(){
//Serial.begin(9600);
pinMode(17, INPUT);
//pinMode (ledPin, OUTPUT);     LED Pin
//pinMode (15, OUTPUT);         Buzzer Pin
}


//main loop to read the PIR sensor and control the LED and buzzer
void loop(){
bool pirPin = digitalRead(PIR_PIN); 

if (pirPin==true){
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