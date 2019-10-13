/*
  Lighting
*/

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
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  static int count = 0;
  int maxcount = sizeof(rgbValue)/sizeof(rgbValue[0]);
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  for (int i = 0; i <= 100; i+=4) {
    controlLeds(rgbValue[count].red, rgbValue[count].green, rgbValue[count].blue, i);
    delay (100);
  }
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  controlLeds(0, 0, 0, 100);
  delay(1000);                       // wait for a second

  count++;
  if (count >= maxcount) {
    count = 0;
  }
}
