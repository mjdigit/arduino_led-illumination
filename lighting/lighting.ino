/*
  Lighting
*/

#include "lighting_internal.h"

DS3232RTC myRTC(false);

SCENE_FUNC sceneFunc = NULL;

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

  sceneFunc = sceneIdle;
}

// the loop function runs over and over again forever
void loop() {
  tmElements_t tm;

  RTC.read(tm);
  debugPrintTime (tm, true);

  if (sceneFunc != NULL) sceneFunc (tm);

  if ((tm.Minute + 0) % 10 == 0) sceneFunc = sceneIdle;
  if ((tm.Minute + 5) % 10 == 0) sceneFunc = sceneRandomFade; 
}
