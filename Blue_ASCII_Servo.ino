#include <Servo.h>

// set left/right servos based on even/odd ASCII values
//  author=blekenbleu,
//  title = SimHub Custom serial device for Blue Pill
//  year =2021
//  url = https://blekenbleu.github.io/Arduino/

// Changelog
// StuyoP, 01.2022 - modified to work with Arduino Nano

#define LED 17		// Blue Pill green LED
Servo left, right;
unsigned long then, timeout=0;
int next = HIGH;
int even = 30, odd = 30;	// even: LED on count
byte ladd=63, radd=65;		// initial servo offsets:  unloaded bracket angles

void setup() {			// setup() code runs once
  then = millis();   		// start the clock
  // initialize as an output digital pin connected to green LED
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);	// turn off LED by floating pin HIGH
  left.attach(9);		// Blue Pill 5V tolerant PWM pins; 
						// StuyoP, 01.2022 - modified pins to reference Arduino Nano Digital Out 9 and 10 
  right.attach(10);
  left.write(ladd);		// initial servo positions
  right.write(radd);

  // Initialize serial and wait for port to be opened:
  Serial.begin(9600);
  while (!Serial)
    delay(1);			// wait for native USB serial port to connect
  Serial.println("Blue_ASCII_Servo: connected");
}

// loop() is not REALLY a loop;
// it is just the main routine, which gets called often.
void loop() {
  // main code goes here, to be called repeatedly:
  byte received;
  unsigned long now = millis();	// should initially toggle on (LOW)

  if (then < now) {		// LED feedback for left vs right vs waiting
    if (1000000 < timeout) {	// idle for a second or so?
      even = odd = 30;		// idle waiting feedback
      timeout = 0;
    }
    if (next == LOW) {
      next = HIGH;
      then = now + odd;		// LED off for odd milliseconds
    }
    else {
      next = LOW;
      then = now + even;	// LED on for even milliseconds
    }
    digitalWrite (LED, next);	// toggle LED: HIGH turns it off
    if (40 > even)		// idle?
      delay(30);		// this may facilitate interrupting
  }
  if (0 < Serial.available()) {
    received = Serial.read();
    if (2 > received) {
      byte add;			// prepare to change servo offset

      while (1 > Serial.available())
        delay(1);
      add = Serial.read();	// immediately next byte is an offset
      if (1 & received)
        radd = add;
      else ladd = add;
    }
    else if (1 & received) {
      right.write((127&received)+radd);
      even = 40;		// LED briefly on
      odd = 180;		// right has long odds
    } else {
      left.write((127&received)+ladd);
      even = 180;		// LED mostly on
      odd = 40;	
    }
    timeout = 0;
  }
  else timeout++;
}
