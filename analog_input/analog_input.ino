#define count(array) (sizeof(array) / sizeof(*array))

int LED_PINS[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

#define ANALOG_INPUT_PIN A4
#define MIN_VALUE_BUTTON_PIN 2
#define MAX_VALUE_BUTTON_PIN 3

#define NUM_SAMPLES 200
#define SAMPLE_DELAY_MS 2

#define ANIMATION_DELAY_MS 50
#define CALIBRATION_MULTIPLIER 1

int minValue = 333;
int maxValue = 1023;

unsigned long sum = 0;

unsigned long now = 0;
unsigned long lastPrinted = 0;

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
  Serial.print("minTreshold=");
  Serial.print(minValue);
  Serial.print("&maxTreshold=");
  Serial.println(maxValue);
}

int calculateNrOfLeds(int average) {
  int span = maxValue - minValue;
  int delta = average - minValue;
  float percentage = (float)delta / (float)span;
  
  float offset = 1.5;
  int numLeds = (percentage * (float)count(LED_PINS)) + offset;
  return numLeds;
}

void printEvery(unsigned long interval, String message) {
  if (lastPrinted + interval < now) {
    lastPrinted = now;
    Serial.println(message);
  }
}

void loop() {
  now = millis();
  
  // Handle millis() overflow every 50 days
  if (now < lastPrinted) {
    lastPrinted = 0;
  }
  
  if (digitalRead(MIN_VALUE_BUTTON_PIN) == LOW) {
    enableNrOfLEDs(0);
    minValue = readAverageAnalogValue(CALIBRATION_MULTIPLIER);
    //printMinMax();
    animateLEDFlow();
  } else if (digitalRead(MAX_VALUE_BUTTON_PIN) == LOW) {
    enableNrOfLEDs(0);
    maxValue = readAverageAnalogValue(CALIBRATION_MULTIPLIER);
    //printMinMax();
    animateLEDFlow();
  } else {
    int average = readAverageAnalogValue(1);
    int numberOfEnabledLEDs = calculateNrOfLeds(average);
    enableNrOfLEDs(numberOfEnabledLEDs);
    printEvery(1000, String("minTreshold=") + String(minValue)
                   + String("&")
                   + String("maxTreshold=") + String(maxValue)
                   + String("&")
                   + String("numberOfEnabledLEDs=")  + String(numberOfEnabledLEDs)
                   + String("&") 
                   + String("analogValue=")  + String(average));
  }
}
