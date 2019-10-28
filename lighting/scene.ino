
long randRed;
long randGreen;
long randBlue;

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
  int startTimeValue, currentTimeValue, endTimeValue;

  for (i = 0; i < elements; i++) {
    convertTimeToTm (table[i].startTimeStr, &startTm);
    convertTimeToTm (table[i].endTimeStr, &endTm);

    startTimeValue   = 3600 * startTm.Hour + 60 * startTm.Minute + startTm.Second;
    currentTimeValue = 3600 * tm.Hour      + 60 * tm.Minute      + tm.Second;
    endTimeValue     = 3600 * endTm.Hour   + 60 * endTm.Minute   + endTm.Second;

    if (startTimeValue <= currentTimeValue && currentTimeValue <= endTimeValue) {
      return &table[i];
    }
  }

  return NULL;
}

void sceneIdle (tmElements_t tm) {
  controlLeds (32, 0, 0, 100);
  delay (50);
  controlLeds (0, 0, 0, 100);
  delayWDT (WDT_DELAY_8S);
}

void sceneRandomFade (tmElements_t tm) {
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
  delayIdle (7000);
}

void sceneCandle (tmElements_t tm) {
  struct rgb baseRgb = {100, 40, 5};
  int rate = 50 + random(20);

  controlLeds (baseRgb.red, baseRgb.green, baseRgb.blue, rate);

  delayIdle (50);
}
