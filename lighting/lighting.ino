/*
  Lighting
*/

#include "lighting_internal.h"

DS3232RTC myRTC(false);
struct rgb gCurrentRgb = {0, 0, 0};

SCENE_TABLE_ELEMENT defaultSceneElement = {"00:00:00", "00:00:00", sceneIdle};
SCENE_TABLE_ELEMENT sceneTable[] = {
  {"00:00:00", "01:00:00", sceneNight},
  {"01:00:00", "02:00:00", sceneCandle},
  {"06:00:00", "07:00:00", sceneMorning},
  {"07:00:00", "09:00:00", sceneRandomFade},
  {"18:00:00", "22:00:00", sceneRandomFade},
  {"22:00:00", "23:59:59", sceneCandle},
};

// the setup function runs once when you press reset or power the board
void setup() {
  #if UPDATE_RTC
  tmElements_t tm;
  #endif
  
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
                   tm
                   );
  if (sceneElement == NULL) {
    sceneElement = &defaultSceneElement;
  }

  sceneElement->sceneFunc (tm);
}
