
long randRed;
long randGreen;
long randBlue;

#define DEFAULT_INTERVAL (10000 / gTimeRate)

struct rgb mColorNight[]   = {{15, 5, 30}};
struct rgb mColorMorning[] = {{255, 191, 120}};
struct rgb mColorSunset1_2_3[]  = {
  {160, 120, 60}, {140, 30, 15}, {120, 30, 10},
  {80, 10, 15}, {20, 0, 20}, {15, 5, 30}
  };
struct rgb mColorSunset4_5_6[]  = {
  {180, 140, 70}, {160, 40, 20}, {150, 40, 20},
  {100, 15, 30}, {20, 0, 20}, {15, 5, 30}
  };
struct rgb mColorSunset7_8[]  = {
  {220, 150, 80}, {180, 40, 20}, {180, 40, 20},
  {120, 20, 40}, {20, 0, 20}, {15, 5, 30}
  };
struct rgb mColorSunset9[]  = {
  {250, 120, 80}, {200, 40, 10}, {200, 40, 10},
  {120, 20, 40}, {20, 0, 20}, {15, 5, 30}
  };

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


void sceneIdle (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm, int mode) {
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

static void fadeTo (
  char *startTimeStr,
  char *endTimeStr,
  struct rgb *rgbTable,
  int tableElements
  )
{
  tmElements_t startTm;
  tmElements_t endTm;
  int intervalMs;
  int i;

  convertTimeToTm (startTimeStr, &startTm);
  convertTimeToTm (endTimeStr, &endTm);
  intervalMs = 10l * (TIME_VALUE (endTm) - TIME_VALUE (startTm)) / (gTimeRate * tableElements);

  for (i = 0; i < tableElements; i++) {
    //DEBUGLN ((i));
    fadeLeds (gCurrentRgb, rgbTable[i], intervalMs, 100);
  }

  // wait for calc error
  delayIdle (
    1000l * (TIME_VALUE (endTm) - TIME_VALUE (startTm)) / gTimeRate
    - (intervalMs * 100 * tableElements)
    );
}

void sceneFadeToMorning (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm, int mode) {
  fadeTo (
    sceneElement->startTimeStr, sceneElement->endTimeStr,
    mColorMorning, sizeof (mColorMorning) / sizeof (struct rgb)
    );
}

void sceneFadeToNight (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm, int mode) {
  fadeTo (
    sceneElement->startTimeStr, sceneElement->endTimeStr,
    mColorNight, sizeof (mColorNight) / sizeof (struct rgb)
    );
}

void sceneSunset (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm, int mode) {
  switch (mode) {
    case 1:
    case 2:
    case 3:
      fadeTo (
        sceneElement->startTimeStr, sceneElement->endTimeStr,
        mColorSunset1_2_3, sizeof (mColorSunset1_2_3) / sizeof (struct rgb)
        );
      break;
    case 4:
    case 5:
    case 6:
      fadeTo (
        sceneElement->startTimeStr, sceneElement->endTimeStr,
        mColorSunset4_5_6, sizeof (mColorSunset4_5_6) / sizeof (struct rgb)
        );
      break;
    case 7:
    case 8:
      fadeTo (
        sceneElement->startTimeStr, sceneElement->endTimeStr,
        mColorSunset7_8, sizeof (mColorSunset7_8) / sizeof (struct rgb)
        );
      break;
    default:
      fadeTo (
        sceneElement->startTimeStr, sceneElement->endTimeStr,
        mColorSunset9, sizeof (mColorSunset9) / sizeof (struct rgb)
        );
      break;
  }
}

void sceneNight (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm, int mode) {
  controlLeds (mColorNight[0].red, mColorNight[0].green, mColorNight[0].blue, 100);
  delayIdle (DEFAULT_INTERVAL);
}

void sceneMorning (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm, int mode) {
  controlLeds (mColorMorning[0].red, mColorMorning[0].green, mColorMorning[0].blue, 100);
  delayIdle (DEFAULT_INTERVAL);
}

struct randRange {
  struct rgb from;
  struct rgb to;
};

struct randRange randTable[] = {
  {{0, 0, 0}, {255, 255, 255}},
  {{0, 192, 192}, {127, 255, 255}},
  {{192, 0, 0}, {255, 127, 127}},
  {{0, 0, 192}, {127, 127, 255}},
  {{192, 0, 192}, {255, 127, 255}},
  {{192, 64, 0}, {255, 127, 63}},
  {{0, 192, 0}, {127, 255, 127}},
  {{192, 192, 0}, {255, 255, 127}},
  {{0, 0, 0}, {255, 255, 255}},
};

void sceneRandomFade (SCENE_TABLE_ELEMENT *sceneElement, tmElements_t tm, int mode) {
  tmElements_t endTm;
  long currentTimeValue, endTimeValue;
  struct rgb rgbValue;
  struct randRange *range;

  int intervalMs;

  convertTimeToTm (sceneElement->endTimeStr, &endTm);
  currentTimeValue = ADJUSTED_TIME_VALUE (TIME_VALUE (tm), gTimeAdjust);
  endTimeValue = TIME_VALUE (endTm);
  if (endTimeValue > currentTimeValue &&
      (endTimeValue - currentTimeValue) * 1000 < DEFAULT_INTERVAL + 3000) {
    delayIdle ((endTimeValue - currentTimeValue) * 1000);
    return;
  }

  range = (mode < 9)? &randTable[mode]: &randTable[0];
  rgbValue.red   = range->from.red + random(range->to.red - range->from.red);
  rgbValue.green = range->from.green + random(range->to.green - range->from.green);
  rgbValue.blue  = range->from.blue + random(range->to.blue - range->from.blue);
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
