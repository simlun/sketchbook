#define count(array) (sizeof(array) / sizeof(*array))

const int DELAY = 100; // ms
int ledPins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };

void setup() {
  for (int i = 0; i < count(ledPins); i++)  {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < count(ledPins); i++) { 
    digitalWrite(ledPins[i], HIGH);
    delay(DELAY);
    digitalWrite(ledPins[i], LOW);
  }

  for (int i = count(ledPins) - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(DELAY);
    digitalWrite(ledPins[i], LOW);
  }
}
