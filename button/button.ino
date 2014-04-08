const int BUTTON = 2;
const int LED =  13;

boolean ledState = false;

void pullUp(int pin) {
  digitalWrite(pin, HIGH);
}

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  pullUp(BUTTON);  
}

boolean isButtonPressed() {
  return digitalRead(BUTTON) == LOW;
}

void toggle(int pin, boolean* state) {
  *state = !(*state);
  digitalWrite(pin, *state);
}

void debounce() {
  delay(150);
}

void waitForButtonRelease() {
  while (isButtonPressed()) {
    // Wait
  }
}

void loop() {
  if (isButtonPressed()) {
    toggle(LED, &ledState);
    debounce();
    waitForButtonRelease();
  }
}
