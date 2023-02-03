/**
  Project Beethoven - piano.ino
  Author - sa-fx

  This code can be used to create a digital keyboard.
  Playing the first 6 notes of happy birthday will result
  in the keyboard playing the rest of the tune.
  Current implementation uses 13 keys on an Arduino Nano,
  but this can be expanded to support more keys on an
  Arduino Mega if desired.
  Library pitches.h created by Elegoo Inc.

  Last updated: 31/01/2023
*/

#include "pitches.h"

// Define pins
#define SPEAKER A1
#define C 2
#define CS 3
#define D 4
#define DS 5
#define E 6
#define F 7
#define FS 8
#define G 9
#define GS 10
#define A 11
#define AS 12
#define B A4
#define C2 A0

// Define delays for notes
#define NOTE_DELAY_1 400
#define NOTE_DELAY_2 NOTE_DELAY_1 / 2
#define NOTE_DELAY_3 NOTE_DELAY_1 / 3
#define NOTE_DELAY_4 NOTE_DELAY_1 - 50
#define NOTE_DELAY_5 NOTE_DELAY_1 + 200

// Define tones of notes for use with tone()
int notes[] = {
  100, 200, NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5, NOTE_C6, 500, 500, 500, NOTE_B5};

// Case counter for switch cases
int caseVar;

void setupWrongNote() {
  //Read every key to determine note to be played
  Serial.println("Now setting up wrong note");
  if(!digitalRead(C) && (caseVar != 0 && caseVar != 1 && caseVar != 3)){
    playNote(C);
    caseVar = 0;
  }
  else if(!digitalRead(CS)){
    playNote(CS);
    caseVar = 0;
  }
  else if(!digitalRead(D) && caseVar != 2){
    playNote(D);
    caseVar = 0;
  }
  else if(!digitalRead(DS)){
    playNote(DS);
    caseVar = 0;
  }
  else if(!digitalRead(E) && caseVar != 5){
    playNote(E);
    caseVar = 0;
  }
  else if(!digitalRead(F) && caseVar != 4){
    playNote(F);
    caseVar = 0;
  }
  else if(!digitalRead(FS)){
    playNote(FS);
    caseVar = 0;
  }
  else if(!digitalRead(G)){
    playNote(G);
    caseVar = 0;
  }
  else if(!digitalRead(GS)){
    playNote(GS);
    caseVar = 0;
  }
  else if(!digitalRead(A)){
    playNote(A);
    caseVar = 0;
  }
  else if(!digitalRead(AS)){
    playNote(AS);
    caseVar = 0;
  }
  else if(!digitalRead(B)){
    playNote(B);
    caseVar = 0;
  }
  else if(!digitalRead(C2)){
    playNote(C2);
    caseVar = 0;
  }
  // Default case is that no key has been pressed
  // As such, caseVar cannot be reset as a default
  return;
}

void playNote(int note) {
  Serial.print("Playing note: ");
  Serial.println(note);
  // Play until the key is no longer being pressed
  while(!digitalRead(note)){
    tone(SPEAKER, notes[note], 100);
  }
  return;
}

