/*
  Lighting
*/

const int analogRedPin   = A1;
const int analogGreenPin = A2;
const int analogBluePin  = A3;

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

static void controlLeds (int redValue, int greenValue, int blueValue) {
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
  controlLeds(rgbValue[count].red, rgbValue[count].green, rgbValue[count].blue);
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  controlLeds(0, 0, 0);
  delay(1000);                       // wait for a second

  count++;
  if (count >= maxcount) {
    count = 0;
  }
}
