/*
  Lighting
*/

#include "lighting_internal.h"

DS3232RTC myRTC(false);
struct rgb gCurrentRgb = {0, 0, 0};
long gTimeAdjust = 0;
int mMode = 0;

#define  START_TIME_STR  "12:00:00"
SCENE_TABLE_ELEMENT defaultSceneElement = {"00:00:00", "00:00:00", sceneIdle};

// the setup function runs once when you press reset or power the board
void setup() {
  tmElements_t tm;
  tmElements_t startTm;

  initializeDipPins ();

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
  gTimeAdjust = TIME_VALUE(startTm) - TIME_VALUE(tm);
  DEBUGLN ((gTimeAdjust));

  if (isSetMode ()) {
    mMode = getModePin ();
    DEBUG (("Setup Mode to: "));
    DEBUGLN ((mMode));
    setMode (mMode);
  } else {
    mMode = getCurrentMode ();
  }
  DEBUG (("Mode: "));
  DEBUGLN ((mMode));
}

// the loop function runs over and over again forever
void loop() {
  tmElements_t tm;
  static int Minute = 0;
  SCENE_TABLE_ELEMENT *sceneTable;
  int elements;
  SCENE_TABLE_ELEMENT *sceneElement;

  RTC.read(tm);
  if (tm.Minute != Minute) {
    debugPrintTime (tm, true);
    Minute = tm.Minute;
  }

  sceneElement = NULL;
  if (getSceneTableByMode (mMode, &sceneTable, &elements)) {
    sceneElement = getSceneElement (sceneTable, elements, tm);
  }
  if (sceneElement == NULL) {
    sceneElement = &defaultSceneElement;
  }

  sceneElement->sceneFunc (sceneElement, tm);
}
