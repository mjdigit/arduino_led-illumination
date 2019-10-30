#include "lighting_internal.h"

void debugPrintTime (tmElements_t tm, boolean linebreak) {
  DEBUG ((tmYearToCalendar (tm.Year)));
  DEBUG (("/"));
  DEBUG ((tm.Month));
  DEBUG (("/"));
  DEBUG ((tm.Day));
  DEBUG ((" "));
  DEBUG ((tm.Hour, DEC));
  DEBUG ((':'));
  DEBUG ((tm.Minute,DEC));
  DEBUG ((':'));
  DEBUG ((tm.Second,DEC));
  if (linebreak) {
      DEBUGLN ((""));
  }
}

void debugPrintRgb (struct rgb rgbValue, boolean linebreak) {
  DEBUG (('('));
  DEBUG ((rgbValue.red, DEC));
  DEBUG ((','));
  DEBUG ((rgbValue.green, DEC));
  DEBUG ((','));
  DEBUG ((rgbValue.blue, DEC));
  DEBUG ((')'));
  if (linebreak) {
      DEBUGLN ((""));
  }
}
