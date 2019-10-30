
#ifndef _LIGHTING_INTERNAL_H_
#define _LIGHTING_INTERNAL_H_

#include <DS3232RTC.h>  /// https://github.com/JChristensen/DS3232RTC

/// ########################################
/// flags
/// ########################################
/// If enabled setup RTC time on startup.
#define UPDATE_RTC   0

/// If enabled serial interface and DEBUG() will be enabled.
#define DEBUG_ENABLE 1

#if DEBUG_ENABLE
  #define DEBUG(x)   Serial.print x
  #define DEBUGLN(x) Serial.println x
#else
  #define DEBUG(x)
  #define DEBUGLN(x)
#endif

/// ########################################
/// pin assignment
/// ########################################
const int analogRedPin   = 3;
const int analogGreenPin = 5;
const int analogBluePin  = 6;

/// ########################################
/// structures/enums
/// ########################################

typedef struct _SCENE_TABLE_ELEMENT SCENE_TABLE_ELEMENT;
typedef void (*SCENE_FUNC) (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm);

struct _SCENE_TABLE_ELEMENT {
  char        *startTimeStr; // "hh:mm:ss"
  char        *endTimeStr;   // "hh:mm:ss"
  SCENE_FUNC  sceneFunc;
};

struct rgb {
  int red;
  int green;
  int blue;
};

enum wdt_delay {
  WDT_DELAY_16MS,
  WDT_DELAY_32MS,
  WDT_DELAY_64MS,
  WDT_DELAY_128MS,
  WDT_DELAY_250MS,
  WDT_DELAY_500MS,
  WDT_DELAY_1S,
  WDT_DELAY_2S,
  WDT_DELAY_4S,
  WDT_DELAY_8S,
  WDT_DELAY_UNKNOWN
};

/// ########################################
/// function declaration
/// ########################################
extern struct rgb gCurrentRgb;
extern long gTimeAdjust;

#define TIME_VALUE(tm)   ((long) 3600*(tm).Hour + 60*(tm).Minute + (tm).Second)
#define ADJUSTED_TIME_VALUE(tv,adj) \
         (((tv) + (adj) < 0l)? ((tv) + (adj) + 24l * 3600): \
          (((tv) + (adj) >= 24l * 3600)? ((tv) + (adj) - 24l * 3600): ((tv) + (adj))))

void sceneIdle (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm);
void sceneFadeToMorning (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm);
void sceneFadeToNight (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm);
void sceneMorning (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm);
void sceneNight (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm);
void sceneRandomFade (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm);
void sceneCandle (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm);

#endif /*_LIGHTING_INTERNAL_H_*/
