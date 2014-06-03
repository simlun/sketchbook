#define count(array) (sizeof(array) / sizeof(*array))

int LED_PINS[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

#define ANALOG_INPUT_PIN A0
#define MIN_VALUE_BUTTON_PIN 2
#define MAX_VALUE_BUTTON_PIN 3
#define NUM_SAMPLES 100
#define SAMPLE_DELAY_MS 1
#define MAIN_LOOP_DELAY_MS 10
#define ANIMATION_DELAY_MS 50

int minValue = 0;
int maxValue = 1023;

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

int readAverageAnalogValue() {
  unsigned long sum = 0;
  
  for (int sampleCount = 0; sampleCount < NUM_SAMPLES; sampleCount++) {
    sum += analogRead(ANALOG_INPUT_PIN);
    delay(SAMPLE_DELAY_MS);
  }

  int average = sum / NUM_SAMPLES;
  return average;
}

void printMinMax() {
  Serial.print("min, max = ");
  Serial.print(minValue);
  Serial.print(", ");
  Serial.println(maxValue);
  animateLEDFlow();
}

void loop() {
  int average = readAverageAnalogValue();
  Serial.print("average = ");
  Serial.println(average);
  
  if (digitalRead(MIN_VALUE_BUTTON_PIN) == LOW) {
    minValue = average;
    printMinMax();
  } else if (digitalRead(MAX_VALUE_BUTTON_PIN) == LOW) {
    maxValue = average;
    printMinMax();
  } else {
    int numberOfEnabledLEDs = 5;
    enableNrOfLEDs(numberOfEnabledLEDs);
  }
  
  delay(MAIN_LOOP_DELAY_MS);
}
