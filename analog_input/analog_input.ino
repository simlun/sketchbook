#define count(array) (sizeof(array) / sizeof(*array))

int analogInputPin = 0;
int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

#define NUM_SAMPLES 100
#define SAMPLE_DELAY_MS 1

unsigned long sum = 0;
unsigned char sampleCount = 0;
int average = 0.0;
int i = 0;
int analogTreshold = 0;

void setup() {
  analogReference(EXTERNAL);
  Serial.begin(9600);
  for (int i = 0; i < count(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  while (sampleCount < NUM_SAMPLES) {
    sum += analogRead(analogInputPin);
    sampleCount++;
    delay(SAMPLE_DELAY_MS);
  }

  average = sum / NUM_SAMPLES;
  sampleCount = 0;
  sum = 0;
  
  Serial.print("A0 average = ");
  Serial.println(average);
  
  for (i = 0; i < count(ledPins); i++) {
    digitalWrite(ledPins[i], LOW);
  }
  
  analogTreshold = (average + 2) / 128;
  for (i = 0; i < analogTreshold; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}
