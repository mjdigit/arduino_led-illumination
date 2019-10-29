
long randRed;
long randGreen;
long randBlue;

#define TIME_VALUE(tm)   (3600*(tm).Hour + 60*(tm).Minute + (tm).Second)
#define DEFAULT_INTERVAL (10000)

struct rgb mColorNight   = {15, 5, 30};
struct rgb mColorMorning = {128, 96, 64};

/**
  Hour, Minute, Second will be overwritten.
**/
bool convertTimeToTm (char *TimeStr, tmElements_t *tm) {
  int Hour, Min, Sec;

  if (sscanf (TimeStr, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;

  tm->Hour = Hour;
  tm->Minute = Min;
  tm->Second = Sec;

  return true;
}

SCENE_TABLE_ELEMENT* getSceneElement (
  SCENE_TABLE_ELEMENT *table,
  int elements,
  tmElements_t tm
  )
{
  int i;
  tmElements_t startTm;
  tmElements_t endTm;

  for (i = 0; i < elements; i++) {
    convertTimeToTm (table[i].startTimeStr, &startTm);
    convertTimeToTm (table[i].endTimeStr, &endTm);

    if (TIME_VALUE (startTm) <= TIME_VALUE (tm) &&
        TIME_VALUE (tm) <= TIME_VALUE (endTm)) {
      return &table[i];
    }
  }

  return NULL;
}


void sceneIdle (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm) {
  controlLeds (32, 0, 0, 100);
  delay (50);
  controlLeds (0, 0, 0, 100);
  delayWDT (WDT_DELAY_8S);
}

void sceneFadeToNight (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm) {
  tmElements_t startTm;
  tmElements_t endTm;
  int intervalMs;

  convertTimeToTm (sceneElement->startTimeStr, &startTm);
  convertTimeToTm (sceneElement->endTimeStr, &endTm);
  intervalMs = 10 * (TIME_VALUE (endTm) - TIME_VALUE (startTm));
  
  fadeLeds (gCurrentRgb, mColorNight, intervalMs, 100);
}

void sceneNight (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm) {
  controlLeds (mColorNight.red, mColorNight.green, mColorNight.blue, 100);
  delayIdle (DEFAULT_INTERVAL);
}

void sceneMorning (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm) {
  controlLeds (mColorMorning.red, mColorMorning.green, mColorMorning.blue, 100);
  delayIdle (DEFAULT_INTERVAL);
}

void sceneRandomFade (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm) {
  static struct rgb prevRgb = {0, 0, 0};
  struct rgb rgbValue;

  #define MAX_PWM 100
  rgbValue.red   = random(MAX_PWM);
  rgbValue.green = random(MAX_PWM);
  rgbValue.blue  = random(MAX_PWM);
  deugPrintRgb (rgbValue, true);
  fadeLeds (prevRgb, rgbValue, 30, 100);
  prevRgb.red   = rgbValue.red;
  prevRgb.green = rgbValue.green;
  prevRgb.blue  = rgbValue.blue;
  delayIdle (DEFAULT_INTERVAL);
}

void sceneCandle (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm) {
  struct rgb baseRgb = {100, 40, 5};
  int rate = 50 + random(20);

  controlLeds (baseRgb.red, baseRgb.green, baseRgb.blue, rate);

  delayIdle (50);
}
