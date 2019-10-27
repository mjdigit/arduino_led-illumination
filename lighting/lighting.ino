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

bool setupTm (const char *DateStr, const char *TimeStr, tmElements_t *tm) {
  #define NUM_MONTH 12
  int Year, Month, Day, Hour, Min, Sec;
  char MonthStr[12];
  const char *MonthTable[NUM_MONTH] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" 
  };

  if (sscanf (DateStr, "%s %d %d", MonthStr, &Day, &Year) != 3) return false;
  if (sscanf (TimeStr, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;

  for (Month = 0; Month < NUM_MONTH; Month++) {
    if (strcmp (MonthStr, MonthTable[Month]) == 0) break;
  }
  if (Month >= NUM_MONTH) return false;

  tm->Year = CalendarYrToTm(Year);
  tm->Month = Month + 1;
  tm->Day = Day;
  tm->Hour = Hour;
  tm->Minute = Min;
  tm->Second = Sec;

  return true;
}


// the setup function runs once when you press reset or power the board
void setup() {
  #if UPDATE_RTC
  tmElements_t tm;
  #endif
  #if DEBUG_ENABLE
  Serial.begin(115200);
  #endif
  myRTC.begin();
  randomSeed(analogRead(0));

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

  sceneFunc = sceneIdle;
}

// the loop function runs over and over again forever
void loop() {
  tmElements_t tm;
  static int Minute = 0;

  RTC.read(tm);
  if (tm.Minute != Minute) {
    debugPrintTime (tm, true);
    Minute = tm.Minute;
  }

  if (sceneFunc != NULL) sceneFunc (tm);

  if ((tm.Minute + 0) % 6 == 0) sceneFunc = sceneIdle;
  if ((tm.Minute + 2) % 6 == 0) sceneFunc = sceneRandomFade;
  if ((tm.Minute + 4) % 6 == 0) sceneFunc = sceneCandle; 
}
