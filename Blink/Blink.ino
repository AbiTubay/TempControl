/*
 * Blink.ino
 * Turn lamp on and off
 * Abigail Tubay 2018
 */

int pin = 11;                // pin number where the ELVIS LED is connected to

/**
 * Set up enviroment for the lamp
 */
void setup() {
  // initialize digital pin as an output.
  pinMode(pin, OUTPUT);
}

/**
 * turn lamp on and off with delay in between 
 */
void loop() {
  digitalWrite(pin, HIGH);    // turn the Lamp on (HIGH is the voltage level)
  delay(25);                  // wait for 0.025 second
  digitalWrite(pin, LOW);     // turn the Lamp off by making the voltage LOW
  delay(25);                  // wait for 0.025 second
}
