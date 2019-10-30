/*
  Lighting
*/

#include "lighting_internal.h"

DS3232RTC myRTC(false);
struct rgb gCurrentRgb = {0, 0, 0};
long mTimeAdjust = 0;

#define  START_TIME_STR  "12:00:00"
SCENE_TABLE_ELEMENT defaultSceneElement = {"00:00:00", "00:00:00", sceneIdle};
SCENE_TABLE_ELEMENT sceneTable[] = {
  {"12:01:00", "12:02:00", sceneRandomFade},
  {"12:02:00", "12:02:02", sceneFadeToNight},
  {"12:02:00", "12:03:00", sceneNight},
  {"12:03:00", "12:04:00", sceneFadeToMorning},
  {"12:04:00", "12:05:00", sceneMorning},
  {"12:05:00", "12:06:00", sceneFadeToNight},
  {"12:06:00", "12:07:00", sceneNight},
  {"12:07:00", "12:08:00", sceneCandle},
  {"12:08:00", "12:08:02", sceneFadeToNight},
  {"12:08:00", "12:09:00", sceneNight},
};

// the setup function runs once when you press reset or power the board
void setup() {
  tmElements_t tm;
  tmElements_t startTm;
  
  myRTC.begin();
  randomSeed(analogRead(0));
  #if DEBUG_ENABLE
  Serial.begin(115200);
  DEBUG (("RTC temp: "));
  DEBUG (((float) RTC.temperature() / 4.0));
  DEBUGLN (("[C]"));
  #endif

  #if UPDATE_RTC
  DEBUG (("Update RTC: "));
  DEBUG ((__DATE__));
  DEBUG ((" "));
  DEBUGLN ((__TIME__));
  if (setupTm (__DATE__, __TIME__, &tm)) {
    RTC.write (tm);
    DEBUG (("RTC updated: "));
    debugPrintTime (tm, true);
  }
  #endif

  RTC.read(tm);
  convertTimeToTm (START_TIME_STR, &startTm);
  mTimeAdjust = TIME_VALUE(startTm) - TIME_VALUE(tm);
}

// the loop function runs over and over again forever
void loop() {
  tmElements_t tm;
  static int Minute = 0;
  SCENE_TABLE_ELEMENT *sceneElement;

  RTC.read(tm);
  if (tm.Minute != Minute) {
    debugPrintTime (tm, true);
    Minute = tm.Minute;
  }

  sceneElement = getSceneElement (
                   sceneTable,
                   sizeof (sceneTable) / sizeof (sceneTable[0]),
                   tm, mTimeAdjust
                   );
  if (sceneElement == NULL) {
    sceneElement = &defaultSceneElement;
  }

  sceneElement->sceneFunc (sceneElement, tm);
}
