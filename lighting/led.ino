
#include "lighting_internal.h"

bool controlLeds (int redValue, int greenValue, int blueValue, int ratio) {
  redValue = (redValue * ratio) / 100;
  greenValue = (greenValue * ratio) / 100;
  blueValue = (blueValue * ratio) / 100;

  if (redValue > 255 || greenValue > 255 || blueValue > 255) return false;

  analogWrite (analogRedPin, redValue);
  analogWrite (analogGreenPin, greenValue);
  analogWrite (analogBluePin, blueValue);


  gCurrentRgb = {redValue, greenValue, blueValue};
  //debugPrintRgb (gCurrentRgb, true);

  return true;
}

/**
  Note:
    steps should be < 100.
**/
void fadeLeds (struct rgb rgbFrom, struct rgb rgbTo, int intervalMs, int steps) {
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

    delayIdle (intervalMs);
  }
  
  controlLeds (rgbTo.red, rgbTo.green, rgbTo.blue, 100);
}
