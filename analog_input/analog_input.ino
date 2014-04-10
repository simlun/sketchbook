int LED_Pins[] = {2, 3, 4, 5, 6, 7, 8, 9};

int tmp;

int Old_LED = 0;

int PotValue = 0;

void setup() {
  for (tmp = 0; tmp < 8; tmp++) {
    pinMode(LED_Pins[tmp], OUTPUT);
  }
}

void loop() {
  PotValue = (analogRead(0) + 2) / 128;
  for (tmp = 0; tmp < 8; tmp++) {
    digitalWrite(LED_Pins[tmp], LOW);
  }
  for (tmp = 0; tmp < PotValue; tmp++) {
    digitalWrite(LED_Pins[tmp], HIGH);
  }
}
