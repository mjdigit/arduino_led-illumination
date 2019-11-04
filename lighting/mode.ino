

SCENE_TABLE_ELEMENT sceneTableDemo[] = {
  {"12:30:00", "12:55:00", sceneRandomFade},
  {"12:55:00", "12:58:00", sceneFadeToMorning},
  {"12:58:00", "13:25:00", sceneMorning},
  {"13:25:00", "13:30:00", sceneSunset},
  {"13:30:00", "14:20:00", sceneNight},
  {"14:20:00", "14:55:00", sceneCandle},
  {"14:55:00", "14:55:05", sceneFadeToNight},
  {"14:55:00", "15:30:00", sceneNight},
};

SCENE_TABLE_ELEMENT sceneTableCandle[] = {
  {"00:00:00", "23:59:59", sceneCandle},
};

SCENE_TABLE_ELEMENT sceneTableFade[] = {
  {"00:00:00", "23:59:59", sceneRandomFade},
};

long getTimeRateByMode (int mode) {
  switch (mode) {
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
    case 10:
      *sceneTable = sceneTableCandle;
      *elements = sizeof (sceneTableCandle) / sizeof (SCENE_TABLE_ELEMENT);
      break;
    case 11:
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
