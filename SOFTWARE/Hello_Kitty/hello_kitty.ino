#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <CapacitiveSensor.h>
#include "definedtones.h"

//DefinePinNumebers:
int buzzer = 0;
int led = 1;
int chrge = 2;
int dischrge = 3;

CapacitiveSensor cs_2_3 = CapacitiveSensor(2, 3);


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

void setup_watchdog(int timerPrescaler) {

  if (timerPrescaler > 9 ) timerPrescaler = 9; //Correct incoming amount if need be

  byte bb = timerPrescaler & 7;
  if (timerPrescaler > 7) bb |= (1 << 5); //Set the special 5th bit if necessary

  //This order of commands is important and cannot be combined
  MCUSR &= ~(1 << WDRF); //Clear the watch dog reset
  WDTCR |= (1 << WDCE) | (1 << WDE); //Set WD_change enable, set WD enable
  WDTCR = bb; //Set new watchdog timeout value
  WDTCR |= _BV(WDIE); //Set the interrupt enable, this will keep unit from resetting after each int
}

ISR(WDT_vect) {

}

void enterSleep(void) {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   /* EDIT: could also use SLEEP_MODE_PWR_DOWN for lowest power consumption. */
  sleep_enable();

  /* Now enter sleep mode. */
  sleep_mode();

  /* The program will continue from here after the WDT timeout*/
  sleep_disable(); /* First thing to do is disable sleep. */

  /* Re-enable the peripherals. */
  // power_all_enable();
}

void setup() {

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  cs_2_3.set_CS_AutocaL_Millis(0xFFFFFFFF);

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  ADCSRA &= ~(1 << ADEN); //Disable ADC, saves ~230uA
  setup_watchdog(7); //Wake up after 2s.
}

void loop() {
  int cnote = 0;
  int cdur = 0;
  int ddelay = 0;
  bool ledon = 0;

  long i = 0;
  int temp = 0;

  long capacitance = 0;

  capacitance = cs_2_3.capacitiveSensor(30);

  if (capacitance > 8) {
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
  wdt_reset();
  enterSleep();
}
