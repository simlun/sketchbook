#define count(array) (sizeof(array) / sizeof(*array))

int LED_PINS[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

#define ANALOG_INPUT_PIN A0
#define MIN_VALUE_BUTTON_PIN 2
#define MAX_VALUE_BUTTON_PIN 3
#define NUM_SAMPLES 200
#define SAMPLE_DELAY_MS 1
#define MAIN_LOOP_DELAY_MS 1
#define ANIMATION_DELAY_MS 50
#define CALIBRATION_MULTIPLIER 15

int minValue = 0;
int maxValue = 1023;

unsigned long sum = 0;

void setup() {
  analogReference(EXTERNAL);
  
  Serial.begin(9600);
  
  pinMode(MIN_VALUE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(MAX_VALUE_BUTTON_PIN, INPUT_PULLUP);
  
  for (int i = 0; i < count(LED_PINS); i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
}

void enableNrOfLEDs(int numberOfEnabledLEDs) {
  // Validate input
  if (numberOfEnabledLEDs < 0) {
    numberOfEnabledLEDs = 0;
  } else if (numberOfEnabledLEDs > count(LED_PINS)) {
    numberOfEnabledLEDs = count(LED_PINS);
  }
  
  // Disable all LEDs
  for (int i = 0; i < count(LED_PINS); i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
  
  // Enable the requested number of LEDs
  if (numberOfEnabledLEDs > 0) {
    for (int i = 0; i < numberOfEnabledLEDs; i++) {
      digitalWrite(LED_PINS[i], HIGH);
    }
  }
}

void animateLEDFlow() {
  // Enable all of them in sequence
  for (int i = 0; i < count(LED_PINS); i++) {
    enableNrOfLEDs(i);
    delay(ANIMATION_DELAY_MS);
  }
  
  // Disable all of them in sequence
  for (int i = 0; i < count(LED_PINS); i++) {
    enableNrOfLEDs(10 - i);
    delay(ANIMATION_DELAY_MS);
  }
}

int readAverageAnalogValue(int multiplier) {
  sum = 0;
  
  for (int sampleCount = 0; sampleCount < (NUM_SAMPLES * multiplier); sampleCount++) {
    sum += analogRead(ANALOG_INPUT_PIN);
    delay(SAMPLE_DELAY_MS);
  }

  int average = sum / (NUM_SAMPLES * multiplier);
  return average;
}

void printMinMax() {
  Serial.print("min, max = ");
  Serial.print(minValue);
  Serial.print(", ");
  Serial.println(maxValue);
}

int calculateNrOfLeds(int average) {
  int span = maxValue - minValue;
  int delta = average - minValue;
  float percentage = (float)delta / (float)span;
  
  // Hack to act steady at limits
  int offset = 1;
  if (percentage > 0.85) {
    percentage = 1.0;
  } else if (percentage < 0.15) {
    percentage = 0.0;
    offset = 0;
  }
  
  int numLeds = (percentage * (float)count(LED_PINS)) + offset;
  return numLeds;
}

void loop() {
  if (digitalRead(MIN_VALUE_BUTTON_PIN) == LOW) {
    enableNrOfLEDs(0);
    minValue = readAverageAnalogValue(CALIBRATION_MULTIPLIER);
    printMinMax();
    animateLEDFlow();
  } else if (digitalRead(MAX_VALUE_BUTTON_PIN) == LOW) {
    enableNrOfLEDs(0);
    maxValue = readAverageAnalogValue(CALIBRATION_MULTIPLIER);
    printMinMax();
    animateLEDFlow();
  } else {
    int average = readAverageAnalogValue(1);
    int numberOfEnabledLEDs = calculateNrOfLeds(average);
    enableNrOfLEDs(numberOfEnabledLEDs);
  }
  
  delay(MAIN_LOOP_DELAY_MS);
}
