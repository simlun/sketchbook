#include <SoftwareSerial.h>

const int RX = 10;
const int TX = 11;
SoftwareSerial mySerial(RX, TX);

const int LED = 13;

unsigned long now = 0;

void setup() {
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
  Serial.println("Hello, world?");

  mySerial.begin(9600);
  mySerial.println("Hello, my world?");
}

void printAndWait() {
  now = (millis() / 1000) % 8;
  
  Serial.println(now);
  mySerial.println(now);
  
  delay(1000);
}

void loop() {
  digitalWrite(LED, HIGH);
  printAndWait();
  digitalWrite(LED, LOW);
  printAndWait();
}
