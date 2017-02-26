
#include "Keyboard.h"

// Mapping arrowkeys to navigate in street view
const int upPin = 2;   // KEY_UP_ARROW
const int leftPin = 3; // KEY_LEFT_ARROW
const int rightPin = 4;// KEY_RIGHT_ARROW
const int pullupPin = 4;// supply vcc

boolean upState = false;
boolean leftState = false;
boolean rightState = false;

int cycles=0;
int pause=0;

void setup() {
  pinMode(upPin, INPUT_PULLUP);
  pinMode(leftPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
  pinMode(pullupPin, OUTPUT);

  digitalWrite(pullupPin, HIGH);

  afficheurSetup();
  Keyboard.begin();
}

void loop() {
  boolean state;

  Keyboard.release(KEY_UP_ARROW);
  state = !digitalRead(upPin);
  if (!upState && state) {
    Keyboard.press(KEY_UP_ARROW);
    upState = true;
    cycles++;
    pause=0;
  }
  if (!state) {
    upState = false;
  }


  state = !digitalRead(leftPin);
  if (!leftState && state) {
    Keyboard.press(KEY_LEFT_ARROW);
    leftState = true;
  }

  if (!state) {
    Keyboard.release(KEY_LEFT_ARROW);
    leftState = false;
  }

  state = !digitalRead(rightPin);
  if (!rightState && state) {
    Keyboard.press(KEY_RIGHT_ARROW);
    rightState = true;
  }

  if (!state) {
    Keyboard.release(KEY_RIGHT_ARROW);
    rightState = false;
  }

  // Rénitialisation automaitque après ~10 secondes
  if(pause++ > 1000) {
    cycles=0;
    pause=0;
  }
  
  displayNumber(cycles);
  refreshDisplay();
}