void happyBirthday() {
  //C C D C G F
  delay(NOTE_DELAY_1);
  tone(SPEAKER, NOTE_C5, NOTE_DELAY_3);
  delay(NOTE_DELAY_2);
  tone(SPEAKER, NOTE_C5, NOTE_DELAY_2);
  delay(NOTE_DELAY_2);
  tone(SPEAKER, NOTE_D5, NOTE_DELAY_4);
  delay(NOTE_DELAY_1);
  tone(SPEAKER, NOTE_C5, NOTE_DELAY_4);
  delay(NOTE_DELAY_1);
  tone(SPEAKER, NOTE_G5, NOTE_DELAY_4);
  delay(NOTE_DELAY_1);
  tone(SPEAKER, NOTE_F5, NOTE_DELAY_5);

  //C C C^ A F E D
  delay(NOTE_DELAY_5*2);
  tone(SPEAKER, NOTE_C5, NOTE_DELAY_3);
  delay(NOTE_DELAY_2);
  tone(SPEAKER, NOTE_C5, NOTE_DELAY_2);
  delay(NOTE_DELAY_2);
  tone(SPEAKER, NOTE_C6, NOTE_DELAY_4);
  delay(NOTE_DELAY_1);
  tone(SPEAKER, NOTE_A5, NOTE_DELAY_4);
  delay(NOTE_DELAY_1);
  tone(SPEAKER, NOTE_F5, NOTE_DELAY_4);
  delay(NOTE_DELAY_1);
  tone(SPEAKER, NOTE_E5, NOTE_DELAY_4);
  delay(NOTE_DELAY_1);
  tone(SPEAKER, NOTE_D5, NOTE_DELAY_5);
  
  //AS AS A F G F
  delay(NOTE_DELAY_5*2);
  tone(SPEAKER, NOTE_AS5, NOTE_DELAY_2);
  delay(NOTE_DELAY_2);
  tone(SPEAKER, NOTE_AS5, NOTE_DELAY_2);
  delay(NOTE_DELAY_2);
  tone(SPEAKER, NOTE_A5, NOTE_DELAY_4);
  delay(NOTE_DELAY_1);
  tone(SPEAKER, NOTE_F5, NOTE_DELAY_4);
  delay(NOTE_DELAY_1);
  tone(SPEAKER, NOTE_G5, NOTE_DELAY_4);
  delay(NOTE_DELAY_1);
  tone(SPEAKER, NOTE_F5, NOTE_DELAY_5);
  delay(NOTE_DELAY_5*2);
  
  caseVar = 0;
  return;
}

void setup() {
  // Debug code
  Serial.begin(9600);

  pinMode(SPEAKER, OUTPUT);
  pinMode(C, INPUT_PULLUP);
  pinMode(CS, INPUT_PULLUP);
  pinMode(D, INPUT_PULLUP);
  pinMode(DS, INPUT_PULLUP);
  pinMode(E, INPUT_PULLUP);
  pinMode(F, INPUT_PULLUP);
  pinMode(FS, INPUT_PULLUP);
  pinMode(G, INPUT_PULLUP);
  pinMode(GS, INPUT_PULLUP);
  pinMode(A, INPUT_PULLUP);
  pinMode(AS, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(C2, INPUT_PULLUP);

  // Counter for the case value (for FSM)
  caseVar = 0;

  // Startup
  Serial.println("Starting buzzer");
  tone(SPEAKER, 800, 500);
  delay(1000);
  tone(SPEAKER, 800, 500);
  delay(1000);
}

void loop() {
  switch (caseVar) {
    case 0:
    Serial.println("Now in case 0");
      if(!digitalRead(C)){
        caseVar += 1;
        playNote(C);
      }
      else{
        setupWrongNote();
      }
      break;
    case 1:
      Serial.println("Now in case 1");
      if(!digitalRead(C)){
        caseVar += 1;
        playNote(C);
      }
      else{
        setupWrongNote();
      }
      break;
    case 2:
      Serial.println("Now in case 2");
      if(!digitalRead(D)){
        caseVar += 1;
        playNote(D);
      }
      else{
        setupWrongNote();
      }
      break;
    case 3:
      Serial.println("Now in case 3");
      if(!digitalRead(C)){
        caseVar += 1;
        playNote(C);
      }
      else{
        setupWrongNote();
      }
      break;
    case 4:
        Serial.println("Now in case 4");
        if(!digitalRead(F)){
        caseVar += 1;
        playNote(F);
      }
      else{
        setupWrongNote();
      }
      break;
    case 5:
      Serial.println("Now in case 5");
      if(!digitalRead(E)){
        playNote(E);
        Serial.println("Initate happy birthday!");
        happyBirthday();
        caseVar = 0;
      }
      else{
        setupWrongNote();
      }
      break;
    default:
      Serial.println("This message should not appear. If it does, it's a bug, so please get in contact.");
      tone(SPEAKER, notes[0], 4000);
      delay(500);
      break;
  }
}
