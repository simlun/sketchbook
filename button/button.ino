const int BUTTON = 2;
const int LED =  13;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);     
}

void loop() {
  int buttonState = digitalRead(BUTTON);
  if (buttonState == LOW) {     
    digitalWrite(LED, HIGH);  
  } else {
    digitalWrite(LED, LOW); 
  }
}
