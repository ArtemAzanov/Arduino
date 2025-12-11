const int RedPin = 4;
const int YellowPin = 3;
const int GreenPin = 2;

void gtr(int pin) {
  digitalWrite(pin, LOW);
  for (int i = 0; i <= 4; i++) {
    digitalWrite(pin, HIGH);
    delay(200);
    digitalWrite(pin, LOW);
    delay(200);

  }

}
void setup () {
  pinMode(RedPin, OUTPUT);
  pinMode(YellowPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);

}

void loop() {
  digitalWrite(RedPin, HIGH);
  delay(5000);
  gtr(RedPin);
  digitalWrite(YellowPin, HIGH);
  delay(2000);
  digitalWrite(YellowPin, LOW);
  digitalWrite(GreenPin, HIGH);
  delay(5000);
  gtr(GreenPin);



}
