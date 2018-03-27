#include <MIDI.h>

int photocell = A9;
int button1 = 1;
int button2 = 2;
int led = 24;
boolean buttonState = LOW;
boolean lastButtonState = LOW;
int sensorVal;
int brightValue;
int darkValue;

int mid = 500;

int photoState;
int lastPhotoState;

void setup()
{
Serial.begin(9600);
pinMode(led, OUTPUT);
pinMode(button1, INPUT);
pinMode(button2, INPUT);
}

void loop()
{
//sensorVal = analogRead(photocell);
//Serial.println(sensorVal);
calibrateBright();
calibrateDark();
checkCell();
//delay(50);
while(usbMIDI.read());
}

void checkCell(){
  lastPhotoState = photoState;
  photoState = analogRead(photocell);

  if (photoState < mid && lastPhotoState > mid){
    digitalWrite(led, HIGH);
    Serial.println("led on");
   usbMIDI.sendNoteOn(60, 127, 1);
  }
  if (photoState > mid && lastPhotoState < mid){
    digitalWrite(led, LOW);
    Serial.println("led off");
  usbMIDI.sendNoteOff(60, 0, 1);
  }
}

void calibrateBright(){ 
  if (digitalRead(button1) == HIGH){
    brightValue = analogRead(photocell);
  }
  mid = ((brightValue + darkValue)/2);
}

void calibrateDark(){
  if (digitalRead(button2) == HIGH){
    darkValue = analogRead(photocell);
  }
  mid = ((brightValue + darkValue)/2);
}

