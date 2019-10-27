
long randRed;
long randGreen;
long randBlue;

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
