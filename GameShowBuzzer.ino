#include "pitches.h"

bool Triggered;
int SelectedPlayer;

int speakerPin = 17;
int hubControlPin = 2;
int hubControlLightPin = 18;

void setup() {
  // put your setup code here, to run once:
  for(int i = 2; i < 16; i++){
    pinMode(i, INPUT);
  }
  
  pinMode(speakerPin, OUTPUT);
  pinMode(hubControlLightPin, OUTPUT);
  Serial.begin(9600);
  Triggered = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!Triggered){
    for(int i = 3; i < 16; i++){
      if(digitalRead(i) == HIGH){
        SelectedPlayer = i;
        pinMode(i, OUTPUT);
        delay(100);
        digitalWrite(i, HIGH);
        digitalWrite(hubControlLightPin, HIGH);
        Triggered = true;
        playButtonNoise();
        break;
      }
    }
  }
  else {
    if(digitalRead(hubControlPin) == HIGH){
      digitalWrite(SelectedPlayer, LOW);
      digitalWrite(hubControlLightPin, LOW);
      delay(100);
      pinMode(SelectedPlayer, INPUT);
      delay(100);
      
      Triggered = false;
    }
  }
}

void playButtonNoise(){
  beep(speakerPin, NOTE_C5, 75);
  delay(10);
  beep(speakerPin, NOTE_D5, 75);
  delay(10);
  beep(speakerPin, NOTE_E5, 75);
  delay(10);
  beep(speakerPin, NOTE_G5, 75);
  delay(10);
  beep(speakerPin, NOTE_E5, 75);
  delay(10);
  beep(speakerPin, NOTE_G5, 75);
  delay(10);
  beep(speakerPin, NOTE_C6, 75);
}

void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds){
  int x;
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for(x = 0; x < loopTime; x++){
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(delayAmount);
  }
}

