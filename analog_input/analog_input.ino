#define count(array) (sizeof(array) / sizeof(*array))

int analogInputPin = 0;
int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
  for (int i = 0; i < count(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  int analogValue = (analogRead(analogInputPin) + 2) / 128;
  for (int i = 0; i < count(ledPins); i++) {
    digitalWrite(ledPins[i], LOW);
  }
  for (int i = 0; i < analogValue; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}
