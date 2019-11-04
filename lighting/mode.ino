

SCENE_TABLE_ELEMENT sceneTableDemo[] = {
  {"12:01:00", "12:02:00", sceneRandomFade},
  {"12:02:00", "12:02:05", sceneFadeToNight},
  {"12:02:00", "12:03:00", sceneNight},
  {"12:03:00", "12:04:00", sceneFadeToMorning},
  {"12:04:00", "12:05:00", sceneMorning},
  {"12:05:00", "12:06:00", sceneFadeToNight},
  {"12:06:00", "12:07:00", sceneNight},
  {"12:07:00", "12:08:00", sceneCandle},
  {"12:08:00", "12:08:05", sceneFadeToNight},
  {"12:08:00", "12:09:00", sceneNight},
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
