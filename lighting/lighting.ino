/*
  Lighting
*/

#include <DS3232RTC.h>  /// https://github.com/JChristensen/DS3232RTC

#include "lighting_internal.h"

DS3232RTC myRTC(false);

long randRed;
long randGreen;
long randBlue;

static struct rgb rgbValue[] = {
  {0, 0, 0},
  {255, 0, 0},
  {0, 255, 0},
  {0, 0, 255},
  {0, 255, 255},
  {255, 0, 255},
  {255, 255, 0},
  {255, 255, 255},
};

// the setup function runs once when you press reset or power the board
void setup() {
  #if UPDATE_RTC
  char timeStr[9] = {0};
  char *hp, *mp, *sp;
  #endif

  #if DEBUG_ENABLE
  Serial.begin(115200);
  #endif
  myRTC.begin();
  randomSeed(analogRead(0));

  #if UPDATE_RTC
  strncpy (timeStr, __TIME__, 7);
  Serial.print ("Update RTC: ");
  Serial.println(timeStr);
  hp = strtok (timeStr, ":");
  mp = strtok (NULL, ":");
  sp = strtok (NULL, ":");
  if (hp != NULL && mp != NULL && sp != NULL) {
    tmElements_t tm;
    tm.Hour   = atoi (hp);
    tm.Minute = atoi (mp);
    tm.Second = atoi (sp);
    RTC.write (tm);
  }
  #endif

  // test
  {
    tmElements_t tm;
    RTC.read(tm);

    while (tm.Minute % 3 != 0) {
      controlLeds (32, 0, 0, 100);
      delay (50);
      controlLeds (0, 0, 0, 100);
      delayWDT (WDT_DELAY_8S);
      RTC.read(tm);
    }
  }
}

// the loop function runs over and over again forever
void loop() {
  tmElements_t tm;
  static struct rgb prevRgb = {0, 0, 0};
  struct rgb rgbValue;

  RTC.read(tm);
  DEBUG ((tm.Hour, DEC));
  DEBUG ((':'));
  DEBUG ((tm.Minute,DEC));
  DEBUG ((':'));
  DEBUG ((tm.Second,DEC));
  DEBUG (("    "));

  #define MAX_PWM 100
  rgbValue.red   = random(MAX_PWM);
  rgbValue.green = random(MAX_PWM);
  rgbValue.blue  = random(MAX_PWM);
  DEBUG ((rgbValue.red, DEC));
  DEBUG ((','));
  DEBUG ((rgbValue.green, DEC));
  DEBUG ((','));
  DEBUGLN ((rgbValue.blue, DEC));
  fadeLeds (prevRgb, rgbValue, 30, 100);
  prevRgb.red   = rgbValue.red;
  prevRgb.green = rgbValue.green;
  prevRgb.blue  = rgbValue.blue;
  delayIdle (7000);
}
