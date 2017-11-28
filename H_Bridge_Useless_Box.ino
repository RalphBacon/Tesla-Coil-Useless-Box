#include "Arduino.h"

// Motor control pins
#define hpos 9 // PWM pin in case we decide to use that
#define hneg 10 // As above

// Original switch pins (old motor connections)
#define swpos 2
#define swneg 3

// Beeper pin
#define beep 12

void setup() {
	Serial.begin(9600);

	// Motor control pins are output signals
	pinMode(hpos, OUTPUT);
	pinMode(hneg, OUTPUT);

	// Switch detection pins are inputs
	pinMode(swpos, INPUT);
	pinMode(swneg, INPUT);

	// Set output to motor to STOP initially
	digitalWrite(hpos, LOW);
	digitalWrite(hneg, LOW);

	Serial.println("Set up completed");
}

void loop() {
	// Wait until the switch has been pressed
	waitUntilSwitchPressedOn();

	// We can do stuff here (beep, play MP3s, flash lights)
	for (char cnt=20; cnt >= 0; cnt--){
		tone(beep, 1000 - (cnt * 10), 100);
		delay(20 + (cnt * 30));
	}

	// Start motor moving to move the switch back off (PWM?)
	digitalWrite(hpos, HIGH);
	digitalWrite(hneg, LOW);

	// Wait until the switch has been switched off
	waitUntilSwitchPressedOff();

	// Reverse the motor to return the arm to rest (PWM?)
	digitalWrite(hpos, LOW);
	digitalWrite(hneg, HIGH);

	// We must now detect the microswitch going LOW (it has opened)
	waitUntilArmInRestPosition();

	// Switch OFF motor
	digitalWrite(hpos, LOW);
	digitalWrite(hneg, LOW);

	// Here we can do other stuff (more MP3 sounds, lights or something)
	tone(beep, 1000, 100);
}

// Has main switch been flipped to ON position
void waitUntilSwitchPressedOn() {
	Serial.println("Waiting for switch ON");
	while (digitalRead(swpos) == LOW) {
		delay(10);
	};
	Serial.println("Switch ON detected");
}

// Has the main switch been flipped back to rest / off position
void waitUntilSwitchPressedOff() {
	Serial.println("Waiting for switch OFF");
	while (digitalRead(swpos) == HIGH) {
		delay(10);
	};
	Serial.println("Switch OFF detected");
}

// Has the µSwtich been closed (B = LOW), time to stop motor
void waitUntilArmInRestPosition() {
	Serial.println("Waiting for REST position");
	while (digitalRead(swneg) == HIGH) {
		delay(10);
	};
	Serial.println("At REST - cycle completed");
}
