
#define SCENE_TABLE_COMMON_FIRST_HALF \
  {"12:30:00", "12:55:00", sceneRandomFade},   \
  {"12:55:00", "12:58:00", sceneFadeToMorning},\
  {"12:58:00", "13:25:00", sceneMorning},      \
  {"13:25:00", "13:30:00", sceneSunset},

#define SCENE_TABLE_COMMON_LAST_HALF \
  {"14:20:00", "14:55:00", sceneCandle},      \
  {"14:55:00", "14:55:05", sceneFadeToNight}, \
  {"14:55:00", "15:30:00", sceneNight},

SCENE_TABLE_ELEMENT sceneTable1[] = {
  SCENE_TABLE_COMMON_FIRST_HALF
  {"13:30:00", "14:24:30", sceneNight},
  SCENE_TABLE_COMMON_LAST_HALF
};
SCENE_TABLE_ELEMENT sceneTable2[] = {
  SCENE_TABLE_COMMON_FIRST_HALF
  {"13:30:00", "14:24:00", sceneNight},
  SCENE_TABLE_COMMON_LAST_HALF
};
SCENE_TABLE_ELEMENT sceneTable3[] = {
  SCENE_TABLE_COMMON_FIRST_HALF
  {"13:30:00", "14:21:30", sceneNight},
  SCENE_TABLE_COMMON_LAST_HALF
};
SCENE_TABLE_ELEMENT sceneTable4[] = {
  SCENE_TABLE_COMMON_FIRST_HALF
  {"13:30:00", "14:22:30", sceneNight},
  SCENE_TABLE_COMMON_LAST_HALF
};
SCENE_TABLE_ELEMENT sceneTable5[] = {
  SCENE_TABLE_COMMON_FIRST_HALF
  {"13:30:00", "14:23:00", sceneNight},
  SCENE_TABLE_COMMON_LAST_HALF
};
SCENE_TABLE_ELEMENT sceneTable6[] = {
  SCENE_TABLE_COMMON_FIRST_HALF
  {"13:30:00", "14:20:30", sceneNight},
  SCENE_TABLE_COMMON_LAST_HALF
};
SCENE_TABLE_ELEMENT sceneTable7[] = {
  SCENE_TABLE_COMMON_FIRST_HALF
  {"13:30:00", "14:23:30", sceneNight},
  SCENE_TABLE_COMMON_LAST_HALF
};
SCENE_TABLE_ELEMENT sceneTable8[] = {
  SCENE_TABLE_COMMON_FIRST_HALF
  {"13:30:00", "14:20:00", sceneNight},
  SCENE_TABLE_COMMON_LAST_HALF
};
SCENE_TABLE_ELEMENT sceneTable9[] = {
  SCENE_TABLE_COMMON_FIRST_HALF
  {"13:30:00", "14:21:00", sceneNight},
  SCENE_TABLE_COMMON_LAST_HALF
};

SCENE_TABLE_ELEMENT sceneTableDemo[] = {
  SCENE_TABLE_COMMON_FIRST_HALF
  {"13:30:00", "14:20:00", sceneNight},
  SCENE_TABLE_COMMON_LAST_HALF
};

SCENE_TABLE_ELEMENT sceneTableCandle[] = {
  {"00:00:00", "23:59:59", sceneCandle},
};

SCENE_TABLE_ELEMENT sceneTableFade[] = {
  {"00:00:00", "23:59:59", sceneRandomFade},
};

long getTimeRateByMode (int mode) {
  switch (mode) {
    case 10: return 16;
    case 11: return 4;
    case 13: return 16;
    case 14: return 4;
    default: return 1;
  }
}

boolean getSceneTableByMode (
  int mode,
  SCENE_TABLE_ELEMENT **sceneTable,
  int *elements
  )
{
  switch (mode) {
    case 0:
      *sceneTable = sceneTable1;
      *elements = sizeof (sceneTable1) / sizeof (SCENE_TABLE_ELEMENT);
      break;
    case 1:
      *sceneTable = sceneTable2;
      *elements = sizeof (sceneTable2) / sizeof (SCENE_TABLE_ELEMENT);
      break;
    case 2:
      *sceneTable = sceneTable3;
      *elements = sizeof (sceneTable3) / sizeof (SCENE_TABLE_ELEMENT);
      break;
    case 3:
      *sceneTable = sceneTable4;
      *elements = sizeof (sceneTable4) / sizeof (SCENE_TABLE_ELEMENT);
      break;
    case 4:
      *sceneTable = sceneTable5;
      *elements = sizeof (sceneTable5) / sizeof (SCENE_TABLE_ELEMENT);
      break;
    case 5:
      *sceneTable = sceneTable6;
      *elements = sizeof (sceneTable6) / sizeof (SCENE_TABLE_ELEMENT);
      break;
    case 6:
      *sceneTable = sceneTable7;
      *elements = sizeof (sceneTable7) / sizeof (SCENE_TABLE_ELEMENT);
      break;
    case 7:
      *sceneTable = sceneTable8;
      *elements = sizeof (sceneTable8) / sizeof (SCENE_TABLE_ELEMENT);
      break;
    case 8:
      *sceneTable = sceneTable9;
      *elements = sizeof (sceneTable9) / sizeof (SCENE_TABLE_ELEMENT);
      break;
    case 9:
      *sceneTable = sceneTableCandle;
      *elements = sizeof (sceneTableCandle) / sizeof (SCENE_TABLE_ELEMENT);
      break;
    case 10:
    case 11:
    case 12:
      *sceneTable = sceneTableFade;
      *elements = sizeof (sceneTableFade) / sizeof (SCENE_TABLE_ELEMENT);
      break;
    case 13:
    case 14:
    case 15:
      *sceneTable = sceneTableDemo;
      *elements = sizeof (sceneTableDemo) / sizeof (SCENE_TABLE_ELEMENT);
      break;
    default:
      return false;
  }

  return true;
}
