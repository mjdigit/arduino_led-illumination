/*
  Lighting
*/

#include <DS3232RTC.h>  /// https://github.com/JChristensen/DS3232RTC

DS3232RTC myRTC(false);

long randRed;
long randGreen;
long randBlue;

#define UPDATE_RTC   0
#define DEBUG_ENABLE 1

#if DEBUG_ENABLE
  #define DEBUG(x)   Serial.print x
  #define DEBUGLN(x) Serial.println x
#else
  #define DEBUG(x)
  #define DEBUGLN(x)
#endif

const int analogRedPin   = 3;
const int analogGreenPin = 5;
const int analogBluePin  = 6;

struct rgb {
  int red;
  int green;
  int blue;
};

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

/// ################################################################################

static void controlLeds (int redValue, int greenValue, int blueValue, int ratio) {
  redValue = (redValue * ratio) / 100;
  greenValue = (greenValue * ratio) / 100;
  blueValue = (blueValue * ratio) / 100;

  analogWrite (analogRedPin, redValue);
  analogWrite (analogGreenPin, greenValue);
  analogWrite (analogBluePin, blueValue);
}

/**
  Note:
    steps should be < 100.
**/
static void fadeLeds (struct rgb rgbFrom, struct rgb rgbTo, int intervalMs, int steps) {
  int  s;
  int  redValue;
  int  greenValue;
  int  blueValue;

  if (intervalMs == 0 || steps > 100) {
    return;
  }

  for (s = 0; s < steps; s++) {
    redValue   = (rgbFrom.red   * (steps - s) + rgbTo.red   * s) / steps;
    greenValue = (rgbFrom.green * (steps - s) + rgbTo.green * s) / steps;
    blueValue  = (rgbFrom.blue  * (steps - s) + rgbTo.blue  * s) / steps;
    controlLeds (redValue, greenValue, blueValue, 100);

    delay (intervalMs);
  }
  
  controlLeds (rgbTo.red, rgbTo.green, rgbTo.blue, 100);
}

/// ################################################################################

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
}

// the loop function runs over and over again forever
void loop() {
  tmElements_t tm;
  static struct rgb prevRgb = {0, 0, 0};
  struct rgb rgbValue;

  RTC.read(tm);
  DEBUG ((tm.Hour, DEC));
  DEBUG ((':'));
  DEBUG ((tm.Minute,DEC));
  DEBUG ((':'));
  DEBUG ((tm.Second,DEC));
  DEBUG (("    "));

  #define MAX_PWM 100
  rgbValue.red   = random(MAX_PWM);
  rgbValue.green = random(MAX_PWM);
  rgbValue.blue  = random(MAX_PWM);
  DEBUG ((rgbValue.red, DEC));
  DEBUG ((','));
  DEBUG ((rgbValue.green, DEC));
  DEBUG ((','));
  DEBUGLN ((rgbValue.blue, DEC));
  fadeLeds (prevRgb, rgbValue, 30, 100);
  prevRgb.red   = rgbValue.red;
  prevRgb.green = rgbValue.green;
  prevRgb.blue  = rgbValue.blue;
  delayIdle (7000);
}
