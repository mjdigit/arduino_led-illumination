
bool setupTm (const char *DateStr, const char *TimeStr, tmElements_t *tm) {
  #define NUM_MONTH 12
  int Year, Month, Day, Hour, Min, Sec;
  char MonthStr[12];
  const char *MonthTable[NUM_MONTH] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" 
  };

  if (sscanf (DateStr, "%s %d %d", MonthStr, &Day, &Year) != 3) return false;
  if (sscanf (TimeStr, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;

  for (Month = 0; Month < NUM_MONTH; Month++) {
    if (strcmp (MonthStr, MonthTable[Month]) == 0) break;
  }
  if (Month >= NUM_MONTH) return false;

  tm->Year = CalendarYrToTm(Year);
  tm->Month = Month + 1;
  tm->Day = Day;
  tm->Hour = Hour;
  tm->Minute = Min;
  tm->Second = Sec;

  return true;
}
