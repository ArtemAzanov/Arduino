#define CLK 2
#define DIO 3

#define BUTTON_START 4
#define BUTTON_RESET 5
#define BUTTON_PLUS 6
#define BUTTON_PLUS_SEC 7
#define BUTTON_MINUS_MIN 8
#define BUTTON_MINUS_SEC 9
#define BUZZER_PIN 11

#include "GyverTM1637.h"

GyverTM1637 disp(CLK, DIO);

uint8_t results[11] = {_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, false};

int remainingSeconds = 0;
bool timerRunning = false;
unsigned long previousMillis = 0;

void setup() {
  disp.clear();
  disp.brightness(7);

  pinMode(BUTTON_START, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
  pinMode(BUTTON_PLUS, INPUT_PULLUP);
  pinMode(BUTTON_PLUS_SEC, INPUT_PULLUP);
  pinMode(BUTTON_MINUS_MIN, INPUT_PULLUP);
  pinMode(BUTTON_MINUS_SEC, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT); 

  previousMillis = millis();
}

void playAlarm() {
  for (int i = 0; i < 3; i++) {           
    tone(BUZZER_PIN, 1000, 500);         
    delay(500);                            
    delay(200);
  }
}

void loop() {


  if (digitalRead(BUTTON_START) == LOW) {
    delay(200);
    if (remainingSeconds > 0) {
      timerRunning = true;
    }
  }


  if (digitalRead(BUTTON_RESET) == LOW) {
    delay(200);
    timerRunning = false;
    remainingSeconds = 0;
    noTone(BUZZER_PIN); 
  }


  if (digitalRead(BUTTON_PLUS) == LOW) {
    delay(200);
    if (timerRunning == false) {
      remainingSeconds = remainingSeconds + 60;
      if (remainingSeconds > 3599) {
        remainingSeconds = 3599;
      }
    }
  }

  if (digitalRead(BUTTON_PLUS_SEC) == LOW) {
    delay(200);
    if (timerRunning == false) {
      remainingSeconds = remainingSeconds + 1;
      if (remainingSeconds > 3599) {
        remainingSeconds = 3599;
      }
    }
  }


  if (digitalRead(BUTTON_MINUS_MIN) == LOW) {
    delay(200);
    if (timerRunning == false) {
      remainingSeconds = remainingSeconds - 60;
      if (remainingSeconds < 0) {
        remainingSeconds = 0;
      }
    }
  }

  if (digitalRead(BUTTON_MINUS_SEC) == LOW) {
    delay(200);
    if (timerRunning == false) {
      remainingSeconds = remainingSeconds - 1;
      if (remainingSeconds < 0) {
        remainingSeconds = 0;
      }
    }
  }









  if (timerRunning == true) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      if (remainingSeconds > 0) {
        remainingSeconds = remainingSeconds - 1;
      }
      if (remainingSeconds == 0) {
        timerRunning = false;
        playAlarm();
      }
    }
  }


  int minutes = remainingSeconds / 60;
  int seconds = remainingSeconds % 60;

  int a = minutes / 10;
  int b = minutes % 10;
  int c = seconds / 10;
  int d = seconds % 10;

  disp.clear();
  disp.displayByte(results[a], results[b], results[c], results[d]);
  disp.point(true);
  delay(10);
}
