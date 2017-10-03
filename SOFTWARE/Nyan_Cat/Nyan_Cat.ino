#include <avr/pgmspace.h>
#include <avr/io.h>
#include "definedtones.h"

//DefinePinNumebers:
int buzzer = 0;
int led = 1;
int chrge = 2;
int dischrge = 3;

const int song[] PROGMEM = {
  G3,QTH,
  A3,QTH,
  DS3, ETH,
  E3, QTH,
  D3, ETH,
  DS3, ETH,
  D3, ETH,
  C3, QTH,
  C3, QTH,
  D3, QTH,
  DS3, QTH,
  DS3, ETH,
  D3, ETH,
  C3, ETH,
  D3, ETH,
  E3, ETH,
  G3, ETH,
  A3, ETH,
  E3, ETH,
  G3, ETH,
  D3, ETH,
  E3, ETH,
  C3, ETH,
  D3, ETH,
  C3, ETH,
  E3, QTH,
  G3, QTH,
  A3, ETH,
  E3, ETH,
  G3, ETH,
  C3, ETH,
  D3, ETH,
  C3, ETH,
  DS3, ETH,
  E3, ETH,
  DS3, ETH,
  D3, ETH,
  C3, ETH,
  D3, ETH,
  DS3, QTH,
  DS3, ETH,
  D3, ETH,
  C3, ETH,
  D3, ETH,
  E3, ETH,
  G3, ETH,
  D3, ETH,
  C3, ETH,
  D3, QTH,
  C3, QTH,
  C3, QTH,
  C3, QTH,
  G2, ETH,
  A2, ETH,
  C3, QTH,
  G2, ETH,
  A2, ETH,
  C3, ETH,
  E3, ETH,
  F3, ETH,
  E3, ETH,
  F3, ETH,
  E3, ETH,
  F3, ETH,
  G3, ETH,
  C3, QTH,
  C3, QTH,
  G2, ETH,
  A2, ETH,
  C3, ETH,
  E3, ETH,
  F3, ETH,
  E3, ETH,
  F3, ETH,
  G3, ETH,
  C3, QTH,
  B2, QTH,
  C3, QTH,
  G2, ETH,
  A2, ETH,
  C3, QTH,
  G2, ETH,
  A2, ETH,
  C3, ETH,
  E3, ETH,
  F3, ETH,
  E3, ETH,
  F3, ETH,
  E3, ETH,
  F3, ETH,
  G3, ETH,
  C3, QTH,
  C3, QTH,
  G2, ETH,
  A2, ETH,
  C3, ETH,
  E3, ETH,
  F3, ETH,
  E3, ETH,
  D3, QTH,
  C3, HTH
};

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
}

void loop() {
  int cnote = 0;
  int cdur = 0;
  int ddelay = 0;
  bool ledon = 0;

  long i = 0;
  int temp = 0;

  for (int cnt = 0; cnt < 202; cnt++) {
    if (!ledon)  {
      digitalWrite(led, LOW);
      ledon = 1;
    }
    else {
      digitalWrite(led, HIGH);
      ledon = 0;
    }
    cnote = pgm_read_word_near(song + cnt++); //notetobeplayed
    cdur = pgm_read_word_near(song + cnt);   //durationofthecurrentnote
    if (cnote > 0) {
      tone(buzzer, cnote);
      delay(cdur);
      noTone(buzzer);
      delay(3);
    }
    else {
      noTone(buzzer);
      delay(cdur);
    }
  }
}
