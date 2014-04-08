const int BUTTON = 2;
const int LED =  13;

void pullUp(int pin) {
  digitalWrite(pin, HIGH);
}

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  pullUp(BUTTON);  
}

void loop() {
  boolean buttonPressed = digitalRead(BUTTON) == LOW;
  if (buttonPressed) {     
    digitalWrite(LED, HIGH);  
  } else {
    digitalWrite(LED, LOW); 
  }
}
