
#include <SPI.h>
#include <SdFat.h>
#include <SFEMP3Shield.h>

const int volume= 60; // MP3 Player volume 0 = máximo, 255= mínimo(off)
int sensorPin = A0; 
int ledPin13 = 13; 

int sensorValue = 0; 

SdFat sd;
SFEMP3Shield MP3player;

void setup() {

sd.begin(SD_SEL, SPI_HALF_SPEED); // ativa o shild
MP3player.begin(); // entra na função MP3

pinMode(sensorPin, INPUT);
pinMode(ledPin13, OUTPUT);

MP3player.setVolume(volume, volume); 
Serial.begin(9600);

}

void loop() {

sensorValue = analogRead(sensorPin);
Serial.println(sensorValue);

if (sensorValue <= 110) {
  MP3player.stopTrack();
  digitalWrite(ledPin13, HIGH);
  }
if  (sensorValue < 400 && sensorValue > 110) {
  MP3player.playTrack(1);
  digitalWrite(ledPin13, LOW);
  }
if (sensorValue < 500 && sensorValue > 400) {
  MP3player.stopTrack();
  digitalWrite(ledPin13, HIGH);
  }
if (sensorValue > 500) {

  MP3player.playTrack(2);
  digitalWrite(ledPin13, LOW);
  }

}
