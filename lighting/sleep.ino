#include <avr/sleep.h>

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
