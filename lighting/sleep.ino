#include <avr/sleep.h>
#include <avr/wdt.h>

#include "lighting_internal.h"

static void delayWdtSetup (int dly) {
  byte data8;

  data8 = dly & 0x7;
  if (dly > 7) {
    data8 |= (1 << 5);
  }
  data8 |= (1 << WDCE);

  MCUSR &= ~(1 << WDRF); // clear watchdog reset flag
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  WDTCSR = data8;
  WDTCSR |= _BV(WDIE);
}

/**
  "ms" should be smaller than 50days.
**/
void delayIdle (unsigned long ms) {
  unsigned long start_millis;

  if (ms <= 16) {
    delay (ms);
    return;
  }

  start_millis = millis ();
  set_sleep_mode (SLEEP_MODE_IDLE);
  while (millis () - start_millis < ms) {
    sleep_mode ();
  }
}

/// http://radiopench.blog96.fc2.com/blog-entry-486.html
void delayWDT (int dly) {
  if (dly >= WDT_DELAY_UNKNOWN) return;
  
  delayWdtSetup (dly);
  ADCSRA &= ~ (1 << ADEN); // disable ADC
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  sleep_enable ();

  sleep_mode ();

  sleep_disable ();
  ADCSRA |= (1 << ADEN); // enable ADC
}

ISR(WDT_vect) {
  //  wdt_cycle++;
}
