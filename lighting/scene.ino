
long randRed;
long randGreen;
long randBlue;

#define DEFAULT_INTERVAL (10000 / gTimeRate)

struct rgb mColorNight   = {15, 5, 30};
struct rgb mColorMorning = {128, 96, 64};

SCENE_TABLE_ELEMENT* getSceneElement (
  SCENE_TABLE_ELEMENT *table,
  int elements,
  tmElements_t tm
  )
{
  long currentTimeValue;
  int i;
  tmElements_t startTm;
  tmElements_t endTm;

  currentTimeValue = ADJUSTED_TIME_VALUE (TIME_VALUE (tm), gTimeAdjust);
  //DEBUG ((currentTimeValue));
  //DEBUG ((", "));
  currentTimeValue = MULTIPLIED_TIME_VALUE (currentTimeValue, gBaseTimeValue, gTimeRate);
  //DEBUGLN ((currentTimeValue));
  for (i = 0; i < elements; i++) {
    convertTimeToTm (table[i].startTimeStr, &startTm);
    convertTimeToTm (table[i].endTimeStr, &endTm);

    if (TIME_VALUE (startTm) <= currentTimeValue &&
        currentTimeValue <= TIME_VALUE (endTm)) {
      return &table[i];
    }
  }

  return NULL;
}


void sceneIdle (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm) {
  controlLeds (32, 0, 0, 100);
  delay (50);
  controlLeds (0, 0, 0, 100);

  switch (gTimeRate) {
    case  1: delayWDT (WDT_DELAY_8S); break;
    case  4: delayWDT (WDT_DELAY_2S); break;
    case 16: delayWDT (WDT_DELAY_500MS); break;
    default: delayWDT (WDT_DELAY_8S); break;
  }
}

static void fadeTo (char *startTimeStr, char *endTimeStr, struct rgb rgbTo) {
  tmElements_t startTm;
  tmElements_t endTm;
  int intervalMs;

  convertTimeToTm (startTimeStr, &startTm);
  convertTimeToTm (endTimeStr, &endTm);
  intervalMs = 10 * (TIME_VALUE (endTm) - TIME_VALUE (startTm)) / gTimeRate;
  
  fadeLeds (gCurrentRgb, rgbTo, intervalMs, 100);
}

void sceneFadeToMorning (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm) {
  fadeTo (sceneElement->startTimeStr, sceneElement->endTimeStr, mColorMorning);
}

void sceneFadeToNight (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm) {
  fadeTo (sceneElement->startTimeStr, sceneElement->endTimeStr, mColorNight);
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
  tmElements_t endTm;
  long currentTimeValue, endTimeValue;
  struct rgb rgbValue;

  int intervalMs;

  convertTimeToTm (sceneElement->endTimeStr, &endTm);
  currentTimeValue = ADJUSTED_TIME_VALUE (TIME_VALUE (tm), gTimeAdjust);
  endTimeValue = TIME_VALUE (endTm);
  if (endTimeValue > currentTimeValue &&
      (endTimeValue - currentTimeValue) * 1000 < DEFAULT_INTERVAL + 3000) {
    delayIdle ((endTimeValue - currentTimeValue) * 1000);
    return;
  }

  #define MAX_PWM 255
  rgbValue.red   = random(MAX_PWM);
  rgbValue.green = random(MAX_PWM);
  rgbValue.blue  = random(MAX_PWM);
  debugPrintRgb (rgbValue, true);
  fadeLeds (gCurrentRgb, rgbValue, 32 / gTimeRate, 100);

  delayIdle (DEFAULT_INTERVAL);
}

void sceneCandle (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm) {
  struct rgb baseRgb = {120, 40, 5};
  int rate = 50 + random(20);

  controlLeds (baseRgb.red, baseRgb.green, baseRgb.blue, rate);

  delayIdle (50);
}
