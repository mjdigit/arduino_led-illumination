#include <EEPROM.h>
#include "lighting_internal.h"

#define EEPROM_MODE_ADDRESS 0

void initializeDipPins () {
  pinMode (setModePin, INPUT);
  pinMode (modePin1, INPUT);
  pinMode (modePin2, INPUT);
  pinMode (modePin3, INPUT);
  pinMode (modePin4, INPUT);
}

boolean isSetMode () {
  return (digitalRead (setModePin) == HIGH)? true: false;
}

int getModePin () {
  int mode = 0;

  mode |= ((digitalRead (modePin1) == HIGH)? 1: 0) << 3;
  mode |= ((digitalRead (modePin2) == HIGH)? 1: 0) << 2;
  mode |= ((digitalRead (modePin3) == HIGH)? 1: 0) << 1;
  mode |= ((digitalRead (modePin4) == HIGH)? 1: 0) << 0;

  return mode;
}

int getCurrentMode () {
  return EEPROM.read (EEPROM_MODE_ADDRESS);
}

void setMode (int mode) {
  EEPROM.write (EEPROM_MODE_ADDRESS, mode);
}
