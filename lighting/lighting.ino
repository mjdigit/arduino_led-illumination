/*
  Lighting
*/

#include <DS3232RTC.h>  /// https://github.com/JChristensen/DS3232RTC

DS3232RTC myRTC(false);

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
  {255, 0, 0},
  {0, 255, 0},
  {0, 0, 255},
  {0, 255, 255},
  {255, 0, 255},
  {255, 255, 0},
  {255, 255, 255},
};

static void controlLeds (int redValue, int greenValue, int blueValue, int ratio) {
  redValue = (redValue * ratio) / 100;
  greenValue = (greenValue * ratio) / 100;
  blueValue = (blueValue * ratio) / 100;

  analogWrite (analogRedPin, redValue);
  analogWrite (analogGreenPin, greenValue);
  analogWrite (analogBluePin, blueValue);
}

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

  RTC.read(tm);
  DEBUG ((tm.Hour, DEC));
  DEBUG ((':'));
  DEBUG ((tm.Minute,DEC));
  DEBUG ((':'));
  DEBUGLN ((tm.Second,DEC));

  controlLeds(tm.Hour * 255 / 24, tm.Minute * 255 / 60, tm.Second * 255 / 60, 100);
  delay (500);
}
